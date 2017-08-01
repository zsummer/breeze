Welcome to the breeze wiki!
## breeze简述  
[![Build Status](https://travis-ci.org/zsummer/breeze.svg?branch=master)](https://travis-ci.org/zsummer/breeze)  
breeze是一个C++的轻量级的分布式服务器引擎, 架构思想为一切皆service.   
breeze is a lightweight, fast, distributed server engine. greatly inspired by docker, bigworld and starwing/loki .  the thoughts is " all is service ".   
  
  
## 特点:    
  
- **实现docker和service的核心代码约2000行, 简洁朴素**.  
  
- 使用C++11标准, 充分发挥shared_ptr,functional, lambda应有的作用, 结合C++异常和模板,**在满足高性能与可靠性的前提下把易用性做到了接近lua这样的脚本语言的水平**.  
  
- **对开发者透明的分布式方案**, 对业务开发者而言并不需要关心分布式本身, 但通过配置可以很灵活的调整服务器负载. (架构思想上可以参考skynet,bigworld,gce,nf等服务器引擎).   
  
- 网络库使用zsummerX, **支持全平台**,win/linux/mac/android/ios, 可以直接嵌入到移动平台的客户端中, 打通移动客户端到服务端的通讯, **zsummerX的特性该服务器引擎全部支持**(本来就是为了breeze写的).  
  
- 协议序列化采用IDL工具生成的方案, 采用的开源库为proto4z. 通过xml配置文件生成**原生的C++,lua,C#数据结构代码**,  支持二进制协议和http协议, 并可以**生成操作mysql的序列化/反序列化代码**. 配合zsummerX可以很方便的在上述语言中混合通讯.  
  
- 日志库使用log4z.  
  
- breeze的单组服务器设计容量在实际项目中, **轻度游戏10~100万同时在线**, 有大量交互的模块和丰富的外围系统的**中度/重度游戏1~10万+在线**(瓶颈在于交互模块的单例service的负载能力, 通过对业务的把握尽量拆分更多的单例service, 转移负载到负载均衡的动态service上可以有效提升和突破这个上限), 数据库注册容量<=1000万(大于这个容量要考虑对数据库进行sharding, 垂直sharding直接根据业务进行分割, 添加更多的数据库service类型和配置即可, 而单表大于1000万需要水平sharding, 这个对dbhelper进行扩展后可以对业务层透明,但暂无需求 并没有去实现. , 另外需要注意减小不需要装载的service的驻留资源, 超规模使用资源不好挥霍的.).  
  




## 核心模块介绍   
### docker:

---  

docker是用来托管service的专用vm:  
> 负责底层的网络通讯,多节点的网络拓扑构建, docker的多节点对上层透明化.  
> docker维护service和镜像service的创建,装载,卸载,销毁等管理操作.  
> service的负载均衡,容灾等处理.  
> 上层只需关注docker所装载的service.   
  
docker的资源消耗:  
> docker集群的socket数量开销= (docker个数的平方)*2  
> docker集群的总端口占用数量开销=docker个数的平方  

  
### service:  
--- 
service是breeze引擎的核心结构, 通过包装对docker接口的再次包装, 实现 "all is service" 这一思想.  
> 通过简单的toService即可把数据发往另外一个service而不需要关心对方装载在本地还是另外一个docker上.  
> 通过sloting方法可以注册当前service可接收的消息类型和对应的处理方法
> toService可以携带本地回调方法, 对方收到消息后通过backToService返回的消息可以直接在回调中处理. 
> 创建一个service只需要集成该基类, 填写对应的onLoad onUnload等方法即可.  
> service的依赖关系通过简单的定义即可, docker会自动组织为正确的装载/卸载依赖拓扑图并据此进行装载和卸载等操作.  
  
  
## 已实现的部分业务模块 (核心框架部分)  
### 登录流程  
--- 
已实现多角色账户的登录,创建用户,装载用户service, 切换用户客户端, 踢掉客户端, 卸载用户service, 离线消息, webservice, dbservice等.  

### DBService  
直接操作数据库的的service, 每个db一个线程, 每个db对应一个service type.  
所有运行中的数据库操作, info,log等 都需要走该service中专.  
配合proto4z的mysql序列化方案, 可以一个调用实现增删改查,  而通过ModuleData的模板类, 则实现按照业务模块一键从数据库中load/create/update/insert等同步.  

### AvatarMgrService  
--- 
玩家中心service, 用于玩家service的创建,装载,客户端认证通讯关联等.  
也用于玩家管理,特别是离线玩家的管理(在线玩家可以直接server对service进行交互). 
  
### WebService  
---  
提供web 服务器/客户端相关服务. 
通过配置可以在该service中直接处理来自web客户端的请求, 并可以处理来自内部的消息然后向外部发起web请求,并回调给来源(服务器gm后台实时查询管理接口, 向外部发起的渠道认证等需求均可满足).  
两者均可做到动态负载均衡.  
  
### OfflineService  
---  
离线管理服务, 对于不在线的用户或者其他没有装载的非单例service, 均可以把本来要交给这些service已装载情况下要处理的消息通过该服务驻留到数据库和内存, 在这些service装载后该离线service会自动推送.  使用方法只是把toService中的Service Type转向到该离线管理服务即可.  
 
### DBDict  
该字典类不属于docker和service, 是一个全局可直接访问的字典集合, 存储服务器引擎所有业务配置(字典)  .

### STWorldMgr  
场景服务, 异构模块.  
该服务为一个小型实时MOBA服务器.  包括场景管理服务和场景服务集群  
目前已经实现作为一个moba游戏的核心框架和模块.   
该服务器的实现初衷为复刻一个小型war3服务器,通过玩法定制实现WAR的各种自定义地图模式.    
对应的客户端项目为breeze_unity3d_client    


## 后续版本计划  
  对service和现有的utls公共小工具添加lua胶水代码, 并实现一套lua版的ModuleData来同步数据库, 这样就引擎的使用者可以自由决策逻辑层用lua还是C++ .   
  该计划的具体实现方案已有, 以及相应的性能,易用性和稳定性也均有可控的预期实现.  
  需求暂不强烈, 暂缓该计划的执行.  

## About The Author  
**Author**: YaweiZhang  
**Mail**: yawei.zhang@foxmail.com  
**GitHub**: https://github.com/zsummer  
  
  
## Friend Open Source  
**NoahGameFrame**  
-  Author: ketoo  
-  GitHub: https://github.com/ketoo/NoahGameFrame  
-  Description: A fast, scalable, distributed game server framework for C++, include actor library, network library,can be used as a real time multiplayer game engine ( MMO RPG ), which plan to support C#/Python/Lua script, and support Unity3d, Cocos2dx, FlashAir client access.  
   
**gce**  
-  Author: nousxiong  
-  GitHub: https://github.com/nousxiong/gce  
-  Description: The Game Communication Environment (GCE) is an actor model framework for online game development.  

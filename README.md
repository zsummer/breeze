Welcome to the breeze wiki!
## breeze简述  
[![Build Status](https://travis-ci.org/zsummer/breeze.svg?branch=master)](https://travis-ci.org/zsummer/breeze)  
breeze是一个C++的轻量级服务器框架, 适合端游/页游/手游/棋牌/IM的分布式服务器端.  
  
## 主要依赖模块  
DB使用mysql,通过proto4z根据原生数据结构生成对应的SQL模板并通过接口动态生成直接可以交给mysql服务执行的最终的增删改查SQL语句.    
网络模块部分使用zsummerX.  
协议解析使用proto4z.  
日志模块使用log4z.

  
## 特点:    
  
总代码量很小 非常轻量级, 可以快速上手使用.  
使用C++11标准, 在满足高性能的同时满足快速开发要求.  
天然的分布式方案,(架构思想上可以参考skynet,bigworld,gce等), 融合了docker的集装箱思想和bigworld的一切皆实体思想.   
网络库使用zsummerX, 可以直接嵌入到移动平台的客户端中, 打通移动客户端到服务端的通讯.  
协议为原生的二进制数据流, 支持lua客户端的使用, 性能非常高(相对于json等方案带来的是更小的流量,更快的响应速度).  
支持HTTP协议, 可以方便的接入第三方的认证充值平台.  
数据采用RC4流式加密, 最小的性能损失和更可靠的加密效果.  

#### cluster版本当前开发进度  

 
- [x] docker起服物理拓扑连接构建  
- [x] docker起服service依赖机制实现,拓扑构建实现.  
- [x] docker起服间,正常运作状态,关服间的service与service, service与docker间的通讯实现.  
- [x] service间rpc通讯实现,支持回调,并自动清理超时等待的call. 
- [x] module机制的实现并无缝集成给service.  
- [x] client==>ServiceUserMgr(用户中心service)==>动态构建ServiceUser ==>回写数据库并卸载==>通知给客户端 用户登录,创角,通讯,离线后一段时间后回写数据库并卸载ServiceUser.  
- [x] service卸载机制实现, 按照依赖顺序反向卸载service, service卸载需要所有module卸载完毕.    
- [x] docker安全关停流程  
- [x] 压测脚本实现,实现一定数量的机器人自动登录,创角,互相通讯,然后仿业务pingpong.  目前测试QPS单节点10K QPS的性能, 未经优化.    
- [x] 通过配置构建10个以上的docker集群, 并进行合理的service划分,然后压测.  
- [x] 鲁棒性更强的负载均衡,非关键service所属的docker宕机后可以保证关键业务的正常运作,并通过在线重启快速恢复服务.  
- [x] ServiceMinitorMgr 监控和统计服务  
- [x] ServiceOfflineMgr 离线消息管理器实现, 需要记录到数据库, 玩家上线后拉取离线消息或者离线奖励等.  
- [x] ServiceWebAgent http协议的对外web server接口实现, http协议连接外部网站并获得数据的web client实现.  
- [ ] ItemModule实现, 实现道具背包系统.  
- [ ] MissionModule实现  
- [ ] 整体性review代码,优化实现.  

## 添加一个service  
1.  在defined.h中添加service类型和类型名字.  
2.  在config.lua配置文件中给新加的service配置一个docker来装载该服务.  
2.  添加一个类并继承Service. 可以直接copy shellService然后修改.  
3.  在docker.cpp中include新添加的文件并在createService中写一行实例化代码.  

## About The Author  
Auther: YaweiZhang  
Mail: yawei.zhang@foxmail.com  
GitHub: https://github.com/zsummer  
  
## Friend Open Source  
**NoahGameFrame**  
-  Auther: ketoo  
-  GitHub: https://github.com/ketoo/NoahGameFrame  
-  Description: A fast, scalable, distributed game server framework for C++, include actor library, network library,can be used as a real time multiplayer game engine ( MMO RPG ), which plan to support C#/Python/Lua script, and support Unity3d, Cocos2dx, FlashAir client access.  
   
**gce**  
-  Auther: nousxiong  
-  GitHub: https://github.com/nousxiong/gce  
-  Description: The Game Communication Environment (GCE) is an actor model framework for online game development.  

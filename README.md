Welcome to the breeze wiki!
#breeze简述  
[![Build Status](https://travis-ci.org/zsummer/breeze.svg?branch=master)](https://travis-ci.org/zsummer/breeze)  
breeze是一个C++的轻量级服务器框架, 适合端游/页游/手游/棋牌/IM的分布式服务器端.  
  
#主要依赖模块  
DB使用mysql,   
kv-cache使用redis,   
网络模块部分使用zsummerX: 支持协议加密, 支持TCP/UDP/HTTP协议, 支持断点重传, 支持windows/linux/iOS/android.    
协议解析使用proto4z: 支持C++/lua/C#  

  
#特点:    
  
总代码量很小 非常轻量级, 可以快速上手使用.  
使用C++11标准, 在满足高性能的同时满足快速开发要求.  
支持分布式的扩展, 使用预留的扩展方案可以快速构建起大型的分布式服务器端.  
网络库使用zsummerX, 可以直接嵌入到移动平台的客户端中, 打通移动客户端到服务端的通讯.  
协议为原生的二进制数据流, 支持lua客户端的使用, 性能非常高(相对于json等方案带来的是更小的流量,更快的响应速度).  
支持HTTP协议, 可以方便的接入第三方的认证充值平台.  
数据采用RC4流式加密, 最小的性能损失和更可靠的加密效果.  

#### cluster版本开发进度  

- [x] docker网络通讯实现  
- [x] docker起服物理拓扑连接构建  
- [x] docker起服service初始化依赖关系  
- [x] docker起服service拓扑构建
- [x] docker间通讯  
- [x] service间通讯  
- [x] service间rpc通讯,支持回调,并自动清理超时等待的call.  
- [x] service卸载机制实现  
- [x] service卸载流程  
- [x] docker安全关停流程  
- [x] module机制的实现并无缝集成给service.  
- [x] client==>ServiceUserMgr(用户中心service)==>动态构建ServiceUser ==>回写数据库并卸载==>通知给客户端 用户登录,创角,通讯,离线后一段时间后回写数据库并卸载ServiceUser.  
- [x] 压测脚本实现,实现一定数量的机器人自动登录,创角,互相通讯,然后仿业务pingpong.  目前测试QPS单节点10K QPS的性能, 未经优化.    
- [x] 通过配置构建10个以上的docker集群, 并进行合理的service划分,然后压测.  
- [x] 鲁棒性更强的负载均衡,非关键service所属的docker宕机后可以保证关键业务的正常运作,并通过在线重启快速恢复服务.  
- [ ] ServiceOfflineMgr 离线消息管理器实现, 需要记录到数据库, 玩家上线后拉取离线消息或者离线奖励等.  
- [ ] ServiceWebAgent http协议的对外接口实现, 可能需要配置文件中有对应配置.  
- [ ] ItemModule实现, 实现道具背包系统.  
MissionModule实现  
- [ ] 整体性review代码,优化实现.  


#About The Author  
Auther: YaweiZhang  
Mail: yawei.zhang@foxmail.com  
GitHub: https://github.com/zsummer  
  

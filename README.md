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

#About The Author  
Auther: YaweiZhang  
Mail: yawei_zhang@foxmail.com  
GitHub: https://github.com/zsummer  
  

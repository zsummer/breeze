Welcome to the mini-breeze wiki!
#mini-breeze简述  
mini-breeze 是breeze的一个分支, breeze是一个C++的轻量级分布式跨平台的服务器框架, 适合端游/页游/手游/棋牌/IM的分布式服务器端.  
  
breeze这套服务器框架暂时不再更新, 有三个原因:  
一点是因为框架本身没有多少逻辑, 框架已经做好并经过测试, 在没有逻辑业务填充的情况下 不需要继续有太多的维护.  
另外一点原因是本身为星形组件式的分布架构, 在高并发的应用服务器领域更为合适, 在轻量级的手游领域是存在一些过度设计的. 
第三点就是 数据落地最初采用的mongodb, 初衷是在大部分KV数据结构的读写中, 性能优势和写业务逻辑的效率都会大幅度提升,  但mongodb的cxx driver和期望差距比较大,  实际上很多情景下性能会退化为mysql级别, 而接口对json数据流的操作与实现都非常ugly 导致用起来没那么舒服, 加上本身代码写的很臃肿, 然后还要依赖庞大的boost库, 编译起来也挺操蛋的,   使用过程中一直有强烈的欲望去重构它,但自己精力和时间有限, 正所谓是鸡肋 弃之可惜 食之无味.  

最终决定放弃mongodb的使用, 转而采用更为稳妥和经典的mysql+KV-cache 这种方案,  而新的redis在支持的数据结构上更胜古老的memcahced, 特别是做排行榜这种业务实现的时候 非常省心.  

因此最终从breeze中branch了一个分支, 为了在前期能快速迭代打磨, 删除掉了分布式架构中其他的节点, 暂时以单节点服务端和单测试客户端的形式推进, 在后续, mini-breeze的所有成果讲回归至breeze,  这样就存在一个单节点可扩充的分布式方案和一个已经实现好的多节点分布式服务器同时存在, 根据项目本身的量级选取不同的框架去使用.  
  

mini-breeze 的server端使用mysql作为数据落地方案, redis为kv-cache方案,  网络模块使用zsummerX, 可以直接把zsummerX嵌入到手机客户端中, 打通了从客户端到服务端的所有通讯工作.   
zsummerX配合proto4z, 支持iOS和android, 可以很方便的嵌入到cocos2dx或者android与iOS的原生APP中,
依赖三方库为 boost, mongodb, lua, log4z, proto4z zsummerX, 其中boost的使用原因在于mongodb-cxx-driver依赖boost 如果换mysqlclient 则可完全脱离boost.  
  
#特点:    
  
总代码量很小 非常轻量级, 可以快速上手使用.  
使用C++11标准, 在满足高性能的同时满足快速开发要求.  
支持分布式的扩展, 使用预留的扩展方案可以快速构建起大型的分布式服务器端.  
网络库使用zsummerX, 可以直接嵌入到移动平台的客户端中(U3D除外), 打通移动客户端到服务端的通讯.  
协议为原生的二进制数据流, 支持lua客户端的使用, 性能非常高(相对于json等方案带来的是更小的流量,更快的响应速度).  
支持HTTP协议, 可以方便的接入第三方的认证充值平台.  
数据采用RC4流式加密, 最小的性能损失和更可靠的加密效果.  

#About The Author  
Auther: YaweiZhang  
Mail: yawei_zhang@foxmail.com  
GitHub: https://github.com/zsummer  
  

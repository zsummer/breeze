 
Proto4z.register(40000,"ClusterPulse") 
Proto4z.ClusterPulse = {} --集群脉冲 
Proto4z.ClusterPulse.__getID = 40000 
Proto4z.ClusterPulse.__getName = "ClusterPulse" 
 
Proto4z.register(40004,"ClusterServiceCreate") 
Proto4z.ClusterServiceCreate = {} --创建并初始化一个service 
Proto4z.ClusterServiceCreate.__getID = 40004 
Proto4z.ClusterServiceCreate.__getName = "ClusterServiceCreate" 
Proto4z.ClusterServiceCreate[1] = {name="serviceType", type="ui16" }  
Proto4z.ClusterServiceCreate[2] = {name="serviceID", type="ui64" }  
Proto4z.ClusterServiceCreate[3] = {name="clusterID", type="ui32" }  
 
Proto4z.register(40006,"ClusterServiceCreateNotice") 
Proto4z.ClusterServiceCreateNotice = {} --服务创建好并初始化成功,广播给所有docker 
Proto4z.ClusterServiceCreateNotice.__getID = 40006 
Proto4z.ClusterServiceCreateNotice.__getName = "ClusterServiceCreateNotice" 
Proto4z.ClusterServiceCreateNotice[1] = {name="serviceType", type="ui16" }  
Proto4z.ClusterServiceCreateNotice[2] = {name="serviceID", type="ui64" }  
Proto4z.ClusterServiceCreateNotice[3] = {name="clusterID", type="ui32" }  
 
Proto4z.register(40007,"ClusterServiceDestroy") 
Proto4z.ClusterServiceDestroy = {} --销毁一个Service 
Proto4z.ClusterServiceDestroy.__getID = 40007 
Proto4z.ClusterServiceDestroy.__getName = "ClusterServiceDestroy" 
Proto4z.ClusterServiceDestroy[1] = {name="serviceType", type="ui16" }  
Proto4z.ClusterServiceDestroy[2] = {name="serviceID", type="ui64" }  
Proto4z.ClusterServiceDestroy[3] = {name="clusterID", type="ui32" }  
 
Proto4z.register(40008,"ClusterServiceDestroyNotice") 
Proto4z.ClusterServiceDestroyNotice = {} --已卸载并完成销毁,广播给所有docker 
Proto4z.ClusterServiceDestroyNotice.__getID = 40008 
Proto4z.ClusterServiceDestroyNotice.__getName = "ClusterServiceDestroyNotice" 
Proto4z.ClusterServiceDestroyNotice[1] = {name="serviceType", type="ui16" }  
Proto4z.ClusterServiceDestroyNotice[2] = {name="serviceID", type="ui64" }  
Proto4z.ClusterServiceDestroyNotice[3] = {name="clusterID", type="ui32" }  
 
Proto4z.register(40002,"ClusterShellForward") 
Proto4z.ClusterShellForward = {} --壳子转发 
Proto4z.ClusterShellForward.__getID = 40002 
Proto4z.ClusterShellForward.__getName = "ClusterShellForward" 
 
Proto4z.register(40003,"ClusterClientForward") 
Proto4z.ClusterClientForward = {} --client转发 
Proto4z.ClusterClientForward.__getID = 40003 
Proto4z.ClusterClientForward.__getName = "ClusterClientForward" 

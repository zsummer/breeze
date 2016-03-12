 
Proto4z.register(40000,"ClusterPulse") 
Proto4z.ClusterPulse = {} --集群脉冲 
Proto4z.ClusterPulse.__getID = 40000 
Proto4z.ClusterPulse.__getName = "ClusterPulse" 
 
Proto4z.register(40001,"ClusterServiceInited") 
Proto4z.ClusterServiceInited = {} --服务初始化成功 
Proto4z.ClusterServiceInited.__getID = 40001 
Proto4z.ClusterServiceInited.__getName = "ClusterServiceInited" 
Proto4z.ClusterServiceInited[1] = {name="serviceType", type="ui16" }  
Proto4z.ClusterServiceInited[2] = {name="serviceID", type="ui64" }  
 
Proto4z.register(40003,"ClusterShellForward") 
Proto4z.ClusterShellForward = {} --壳子转发 
Proto4z.ClusterShellForward.__getID = 40003 
Proto4z.ClusterShellForward.__getName = "ClusterShellForward" 
 
Proto4z.register(40004,"ClusterShellBack") 
Proto4z.ClusterShellBack = {} --壳子请求 
Proto4z.ClusterShellBack.__getID = 40004 
Proto4z.ClusterShellBack.__getName = "ClusterShellBack" 

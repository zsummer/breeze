 
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
 
Proto4z.register(40002,"ClusterShellForward") 
Proto4z.ClusterShellForward = {} --壳子转发 
Proto4z.ClusterShellForward.__getID = 40002 
Proto4z.ClusterShellForward.__getName = "ClusterShellForward" 
 
Proto4z.register(40003,"ClusterClientForward") 
Proto4z.ClusterClientForward = {} --client转发 
Proto4z.ClusterClientForward.__getID = 40003 
Proto4z.ClusterClientForward.__getName = "ClusterClientForward" 

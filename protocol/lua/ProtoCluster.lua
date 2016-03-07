 
Proto4z.register(50000,"ClusterPulse") 
Proto4z.ClusterPulse = {} --集群脉冲 
Proto4z.ClusterPulse.__getID = 50000 
Proto4z.ClusterPulse.__getName = "ClusterPulse" 
 
Proto4z.register(50001,"ClusterServiceInited") 
Proto4z.ClusterServiceInited = {} --服务初始化成功 
Proto4z.ClusterServiceInited.__getID = 50001 
Proto4z.ClusterServiceInited.__getName = "ClusterServiceInited" 
Proto4z.ClusterServiceInited[1] = {name="serviceType", type="ui16" }  
Proto4z.ClusterServiceInited[2] = {name="serviceID", type="ui64" }  

 
Proto4z.register(40000,"ClusterPulse") 
Proto4z.ClusterPulse = {} --集群脉冲 
Proto4z.ClusterPulse.__getID = 40000 
Proto4z.ClusterPulse.__getName = "ClusterPulse" 
 
Proto4z.register(40013,"CreateServiceInDocker") 
Proto4z.CreateServiceInDocker = {} --创建并初始化一个service 
Proto4z.CreateServiceInDocker.__getID = 40013 
Proto4z.CreateServiceInDocker.__getName = "CreateServiceInDocker" 
Proto4z.CreateServiceInDocker[1] = {name="serviceType", type="ui16" }  
Proto4z.CreateServiceInDocker[2] = {name="serviceID", type="ui64" }  
Proto4z.CreateServiceInDocker[3] = {name="clusterID", type="ui32" }  
 
Proto4z.register(40010,"CreateServiceNotice") 
Proto4z.CreateServiceNotice = {} --服务创建好并初始化成功,广播给所有docker 
Proto4z.CreateServiceNotice.__getID = 40010 
Proto4z.CreateServiceNotice.__getName = "CreateServiceNotice" 
Proto4z.CreateServiceNotice[1] = {name="serviceType", type="ui16" }  
Proto4z.CreateServiceNotice[2] = {name="serviceID", type="ui64" }  
Proto4z.CreateServiceNotice[3] = {name="clusterID", type="ui32" }  
 
Proto4z.register(40014,"DestroyServiceInDocker") 
Proto4z.DestroyServiceInDocker = {} --销毁一个Service 
Proto4z.DestroyServiceInDocker.__getID = 40014 
Proto4z.DestroyServiceInDocker.__getName = "DestroyServiceInDocker" 
Proto4z.DestroyServiceInDocker[1] = {name="serviceType", type="ui16" }  
Proto4z.DestroyServiceInDocker[2] = {name="serviceID", type="ui64" }  
 
Proto4z.register(40012,"DestroyServiceNotice") 
Proto4z.DestroyServiceNotice = {} --已卸载并完成销毁,广播给所有docker 
Proto4z.DestroyServiceNotice.__getID = 40012 
Proto4z.DestroyServiceNotice.__getName = "DestroyServiceNotice" 
Proto4z.DestroyServiceNotice[1] = {name="serviceType", type="ui16" }  
Proto4z.DestroyServiceNotice[2] = {name="serviceID", type="ui64" }  
 
Proto4z.register(40002,"ClusterShellForward") 
Proto4z.ClusterShellForward = {} --壳子转发 
Proto4z.ClusterShellForward.__getID = 40002 
Proto4z.ClusterShellForward.__getName = "ClusterShellForward" 
 
Proto4z.register(40003,"ClusterClientForward") 
Proto4z.ClusterClientForward = {} --client转发 
Proto4z.ClusterClientForward.__getID = 40003 
Proto4z.ClusterClientForward.__getName = "ClusterClientForward" 

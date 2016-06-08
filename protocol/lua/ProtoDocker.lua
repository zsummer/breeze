 
Proto4z.register(2000,"DockerPulse") 
Proto4z.DockerPulse = {} --集群脉冲 
Proto4z.DockerPulse.__getID = 2000 
Proto4z.DockerPulse.__getName = "DockerPulse" 
 
Proto4z.register(2014,"LoadServiceInDocker") 
Proto4z.LoadServiceInDocker = {} --在Docker中装载一个Service 
Proto4z.LoadServiceInDocker.__getID = 2014 
Proto4z.LoadServiceInDocker.__getName = "LoadServiceInDocker" 
Proto4z.LoadServiceInDocker[1] = {name="serviceType", type="ui16" }  
Proto4z.LoadServiceInDocker[2] = {name="serviceID", type="ui64" }  
Proto4z.LoadServiceInDocker[3] = {name="serviceName", type="string" }  
Proto4z.LoadServiceInDocker[4] = {name="clientDockerID", type="ui32" }  
Proto4z.LoadServiceInDocker[5] = {name="clientSessionID", type="ui32" }  
 
Proto4z.register(2016,"LoadServiceNotice") 
Proto4z.LoadServiceNotice = {} --通知其他Docker有Service已装载 
Proto4z.LoadServiceNotice.__getID = 2016 
Proto4z.LoadServiceNotice.__getName = "LoadServiceNotice" 
Proto4z.LoadServiceNotice[1] = {name="serviceDockerID", type="ui32" }  
Proto4z.LoadServiceNotice[2] = {name="serviceType", type="ui16" }  
Proto4z.LoadServiceNotice[3] = {name="serviceID", type="ui64" }  
Proto4z.LoadServiceNotice[4] = {name="serviceName", type="string" }  
Proto4z.LoadServiceNotice[5] = {name="status", type="ui16" }  
Proto4z.LoadServiceNotice[6] = {name="clientDockerID", type="ui32" }  
Proto4z.LoadServiceNotice[7] = {name="clientSessionID", type="ui32" }  
 
Proto4z.register(2017,"SwitchServiceClient") 
Proto4z.SwitchServiceClient = {} --更改clientID 
Proto4z.SwitchServiceClient.__getID = 2017 
Proto4z.SwitchServiceClient.__getName = "SwitchServiceClient" 
Proto4z.SwitchServiceClient[1] = {name="serviceType", type="ui16" }  
Proto4z.SwitchServiceClient[2] = {name="serviceID", type="ui64" }  
Proto4z.SwitchServiceClient[3] = {name="clientDockerID", type="ui32" }  
Proto4z.SwitchServiceClient[4] = {name="clientSessionID", type="ui32" }  
 
Proto4z.register(2004,"KickRealClient") 
Proto4z.KickRealClient = {} --踢掉一个客户端 
Proto4z.KickRealClient.__getID = 2004 
Proto4z.KickRealClient.__getName = "KickRealClient" 
Proto4z.KickRealClient[1] = {name="clientSessionID", type="ui32" }  
 
Proto4z.register(2005,"RealClientClosedNotice") 
Proto4z.RealClientClosedNotice = {} --客户端离线通知 
Proto4z.RealClientClosedNotice.__getID = 2005 
Proto4z.RealClientClosedNotice.__getName = "RealClientClosedNotice" 
Proto4z.RealClientClosedNotice[1] = {name="serviceID", type="ui64" }  
Proto4z.RealClientClosedNotice[2] = {name="clientDockerID", type="ui32" }  
Proto4z.RealClientClosedNotice[3] = {name="clientSessionID", type="ui32" }  
 
Proto4z.register(2011,"UnloadServiceInDocker") 
Proto4z.UnloadServiceInDocker = {} --卸载一个Service 
Proto4z.UnloadServiceInDocker.__getID = 2011 
Proto4z.UnloadServiceInDocker.__getName = "UnloadServiceInDocker" 
Proto4z.UnloadServiceInDocker[1] = {name="serviceType", type="ui16" }  
Proto4z.UnloadServiceInDocker[2] = {name="serviceID", type="ui64" }  
 
Proto4z.register(2013,"UnloadedServiceNotice") 
Proto4z.UnloadedServiceNotice = {} --已卸载并完成销毁,广播给所有docker 
Proto4z.UnloadedServiceNotice.__getID = 2013 
Proto4z.UnloadedServiceNotice.__getName = "UnloadedServiceNotice" 
Proto4z.UnloadedServiceNotice[1] = {name="serviceType", type="ui16" }  
Proto4z.UnloadedServiceNotice[2] = {name="serviceID", type="ui64" }  
 
Proto4z.register(2008,"ShutdownClusterServer") 
Proto4z.ShutdownClusterServer = {} --关闭服务器集群 
Proto4z.ShutdownClusterServer.__getID = 2008 
Proto4z.ShutdownClusterServer.__getName = "ShutdownClusterServer" 
 
Proto4z.register(2009,"ForwardToService") 
Proto4z.ForwardToService = {} --转发到其他docker上的Service 
Proto4z.ForwardToService.__getID = 2009 
Proto4z.ForwardToService.__getName = "ForwardToService" 
 
Proto4z.register(2010,"ForwardToRealClient") 
Proto4z.ForwardToRealClient = {} --转发给真正的client 
Proto4z.ForwardToRealClient.__getID = 2010 
Proto4z.ForwardToRealClient.__getName = "ForwardToRealClient" 

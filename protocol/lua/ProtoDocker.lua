 
Proto4z.register(2000,"DockerPulse") 
Proto4z.DockerPulse = {} --集群脉冲 
Proto4z.DockerPulse.__getID = 2000 
Proto4z.DockerPulse.__getName = "DockerPulse" 
 
Proto4z.register(2001,"CreateServiceInDocker") 
Proto4z.CreateServiceInDocker = {} --创建并初始化一个service 
Proto4z.CreateServiceInDocker.__getID = 2001 
Proto4z.CreateServiceInDocker.__getName = "CreateServiceInDocker" 
Proto4z.CreateServiceInDocker[1] = {name="serviceType", type="ui16" }  
Proto4z.CreateServiceInDocker[2] = {name="serviceID", type="ui64" }  
Proto4z.CreateServiceInDocker[3] = {name="serviceName", type="string" }  
Proto4z.CreateServiceInDocker[4] = {name="clientDockerID", type="ui32" }  
Proto4z.CreateServiceInDocker[5] = {name="clientSessionID", type="ui32" }  
 
Proto4z.register(2003,"CreateOrRefreshServiceNotice") 
Proto4z.CreateOrRefreshServiceNotice = {} --广播给所有docker 
Proto4z.CreateOrRefreshServiceNotice.__getID = 2003 
Proto4z.CreateOrRefreshServiceNotice.__getName = "CreateOrRefreshServiceNotice" 
Proto4z.CreateOrRefreshServiceNotice[1] = {name="serviceDockerID", type="ui32" }  
Proto4z.CreateOrRefreshServiceNotice[2] = {name="serviceType", type="ui16" }  
Proto4z.CreateOrRefreshServiceNotice[3] = {name="serviceID", type="ui64" }  
Proto4z.CreateOrRefreshServiceNotice[4] = {name="serviceName", type="string" }  
Proto4z.CreateOrRefreshServiceNotice[5] = {name="status", type="ui16" }  
Proto4z.CreateOrRefreshServiceNotice[6] = {name="clientDockerID", type="ui32" }  
Proto4z.CreateOrRefreshServiceNotice[7] = {name="clientSessionID", type="ui32" }  
 
Proto4z.register(2002,"ChangeServiceClient") 
Proto4z.ChangeServiceClient = {} --更改clientID 
Proto4z.ChangeServiceClient.__getID = 2002 
Proto4z.ChangeServiceClient.__getName = "ChangeServiceClient" 
Proto4z.ChangeServiceClient[1] = {name="serviceType", type="ui16" }  
Proto4z.ChangeServiceClient[2] = {name="serviceID", type="ui64" }  
Proto4z.ChangeServiceClient[3] = {name="clientDockerID", type="ui32" }  
Proto4z.ChangeServiceClient[4] = {name="clientSessionID", type="ui32" }  
 
Proto4z.register(2008,"KickRealClient") 
Proto4z.KickRealClient = {} --踢掉一个客户端 
Proto4z.KickRealClient.__getID = 2008 
Proto4z.KickRealClient.__getName = "KickRealClient" 
Proto4z.KickRealClient[1] = {name="clientSessionID", type="ui32" }  
 
Proto4z.register(2009,"RealClientClosedNotice") 
Proto4z.RealClientClosedNotice = {} --客户端离线通知 
Proto4z.RealClientClosedNotice.__getID = 2009 
Proto4z.RealClientClosedNotice.__getName = "RealClientClosedNotice" 
Proto4z.RealClientClosedNotice[1] = {name="serviceID", type="ui64" }  
Proto4z.RealClientClosedNotice[2] = {name="clientDockerID", type="ui32" }  
Proto4z.RealClientClosedNotice[3] = {name="clientSessionID", type="ui32" }  
 
Proto4z.register(2004,"DestroyServiceInDocker") 
Proto4z.DestroyServiceInDocker = {} --销毁一个Service 
Proto4z.DestroyServiceInDocker.__getID = 2004 
Proto4z.DestroyServiceInDocker.__getName = "DestroyServiceInDocker" 
Proto4z.DestroyServiceInDocker[1] = {name="serviceType", type="ui16" }  
Proto4z.DestroyServiceInDocker[2] = {name="serviceID", type="ui64" }  
 
Proto4z.register(2005,"DestroyServiceNotice") 
Proto4z.DestroyServiceNotice = {} --已卸载并完成销毁,广播给所有docker 
Proto4z.DestroyServiceNotice.__getID = 2005 
Proto4z.DestroyServiceNotice.__getName = "DestroyServiceNotice" 
Proto4z.DestroyServiceNotice[1] = {name="serviceType", type="ui16" }  
Proto4z.DestroyServiceNotice[2] = {name="serviceID", type="ui64" }  
 
Proto4z.register(2010,"ShutdownClusterServer") 
Proto4z.ShutdownClusterServer = {} --关闭服务器集群 
Proto4z.ShutdownClusterServer.__getID = 2010 
Proto4z.ShutdownClusterServer.__getName = "ShutdownClusterServer" 
 
Proto4z.register(2006,"ForwardToService") 
Proto4z.ForwardToService = {} --转发到其他docker上的Service 
Proto4z.ForwardToService.__getID = 2006 
Proto4z.ForwardToService.__getName = "ForwardToService" 
 
Proto4z.register(2007,"ForwardToRealClient") 
Proto4z.ForwardToRealClient = {} --转发给真正的client 
Proto4z.ForwardToRealClient.__getID = 2007 
Proto4z.ForwardToRealClient.__getName = "ForwardToRealClient" 

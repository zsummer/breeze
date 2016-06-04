 
Proto4z.register(40000,"DockerPulse") 
Proto4z.DockerPulse = {} --集群脉冲 
Proto4z.DockerPulse.__getID = 40000 
Proto4z.DockerPulse.__getName = "DockerPulse" 
 
Proto4z.register(40001,"CreateServiceInDocker") 
Proto4z.CreateServiceInDocker = {} --创建并初始化一个service 
Proto4z.CreateServiceInDocker.__getID = 40001 
Proto4z.CreateServiceInDocker.__getName = "CreateServiceInDocker" 
Proto4z.CreateServiceInDocker[1] = {name="serviceType", type="ui16" }  
Proto4z.CreateServiceInDocker[2] = {name="serviceID", type="ui64" }  
Proto4z.CreateServiceInDocker[3] = {name="clientDockerID", type="ui32" }  
Proto4z.CreateServiceInDocker[4] = {name="clientSessionID", type="ui32" }  
 
Proto4z.register(40002,"ChangeServiceClient") 
Proto4z.ChangeServiceClient = {} --更改clientID 
Proto4z.ChangeServiceClient.__getID = 40002 
Proto4z.ChangeServiceClient.__getName = "ChangeServiceClient" 
Proto4z.ChangeServiceClient[1] = {name="serviceType", type="ui16" }  
Proto4z.ChangeServiceClient[2] = {name="serviceID", type="ui64" }  
Proto4z.ChangeServiceClient[3] = {name="clientDockerID", type="ui32" }  
Proto4z.ChangeServiceClient[4] = {name="clientSessionID", type="ui32" }  
 
Proto4z.register(40003,"CreateOrRefreshServiceNotice") 
Proto4z.CreateOrRefreshServiceNotice = {} --广播给所有docker 
Proto4z.CreateOrRefreshServiceNotice.__getID = 40003 
Proto4z.CreateOrRefreshServiceNotice.__getName = "CreateOrRefreshServiceNotice" 
Proto4z.CreateOrRefreshServiceNotice[1] = {name="serviceType", type="ui16" }  
Proto4z.CreateOrRefreshServiceNotice[2] = {name="serviceID", type="ui64" }  
Proto4z.CreateOrRefreshServiceNotice[3] = {name="dockerID", type="ui32" }  
Proto4z.CreateOrRefreshServiceNotice[4] = {name="clientDockerID", type="ui32" }  
Proto4z.CreateOrRefreshServiceNotice[5] = {name="clientSessionID", type="ui32" }  
 
Proto4z.register(40004,"DestroyServiceInDocker") 
Proto4z.DestroyServiceInDocker = {} --销毁一个Service 
Proto4z.DestroyServiceInDocker.__getID = 40004 
Proto4z.DestroyServiceInDocker.__getName = "DestroyServiceInDocker" 
Proto4z.DestroyServiceInDocker[1] = {name="serviceType", type="ui16" }  
Proto4z.DestroyServiceInDocker[2] = {name="serviceID", type="ui64" }  
 
Proto4z.register(40005,"DestroyServiceNotice") 
Proto4z.DestroyServiceNotice = {} --已卸载并完成销毁,广播给所有docker 
Proto4z.DestroyServiceNotice.__getID = 40005 
Proto4z.DestroyServiceNotice.__getName = "DestroyServiceNotice" 
Proto4z.DestroyServiceNotice[1] = {name="serviceType", type="ui16" }  
Proto4z.DestroyServiceNotice[2] = {name="serviceID", type="ui64" }  
 
Proto4z.register(40006,"ForwardToService") 
Proto4z.ForwardToService = {} --转发到其他docker上的Service 
Proto4z.ForwardToService.__getID = 40006 
Proto4z.ForwardToService.__getName = "ForwardToService" 
 
Proto4z.register(40007,"ForwardToRealClient") 
Proto4z.ForwardToRealClient = {} --转发给真正的client 
Proto4z.ForwardToRealClient.__getID = 40007 
Proto4z.ForwardToRealClient.__getName = "ForwardToRealClient" 

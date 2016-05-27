 
Proto4z.register(40007,"DockerPulse") 
Proto4z.DockerPulse = {} --集群脉冲 
Proto4z.DockerPulse.__getID = 40007 
Proto4z.DockerPulse.__getName = "DockerPulse" 
 
Proto4z.register(40001,"CreateServiceInDocker") 
Proto4z.CreateServiceInDocker = {} --创建并初始化一个service 
Proto4z.CreateServiceInDocker.__getID = 40001 
Proto4z.CreateServiceInDocker.__getName = "CreateServiceInDocker" 
Proto4z.CreateServiceInDocker[1] = {name="serviceType", type="ui16" }  
Proto4z.CreateServiceInDocker[2] = {name="serviceID", type="ui64" }  
Proto4z.CreateServiceInDocker[3] = {name="dockerID", type="ui32" }  
Proto4z.CreateServiceInDocker[4] = {name="clientID", type="ui32" }  
 
Proto4z.register(40002,"CreateServiceNotice") 
Proto4z.CreateServiceNotice = {} --服务创建好并初始化成功,广播给所有docker 
Proto4z.CreateServiceNotice.__getID = 40002 
Proto4z.CreateServiceNotice.__getName = "CreateServiceNotice" 
Proto4z.CreateServiceNotice[1] = {name="serviceType", type="ui16" }  
Proto4z.CreateServiceNotice[2] = {name="serviceID", type="ui64" }  
Proto4z.CreateServiceNotice[3] = {name="dockerID", type="ui32" }  
Proto4z.CreateServiceNotice[4] = {name="clientID", type="ui32" }  
 
Proto4z.register(40003,"DestroyServiceInDocker") 
Proto4z.DestroyServiceInDocker = {} --销毁一个Service 
Proto4z.DestroyServiceInDocker.__getID = 40003 
Proto4z.DestroyServiceInDocker.__getName = "DestroyServiceInDocker" 
Proto4z.DestroyServiceInDocker[1] = {name="serviceType", type="ui16" }  
Proto4z.DestroyServiceInDocker[2] = {name="serviceID", type="ui64" }  
 
Proto4z.register(40004,"DestroyServiceNotice") 
Proto4z.DestroyServiceNotice = {} --已卸载并完成销毁,广播给所有docker 
Proto4z.DestroyServiceNotice.__getID = 40004 
Proto4z.DestroyServiceNotice.__getName = "DestroyServiceNotice" 
Proto4z.DestroyServiceNotice[1] = {name="serviceType", type="ui16" }  
Proto4z.DestroyServiceNotice[2] = {name="serviceID", type="ui64" }  
 
Proto4z.register(40005,"ShellForward") 
Proto4z.ShellForward = {} --壳子转发 
Proto4z.ShellForward.__getID = 40005 
Proto4z.ShellForward.__getName = "ShellForward" 
 
Proto4z.register(40006,"ClientForward") 
Proto4z.ClientForward = {} --client转发 
Proto4z.ClientForward.__getID = 40006 
Proto4z.ClientForward.__getName = "ClientForward" 

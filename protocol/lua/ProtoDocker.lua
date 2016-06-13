 
Proto4z.register(2000,"DockerPulse") 
Proto4z.DockerPulse = {} --集群脉冲 
Proto4z.DockerPulse.__protoID = 2000 
Proto4z.DockerPulse.__protoName = "DockerPulse" 
 
Proto4z.register(2014,"SessionPulse") 
Proto4z.SessionPulse = {} --对于建立了UserService的客户端,通过该消息驱动onTick 
Proto4z.SessionPulse.__protoID = 2014 
Proto4z.SessionPulse.__protoName = "SessionPulse" 
Proto4z.SessionPulse[1] = {name="serviceID", type="ui64" }  
 
Proto4z.register(2001,"LoadServiceInDocker") 
Proto4z.LoadServiceInDocker = {} --在Docker中装载一个Service 
Proto4z.LoadServiceInDocker.__protoID = 2001 
Proto4z.LoadServiceInDocker.__protoName = "LoadServiceInDocker" 
Proto4z.LoadServiceInDocker[1] = {name="serviceType", type="ui16" }  
Proto4z.LoadServiceInDocker[2] = {name="serviceID", type="ui64" }  
Proto4z.LoadServiceInDocker[3] = {name="serviceName", type="string" }  
Proto4z.LoadServiceInDocker[4] = {name="clientDockerID", type="ui32" }  
Proto4z.LoadServiceInDocker[5] = {name="clientSessionID", type="ui32" }  
 
Proto4z.register(2002,"LoadServiceNotice") 
Proto4z.LoadServiceNotice = {} --通知其他Docker有Service已装载 
Proto4z.LoadServiceNotice.__protoID = 2002 
Proto4z.LoadServiceNotice.__protoName = "LoadServiceNotice" 
Proto4z.LoadServiceNotice[1] = {name="serviceDockerID", type="ui32" }  
Proto4z.LoadServiceNotice[2] = {name="serviceType", type="ui16" }  
Proto4z.LoadServiceNotice[3] = {name="serviceID", type="ui64" }  
Proto4z.LoadServiceNotice[4] = {name="serviceName", type="string" }  
Proto4z.LoadServiceNotice[5] = {name="status", type="ui16" }  
Proto4z.LoadServiceNotice[6] = {name="clientDockerID", type="ui32" }  
Proto4z.LoadServiceNotice[7] = {name="clientSessionID", type="ui32" }  
 
Proto4z.register(2003,"RefreshServiceToMgrNotice") 
Proto4z.RefreshServiceToMgrNotice = {} --Multi-Servie发生状态变化时候通知给管理器 
Proto4z.RefreshServiceToMgrNotice.__protoID = 2003 
Proto4z.RefreshServiceToMgrNotice.__protoName = "RefreshServiceToMgrNotice" 
Proto4z.RefreshServiceToMgrNotice[1] = {name="serviceDockerID", type="ui32" }  
Proto4z.RefreshServiceToMgrNotice[2] = {name="serviceType", type="ui16" }  
Proto4z.RefreshServiceToMgrNotice[3] = {name="serviceID", type="ui64" }  
Proto4z.RefreshServiceToMgrNotice[4] = {name="serviceName", type="string" }  
Proto4z.RefreshServiceToMgrNotice[5] = {name="status", type="ui16" }  
Proto4z.RefreshServiceToMgrNotice[6] = {name="clientDockerID", type="ui32" }  
Proto4z.RefreshServiceToMgrNotice[7] = {name="clientSessionID", type="ui32" }  
 
Proto4z.register(2004,"SwitchServiceClient") 
Proto4z.SwitchServiceClient = {} --更改clientID 
Proto4z.SwitchServiceClient.__protoID = 2004 
Proto4z.SwitchServiceClient.__protoName = "SwitchServiceClient" 
Proto4z.SwitchServiceClient[1] = {name="serviceType", type="ui16" }  
Proto4z.SwitchServiceClient[2] = {name="serviceID", type="ui64" }  
Proto4z.SwitchServiceClient[3] = {name="clientDockerID", type="ui32" }  
Proto4z.SwitchServiceClient[4] = {name="clientSessionID", type="ui32" }  
 
Proto4z.register(2005,"SwitchServiceClientNotice") 
Proto4z.SwitchServiceClientNotice = {} --更改clientID 
Proto4z.SwitchServiceClientNotice.__protoID = 2005 
Proto4z.SwitchServiceClientNotice.__protoName = "SwitchServiceClientNotice" 
Proto4z.SwitchServiceClientNotice[1] = {name="serviceType", type="ui16" }  
Proto4z.SwitchServiceClientNotice[2] = {name="serviceID", type="ui64" }  
Proto4z.SwitchServiceClientNotice[3] = {name="clientDockerID", type="ui32" }  
Proto4z.SwitchServiceClientNotice[4] = {name="clientSessionID", type="ui32" }  
 
Proto4z.register(2006,"KickRealClient") 
Proto4z.KickRealClient = {} --踢掉一个客户端 
Proto4z.KickRealClient.__protoID = 2006 
Proto4z.KickRealClient.__protoName = "KickRealClient" 
Proto4z.KickRealClient[1] = {name="clientSessionID", type="ui32" }  
 
Proto4z.register(2007,"RealClientClosedNotice") 
Proto4z.RealClientClosedNotice = {} --客户端离线通知 
Proto4z.RealClientClosedNotice.__protoID = 2007 
Proto4z.RealClientClosedNotice.__protoName = "RealClientClosedNotice" 
Proto4z.RealClientClosedNotice[1] = {name="serviceID", type="ui64" }  
Proto4z.RealClientClosedNotice[2] = {name="clientDockerID", type="ui32" }  
Proto4z.RealClientClosedNotice[3] = {name="clientSessionID", type="ui32" }  
 
Proto4z.register(2008,"UnloadServiceInDocker") 
Proto4z.UnloadServiceInDocker = {} --卸载一个Service 
Proto4z.UnloadServiceInDocker.__protoID = 2008 
Proto4z.UnloadServiceInDocker.__protoName = "UnloadServiceInDocker" 
Proto4z.UnloadServiceInDocker[1] = {name="serviceType", type="ui16" }  
Proto4z.UnloadServiceInDocker[2] = {name="serviceID", type="ui64" }  
 
Proto4z.register(2009,"UnloadedServiceNotice") 
Proto4z.UnloadedServiceNotice = {} --已卸载并完成销毁,广播给所有docker 
Proto4z.UnloadedServiceNotice.__protoID = 2009 
Proto4z.UnloadedServiceNotice.__protoName = "UnloadedServiceNotice" 
Proto4z.UnloadedServiceNotice[1] = {name="serviceType", type="ui16" }  
Proto4z.UnloadedServiceNotice[2] = {name="serviceID", type="ui64" }  
 
Proto4z.register(2010,"ShutdownClusterServer") 
Proto4z.ShutdownClusterServer = {} --关闭服务器集群 
Proto4z.ShutdownClusterServer.__protoID = 2010 
Proto4z.ShutdownClusterServer.__protoName = "ShutdownClusterServer" 
 
Proto4z.register(2011,"ForwardToService") 
Proto4z.ForwardToService = {} --转发到其他docker上的Service 
Proto4z.ForwardToService.__protoID = 2011 
Proto4z.ForwardToService.__protoName = "ForwardToService" 
 
Proto4z.register(2012,"ForwardToRealClient") 
Proto4z.ForwardToRealClient = {} --转发给真正的client 
Proto4z.ForwardToRealClient.__protoID = 2012 
Proto4z.ForwardToRealClient.__protoName = "ForwardToRealClient" 

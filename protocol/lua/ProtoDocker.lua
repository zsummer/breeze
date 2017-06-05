 
Proto4z.register(3000,"DockerKnock") 
Proto4z.DockerKnock = {}  
Proto4z.DockerKnock.__protoID = 3000 
Proto4z.DockerKnock.__protoName = "DockerKnock" 
Proto4z.DockerKnock[1] = {name="areaID", type="ui64" }  
Proto4z.DockerKnock[2] = {name="dockerID", type="ui64" }  
 
Proto4z.register(3001,"DockerPulse") 
Proto4z.DockerPulse = {} --集群脉冲 
Proto4z.DockerPulse.__protoID = 3001 
Proto4z.DockerPulse.__protoName = "DockerPulse" 
 
Proto4z.register(3002,"LoadService") 
Proto4z.LoadService = {} --在Docker中装载一个Service 
Proto4z.LoadService.__protoID = 3002 
Proto4z.LoadService.__protoName = "LoadService" 
Proto4z.LoadService[1] = {name="serviceType", type="ui16" }  
Proto4z.LoadService[2] = {name="serviceID", type="ui64" }  
Proto4z.LoadService[3] = {name="serviceName", type="string" }  
Proto4z.LoadService[4] = {name="clientDockerID", type="ui64" }  
Proto4z.LoadService[5] = {name="clientSessionID", type="ui32" }  
 
Proto4z.register(3003,"ServiceInfo") 
Proto4z.ServiceInfo = {} --Service被装载或者属性更改,需要通知给其他Docker的信息 
Proto4z.ServiceInfo.__protoID = 3003 
Proto4z.ServiceInfo.__protoName = "ServiceInfo" 
Proto4z.ServiceInfo[1] = {name="serviceDockerID", type="ui64" }  
Proto4z.ServiceInfo[2] = {name="serviceType", type="ui16" }  
Proto4z.ServiceInfo[3] = {name="serviceID", type="ui64" }  
Proto4z.ServiceInfo[4] = {name="serviceName", type="string" }  
Proto4z.ServiceInfo[5] = {name="status", type="ui16" }  
Proto4z.ServiceInfo[6] = {name="clientDockerID", type="ui64" }  
Proto4z.ServiceInfo[7] = {name="clientSessionID", type="ui32" }  
 
Proto4z.ServiceInfoArray = {}  
Proto4z.ServiceInfoArray.__protoName = "ServiceInfoArray" 
Proto4z.ServiceInfoArray.__protoDesc = "array" 
Proto4z.ServiceInfoArray.__protoTypeV = "ServiceInfo" 
 
Proto4z.register(3004,"LoadServiceNotice") 
Proto4z.LoadServiceNotice = {} --通知其他Docker有Service已装载 
Proto4z.LoadServiceNotice.__protoID = 3004 
Proto4z.LoadServiceNotice.__protoName = "LoadServiceNotice" 
Proto4z.LoadServiceNotice[1] = {name="shellServiceInfos", type="ServiceInfoArray" }  
 
Proto4z.register(3005,"RefreshServiceToMgrNotice") 
Proto4z.RefreshServiceToMgrNotice = {} --Multi-Servie发生状态变化时候通知给管理器 
Proto4z.RefreshServiceToMgrNotice.__protoID = 3005 
Proto4z.RefreshServiceToMgrNotice.__protoName = "RefreshServiceToMgrNotice" 
Proto4z.RefreshServiceToMgrNotice[1] = {name="shellServiceInfos", type="ServiceInfoArray" }  
 
Proto4z.register(3006,"SwitchServiceClientNotice") 
Proto4z.SwitchServiceClientNotice = {} --更改clientID 
Proto4z.SwitchServiceClientNotice.__protoID = 3006 
Proto4z.SwitchServiceClientNotice.__protoName = "SwitchServiceClientNotice" 
Proto4z.SwitchServiceClientNotice[1] = {name="serviceType", type="ui16" }  
Proto4z.SwitchServiceClientNotice[2] = {name="serviceID", type="ui64" }  
Proto4z.SwitchServiceClientNotice[3] = {name="clientDockerID", type="ui64" }  
Proto4z.SwitchServiceClientNotice[4] = {name="clientSessionID", type="ui32" }  
 
Proto4z.register(3007,"KickRealClient") 
Proto4z.KickRealClient = {} --踢掉一个客户端 
Proto4z.KickRealClient.__protoID = 3007 
Proto4z.KickRealClient.__protoName = "KickRealClient" 
Proto4z.KickRealClient[1] = {name="clientSessionID", type="ui32" }  
 
Proto4z.register(3008,"RealClientClosedNotice") 
Proto4z.RealClientClosedNotice = {} --客户端离线通知 
Proto4z.RealClientClosedNotice.__protoID = 3008 
Proto4z.RealClientClosedNotice.__protoName = "RealClientClosedNotice" 
Proto4z.RealClientClosedNotice[1] = {name="serviceID", type="ui64" }  
Proto4z.RealClientClosedNotice[2] = {name="clientDockerID", type="ui64" }  
Proto4z.RealClientClosedNotice[3] = {name="clientSessionID", type="ui32" }  
 
Proto4z.register(3009,"UnloadServiceInDocker") 
Proto4z.UnloadServiceInDocker = {} --卸载一个Service 
Proto4z.UnloadServiceInDocker.__protoID = 3009 
Proto4z.UnloadServiceInDocker.__protoName = "UnloadServiceInDocker" 
Proto4z.UnloadServiceInDocker[1] = {name="serviceType", type="ui16" }  
Proto4z.UnloadServiceInDocker[2] = {name="serviceID", type="ui64" }  
 
Proto4z.register(3010,"UnloadedServiceNotice") 
Proto4z.UnloadedServiceNotice = {} --已卸载并完成销毁,广播给所有docker 
Proto4z.UnloadedServiceNotice.__protoID = 3010 
Proto4z.UnloadedServiceNotice.__protoName = "UnloadedServiceNotice" 
Proto4z.UnloadedServiceNotice[1] = {name="serviceType", type="ui16" }  
Proto4z.UnloadedServiceNotice[2] = {name="serviceID", type="ui64" }  
 
Proto4z.register(3011,"ShutdownClusterServer") 
Proto4z.ShutdownClusterServer = {} --关闭服务器集群 
Proto4z.ShutdownClusterServer.__protoID = 3011 
Proto4z.ShutdownClusterServer.__protoName = "ShutdownClusterServer" 
 
Proto4z.register(3012,"ForwardToService") 
Proto4z.ForwardToService = {} --转发到其他docker上的Service 
Proto4z.ForwardToService.__protoID = 3012 
Proto4z.ForwardToService.__protoName = "ForwardToService" 
 
Proto4z.register(3013,"ForwardToRealClient") 
Proto4z.ForwardToRealClient = {} --转发给真正的client 
Proto4z.ForwardToRealClient.__protoID = 3013 
Proto4z.ForwardToRealClient.__protoName = "ForwardToRealClient" 
 
Proto4z.register(3014,"ForwardToDocker") 
Proto4z.ForwardToDocker = {} --转发给Docker 
Proto4z.ForwardToDocker.__protoID = 3014 
Proto4z.ForwardToDocker.__protoName = "ForwardToDocker" 
 
Proto4z.register(3015,"ReloadDBDictNotice") 
Proto4z.ReloadDBDictNotice = {} --重新加载字典文件 
Proto4z.ReloadDBDictNotice.__protoID = 3015 
Proto4z.ReloadDBDictNotice.__protoName = "ReloadDBDictNotice" 
 
Proto4z.register(3016,"ReloadDBDictFinish") 
Proto4z.ReloadDBDictFinish = {} --重新加载字典文件 
Proto4z.ReloadDBDictFinish.__protoID = 3016 
Proto4z.ReloadDBDictFinish.__protoName = "ReloadDBDictFinish" 
Proto4z.ReloadDBDictFinish[1] = {name="dockerID", type="ui64" }  
Proto4z.ReloadDBDictFinish[2] = {name="activeTime", type="double" }  
Proto4z.ReloadDBDictFinish[3] = {name="used", type="double" }  
 
Proto4z.register(3017,"KickClientsNotice") 
Proto4z.KickClientsNotice = {} --踢人 
Proto4z.KickClientsNotice.__protoID = 3017 
Proto4z.KickClientsNotice.__protoName = "KickClientsNotice" 
Proto4z.KickClientsNotice[1] = {name="isAll", type="ui16" }  
Proto4z.KickClientsNotice[2] = {name="avatars", type="ServiceIDArray" } --指定avatar 
Proto4z.KickClientsNotice[3] = {name="accounts", type="AccountArray" } --指定account 
Proto4z.KickClientsNotice[4] = {name="forbidDuration", type="ui64" } --限制登录的持续时间(关服前有效 不记录到数据库) 
 
Proto4z.DBStringArray = {}  
Proto4z.DBStringArray.__protoName = "DBStringArray" 
Proto4z.DBStringArray.__protoDesc = "array" 
Proto4z.DBStringArray.__protoTypeV = "string" 
 
Proto4z.register(3018,"DBDataResult") 
Proto4z.DBDataResult = {}  
Proto4z.DBDataResult.__protoID = 3018 
Proto4z.DBDataResult.__protoName = "DBDataResult" 
Proto4z.DBDataResult[1] = {name="qc", type="ui16" }  
Proto4z.DBDataResult[2] = {name="errMsg", type="string" }  
Proto4z.DBDataResult[3] = {name="sql", type="string" }  
Proto4z.DBDataResult[4] = {name="affected", type="ui64" }  
Proto4z.DBDataResult[5] = {name="fields", type="DBStringArray" }  
 
Proto4z.DBDataResultArray = {}  
Proto4z.DBDataResultArray.__protoName = "DBDataResultArray" 
Proto4z.DBDataResultArray.__protoDesc = "array" 
Proto4z.DBDataResultArray.__protoTypeV = "DBDataResult" 
 
Proto4z.register(3019,"DBQueryReq") 
Proto4z.DBQueryReq = {} --通用SQL语句执行协议 
Proto4z.DBQueryReq.__protoID = 3019 
Proto4z.DBQueryReq.__protoName = "DBQueryReq" 
Proto4z.DBQueryReq[1] = {name="sql", type="string" }  
 
Proto4z.register(3020,"DBQueryResp") 
Proto4z.DBQueryResp = {} --通用SQL语句执行协议返回,DBDataResult可以借助dbHepler进行构建DBResult 
Proto4z.DBQueryResp.__protoID = 3020 
Proto4z.DBQueryResp.__protoName = "DBQueryResp" 
Proto4z.DBQueryResp[1] = {name="retCode", type="ui16" }  
Proto4z.DBQueryResp[2] = {name="result", type="DBDataResult" }  
 
Proto4z.register(3021,"DBQueryArrayReq") 
Proto4z.DBQueryArrayReq = {} --通用批量SQL语句执行协议 
Proto4z.DBQueryArrayReq.__protoID = 3021 
Proto4z.DBQueryArrayReq.__protoName = "DBQueryArrayReq" 
Proto4z.DBQueryArrayReq[1] = {name="sqls", type="DBStringArray" }  
 
Proto4z.register(3022,"DBQueryArrayResp") 
Proto4z.DBQueryArrayResp = {} --通用批量SQL语句执行协议 
Proto4z.DBQueryArrayResp.__protoID = 3022 
Proto4z.DBQueryArrayResp.__protoName = "DBQueryArrayResp" 
Proto4z.DBQueryArrayResp[1] = {name="retCode", type="ui16" }  
Proto4z.DBQueryArrayResp[2] = {name="results", type="DBDataResultArray" } --批量返回,注意不要超出协议包最大长度 
 
Proto4z.WebAgentHead = {}  
Proto4z.WebAgentHead.__protoName = "WebAgentHead" 
Proto4z.WebAgentHead.__protoDesc = "map" 
Proto4z.WebAgentHead.__protoTypeK = "string" 
Proto4z.WebAgentHead.__protoTypeV = "string" 
 
Proto4z.register(3023,"WebAgentClientRequestAPI") 
Proto4z.WebAgentClientRequestAPI = {}  
Proto4z.WebAgentClientRequestAPI.__protoID = 3023 
Proto4z.WebAgentClientRequestAPI.__protoName = "WebAgentClientRequestAPI" 
Proto4z.WebAgentClientRequestAPI[1] = {name="method", type="string" }  
Proto4z.WebAgentClientRequestAPI[2] = {name="methodLine", type="string" }  
Proto4z.WebAgentClientRequestAPI[3] = {name="heads", type="WebAgentHead" }  
Proto4z.WebAgentClientRequestAPI[4] = {name="body", type="string" }  
 
Proto4z.register(3024,"WebServerRequest") 
Proto4z.WebServerRequest = {}  
Proto4z.WebServerRequest.__protoID = 3024 
Proto4z.WebServerRequest.__protoName = "WebServerRequest" 
Proto4z.WebServerRequest[1] = {name="fromServiceType", type="ui16" }  
Proto4z.WebServerRequest[2] = {name="fromServiceID", type="ui64" }  
Proto4z.WebServerRequest[3] = {name="traceID", type="ui64" }  
Proto4z.WebServerRequest[4] = {name="ip", type="string" }  
Proto4z.WebServerRequest[5] = {name="port", type="ui16" }  
Proto4z.WebServerRequest[6] = {name="host", type="string" }  
Proto4z.WebServerRequest[7] = {name="uri", type="string" }  
Proto4z.WebServerRequest[8] = {name="webparams", type="string" }  
Proto4z.WebServerRequest[9] = {name="heads", type="WebAgentHead" }  
Proto4z.WebServerRequest[10] = {name="isGet", type="ui8" } --get or post 
 
Proto4z.register(3025,"WebServerResponse") 
Proto4z.WebServerResponse = {}  
Proto4z.WebServerResponse.__protoID = 3025 
Proto4z.WebServerResponse.__protoName = "WebServerResponse" 
Proto4z.WebServerResponse[1] = {name="method", type="string" }  
Proto4z.WebServerResponse[2] = {name="methodLine", type="string" }  
Proto4z.WebServerResponse[3] = {name="heads", type="WebAgentHead" }  
Proto4z.WebServerResponse[4] = {name="body", type="string" }  
 
Proto4z.register(3026,"AvatarOffline") 
Proto4z.AvatarOffline = {}  
Proto4z.AvatarOffline.__protoID = 3026 
Proto4z.AvatarOffline.__protoName = "AvatarOffline" 
Proto4z.AvatarOffline[1] = {name="id", type="ui64" }  
Proto4z.AvatarOffline[2] = {name="avatarID", type="ui64" }  
Proto4z.AvatarOffline[3] = {name="streamBlob", type="string" }  
Proto4z.AvatarOffline[4] = {name="status", type="ui16" }  
Proto4z.AvatarOffline[5] = {name="timestamp", type="ui64" }  

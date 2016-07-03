 
Proto4z.register(2014,"SelfBeingPulse") 
Proto4z.SelfBeingPulse = {}  
Proto4z.SelfBeingPulse.__protoID = 2014 
Proto4z.SelfBeingPulse.__protoName = "SelfBeingPulse" 
Proto4z.SelfBeingPulse[1] = {name="areaID", type="ui64" }  
Proto4z.SelfBeingPulse[2] = {name="dockerID", type="ui64" }  
 
Proto4z.register(2000,"DockerPulse") 
Proto4z.DockerPulse = {} --集群脉冲 
Proto4z.DockerPulse.__protoID = 2000 
Proto4z.DockerPulse.__protoName = "DockerPulse" 
 
Proto4z.register(2002,"LoadServiceInDocker") 
Proto4z.LoadServiceInDocker = {} --在Docker中装载一个Service 
Proto4z.LoadServiceInDocker.__protoID = 2002 
Proto4z.LoadServiceInDocker.__protoName = "LoadServiceInDocker" 
Proto4z.LoadServiceInDocker[1] = {name="serviceType", type="ui16" }  
Proto4z.LoadServiceInDocker[2] = {name="serviceID", type="ui64" }  
Proto4z.LoadServiceInDocker[3] = {name="serviceName", type="string" }  
Proto4z.LoadServiceInDocker[4] = {name="clientDockerID", type="ui32" }  
Proto4z.LoadServiceInDocker[5] = {name="clientSessionID", type="ui32" }  
 
Proto4z.register(2013,"ShellServiceInfo") 
Proto4z.ShellServiceInfo = {} --Service被装载或者属性更改,需要通知给其他Docker的信息 
Proto4z.ShellServiceInfo.__protoID = 2013 
Proto4z.ShellServiceInfo.__protoName = "ShellServiceInfo" 
Proto4z.ShellServiceInfo[1] = {name="serviceDockerID", type="ui32" }  
Proto4z.ShellServiceInfo[2] = {name="serviceType", type="ui16" }  
Proto4z.ShellServiceInfo[3] = {name="serviceID", type="ui64" }  
Proto4z.ShellServiceInfo[4] = {name="serviceName", type="string" }  
Proto4z.ShellServiceInfo[5] = {name="status", type="ui16" }  
Proto4z.ShellServiceInfo[6] = {name="clientDockerID", type="ui32" }  
Proto4z.ShellServiceInfo[7] = {name="clientSessionID", type="ui32" }  
 
Proto4z.ShellServiceInfoArray = {}  
Proto4z.ShellServiceInfoArray.__protoName = "ShellServiceInfoArray" 
Proto4z.ShellServiceInfoArray.__protoDesc = "array" 
Proto4z.ShellServiceInfoArray.__protoTypeV = "ShellServiceInfo" 
 
Proto4z.register(2003,"LoadServiceNotice") 
Proto4z.LoadServiceNotice = {} --通知其他Docker有Service已装载 
Proto4z.LoadServiceNotice.__protoID = 2003 
Proto4z.LoadServiceNotice.__protoName = "LoadServiceNotice" 
Proto4z.LoadServiceNotice[1] = {name="shellServiceInfos", type="ShellServiceInfoArray" }  
 
Proto4z.register(2004,"RefreshServiceToMgrNotice") 
Proto4z.RefreshServiceToMgrNotice = {} --Multi-Servie发生状态变化时候通知给管理器 
Proto4z.RefreshServiceToMgrNotice.__protoID = 2004 
Proto4z.RefreshServiceToMgrNotice.__protoName = "RefreshServiceToMgrNotice" 
Proto4z.RefreshServiceToMgrNotice[1] = {name="shellServiceInfos", type="ShellServiceInfoArray" }  
 
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
 
Proto4z.DBStringArray = {}  
Proto4z.DBStringArray.__protoName = "DBStringArray" 
Proto4z.DBStringArray.__protoDesc = "array" 
Proto4z.DBStringArray.__protoTypeV = "string" 
 
Proto4z.register(2015,"DBDataResult") 
Proto4z.DBDataResult = {}  
Proto4z.DBDataResult.__protoID = 2015 
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
 
Proto4z.register(2016,"DBQueryReq") 
Proto4z.DBQueryReq = {} --通用SQL语句执行协议 
Proto4z.DBQueryReq.__protoID = 2016 
Proto4z.DBQueryReq.__protoName = "DBQueryReq" 
Proto4z.DBQueryReq[1] = {name="sql", type="string" }  
 
Proto4z.register(2017,"DBQueryResp") 
Proto4z.DBQueryResp = {} --通用SQL语句执行协议返回,DBDataResult可以借助dbHepler进行构建DBResult 
Proto4z.DBQueryResp.__protoID = 2017 
Proto4z.DBQueryResp.__protoName = "DBQueryResp" 
Proto4z.DBQueryResp[1] = {name="retCode", type="ui16" }  
Proto4z.DBQueryResp[2] = {name="result", type="DBDataResult" }  
 
Proto4z.register(2018,"DBQueryArrayReq") 
Proto4z.DBQueryArrayReq = {} --通用批量SQL语句执行协议 
Proto4z.DBQueryArrayReq.__protoID = 2018 
Proto4z.DBQueryArrayReq.__protoName = "DBQueryArrayReq" 
Proto4z.DBQueryArrayReq[1] = {name="sqls", type="DBStringArray" }  
 
Proto4z.register(2019,"DBQueryArrayResp") 
Proto4z.DBQueryArrayResp = {} --通用批量SQL语句执行协议 
Proto4z.DBQueryArrayResp.__protoID = 2019 
Proto4z.DBQueryArrayResp.__protoName = "DBQueryArrayResp" 
Proto4z.DBQueryArrayResp[1] = {name="retCode", type="ui16" }  
Proto4z.DBQueryArrayResp[2] = {name="results", type="DBDataResultArray" } --批量返回,注意不要超出协议包最大长度 
 
Proto4z.WebAgentHead = {}  
Proto4z.WebAgentHead.__protoName = "WebAgentHead" 
Proto4z.WebAgentHead.__protoDesc = "map" 
Proto4z.WebAgentHead.__protoTypeK = "string" 
Proto4z.WebAgentHead.__protoTypeV = "string" 
 
Proto4z.register(2020,"WebAgentClientRequestAPI") 
Proto4z.WebAgentClientRequestAPI = {}  
Proto4z.WebAgentClientRequestAPI.__protoID = 2020 
Proto4z.WebAgentClientRequestAPI.__protoName = "WebAgentClientRequestAPI" 
Proto4z.WebAgentClientRequestAPI[1] = {name="webClientID", type="ui32" }  
Proto4z.WebAgentClientRequestAPI[2] = {name="method", type="string" }  
Proto4z.WebAgentClientRequestAPI[3] = {name="methodLine", type="string" }  
Proto4z.WebAgentClientRequestAPI[4] = {name="heads", type="WebAgentHead" }  
Proto4z.WebAgentClientRequestAPI[5] = {name="body", type="string" }  
 
Proto4z.register(2021,"WebServerRequest") 
Proto4z.WebServerRequest = {}  
Proto4z.WebServerRequest.__protoID = 2021 
Proto4z.WebServerRequest.__protoName = "WebServerRequest" 
Proto4z.WebServerRequest[1] = {name="fromServiceType", type="ui32" }  
Proto4z.WebServerRequest[2] = {name="fromServiceID", type="ui64" }  
Proto4z.WebServerRequest[3] = {name="traceID", type="ui32" }  
Proto4z.WebServerRequest[4] = {name="ip", type="string" }  
Proto4z.WebServerRequest[5] = {name="port", type="ui16" }  
Proto4z.WebServerRequest[6] = {name="host", type="string" }  
Proto4z.WebServerRequest[7] = {name="uri", type="string" }  
Proto4z.WebServerRequest[8] = {name="params", type="string" }  
Proto4z.WebServerRequest[9] = {name="heads", type="WebAgentHead" }  
Proto4z.WebServerRequest[10] = {name="isGet", type="ui8" } --get or post 
 
Proto4z.register(2022,"WebServerResponse") 
Proto4z.WebServerResponse = {}  
Proto4z.WebServerResponse.__protoID = 2022 
Proto4z.WebServerResponse.__protoName = "WebServerResponse" 
Proto4z.WebServerResponse[1] = {name="method", type="string" }  
Proto4z.WebServerResponse[2] = {name="methodLine", type="string" }  
Proto4z.WebServerResponse[3] = {name="heads", type="WebAgentHead" }  
Proto4z.WebServerResponse[4] = {name="body", type="string" }  
 
Proto4z.register(2023,"UserOffline") 
Proto4z.UserOffline = {}  
Proto4z.UserOffline.__protoID = 2023 
Proto4z.UserOffline.__protoName = "UserOffline" 
Proto4z.UserOffline[1] = {name="id", type="ui64" }  
Proto4z.UserOffline[2] = {name="userID", type="ui64" }  
Proto4z.UserOffline[3] = {name="streamBlob", type="string" }  
Proto4z.UserOffline[4] = {name="status", type="ui16" }  
Proto4z.UserOffline[5] = {name="timestamp", type="ui64" }  

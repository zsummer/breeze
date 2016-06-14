 
Proto4z.WebAgentHead = {}  
Proto4z.WebAgentHead.__protoName = "WebAgentHead" 
Proto4z.WebAgentHead.__protoDesc = "map" 
Proto4z.WebAgentHead.__protoTypeK = "string" 
Proto4z.WebAgentHead.__protoTypeV = "string" 
 
Proto4z.register(5105,"WebAgentClientRequestAPI") 
Proto4z.WebAgentClientRequestAPI = {}  
Proto4z.WebAgentClientRequestAPI.__protoID = 5105 
Proto4z.WebAgentClientRequestAPI.__protoName = "WebAgentClientRequestAPI" 
Proto4z.WebAgentClientRequestAPI[1] = {name="webClientID", type="ui32" }  
Proto4z.WebAgentClientRequestAPI[2] = {name="method", type="string" }  
Proto4z.WebAgentClientRequestAPI[3] = {name="methodLine", type="string" }  
Proto4z.WebAgentClientRequestAPI[4] = {name="heads", type="WebAgentHead" }  
Proto4z.WebAgentClientRequestAPI[5] = {name="body", type="string" }  
 
Proto4z.register(5106,"WebServerRequest") 
Proto4z.WebServerRequest = {}  
Proto4z.WebServerRequest.__protoID = 5106 
Proto4z.WebServerRequest.__protoName = "WebServerRequest" 
Proto4z.WebServerRequest[1] = {name="fromServiceType", type="ui32" }  
Proto4z.WebServerRequest[2] = {name="fromServiceID", type="ui64" }  
Proto4z.WebServerRequest[3] = {name="traceID", type="ui32" }  
Proto4z.WebServerRequest[4] = {name="ip", type="string" }  
Proto4z.WebServerRequest[5] = {name="port", type="ui16" }  
Proto4z.WebServerRequest[6] = {name="uri", type="string" }  
Proto4z.WebServerRequest[7] = {name="params", type="string" }  
Proto4z.WebServerRequest[8] = {name="heads", type="WebAgentHead" }  
Proto4z.WebServerRequest[9] = {name="isGet", type="ui8" } --get or post 
 
Proto4z.register(5107,"WebServerResponse") 
Proto4z.WebServerResponse = {}  
Proto4z.WebServerResponse.__protoID = 5107 
Proto4z.WebServerResponse.__protoName = "WebServerResponse" 
Proto4z.WebServerResponse[1] = {name="method", type="string" }  
Proto4z.WebServerResponse[2] = {name="methodLine", type="string" }  
Proto4z.WebServerResponse[3] = {name="heads", type="WebAgentHead" }  
Proto4z.WebServerResponse[4] = {name="body", type="string" }  

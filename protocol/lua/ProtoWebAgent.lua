 
Proto4z.WebAgentHead = {}  
Proto4z.WebAgentHead.__protoName = "WebAgentHead" 
Proto4z.WebAgentHead.__protoDesc = "map" 
Proto4z.WebAgentHead.__protoTypeK = "string" 
Proto4z.WebAgentHead.__protoTypeV = "string" 
 
Proto4z.register(5100,"WebAgentToService") 
Proto4z.WebAgentToService = {}  
Proto4z.WebAgentToService.__protoID = 5100 
Proto4z.WebAgentToService.__protoName = "WebAgentToService" 
Proto4z.WebAgentToService[1] = {name="webClientID", type="ui32" }  
Proto4z.WebAgentToService[2] = {name="method", type="string" }  
Proto4z.WebAgentToService[3] = {name="methodLine", type="string" }  
Proto4z.WebAgentToService[4] = {name="heads", type="WebAgentHead" }  
Proto4z.WebAgentToService[5] = {name="body", type="string" }  
 
Proto4z.register(5101,"WebAgentToClient") 
Proto4z.WebAgentToClient = {}  
Proto4z.WebAgentToClient.__protoID = 5101 
Proto4z.WebAgentToClient.__protoName = "WebAgentToClient" 
Proto4z.WebAgentToClient[1] = {name="method", type="string" }  
Proto4z.WebAgentToClient[2] = {name="methodLine", type="string" }  
Proto4z.WebAgentToClient[3] = {name="heads", type="WebAgentHead" }  
Proto4z.WebAgentToClient[4] = {name="body", type="string" }  

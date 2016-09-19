 
Proto4z.SceneTypeArray = {}  
Proto4z.SceneTypeArray.__protoName = "SceneTypeArray" 
Proto4z.SceneTypeArray.__protoDesc = "array" 
Proto4z.SceneTypeArray.__protoTypeV = "ui16" 
 
Proto4z.register(39004,"SceneKnock") 
Proto4z.SceneKnock = {} --战场服务器挂载 
Proto4z.SceneKnock.__protoID = 39004 
Proto4z.SceneKnock.__protoName = "SceneKnock" 
Proto4z.SceneKnock[1] = {name="lineID", type="ui32" } --分线ID 
Proto4z.SceneKnock[2] = {name="pubHost", type="string" }  
Proto4z.SceneKnock[3] = {name="pubPort", type="ui16" }  
 
Proto4z.register(39005,"ScenePulse") 
Proto4z.ScenePulse = {} --集群脉冲 
Proto4z.ScenePulse.__protoID = 39005 
Proto4z.ScenePulse.__protoName = "ScenePulse" 
 
Proto4z.register(39000,"AllocateSceneReq") 
Proto4z.AllocateSceneReq = {} --分配战场 
Proto4z.AllocateSceneReq.__protoID = 39000 
Proto4z.AllocateSceneReq.__protoName = "AllocateSceneReq" 
Proto4z.AllocateSceneReq[1] = {name="sceneType", type="ui16" } --类型 
Proto4z.AllocateSceneReq[2] = {name="mapID", type="ui32" }  
Proto4z.AllocateSceneReq[3] = {name="involeds", type="AvatarBaseInfoArray" } --匹配列表中的玩家 
 
Proto4z.register(39001,"AllocateSceneResp") 
Proto4z.AllocateSceneResp = {} --分配战场 
Proto4z.AllocateSceneResp.__protoID = 39001 
Proto4z.AllocateSceneResp.__protoName = "AllocateSceneResp" 
Proto4z.AllocateSceneResp[1] = {name="retCode", type="ui16" }  
Proto4z.AllocateSceneResp[2] = {name="tokens", type="SceneTokenInfoArray" } --匹配列表中的玩家 

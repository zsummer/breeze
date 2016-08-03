 
Proto4z.register(39000,"AllocateSceneReq") 
Proto4z.AllocateSceneReq = {} --分配新战场 
Proto4z.AllocateSceneReq.__protoID = 39000 
Proto4z.AllocateSceneReq.__protoName = "AllocateSceneReq" 
Proto4z.AllocateSceneReq[1] = {name="sceneType", type="ui16" } --类型 
Proto4z.AllocateSceneReq[2] = {name="mapID", type="ui32" }  
Proto4z.AllocateSceneReq[3] = {name="involeds", type="AvatarBaseInfoArray" } --匹配列表中的玩家 
 
Proto4z.register(39001,"AllocateSceneResp") 
Proto4z.AllocateSceneResp = {} --分配新战场 
Proto4z.AllocateSceneResp.__protoID = 39001 
Proto4z.AllocateSceneResp.__protoName = "AllocateSceneResp" 
Proto4z.AllocateSceneResp[1] = {name="retCode", type="ui16" }  
Proto4z.AllocateSceneResp[2] = {name="tokens", type="SceneTokenInfoArray" } --匹配列表中的玩家 

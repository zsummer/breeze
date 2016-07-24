 
Proto4z.register(39015,"AllocateSpaceReq") 
Proto4z.AllocateSpaceReq = {} --分配新战场 
Proto4z.AllocateSpaceReq.__protoID = 39015 
Proto4z.AllocateSpaceReq.__protoName = "AllocateSpaceReq" 
Proto4z.AllocateSpaceReq[1] = {name="spaceType", type="ui16" } --类型 
Proto4z.AllocateSpaceReq[2] = {name="mapID", type="ui32" }  
Proto4z.AllocateSpaceReq[3] = {name="involeds", type="UserBaseInfoArray" } --匹配列表中的玩家 
 
Proto4z.register(39016,"AllocateSpaceResp") 
Proto4z.AllocateSpaceResp = {} --分配新战场 
Proto4z.AllocateSpaceResp.__protoID = 39016 
Proto4z.AllocateSpaceResp.__protoName = "AllocateSpaceResp" 
Proto4z.AllocateSpaceResp[1] = {name="retCode", type="ui16" }  
Proto4z.AllocateSpaceResp[2] = {name="tokens", type="SpaceTokenInfoArray" } --匹配列表中的玩家 

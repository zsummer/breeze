 
Proto4z.register(39010,"SpaceInfoToWorldNotice") 
Proto4z.SpaceInfoToWorldNotice = {} --数据刷给world 
Proto4z.SpaceInfoToWorldNotice.__protoID = 39010 
Proto4z.SpaceInfoToWorldNotice.__protoName = "SpaceInfoToWorldNotice" 
Proto4z.SpaceInfoToWorldNotice[1] = {name="host", type="string" } --服务器host 
Proto4z.SpaceInfoToWorldNotice[2] = {name="port", type="ui16" } --服务器port 
Proto4z.SpaceInfoToWorldNotice[3] = {name="spaceInfos", type="SpaceInfoArray" } --类型 
 
Proto4z.register(39013,"FillUserToSpaceReq") 
Proto4z.FillUserToSpaceReq = {} --token丢给space 
Proto4z.FillUserToSpaceReq.__protoID = 39013 
Proto4z.FillUserToSpaceReq.__protoName = "FillUserToSpaceReq" 
Proto4z.FillUserToSpaceReq[1] = {name="spaceID", type="SpaceID" } --id 
Proto4z.FillUserToSpaceReq[2] = {name="sceneType", type="ui16" } --类型 
Proto4z.FillUserToSpaceReq[3] = {name="token", type="string" } --服务器port 
Proto4z.FillUserToSpaceReq[4] = {name="baseInfo", type="UserBaseInfo" } --类型 
 
Proto4z.register(39014,"FillUserToSpaceResp") 
Proto4z.FillUserToSpaceResp = {} --token丢给space 
Proto4z.FillUserToSpaceResp.__protoID = 39014 
Proto4z.FillUserToSpaceResp.__protoName = "FillUserToSpaceResp" 
Proto4z.FillUserToSpaceResp[1] = {name="userID", type="ui64" }  
Proto4z.FillUserToSpaceResp[2] = {name="spaceID", type="SpaceID" } --id 
Proto4z.FillUserToSpaceResp[3] = {name="sceneType", type="ui16" } --类型 

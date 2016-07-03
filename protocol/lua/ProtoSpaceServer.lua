 
Proto4z.register(39010,"SpaceInfoToWorldNotice") 
Proto4z.SpaceInfoToWorldNotice = {} --数据刷给world 
Proto4z.SpaceInfoToWorldNotice.__protoID = 39010 
Proto4z.SpaceInfoToWorldNotice.__protoName = "SpaceInfoToWorldNotice" 
Proto4z.SpaceInfoToWorldNotice[1] = {name="host", type="string" } --服务器host 
Proto4z.SpaceInfoToWorldNotice[2] = {name="port", type="ui16" } --服务器port 
Proto4z.SpaceInfoToWorldNotice[3] = {name="spaceInfos", type="SpaceInfoArray" } --类型 
 
Proto4z.register(39012,"FillUserToSpaceNotice") 
Proto4z.FillUserToSpaceNotice = {} --token丢给space 
Proto4z.FillUserToSpaceNotice.__protoID = 39012 
Proto4z.FillUserToSpaceNotice.__protoName = "FillUserToSpaceNotice" 
Proto4z.FillUserToSpaceNotice[1] = {name="userID", type="ui64" }  
Proto4z.FillUserToSpaceNotice[2] = {name="token", type="string" } --服务器port 
Proto4z.FillUserToSpaceNotice[3] = {name="spaceID", type="SpaceID" } --类型 
Proto4z.FillUserToSpaceNotice[4] = {name="baseInfo", type="UserBaseInfo" } --类型 
Proto4z.FillUserToSpaceNotice[5] = {name="effects", type="FightEffect" } --类型 

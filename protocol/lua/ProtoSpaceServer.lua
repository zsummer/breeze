 
Proto4z.register(39000,"WorldSceneInfoReq") 
Proto4z.WorldSceneInfoReq = {} --获取场景信息 
Proto4z.WorldSceneInfoReq.__protoID = 39000 
Proto4z.WorldSceneInfoReq.__protoName = "WorldSceneInfoReq" 
Proto4z.WorldSceneInfoReq[1] = {name="userID", type="ui64" }  
 
Proto4z.register(39001,"WorldSceneInfoAck") 
Proto4z.WorldSceneInfoAck = {} --获取场景信息 
Proto4z.WorldSceneInfoAck.__protoID = 39001 
Proto4z.WorldSceneInfoAck.__protoName = "WorldSceneInfoAck" 
Proto4z.WorldSceneInfoAck[1] = {name="retCode", type="ui16" } --错误码 
Proto4z.WorldSceneInfoAck[2] = {name="userID", type="ui64" }  
Proto4z.WorldSceneInfoAck[3] = {name="scenes", type="SceneInfoArray" }  
 
Proto4z.register(39002,"WorldTryEnterSceneReq") 
Proto4z.WorldTryEnterSceneReq = {} --进入场景 
Proto4z.WorldTryEnterSceneReq.__protoID = 39002 
Proto4z.WorldTryEnterSceneReq.__protoName = "WorldTryEnterSceneReq" 
Proto4z.WorldTryEnterSceneReq[1] = {name="userID", type="ui64" }  
Proto4z.WorldTryEnterSceneReq[2] = {name="type", type="ui16" } --类型, 如果是不同类型,该请求会触发场景切换动作 
 
Proto4z.register(39003,"WorldTryEnterSceneAck") 
Proto4z.WorldTryEnterSceneAck = {} --进入场景 
Proto4z.WorldTryEnterSceneAck.__protoID = 39003 
Proto4z.WorldTryEnterSceneAck.__protoName = "WorldTryEnterSceneAck" 
Proto4z.WorldTryEnterSceneAck[1] = {name="retCode", type="ui16" } --错误码 
Proto4z.WorldTryEnterSceneAck[2] = {name="userID", type="ui64" }  
Proto4z.WorldTryEnterSceneAck[3] = {name="scenes", type="SceneInfoArray" } --要检查状态, 如果是主城则状态会直接切换为INSTACING, 如果是需要匹配的 状态为匹配中 
 
Proto4z.register(39004,"WorldSceneInfoNotice") 
Proto4z.WorldSceneInfoNotice = {} --场景信息刷新,如果是匹配模式, 需要扩展当前匹配信息到该协议中 
Proto4z.WorldSceneInfoNotice.__protoID = 39004 
Proto4z.WorldSceneInfoNotice.__protoName = "WorldSceneInfoNotice" 
Proto4z.WorldSceneInfoNotice[1] = {name="retCode", type="ui16" } --错误码 
Proto4z.WorldSceneInfoNotice[2] = {name="userID", type="ui64" }  
Proto4z.WorldSceneInfoNotice[3] = {name="scenes", type="SceneInfoArray" } --要检查状态, 如果是主城则状态会置换为INSTACING, 如果是需要匹配的 状态为匹配中 
 
Proto4z.register(39005,"WorldLeaveSceneReq") 
Proto4z.WorldLeaveSceneReq = {} --离开场景 
Proto4z.WorldLeaveSceneReq.__protoID = 39005 
Proto4z.WorldLeaveSceneReq.__protoName = "WorldLeaveSceneReq" 
Proto4z.WorldLeaveSceneReq[1] = {name="userID", type="ui64" }  
Proto4z.WorldLeaveSceneReq[2] = {name="type", type="ui16" } --类型 
 
Proto4z.register(39006,"WorldLeaveSceneAck") 
Proto4z.WorldLeaveSceneAck = {} --离开场景 
Proto4z.WorldLeaveSceneAck.__protoID = 39006 
Proto4z.WorldLeaveSceneAck.__protoName = "WorldLeaveSceneAck" 
Proto4z.WorldLeaveSceneAck[1] = {name="retCode", type="ui16" } --错误码 
Proto4z.WorldLeaveSceneAck[2] = {name="userID", type="ui64" }  
Proto4z.WorldLeaveSceneAck[3] = {name="scenes", type="SceneInfoArray" } --要检查状态, 如果是主城则状态会置换为INSTACING, 如果是需要匹配的 状态为匹配中 
 
Proto4z.register(39007,"WorldQuitSceneReq") 
Proto4z.WorldQuitSceneReq = {} --退出场景 
Proto4z.WorldQuitSceneReq.__protoID = 39007 
Proto4z.WorldQuitSceneReq.__protoName = "WorldQuitSceneReq" 
Proto4z.WorldQuitSceneReq[1] = {name="userID", type="ui64" }  
Proto4z.WorldQuitSceneReq[2] = {name="type", type="ui16" } --类型 
 
Proto4z.register(39008,"WorldQuitSceneAck") 
Proto4z.WorldQuitSceneAck = {} --退出场景 
Proto4z.WorldQuitSceneAck.__protoID = 39008 
Proto4z.WorldQuitSceneAck.__protoName = "WorldQuitSceneAck" 
Proto4z.WorldQuitSceneAck[1] = {name="retCode", type="ui16" } --错误码 
Proto4z.WorldQuitSceneAck[2] = {name="userID", type="ui64" }  
Proto4z.WorldQuitSceneAck[3] = {name="scenes", type="SceneInfoArray" } --要检查状态, 如果是主城则状态会置换为INSTACING, 如果是需要匹配的 状态为匹配中 
 
Proto4z.register(39010,"SpaceInfoToWorldNotice") 
Proto4z.SpaceInfoToWorldNotice = {} --数据刷给world 
Proto4z.SpaceInfoToWorldNotice.__protoID = 39010 
Proto4z.SpaceInfoToWorldNotice.__protoName = "SpaceInfoToWorldNotice" 
Proto4z.SpaceInfoToWorldNotice[1] = {name="host", type="string" } --服务器host 
Proto4z.SpaceInfoToWorldNotice[2] = {name="port", type="ui16" } --服务器port 
Proto4z.SpaceInfoToWorldNotice[3] = {name="spaceInfos", type="SpaceInfoArray" } --类型 
 
Proto4z.register(39011,"TokenInfoToSpaceNotice") 
Proto4z.TokenInfoToSpaceNotice = {} --token丢给space 
Proto4z.TokenInfoToSpaceNotice.__protoID = 39011 
Proto4z.TokenInfoToSpaceNotice.__protoName = "TokenInfoToSpaceNotice" 
Proto4z.TokenInfoToSpaceNotice[1] = {name="userID", type="ui64" }  
Proto4z.TokenInfoToSpaceNotice[2] = {name="token", type="string" } --服务器port 
Proto4z.TokenInfoToSpaceNotice[3] = {name="spaceID", type="SpaceID" } --类型 
Proto4z.TokenInfoToSpaceNotice[4] = {name="baseInfo", type="UserBaseInfo" } --类型 
Proto4z.TokenInfoToSpaceNotice[5] = {name="effects", type="FightEffect" } --类型 

 
Proto4z.register(50000,"SceneInfoReq") 
Proto4z.SceneInfoReq = {} --获取场景信息 
Proto4z.SceneInfoReq.__protoID = 50000 
Proto4z.SceneInfoReq.__protoName = "SceneInfoReq" 
 
Proto4z.register(50001,"SceneInfoAck") 
Proto4z.SceneInfoAck = {} --获取场景信息 
Proto4z.SceneInfoAck.__protoID = 50001 
Proto4z.SceneInfoAck.__protoName = "SceneInfoAck" 
Proto4z.SceneInfoAck[1] = {name="retCode", type="ui16" } --错误码 
Proto4z.SceneInfoAck[2] = {name="scenes", type="SceneInfoArray" }  
 
Proto4z.register(50002,"TryEnterSceneReq") 
Proto4z.TryEnterSceneReq = {} --进入场景 
Proto4z.TryEnterSceneReq.__protoID = 50002 
Proto4z.TryEnterSceneReq.__protoName = "TryEnterSceneReq" 
Proto4z.TryEnterSceneReq[1] = {name="type", type="ui16" } --类型, 如果是不同类型,该请求会触发场景切换动作 
 
Proto4z.register(50003,"TryEnterSceneAck") 
Proto4z.TryEnterSceneAck = {} --进入场景 
Proto4z.TryEnterSceneAck.__protoID = 50003 
Proto4z.TryEnterSceneAck.__protoName = "TryEnterSceneAck" 
Proto4z.TryEnterSceneAck[1] = {name="retCode", type="ui16" } --错误码 
Proto4z.TryEnterSceneAck[2] = {name="scenes", type="SceneInfoArray" } --要检查状态, 如果是主城则状态会置换为INSTACING, 如果是需要匹配的 状态为匹配中 
 
Proto4z.register(50004,"SceneInfoNotice") 
Proto4z.SceneInfoNotice = {} --场景信息刷新,如果是匹配模式, 需要扩展当前匹配信息到该协议中 
Proto4z.SceneInfoNotice.__protoID = 50004 
Proto4z.SceneInfoNotice.__protoName = "SceneInfoNotice" 
Proto4z.SceneInfoNotice[1] = {name="retCode", type="ui16" } --错误码 
Proto4z.SceneInfoNotice[2] = {name="scenes", type="SceneInfoArray" } --要检查状态, 如果是主城则状态会置换为INSTACING, 如果是需要匹配的 状态为匹配中 
 
Proto4z.register(50005,"LeaveSceneReq") 
Proto4z.LeaveSceneReq = {} --离开场景 
Proto4z.LeaveSceneReq.__protoID = 50005 
Proto4z.LeaveSceneReq.__protoName = "LeaveSceneReq" 
Proto4z.LeaveSceneReq[1] = {name="type", type="ui16" } --类型 
 
Proto4z.register(50006,"LeaveSceneAck") 
Proto4z.LeaveSceneAck = {} --离开场景 
Proto4z.LeaveSceneAck.__protoID = 50006 
Proto4z.LeaveSceneAck.__protoName = "LeaveSceneAck" 
Proto4z.LeaveSceneAck[1] = {name="retCode", type="ui16" } --错误码 
Proto4z.LeaveSceneAck[2] = {name="scenes", type="SceneInfoArray" } --要检查状态, 如果是主城则状态会置换为INSTACING, 如果是需要匹配的 状态为匹配中 
 
Proto4z.register(50007,"QuitSceneReq") 
Proto4z.QuitSceneReq = {} --退出场景 
Proto4z.QuitSceneReq.__protoID = 50007 
Proto4z.QuitSceneReq.__protoName = "QuitSceneReq" 
Proto4z.QuitSceneReq[1] = {name="type", type="ui16" } --类型 
 
Proto4z.register(50008,"QuitSceneAck") 
Proto4z.QuitSceneAck = {} --退出场景 
Proto4z.QuitSceneAck.__protoID = 50008 
Proto4z.QuitSceneAck.__protoName = "QuitSceneAck" 
Proto4z.QuitSceneAck[1] = {name="retCode", type="ui16" } --错误码 
Proto4z.QuitSceneAck[2] = {name="scenes", type="SceneInfoArray" } --要检查状态, 如果是主城则状态会置换为INSTACING, 如果是需要匹配的 状态为匹配中 

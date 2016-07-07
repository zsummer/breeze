 
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
 
Proto4z.register(50009,"FillSpaceNotice") 
Proto4z.FillSpaceNotice = {} --填充场景数据 
Proto4z.FillSpaceNotice.__protoID = 50009 
Proto4z.FillSpaceNotice.__protoName = "FillSpaceNotice" 
Proto4z.FillSpaceNotice[1] = {name="entitys", type="EntityFullInfoArray" } --这里包含有所有当前场景下的实体属性和状态数据 
Proto4z.FillSpaceNotice[2] = {name="spaceStartTime", type="double" } --服务器战场开始时间 
Proto4z.FillSpaceNotice[3] = {name="spaceEndTime", type="double" } --服务器战场结束时间 
Proto4z.FillSpaceNotice[4] = {name="serverTime", type="double" } --服务器当前时间 
 
Proto4z.register(50010,"RefreshSpaceNotice") 
Proto4z.RefreshSpaceNotice = {} --增量更新场景中的实体数据, 服务器定时100ms广播 
Proto4z.RefreshSpaceNotice.__protoID = 50010 
Proto4z.RefreshSpaceNotice.__protoName = "RefreshSpaceNotice" 
Proto4z.RefreshSpaceNotice[1] = {name="entitys", type="EntityInfoArray" }  
Proto4z.RefreshSpaceNotice[2] = {name="reports", type="EntityReportArray" }  
Proto4z.RefreshSpaceNotice[3] = {name="serverTime", type="double" } --服务器当前时间 
 
Proto4z.register(50011,"AddEntityNotice") 
Proto4z.AddEntityNotice = {} --一批实体加入场景时, 把这些实体的数据广播给其他玩家 
Proto4z.AddEntityNotice.__protoID = 50011 
Proto4z.AddEntityNotice.__protoName = "AddEntityNotice" 
Proto4z.AddEntityNotice[1] = {name="entitys", type="EntityFullInfoArray" }  
Proto4z.AddEntityNotice[2] = {name="serverTime", type="double" } --服务器当前时间 
 
Proto4z.register(50012,"RemoveEntityNotice") 
Proto4z.RemoveEntityNotice = {} --实体离开场景时, 把该实体的数据广播给其他玩家 
Proto4z.RemoveEntityNotice.__protoID = 50012 
Proto4z.RemoveEntityNotice.__protoName = "RemoveEntityNotice" 
Proto4z.RemoveEntityNotice[1] = {name="eids", type="EntityIDArray" }  
Proto4z.RemoveEntityNotice[2] = {name="serverTime", type="double" } --服务器当前时间 

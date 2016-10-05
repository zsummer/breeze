 
Proto4z.register(39000,"SceneKnock") 
Proto4z.SceneKnock = {} --战场服务器挂载 
Proto4z.SceneKnock.__protoID = 39000 
Proto4z.SceneKnock.__protoName = "SceneKnock" 
Proto4z.SceneKnock[1] = {name="lineID", type="ui64" } --分线ID 
Proto4z.SceneKnock[2] = {name="pubHost", type="string" }  
Proto4z.SceneKnock[3] = {name="pubPort", type="ui16" }  
 
Proto4z.register(39001,"ScenePulse") 
Proto4z.ScenePulse = {} --集群脉冲 
Proto4z.ScenePulse.__protoID = 39001 
Proto4z.ScenePulse.__protoName = "ScenePulse" 
 
Proto4z.register(39002,"SceneServerJoinGroupIns") 
Proto4z.SceneServerJoinGroupIns = {} --创建/加入编队, 来自docker的指令 
Proto4z.SceneServerJoinGroupIns.__protoID = 39002 
Proto4z.SceneServerJoinGroupIns.__protoName = "SceneServerJoinGroupIns" 
Proto4z.SceneServerJoinGroupIns[1] = {name="groupID", type="ui64" } --编队ID, 0为创建 
Proto4z.SceneServerJoinGroupIns[2] = {name="baseInfo", type="AvatarBaseInfo" } --角色数据 
 
Proto4z.register(39003,"ApplyForSceneServerReq") 
Proto4z.ApplyForSceneServerReq = {} --请求战场 
Proto4z.ApplyForSceneServerReq.__protoID = 39003 
Proto4z.ApplyForSceneServerReq.__protoName = "ApplyForSceneServerReq" 
Proto4z.ApplyForSceneServerReq[1] = {name="sceneType", type="ui16" } --类型 
Proto4z.ApplyForSceneServerReq[2] = {name="mapID", type="ui64" }  
Proto4z.ApplyForSceneServerReq[3] = {name="avatars", type="AvatarBaseInfoArray" } --匹配列表中的玩家 
 
Proto4z.register(39004,"FeedbackAvatarStatusNotice") 
Proto4z.FeedbackAvatarStatusNotice = {} --scene ==> world 
Proto4z.FeedbackAvatarStatusNotice.__protoID = 39004 
Proto4z.FeedbackAvatarStatusNotice.__protoName = "FeedbackAvatarStatusNotice" 
Proto4z.FeedbackAvatarStatusNotice[1] = {name="avatarID", type="ui64" }  
Proto4z.FeedbackAvatarStatusNotice[2] = {name="status", type="ui16" }  
Proto4z.FeedbackAvatarStatusNotice[3] = {name="token", type="string" }  

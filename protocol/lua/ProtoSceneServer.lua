 
Proto4z.SceneTypeArray = {}  
Proto4z.SceneTypeArray.__protoName = "SceneTypeArray" 
Proto4z.SceneTypeArray.__protoDesc = "array" 
Proto4z.SceneTypeArray.__protoTypeV = "ui16" 
 
Proto4z.register(39008,"SceneKnock") 
Proto4z.SceneKnock = {} --战场服务器挂载 
Proto4z.SceneKnock.__protoID = 39008 
Proto4z.SceneKnock.__protoName = "SceneKnock" 
Proto4z.SceneKnock[1] = {name="lineID", type="ui64" } --分线ID 
Proto4z.SceneKnock[2] = {name="pubHost", type="string" }  
Proto4z.SceneKnock[3] = {name="pubPort", type="ui16" }  
 
Proto4z.register(39009,"ScenePulse") 
Proto4z.ScenePulse = {} --集群脉冲 
Proto4z.ScenePulse.__protoID = 39009 
Proto4z.ScenePulse.__protoName = "ScenePulse" 
 
Proto4z.register(39010,"ApplyForSceneServerReq") 
Proto4z.ApplyForSceneServerReq = {} --请求战场 
Proto4z.ApplyForSceneServerReq.__protoID = 39010 
Proto4z.ApplyForSceneServerReq.__protoName = "ApplyForSceneServerReq" 
Proto4z.ApplyForSceneServerReq[1] = {name="sceneType", type="ui16" } --类型 
Proto4z.ApplyForSceneServerReq[2] = {name="mapID", type="ui64" }  
Proto4z.ApplyForSceneServerReq[3] = {name="avatars", type="AvatarBaseInfoArray" } --匹配列表中的玩家 
 
Proto4z.register(39011,"FeedbackAvatarStatusNotice") 
Proto4z.FeedbackAvatarStatusNotice = {} --scene ==> world 
Proto4z.FeedbackAvatarStatusNotice.__protoID = 39011 
Proto4z.FeedbackAvatarStatusNotice.__protoName = "FeedbackAvatarStatusNotice" 
Proto4z.FeedbackAvatarStatusNotice[1] = {name="avatarID", type="ui64" }  
Proto4z.FeedbackAvatarStatusNotice[2] = {name="status", type="ui16" }  
Proto4z.FeedbackAvatarStatusNotice[3] = {name="token", type="string" }  

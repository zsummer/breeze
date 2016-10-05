 
Proto4z.register(40034,"ClientPulse") 
Proto4z.ClientPulse = {} --客户端脉冲请求 
Proto4z.ClientPulse.__protoID = 40034 
Proto4z.ClientPulse.__protoName = "ClientPulse" 
 
Proto4z.register(40035,"ClientAuthReq") 
Proto4z.ClientAuthReq = {} --认证请求 
Proto4z.ClientAuthReq.__protoID = 40035 
Proto4z.ClientAuthReq.__protoName = "ClientAuthReq" 
Proto4z.ClientAuthReq[1] = {name="account", type="string" }  
Proto4z.ClientAuthReq[2] = {name="token", type="string" }  
 
Proto4z.register(40036,"ClientAuthResp") 
Proto4z.ClientAuthResp = {} --认证返回 
Proto4z.ClientAuthResp.__protoID = 40036 
Proto4z.ClientAuthResp.__protoName = "ClientAuthResp" 
Proto4z.ClientAuthResp[1] = {name="retCode", type="ui16" }  
Proto4z.ClientAuthResp[2] = {name="account", type="string" }  
Proto4z.ClientAuthResp[3] = {name="token", type="string" }  
Proto4z.ClientAuthResp[4] = {name="previews", type="AvatarPreviewArray" }  
 
Proto4z.register(40037,"CreateAvatarReq") 
Proto4z.CreateAvatarReq = {} --创角色请求 
Proto4z.CreateAvatarReq.__protoID = 40037 
Proto4z.CreateAvatarReq.__protoName = "CreateAvatarReq" 
Proto4z.CreateAvatarReq[1] = {name="accountName", type="string" } --这个字段会被服务器填充.客户端可以不填写 
Proto4z.CreateAvatarReq[2] = {name="userName", type="string" }  
 
Proto4z.register(40038,"CreateAvatarResp") 
Proto4z.CreateAvatarResp = {} --创角色请求返回 
Proto4z.CreateAvatarResp.__protoID = 40038 
Proto4z.CreateAvatarResp.__protoName = "CreateAvatarResp" 
Proto4z.CreateAvatarResp[1] = {name="retCode", type="ui16" }  
Proto4z.CreateAvatarResp[2] = {name="avatarID", type="ui64" }  
Proto4z.CreateAvatarResp[3] = {name="previews", type="AvatarPreviewArray" }  
 
Proto4z.register(40039,"AttachAvatarReq") 
Proto4z.AttachAvatarReq = {} --选角色请求 
Proto4z.AttachAvatarReq.__protoID = 40039 
Proto4z.AttachAvatarReq.__protoName = "AttachAvatarReq" 
Proto4z.AttachAvatarReq[1] = {name="accountName", type="string" } --这个字段会被服务器填充.客户端可以不填写 
Proto4z.AttachAvatarReq[2] = {name="avatarID", type="ui64" }  
 
Proto4z.register(40040,"AttachAvatarResp") 
Proto4z.AttachAvatarResp = {} --选角色请求返回 
Proto4z.AttachAvatarResp.__protoID = 40040 
Proto4z.AttachAvatarResp.__protoName = "AttachAvatarResp" 
Proto4z.AttachAvatarResp[1] = {name="retCode", type="ui16" }  
Proto4z.AttachAvatarResp[2] = {name="baseInfo", type="AvatarBaseInfo" }  
Proto4z.AttachAvatarResp[3] = {name="props", type="AvatarPropMap" }  
 
Proto4z.register(40041,"AvatarBaseInfoNotice") 
Proto4z.AvatarBaseInfoNotice = {}  
Proto4z.AvatarBaseInfoNotice.__protoID = 40041 
Proto4z.AvatarBaseInfoNotice.__protoName = "AvatarBaseInfoNotice" 
Proto4z.AvatarBaseInfoNotice[1] = {name="baseInfo", type="AvatarBaseInfo" }  
 
Proto4z.register(40042,"AvatarPropMapNotice") 
Proto4z.AvatarPropMapNotice = {}  
Proto4z.AvatarPropMapNotice.__protoID = 40042 
Proto4z.AvatarPropMapNotice.__protoName = "AvatarPropMapNotice" 
Proto4z.AvatarPropMapNotice[1] = {name="avatarID", type="ui64" }  
Proto4z.AvatarPropMapNotice[2] = {name="props", type="AvatarPropMap" }  
 
Proto4z.register(40043,"SceneGroupGetStatusReq") 
Proto4z.SceneGroupGetStatusReq = {} --获取当前角色的场景状态数据 
Proto4z.SceneGroupGetStatusReq.__protoID = 40043 
Proto4z.SceneGroupGetStatusReq.__protoName = "SceneGroupGetStatusReq" 
 
Proto4z.register(40044,"SceneGroupGetStatusResp") 
Proto4z.SceneGroupGetStatusResp = {}  
Proto4z.SceneGroupGetStatusResp.__protoID = 40044 
Proto4z.SceneGroupGetStatusResp.__protoName = "SceneGroupGetStatusResp" 
Proto4z.SceneGroupGetStatusResp[1] = {name="retCode", type="ui16" }  
 
Proto4z.register(40045,"SceneGroupAvatarInfo") 
Proto4z.SceneGroupAvatarInfo = {}  
Proto4z.SceneGroupAvatarInfo.__protoID = 40045 
Proto4z.SceneGroupAvatarInfo.__protoName = "SceneGroupAvatarInfo" 
Proto4z.SceneGroupAvatarInfo[1] = {name="baseInfo", type="AvatarBaseInfo" }  
Proto4z.SceneGroupAvatarInfo[2] = {name="powerType", type="ui16" } --0普通,1leader,2master 
 
Proto4z.SceneGroupAvatarInfoArray = {}  
Proto4z.SceneGroupAvatarInfoArray.__protoName = "SceneGroupAvatarInfoArray" 
Proto4z.SceneGroupAvatarInfoArray.__protoDesc = "array" 
Proto4z.SceneGroupAvatarInfoArray.__protoTypeV = "SceneGroupAvatarInfo" 
 
Proto4z.register(40046,"SceneGroupInfoNotice") 
Proto4z.SceneGroupInfoNotice = {} --编队数据通知 
Proto4z.SceneGroupInfoNotice.__protoID = 40046 
Proto4z.SceneGroupInfoNotice.__protoName = "SceneGroupInfoNotice" 
Proto4z.SceneGroupInfoNotice[1] = {name="sceneType", type="ui16" } --场景类型 
Proto4z.SceneGroupInfoNotice[2] = {name="mapID", type="ui64" }  
Proto4z.SceneGroupInfoNotice[3] = {name="groupID", type="ui64" }  
Proto4z.SceneGroupInfoNotice[4] = {name="sceneStatus", type="ui16" } --状态 
Proto4z.SceneGroupInfoNotice[5] = {name="lineID", type="ui64" } --分线ID 
Proto4z.SceneGroupInfoNotice[6] = {name="sceneID", type="ui64" } --场景实例ID 
Proto4z.SceneGroupInfoNotice[7] = {name="host", type="string" } --服务器host 
Proto4z.SceneGroupInfoNotice[8] = {name="port", type="ui16" } --服务器port 
Proto4z.SceneGroupInfoNotice[9] = {name="token", type="string" } --自己的令牌 
Proto4z.SceneGroupInfoNotice[10] = {name="members", type="SceneGroupAvatarInfoArray" } --队友数据 
 
Proto4z.register(40047,"SceneGroupCreateReq") 
Proto4z.SceneGroupCreateReq = {} --发起组队请求 
Proto4z.SceneGroupCreateReq.__protoID = 40047 
Proto4z.SceneGroupCreateReq.__protoName = "SceneGroupCreateReq" 
 
Proto4z.register(40048,"SceneGroupCreateResp") 
Proto4z.SceneGroupCreateResp = {}  
Proto4z.SceneGroupCreateResp.__protoID = 40048 
Proto4z.SceneGroupCreateResp.__protoName = "SceneGroupCreateResp" 
Proto4z.SceneGroupCreateResp[1] = {name="retCode", type="ui16" }  
 
Proto4z.register(40049,"SceneGroupJoinReq") 
Proto4z.SceneGroupJoinReq = {} --加入组队 
Proto4z.SceneGroupJoinReq.__protoID = 40049 
Proto4z.SceneGroupJoinReq.__protoName = "SceneGroupJoinReq" 
Proto4z.SceneGroupJoinReq[1] = {name="groupID", type="ui64" }  
 
Proto4z.register(40050,"SceneGroupJoinResp") 
Proto4z.SceneGroupJoinResp = {}  
Proto4z.SceneGroupJoinResp.__protoID = 40050 
Proto4z.SceneGroupJoinResp.__protoName = "SceneGroupJoinResp" 
Proto4z.SceneGroupJoinResp[1] = {name="retCode", type="ui16" }  
 
Proto4z.register(40051,"SceneGroupInviteReq") 
Proto4z.SceneGroupInviteReq = {} --邀请对方加入自己的编队 
Proto4z.SceneGroupInviteReq.__protoID = 40051 
Proto4z.SceneGroupInviteReq.__protoName = "SceneGroupInviteReq" 
Proto4z.SceneGroupInviteReq[1] = {name="avatarID", type="ui64" }  
 
Proto4z.register(40052,"SceneGroupInviteResp") 
Proto4z.SceneGroupInviteResp = {}  
Proto4z.SceneGroupInviteResp.__protoID = 40052 
Proto4z.SceneGroupInviteResp.__protoName = "SceneGroupInviteResp" 
Proto4z.SceneGroupInviteResp[1] = {name="retCode", type="ui16" }  
 
Proto4z.register(40053,"SceneGroupRejectReq") 
Proto4z.SceneGroupRejectReq = {} --拒绝对方邀请 
Proto4z.SceneGroupRejectReq.__protoID = 40053 
Proto4z.SceneGroupRejectReq.__protoName = "SceneGroupRejectReq" 
Proto4z.SceneGroupRejectReq[1] = {name="groupID", type="ui64" }  
 
Proto4z.register(40054,"SceneGroupRejectResp") 
Proto4z.SceneGroupRejectResp = {}  
Proto4z.SceneGroupRejectResp.__protoID = 40054 
Proto4z.SceneGroupRejectResp.__protoName = "SceneGroupRejectResp" 
Proto4z.SceneGroupRejectResp[1] = {name="retCode", type="ui16" }  
 
Proto4z.register(40055,"SceneGroupLeaveReq") 
Proto4z.SceneGroupLeaveReq = {} --离开编队 
Proto4z.SceneGroupLeaveReq.__protoID = 40055 
Proto4z.SceneGroupLeaveReq.__protoName = "SceneGroupLeaveReq" 
 
Proto4z.register(40056,"SceneGroupLeaveResp") 
Proto4z.SceneGroupLeaveResp = {}  
Proto4z.SceneGroupLeaveResp.__protoID = 40056 
Proto4z.SceneGroupLeaveResp.__protoName = "SceneGroupLeaveResp" 
Proto4z.SceneGroupLeaveResp[1] = {name="retCode", type="ui16" }  
 
Proto4z.register(40057,"SceneGroupEnterSceneReq") 
Proto4z.SceneGroupEnterSceneReq = {} --申请进入场景 
Proto4z.SceneGroupEnterSceneReq.__protoID = 40057 
Proto4z.SceneGroupEnterSceneReq.__protoName = "SceneGroupEnterSceneReq" 
Proto4z.SceneGroupEnterSceneReq[1] = {name="sceneType", type="ui16" }  
Proto4z.SceneGroupEnterSceneReq[2] = {name="mapID", type="ui64" }  
 
Proto4z.register(40058,"SceneGroupEnterSceneResp") 
Proto4z.SceneGroupEnterSceneResp = {}  
Proto4z.SceneGroupEnterSceneResp.__protoID = 40058 
Proto4z.SceneGroupEnterSceneResp.__protoName = "SceneGroupEnterSceneResp" 
Proto4z.SceneGroupEnterSceneResp[1] = {name="retCode", type="ui16" }  
 
Proto4z.register(40059,"SceneGroupCancelEnterReq") 
Proto4z.SceneGroupCancelEnterReq = {} --取消申请(根据状态不同会有取消匹配,重置状态,结束战斗(可中途结束的场景类型) 
Proto4z.SceneGroupCancelEnterReq.__protoID = 40059 
Proto4z.SceneGroupCancelEnterReq.__protoName = "SceneGroupCancelEnterReq" 
 
Proto4z.register(40060,"SceneGroupCancelEnterResp") 
Proto4z.SceneGroupCancelEnterResp = {}  
Proto4z.SceneGroupCancelEnterResp.__protoID = 40060 
Proto4z.SceneGroupCancelEnterResp.__protoName = "SceneGroupCancelEnterResp" 
Proto4z.SceneGroupCancelEnterResp[1] = {name="retCode", type="ui16" }  
 
Proto4z.register(40061,"ChatReq") 
Proto4z.ChatReq = {}  
Proto4z.ChatReq.__protoID = 40061 
Proto4z.ChatReq.__protoName = "ChatReq" 
Proto4z.ChatReq[1] = {name="channelID", type="ui16" }  
Proto4z.ChatReq[2] = {name="targetID", type="ui64" }  
Proto4z.ChatReq[3] = {name="msg", type="string" }  
 
Proto4z.register(40062,"ChatResp") 
Proto4z.ChatResp = {}  
Proto4z.ChatResp.__protoID = 40062 
Proto4z.ChatResp.__protoName = "ChatResp" 
Proto4z.ChatResp[1] = {name="channelID", type="ui16" }  
Proto4z.ChatResp[2] = {name="sourceID", type="ui64" }  
Proto4z.ChatResp[3] = {name="sourceName", type="string" }  
Proto4z.ChatResp[4] = {name="targetID", type="ui64" }  
Proto4z.ChatResp[5] = {name="targetName", type="string" }  
Proto4z.ChatResp[6] = {name="msg", type="string" }  
Proto4z.ChatResp[7] = {name="chatTime", type="ui64" }  
 
Proto4z.register(40063,"PingPongReq") 
Proto4z.PingPongReq = {}  
Proto4z.PingPongReq.__protoID = 40063 
Proto4z.PingPongReq.__protoName = "PingPongReq" 
Proto4z.PingPongReq[1] = {name="msg", type="string" }  
 
Proto4z.register(40064,"PingPongResp") 
Proto4z.PingPongResp = {}  
Proto4z.PingPongResp.__protoID = 40064 
Proto4z.PingPongResp.__protoName = "PingPongResp" 
Proto4z.PingPongResp[1] = {name="msg", type="string" }  
 
Proto4z.register(40065,"ChangeIconIDReq") 
Proto4z.ChangeIconIDReq = {}  
Proto4z.ChangeIconIDReq.__protoID = 40065 
Proto4z.ChangeIconIDReq.__protoName = "ChangeIconIDReq" 
Proto4z.ChangeIconIDReq[1] = {name="iconID", type="i32" }  
 
Proto4z.register(40066,"ChangeIconIDResp") 
Proto4z.ChangeIconIDResp = {}  
Proto4z.ChangeIconIDResp.__protoID = 40066 
Proto4z.ChangeIconIDResp.__protoName = "ChangeIconIDResp" 
Proto4z.ChangeIconIDResp[1] = {name="retCode", type="ui16" }  
Proto4z.ChangeIconIDResp[2] = {name="iconID", type="i32" }  
 
Proto4z.register(40067,"ChangeModeIDReq") 
Proto4z.ChangeModeIDReq = {}  
Proto4z.ChangeModeIDReq.__protoID = 40067 
Proto4z.ChangeModeIDReq.__protoName = "ChangeModeIDReq" 
Proto4z.ChangeModeIDReq[1] = {name="modeID", type="i32" }  
 
Proto4z.register(40068,"ChangeModeIDResp") 
Proto4z.ChangeModeIDResp = {}  
Proto4z.ChangeModeIDResp.__protoID = 40068 
Proto4z.ChangeModeIDResp.__protoName = "ChangeModeIDResp" 
Proto4z.ChangeModeIDResp[1] = {name="retCode", type="ui16" }  
Proto4z.ChangeModeIDResp[2] = {name="modeID", type="i32" }  

 
Proto4z.register(40000,"ClientPulse") 
Proto4z.ClientPulse = {} --客户端脉冲请求 
Proto4z.ClientPulse.__protoID = 40000 
Proto4z.ClientPulse.__protoName = "ClientPulse" 
 
Proto4z.register(40001,"ClientAuthReq") 
Proto4z.ClientAuthReq = {} --认证请求 
Proto4z.ClientAuthReq.__protoID = 40001 
Proto4z.ClientAuthReq.__protoName = "ClientAuthReq" 
Proto4z.ClientAuthReq[1] = {name="account", type="string" }  
Proto4z.ClientAuthReq[2] = {name="token", type="string" }  
 
Proto4z.register(40002,"ClientAuthResp") 
Proto4z.ClientAuthResp = {} --认证返回 
Proto4z.ClientAuthResp.__protoID = 40002 
Proto4z.ClientAuthResp.__protoName = "ClientAuthResp" 
Proto4z.ClientAuthResp[1] = {name="retCode", type="ui16" }  
Proto4z.ClientAuthResp[2] = {name="account", type="string" }  
Proto4z.ClientAuthResp[3] = {name="token", type="string" }  
Proto4z.ClientAuthResp[4] = {name="previews", type="AvatarPreviewArray" }  
 
Proto4z.register(40003,"CreateAvatarReq") 
Proto4z.CreateAvatarReq = {} --创角色请求 
Proto4z.CreateAvatarReq.__protoID = 40003 
Proto4z.CreateAvatarReq.__protoName = "CreateAvatarReq" 
Proto4z.CreateAvatarReq[1] = {name="accountName", type="string" } --这个字段会被服务器填充.客户端可以不填写 
Proto4z.CreateAvatarReq[2] = {name="avatarName", type="string" }  
 
Proto4z.register(40004,"CreateAvatarResp") 
Proto4z.CreateAvatarResp = {} --创角色请求返回 
Proto4z.CreateAvatarResp.__protoID = 40004 
Proto4z.CreateAvatarResp.__protoName = "CreateAvatarResp" 
Proto4z.CreateAvatarResp[1] = {name="retCode", type="ui16" }  
Proto4z.CreateAvatarResp[2] = {name="avatarID", type="ui64" }  
Proto4z.CreateAvatarResp[3] = {name="previews", type="AvatarPreviewArray" }  
 
Proto4z.register(40005,"AttachAvatarReq") 
Proto4z.AttachAvatarReq = {} --选角色请求 
Proto4z.AttachAvatarReq.__protoID = 40005 
Proto4z.AttachAvatarReq.__protoName = "AttachAvatarReq" 
Proto4z.AttachAvatarReq[1] = {name="accountName", type="string" } --这个字段会被服务器填充.客户端可以不填写 
Proto4z.AttachAvatarReq[2] = {name="avatarID", type="ui64" }  
 
Proto4z.register(40006,"AttachAvatarResp") 
Proto4z.AttachAvatarResp = {} --选角色请求返回 
Proto4z.AttachAvatarResp.__protoID = 40006 
Proto4z.AttachAvatarResp.__protoName = "AttachAvatarResp" 
Proto4z.AttachAvatarResp[1] = {name="retCode", type="ui16" }  
Proto4z.AttachAvatarResp[2] = {name="baseInfo", type="AvatarBaseInfo" }  
 
Proto4z.register(40007,"AvatarBaseInfoNotice") 
Proto4z.AvatarBaseInfoNotice = {}  
Proto4z.AvatarBaseInfoNotice.__protoID = 40007 
Proto4z.AvatarBaseInfoNotice.__protoName = "AvatarBaseInfoNotice" 
Proto4z.AvatarBaseInfoNotice[1] = {name="baseInfo", type="AvatarBaseInfo" }  
 
Proto4z.register(40008,"AvatarPropMapNotice") 
Proto4z.AvatarPropMapNotice = {}  
Proto4z.AvatarPropMapNotice.__protoID = 40008 
Proto4z.AvatarPropMapNotice.__protoName = "AvatarPropMapNotice" 
Proto4z.AvatarPropMapNotice[1] = {name="avatarID", type="ui64" }  
 
Proto4z.register(40009,"SceneGroupInfoNotice") 
Proto4z.SceneGroupInfoNotice = {} --编队数据通知 
Proto4z.SceneGroupInfoNotice.__protoID = 40009 
Proto4z.SceneGroupInfoNotice.__protoName = "SceneGroupInfoNotice" 
Proto4z.SceneGroupInfoNotice[1] = {name="groupInfo", type="SceneGroupInfo" }  
 
Proto4z.register(40010,"SceneGroupGetReq") 
Proto4z.SceneGroupGetReq = {} --获取当前角色的场景状态数据 
Proto4z.SceneGroupGetReq.__protoID = 40010 
Proto4z.SceneGroupGetReq.__protoName = "SceneGroupGetReq" 
 
Proto4z.register(40011,"SceneGroupGetResp") 
Proto4z.SceneGroupGetResp = {}  
Proto4z.SceneGroupGetResp.__protoID = 40011 
Proto4z.SceneGroupGetResp.__protoName = "SceneGroupGetResp" 
Proto4z.SceneGroupGetResp[1] = {name="retCode", type="ui16" }  
 
Proto4z.register(40012,"SceneGroupEnterReq") 
Proto4z.SceneGroupEnterReq = {} --申请进入场景 
Proto4z.SceneGroupEnterReq.__protoID = 40012 
Proto4z.SceneGroupEnterReq.__protoName = "SceneGroupEnterReq" 
Proto4z.SceneGroupEnterReq[1] = {name="sceneType", type="ui16" }  
Proto4z.SceneGroupEnterReq[2] = {name="mapID", type="ui64" }  
 
Proto4z.register(40013,"SceneGroupEnterResp") 
Proto4z.SceneGroupEnterResp = {}  
Proto4z.SceneGroupEnterResp.__protoID = 40013 
Proto4z.SceneGroupEnterResp.__protoName = "SceneGroupEnterResp" 
Proto4z.SceneGroupEnterResp[1] = {name="retCode", type="ui16" }  
 
Proto4z.register(40014,"SceneGroupCancelReq") 
Proto4z.SceneGroupCancelReq = {} --取消申请(根据状态不同会有取消匹配,重置状态,结束战斗(可中途结束的场景类型) 
Proto4z.SceneGroupCancelReq.__protoID = 40014 
Proto4z.SceneGroupCancelReq.__protoName = "SceneGroupCancelReq" 
 
Proto4z.register(40015,"SceneGroupCancelResp") 
Proto4z.SceneGroupCancelResp = {}  
Proto4z.SceneGroupCancelResp.__protoID = 40015 
Proto4z.SceneGroupCancelResp.__protoName = "SceneGroupCancelResp" 
Proto4z.SceneGroupCancelResp[1] = {name="retCode", type="ui16" }  
 
Proto4z.register(40016,"SceneGroupCreateReq") 
Proto4z.SceneGroupCreateReq = {} --发起组队请求 
Proto4z.SceneGroupCreateReq.__protoID = 40016 
Proto4z.SceneGroupCreateReq.__protoName = "SceneGroupCreateReq" 
 
Proto4z.register(40017,"SceneGroupCreateResp") 
Proto4z.SceneGroupCreateResp = {}  
Proto4z.SceneGroupCreateResp.__protoID = 40017 
Proto4z.SceneGroupCreateResp.__protoName = "SceneGroupCreateResp" 
Proto4z.SceneGroupCreateResp[1] = {name="retCode", type="ui16" }  
 
Proto4z.register(40018,"SceneGroupJoinReq") 
Proto4z.SceneGroupJoinReq = {} --加入组队 
Proto4z.SceneGroupJoinReq.__protoID = 40018 
Proto4z.SceneGroupJoinReq.__protoName = "SceneGroupJoinReq" 
Proto4z.SceneGroupJoinReq[1] = {name="groupID", type="ui64" }  
 
Proto4z.register(40019,"SceneGroupJoinResp") 
Proto4z.SceneGroupJoinResp = {}  
Proto4z.SceneGroupJoinResp.__protoID = 40019 
Proto4z.SceneGroupJoinResp.__protoName = "SceneGroupJoinResp" 
Proto4z.SceneGroupJoinResp[1] = {name="retCode", type="ui16" }  
 
Proto4z.register(40020,"SceneGroupInviteReq") 
Proto4z.SceneGroupInviteReq = {} --邀请对方加入自己的编队 
Proto4z.SceneGroupInviteReq.__protoID = 40020 
Proto4z.SceneGroupInviteReq.__protoName = "SceneGroupInviteReq" 
Proto4z.SceneGroupInviteReq[1] = {name="avatarID", type="ui64" }  
 
Proto4z.register(40021,"SceneGroupInviteResp") 
Proto4z.SceneGroupInviteResp = {}  
Proto4z.SceneGroupInviteResp.__protoID = 40021 
Proto4z.SceneGroupInviteResp.__protoName = "SceneGroupInviteResp" 
Proto4z.SceneGroupInviteResp[1] = {name="retCode", type="ui16" }  
 
Proto4z.register(40022,"SceneGroupInviteNotice") 
Proto4z.SceneGroupInviteNotice = {}  
Proto4z.SceneGroupInviteNotice.__protoID = 40022 
Proto4z.SceneGroupInviteNotice.__protoName = "SceneGroupInviteNotice" 
Proto4z.SceneGroupInviteNotice[1] = {name="avatarID", type="ui64" }  
Proto4z.SceneGroupInviteNotice[2] = {name="avatarName", type="string" }  
Proto4z.SceneGroupInviteNotice[3] = {name="groupID", type="ui64" }  
 
Proto4z.register(40023,"SceneGroupRejectReq") 
Proto4z.SceneGroupRejectReq = {} --拒绝对方邀请 
Proto4z.SceneGroupRejectReq.__protoID = 40023 
Proto4z.SceneGroupRejectReq.__protoName = "SceneGroupRejectReq" 
Proto4z.SceneGroupRejectReq[1] = {name="groupID", type="ui64" }  
 
Proto4z.register(40024,"SceneGroupRejectResp") 
Proto4z.SceneGroupRejectResp = {}  
Proto4z.SceneGroupRejectResp.__protoID = 40024 
Proto4z.SceneGroupRejectResp.__protoName = "SceneGroupRejectResp" 
Proto4z.SceneGroupRejectResp[1] = {name="retCode", type="ui16" }  
 
Proto4z.register(40025,"SceneGroupLeaveReq") 
Proto4z.SceneGroupLeaveReq = {} --离开编队 
Proto4z.SceneGroupLeaveReq.__protoID = 40025 
Proto4z.SceneGroupLeaveReq.__protoName = "SceneGroupLeaveReq" 
 
Proto4z.register(40026,"SceneGroupLeaveResp") 
Proto4z.SceneGroupLeaveResp = {}  
Proto4z.SceneGroupLeaveResp.__protoID = 40026 
Proto4z.SceneGroupLeaveResp.__protoName = "SceneGroupLeaveResp" 
Proto4z.SceneGroupLeaveResp[1] = {name="retCode", type="ui16" }  
 
Proto4z.register(40027,"ChatReq") 
Proto4z.ChatReq = {}  
Proto4z.ChatReq.__protoID = 40027 
Proto4z.ChatReq.__protoName = "ChatReq" 
Proto4z.ChatReq[1] = {name="channelID", type="ui16" }  
Proto4z.ChatReq[2] = {name="targetID", type="ui64" }  
Proto4z.ChatReq[3] = {name="msg", type="string" }  
 
Proto4z.register(40028,"ChatResp") 
Proto4z.ChatResp = {}  
Proto4z.ChatResp.__protoID = 40028 
Proto4z.ChatResp.__protoName = "ChatResp" 
Proto4z.ChatResp[1] = {name="channelID", type="ui16" }  
Proto4z.ChatResp[2] = {name="sourceID", type="ui64" }  
Proto4z.ChatResp[3] = {name="sourceName", type="string" }  
Proto4z.ChatResp[4] = {name="targetID", type="ui64" }  
Proto4z.ChatResp[5] = {name="targetName", type="string" }  
Proto4z.ChatResp[6] = {name="msg", type="string" }  
Proto4z.ChatResp[7] = {name="chatTime", type="ui64" }  
 
Proto4z.register(40029,"PingPongReq") 
Proto4z.PingPongReq = {}  
Proto4z.PingPongReq.__protoID = 40029 
Proto4z.PingPongReq.__protoName = "PingPongReq" 
Proto4z.PingPongReq[1] = {name="msg", type="string" }  
 
Proto4z.register(40030,"PingPongResp") 
Proto4z.PingPongResp = {}  
Proto4z.PingPongResp.__protoID = 40030 
Proto4z.PingPongResp.__protoName = "PingPongResp" 
Proto4z.PingPongResp[1] = {name="msg", type="string" }  
 
Proto4z.register(40031,"ChangeIconIDReq") 
Proto4z.ChangeIconIDReq = {}  
Proto4z.ChangeIconIDReq.__protoID = 40031 
Proto4z.ChangeIconIDReq.__protoName = "ChangeIconIDReq" 
Proto4z.ChangeIconIDReq[1] = {name="iconID", type="ui64" }  
 
Proto4z.register(40032,"ChangeIconIDResp") 
Proto4z.ChangeIconIDResp = {}  
Proto4z.ChangeIconIDResp.__protoID = 40032 
Proto4z.ChangeIconIDResp.__protoName = "ChangeIconIDResp" 
Proto4z.ChangeIconIDResp[1] = {name="retCode", type="ui16" }  
Proto4z.ChangeIconIDResp[2] = {name="iconID", type="ui64" }  
 
Proto4z.register(40033,"ChangeModeIDReq") 
Proto4z.ChangeModeIDReq = {}  
Proto4z.ChangeModeIDReq.__protoID = 40033 
Proto4z.ChangeModeIDReq.__protoName = "ChangeModeIDReq" 
Proto4z.ChangeModeIDReq[1] = {name="modeID", type="ui64" }  
 
Proto4z.register(40034,"ChangeModeIDResp") 
Proto4z.ChangeModeIDResp = {}  
Proto4z.ChangeModeIDResp.__protoID = 40034 
Proto4z.ChangeModeIDResp.__protoName = "ChangeModeIDResp" 
Proto4z.ChangeModeIDResp[1] = {name="retCode", type="ui16" }  
Proto4z.ChangeModeIDResp[2] = {name="modeID", type="ui64" }  

 
Proto4z.register(55000,"ClientPulse") 
Proto4z.ClientPulse = {} --客户端脉冲请求 
Proto4z.ClientPulse.__protoID = 55000 
Proto4z.ClientPulse.__protoName = "ClientPulse" 
 
Proto4z.register(55001,"ClientAuthReq") 
Proto4z.ClientAuthReq = {} --认证请求 
Proto4z.ClientAuthReq.__protoID = 55001 
Proto4z.ClientAuthReq.__protoName = "ClientAuthReq" 
Proto4z.ClientAuthReq[1] = {name="account", type="string" }  
Proto4z.ClientAuthReq[2] = {name="token", type="string" }  
 
Proto4z.register(55002,"ClientAuthResp") 
Proto4z.ClientAuthResp = {} --认证返回 
Proto4z.ClientAuthResp.__protoID = 55002 
Proto4z.ClientAuthResp.__protoName = "ClientAuthResp" 
Proto4z.ClientAuthResp[1] = {name="retCode", type="ui16" }  
Proto4z.ClientAuthResp[2] = {name="account", type="string" }  
Proto4z.ClientAuthResp[3] = {name="token", type="string" }  
Proto4z.ClientAuthResp[4] = {name="previews", type="AvatarPreviewArray" }  
 
Proto4z.register(55003,"CreateAvatarReq") 
Proto4z.CreateAvatarReq = {} --创角色请求 
Proto4z.CreateAvatarReq.__protoID = 55003 
Proto4z.CreateAvatarReq.__protoName = "CreateAvatarReq" 
Proto4z.CreateAvatarReq[1] = {name="accountName", type="string" } --这个字段会被服务器填充.客户端可以不填写 
Proto4z.CreateAvatarReq[2] = {name="avatarName", type="string" }  
 
Proto4z.register(55004,"CreateAvatarResp") 
Proto4z.CreateAvatarResp = {} --创角色请求返回 
Proto4z.CreateAvatarResp.__protoID = 55004 
Proto4z.CreateAvatarResp.__protoName = "CreateAvatarResp" 
Proto4z.CreateAvatarResp[1] = {name="retCode", type="ui16" }  
Proto4z.CreateAvatarResp[2] = {name="avatarID", type="ui64" }  
Proto4z.CreateAvatarResp[3] = {name="previews", type="AvatarPreviewArray" }  
 
Proto4z.DeviceInfo = {}  
Proto4z.DeviceInfo.__protoName = "DeviceInfo" 
Proto4z.DeviceInfo.__protoDesc = "map" 
Proto4z.DeviceInfo.__protoTypeK = "string" 
Proto4z.DeviceInfo.__protoTypeV = "string" 
 
Proto4z.register(55005,"AttachAvatarReq") 
Proto4z.AttachAvatarReq = {} --选角色请求 
Proto4z.AttachAvatarReq.__protoID = 55005 
Proto4z.AttachAvatarReq.__protoName = "AttachAvatarReq" 
Proto4z.AttachAvatarReq[1] = {name="accountName", type="string" } --这个字段会被服务器填充.客户端可以不填写 
Proto4z.AttachAvatarReq[2] = {name="avatarID", type="ui64" }  
Proto4z.AttachAvatarReq[3] = {name="di", type="DeviceInfo" }  
 
Proto4z.register(55006,"AttachAvatarResp") 
Proto4z.AttachAvatarResp = {} --选角色请求返回 
Proto4z.AttachAvatarResp.__protoID = 55006 
Proto4z.AttachAvatarResp.__protoName = "AttachAvatarResp" 
Proto4z.AttachAvatarResp[1] = {name="retCode", type="ui16" }  
Proto4z.AttachAvatarResp[2] = {name="baseInfo", type="AvatarBaseInfo" }  
 
Proto4z.register(55007,"AvatarBaseInfoNotice") 
Proto4z.AvatarBaseInfoNotice = {}  
Proto4z.AvatarBaseInfoNotice.__protoID = 55007 
Proto4z.AvatarBaseInfoNotice.__protoName = "AvatarBaseInfoNotice" 
Proto4z.AvatarBaseInfoNotice[1] = {name="baseInfo", type="AvatarBaseInfo" }  
 
Proto4z.register(55008,"AvatarPropMapNotice") 
Proto4z.AvatarPropMapNotice = {}  
Proto4z.AvatarPropMapNotice.__protoID = 55008 
Proto4z.AvatarPropMapNotice.__protoName = "AvatarPropMapNotice" 
Proto4z.AvatarPropMapNotice[1] = {name="avatarID", type="ui64" }  
 
Proto4z.register(55009,"SceneGroupInfoNotice") 
Proto4z.SceneGroupInfoNotice = {} --编队数据通知 
Proto4z.SceneGroupInfoNotice.__protoID = 55009 
Proto4z.SceneGroupInfoNotice.__protoName = "SceneGroupInfoNotice" 
Proto4z.SceneGroupInfoNotice[1] = {name="groupInfo", type="SceneGroupInfo" }  
 
Proto4z.register(55010,"SceneGroupGetReq") 
Proto4z.SceneGroupGetReq = {} --获取当前角色的场景状态数据 
Proto4z.SceneGroupGetReq.__protoID = 55010 
Proto4z.SceneGroupGetReq.__protoName = "SceneGroupGetReq" 
 
Proto4z.register(55011,"SceneGroupGetResp") 
Proto4z.SceneGroupGetResp = {}  
Proto4z.SceneGroupGetResp.__protoID = 55011 
Proto4z.SceneGroupGetResp.__protoName = "SceneGroupGetResp" 
Proto4z.SceneGroupGetResp[1] = {name="retCode", type="ui16" }  
 
Proto4z.register(55012,"SceneGroupEnterReq") 
Proto4z.SceneGroupEnterReq = {} --申请进入场景 
Proto4z.SceneGroupEnterReq.__protoID = 55012 
Proto4z.SceneGroupEnterReq.__protoName = "SceneGroupEnterReq" 
Proto4z.SceneGroupEnterReq[1] = {name="sceneType", type="ui16" }  
Proto4z.SceneGroupEnterReq[2] = {name="mapID", type="ui64" }  
 
Proto4z.register(55013,"SceneGroupEnterResp") 
Proto4z.SceneGroupEnterResp = {}  
Proto4z.SceneGroupEnterResp.__protoID = 55013 
Proto4z.SceneGroupEnterResp.__protoName = "SceneGroupEnterResp" 
Proto4z.SceneGroupEnterResp[1] = {name="retCode", type="ui16" }  
 
Proto4z.register(55014,"SceneGroupCancelReq") 
Proto4z.SceneGroupCancelReq = {} --取消申请(根据状态不同会有取消匹配,重置状态,结束战斗(可中途结束的场景类型) 
Proto4z.SceneGroupCancelReq.__protoID = 55014 
Proto4z.SceneGroupCancelReq.__protoName = "SceneGroupCancelReq" 
 
Proto4z.register(55015,"SceneGroupCancelResp") 
Proto4z.SceneGroupCancelResp = {}  
Proto4z.SceneGroupCancelResp.__protoID = 55015 
Proto4z.SceneGroupCancelResp.__protoName = "SceneGroupCancelResp" 
Proto4z.SceneGroupCancelResp[1] = {name="retCode", type="ui16" }  
 
Proto4z.register(55016,"SceneGroupCreateReq") 
Proto4z.SceneGroupCreateReq = {} --发起组队请求 
Proto4z.SceneGroupCreateReq.__protoID = 55016 
Proto4z.SceneGroupCreateReq.__protoName = "SceneGroupCreateReq" 
 
Proto4z.register(55017,"SceneGroupCreateResp") 
Proto4z.SceneGroupCreateResp = {}  
Proto4z.SceneGroupCreateResp.__protoID = 55017 
Proto4z.SceneGroupCreateResp.__protoName = "SceneGroupCreateResp" 
Proto4z.SceneGroupCreateResp[1] = {name="retCode", type="ui16" }  
 
Proto4z.register(55018,"SceneGroupJoinReq") 
Proto4z.SceneGroupJoinReq = {} --加入组队 
Proto4z.SceneGroupJoinReq.__protoID = 55018 
Proto4z.SceneGroupJoinReq.__protoName = "SceneGroupJoinReq" 
Proto4z.SceneGroupJoinReq[1] = {name="groupID", type="ui64" }  
 
Proto4z.register(55019,"SceneGroupJoinResp") 
Proto4z.SceneGroupJoinResp = {}  
Proto4z.SceneGroupJoinResp.__protoID = 55019 
Proto4z.SceneGroupJoinResp.__protoName = "SceneGroupJoinResp" 
Proto4z.SceneGroupJoinResp[1] = {name="retCode", type="ui16" }  
 
Proto4z.register(55020,"SceneGroupInviteReq") 
Proto4z.SceneGroupInviteReq = {} --邀请对方加入自己的编队 
Proto4z.SceneGroupInviteReq.__protoID = 55020 
Proto4z.SceneGroupInviteReq.__protoName = "SceneGroupInviteReq" 
Proto4z.SceneGroupInviteReq[1] = {name="avatarID", type="ui64" }  
 
Proto4z.register(55021,"SceneGroupInviteResp") 
Proto4z.SceneGroupInviteResp = {}  
Proto4z.SceneGroupInviteResp.__protoID = 55021 
Proto4z.SceneGroupInviteResp.__protoName = "SceneGroupInviteResp" 
Proto4z.SceneGroupInviteResp[1] = {name="retCode", type="ui16" }  
 
Proto4z.register(55022,"SceneGroupInviteNotice") 
Proto4z.SceneGroupInviteNotice = {}  
Proto4z.SceneGroupInviteNotice.__protoID = 55022 
Proto4z.SceneGroupInviteNotice.__protoName = "SceneGroupInviteNotice" 
Proto4z.SceneGroupInviteNotice[1] = {name="avatarID", type="ui64" }  
Proto4z.SceneGroupInviteNotice[2] = {name="avatarName", type="string" }  
Proto4z.SceneGroupInviteNotice[3] = {name="groupID", type="ui64" }  
 
Proto4z.register(55023,"SceneGroupRejectReq") 
Proto4z.SceneGroupRejectReq = {} --拒绝对方邀请 
Proto4z.SceneGroupRejectReq.__protoID = 55023 
Proto4z.SceneGroupRejectReq.__protoName = "SceneGroupRejectReq" 
Proto4z.SceneGroupRejectReq[1] = {name="groupID", type="ui64" }  
 
Proto4z.register(55024,"SceneGroupRejectResp") 
Proto4z.SceneGroupRejectResp = {}  
Proto4z.SceneGroupRejectResp.__protoID = 55024 
Proto4z.SceneGroupRejectResp.__protoName = "SceneGroupRejectResp" 
Proto4z.SceneGroupRejectResp[1] = {name="retCode", type="ui16" }  
 
Proto4z.register(55025,"SceneGroupLeaveReq") 
Proto4z.SceneGroupLeaveReq = {} --离开编队 
Proto4z.SceneGroupLeaveReq.__protoID = 55025 
Proto4z.SceneGroupLeaveReq.__protoName = "SceneGroupLeaveReq" 
 
Proto4z.register(55026,"SceneGroupLeaveResp") 
Proto4z.SceneGroupLeaveResp = {}  
Proto4z.SceneGroupLeaveResp.__protoID = 55026 
Proto4z.SceneGroupLeaveResp.__protoName = "SceneGroupLeaveResp" 
Proto4z.SceneGroupLeaveResp[1] = {name="retCode", type="ui16" }  
 
Proto4z.register(55027,"ChatReq") 
Proto4z.ChatReq = {}  
Proto4z.ChatReq.__protoID = 55027 
Proto4z.ChatReq.__protoName = "ChatReq" 
Proto4z.ChatReq[1] = {name="channelID", type="ui16" }  
Proto4z.ChatReq[2] = {name="targetID", type="ui64" }  
Proto4z.ChatReq[3] = {name="msg", type="string" }  
 
Proto4z.register(55028,"ChatResp") 
Proto4z.ChatResp = {}  
Proto4z.ChatResp.__protoID = 55028 
Proto4z.ChatResp.__protoName = "ChatResp" 
Proto4z.ChatResp[1] = {name="channelID", type="ui16" }  
Proto4z.ChatResp[2] = {name="sourceID", type="ui64" }  
Proto4z.ChatResp[3] = {name="sourceName", type="string" }  
Proto4z.ChatResp[4] = {name="targetID", type="ui64" }  
Proto4z.ChatResp[5] = {name="targetName", type="string" }  
Proto4z.ChatResp[6] = {name="msg", type="string" }  
Proto4z.ChatResp[7] = {name="chatTime", type="ui64" }  
 
Proto4z.register(55029,"PingPongReq") 
Proto4z.PingPongReq = {}  
Proto4z.PingPongReq.__protoID = 55029 
Proto4z.PingPongReq.__protoName = "PingPongReq" 
Proto4z.PingPongReq[1] = {name="msg", type="string" }  
 
Proto4z.register(55030,"PingPongResp") 
Proto4z.PingPongResp = {}  
Proto4z.PingPongResp.__protoID = 55030 
Proto4z.PingPongResp.__protoName = "PingPongResp" 
Proto4z.PingPongResp[1] = {name="msg", type="string" }  
 
Proto4z.register(55031,"ChangeIconIDReq") 
Proto4z.ChangeIconIDReq = {}  
Proto4z.ChangeIconIDReq.__protoID = 55031 
Proto4z.ChangeIconIDReq.__protoName = "ChangeIconIDReq" 
Proto4z.ChangeIconIDReq[1] = {name="iconID", type="ui64" }  
 
Proto4z.register(55032,"ChangeIconIDResp") 
Proto4z.ChangeIconIDResp = {}  
Proto4z.ChangeIconIDResp.__protoID = 55032 
Proto4z.ChangeIconIDResp.__protoName = "ChangeIconIDResp" 
Proto4z.ChangeIconIDResp[1] = {name="retCode", type="ui16" }  
Proto4z.ChangeIconIDResp[2] = {name="iconID", type="ui64" }  
 
Proto4z.register(55033,"ChangeModeIDReq") 
Proto4z.ChangeModeIDReq = {}  
Proto4z.ChangeModeIDReq.__protoID = 55033 
Proto4z.ChangeModeIDReq.__protoName = "ChangeModeIDReq" 
Proto4z.ChangeModeIDReq[1] = {name="modeID", type="ui64" }  
 
Proto4z.register(55034,"ChangeModeIDResp") 
Proto4z.ChangeModeIDResp = {}  
Proto4z.ChangeModeIDResp.__protoID = 55034 
Proto4z.ChangeModeIDResp.__protoName = "ChangeModeIDResp" 
Proto4z.ChangeModeIDResp[1] = {name="retCode", type="ui16" }  
Proto4z.ChangeModeIDResp[2] = {name="modeID", type="ui64" }  

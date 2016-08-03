 
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
Proto4z.CreateAvatarReq[2] = {name="userName", type="string" }  
 
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
Proto4z.AttachAvatarResp[2] = {name="avatarID", type="ui64" }  
 
Proto4z.register(40018,"GetSceneTokenInfoReq") 
Proto4z.GetSceneTokenInfoReq = {}  
Proto4z.GetSceneTokenInfoReq.__protoID = 40018 
Proto4z.GetSceneTokenInfoReq.__protoName = "GetSceneTokenInfoReq" 
 
Proto4z.register(40019,"GetSceneTokenInfoResp") 
Proto4z.GetSceneTokenInfoResp = {}  
Proto4z.GetSceneTokenInfoResp.__protoID = 40019 
Proto4z.GetSceneTokenInfoResp.__protoName = "GetSceneTokenInfoResp" 
Proto4z.GetSceneTokenInfoResp[1] = {name="retCode", type="ui16" }  
Proto4z.GetSceneTokenInfoResp[2] = {name="tokenInfo", type="SceneTokenInfo" }  
 
Proto4z.register(40020,"JoinSceneReq") 
Proto4z.JoinSceneReq = {}  
Proto4z.JoinSceneReq.__protoID = 40020 
Proto4z.JoinSceneReq.__protoName = "JoinSceneReq" 
Proto4z.JoinSceneReq[1] = {name="spaceType", type="ui16" }  
Proto4z.JoinSceneReq[2] = {name="mapID", type="ui32" }  
 
Proto4z.register(40021,"JoinSceneResp") 
Proto4z.JoinSceneResp = {}  
Proto4z.JoinSceneResp.__protoID = 40021 
Proto4z.JoinSceneResp.__protoName = "JoinSceneResp" 
Proto4z.JoinSceneResp[1] = {name="retCode", type="ui16" }  
Proto4z.JoinSceneResp[2] = {name="tokenInfo", type="SceneTokenInfo" }  
 
Proto4z.register(40022,"JoinSceneNotice") 
Proto4z.JoinSceneNotice = {}  
Proto4z.JoinSceneNotice.__protoID = 40022 
Proto4z.JoinSceneNotice.__protoName = "JoinSceneNotice" 
Proto4z.JoinSceneNotice[1] = {name="tokenInfo", type="SceneTokenInfo" }  
 
Proto4z.register(40023,"LeaveSceneReq") 
Proto4z.LeaveSceneReq = {}  
Proto4z.LeaveSceneReq.__protoID = 40023 
Proto4z.LeaveSceneReq.__protoName = "LeaveSceneReq" 
Proto4z.LeaveSceneReq[1] = {name="spaceID", type="ui32" }  
 
Proto4z.register(40024,"LeaveSceneResp") 
Proto4z.LeaveSceneResp = {}  
Proto4z.LeaveSceneResp.__protoID = 40024 
Proto4z.LeaveSceneResp.__protoName = "LeaveSceneResp" 
Proto4z.LeaveSceneResp[1] = {name="retCode", type="ui16" }  
Proto4z.LeaveSceneResp[2] = {name="tokenInfo", type="SceneTokenInfo" }  
 
Proto4z.register(40014,"ChatReq") 
Proto4z.ChatReq = {}  
Proto4z.ChatReq.__protoID = 40014 
Proto4z.ChatReq.__protoName = "ChatReq" 
Proto4z.ChatReq[1] = {name="avatarID", type="ui64" }  
Proto4z.ChatReq[2] = {name="msg", type="string" }  
 
Proto4z.register(40015,"ChatResp") 
Proto4z.ChatResp = {}  
Proto4z.ChatResp.__protoID = 40015 
Proto4z.ChatResp.__protoName = "ChatResp" 
Proto4z.ChatResp[1] = {name="fromAvatarID", type="ui64" }  
Proto4z.ChatResp[2] = {name="msg", type="string" }  
 
Proto4z.register(40016,"PingPongReq") 
Proto4z.PingPongReq = {}  
Proto4z.PingPongReq.__protoID = 40016 
Proto4z.PingPongReq.__protoName = "PingPongReq" 
Proto4z.PingPongReq[1] = {name="msg", type="string" }  
 
Proto4z.register(40017,"PingPongResp") 
Proto4z.PingPongResp = {}  
Proto4z.PingPongResp.__protoID = 40017 
Proto4z.PingPongResp.__protoName = "PingPongResp" 
Proto4z.PingPongResp[1] = {name="msg", type="string" }  

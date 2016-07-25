 
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
Proto4z.ClientAuthResp[4] = {name="previews", type="UserPreviewArray" }  
 
Proto4z.register(40003,"CreateUserReq") 
Proto4z.CreateUserReq = {} --创角色请求 
Proto4z.CreateUserReq.__protoID = 40003 
Proto4z.CreateUserReq.__protoName = "CreateUserReq" 
Proto4z.CreateUserReq[1] = {name="accountName", type="string" } --这个字段会被服务器填充.客户端可以不填写 
Proto4z.CreateUserReq[2] = {name="userName", type="string" }  
 
Proto4z.register(40004,"CreateUserResp") 
Proto4z.CreateUserResp = {} --创角色请求返回 
Proto4z.CreateUserResp.__protoID = 40004 
Proto4z.CreateUserResp.__protoName = "CreateUserResp" 
Proto4z.CreateUserResp[1] = {name="retCode", type="ui16" }  
Proto4z.CreateUserResp[2] = {name="userID", type="ui64" }  
Proto4z.CreateUserResp[3] = {name="previews", type="UserPreviewArray" }  
 
Proto4z.register(40005,"AttachUserReq") 
Proto4z.AttachUserReq = {} --选角色请求 
Proto4z.AttachUserReq.__protoID = 40005 
Proto4z.AttachUserReq.__protoName = "AttachUserReq" 
Proto4z.AttachUserReq[1] = {name="accountName", type="string" } --这个字段会被服务器填充.客户端可以不填写 
Proto4z.AttachUserReq[2] = {name="userID", type="ui64" }  
 
Proto4z.register(40006,"AttachUserResp") 
Proto4z.AttachUserResp = {} --选角色请求返回 
Proto4z.AttachUserResp.__protoID = 40006 
Proto4z.AttachUserResp.__protoName = "AttachUserResp" 
Proto4z.AttachUserResp[1] = {name="retCode", type="ui16" }  
Proto4z.AttachUserResp[2] = {name="userID", type="ui64" }  
 
Proto4z.register(40027,"GetSpaceTokenInfoReq") 
Proto4z.GetSpaceTokenInfoReq = {}  
Proto4z.GetSpaceTokenInfoReq.__protoID = 40027 
Proto4z.GetSpaceTokenInfoReq.__protoName = "GetSpaceTokenInfoReq" 
 
Proto4z.register(40028,"GetSpaceTokenInfoResp") 
Proto4z.GetSpaceTokenInfoResp = {}  
Proto4z.GetSpaceTokenInfoResp.__protoID = 40028 
Proto4z.GetSpaceTokenInfoResp.__protoName = "GetSpaceTokenInfoResp" 
Proto4z.GetSpaceTokenInfoResp[1] = {name="tokenInfo", type="SpaceTokenInfo" }  
 
Proto4z.register(40020,"JoinSpaceReq") 
Proto4z.JoinSpaceReq = {}  
Proto4z.JoinSpaceReq.__protoID = 40020 
Proto4z.JoinSpaceReq.__protoName = "JoinSpaceReq" 
Proto4z.JoinSpaceReq[1] = {name="spaceType", type="ui16" }  
Proto4z.JoinSpaceReq[2] = {name="mapID", type="ui32" }  
 
Proto4z.register(40021,"JoinSpaceResp") 
Proto4z.JoinSpaceResp = {}  
Proto4z.JoinSpaceResp.__protoID = 40021 
Proto4z.JoinSpaceResp.__protoName = "JoinSpaceResp" 
Proto4z.JoinSpaceResp[1] = {name="retCode", type="ui16" }  
Proto4z.JoinSpaceResp[2] = {name="spaceInfo", type="SpaceTokenInfo" }  
 
Proto4z.register(40024,"JoinSpaceNotice") 
Proto4z.JoinSpaceNotice = {}  
Proto4z.JoinSpaceNotice.__protoID = 40024 
Proto4z.JoinSpaceNotice.__protoName = "JoinSpaceNotice" 
Proto4z.JoinSpaceNotice[1] = {name="spaceInfo", type="SpaceTokenInfo" }  
 
Proto4z.register(40025,"LeaveSpaceReq") 
Proto4z.LeaveSpaceReq = {}  
Proto4z.LeaveSpaceReq.__protoID = 40025 
Proto4z.LeaveSpaceReq.__protoName = "LeaveSpaceReq" 
Proto4z.LeaveSpaceReq[1] = {name="spaceID", type="ui32" }  
 
Proto4z.register(40026,"LeaveSpaceResp") 
Proto4z.LeaveSpaceResp = {}  
Proto4z.LeaveSpaceResp.__protoID = 40026 
Proto4z.LeaveSpaceResp.__protoName = "LeaveSpaceResp" 
Proto4z.LeaveSpaceResp[1] = {name="retCode", type="ui16" }  
Proto4z.LeaveSpaceResp[2] = {name="spaceInfo", type="SpaceTokenInfo" }  
 
Proto4z.register(40007,"UserChatReq") 
Proto4z.UserChatReq = {}  
Proto4z.UserChatReq.__protoID = 40007 
Proto4z.UserChatReq.__protoName = "UserChatReq" 
Proto4z.UserChatReq[1] = {name="userID", type="ui64" }  
Proto4z.UserChatReq[2] = {name="msg", type="string" }  
 
Proto4z.register(40008,"UserChatResp") 
Proto4z.UserChatResp = {}  
Proto4z.UserChatResp.__protoID = 40008 
Proto4z.UserChatResp.__protoName = "UserChatResp" 
Proto4z.UserChatResp[1] = {name="fromUserID", type="ui64" }  
Proto4z.UserChatResp[2] = {name="msg", type="string" }  
 
Proto4z.register(40009,"UserPingPongReq") 
Proto4z.UserPingPongReq = {}  
Proto4z.UserPingPongReq.__protoID = 40009 
Proto4z.UserPingPongReq.__protoName = "UserPingPongReq" 
Proto4z.UserPingPongReq[1] = {name="msg", type="string" }  
 
Proto4z.register(40010,"UserPingPongResp") 
Proto4z.UserPingPongResp = {}  
Proto4z.UserPingPongResp.__protoID = 40010 
Proto4z.UserPingPongResp.__protoName = "UserPingPongResp" 
Proto4z.UserPingPongResp[1] = {name="msg", type="string" }  

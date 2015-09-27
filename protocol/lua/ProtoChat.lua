 
Proto4z.CHANNEL_PRIVATE = 0--私聊, 需要指明具体某个uid 
Proto4z.CHANNEL_WORLD = 1--世界 
Proto4z.CHANNEL_GROUP = 2--群组, 需要指明具体某个groupid 
 
Proto4z.register(1100,"JoinGropuReq") 
Proto4z.JoinGropuReq = {} --加入频道 
Proto4z.JoinGropuReq.__getID = 1100 
Proto4z.JoinGropuReq.__getName = "JoinGropuReq" 
Proto4z.JoinGropuReq[1] = {name="chlType", type="ui8" } --channel type 
 
Proto4z.register(1101,"JoinGropuAck") 
Proto4z.JoinGropuAck = {}  
Proto4z.JoinGropuAck.__getID = 1101 
Proto4z.JoinGropuAck.__getName = "JoinGropuAck" 
Proto4z.JoinGropuAck[1] = {name="retCode", type="ui16" }  
Proto4z.JoinGropuAck[2] = {name="chlType", type="ui8" } --channel type 
 
Proto4z.register(1102,"LeaveGropuReq") 
Proto4z.LeaveGropuReq = {} --加入频道 
Proto4z.LeaveGropuReq.__getID = 1102 
Proto4z.LeaveGropuReq.__getName = "LeaveGropuReq" 
Proto4z.LeaveGropuReq[1] = {name="chlType", type="ui8" } --channel type 
 
Proto4z.register(1103,"LeaveGropuAck") 
Proto4z.LeaveGropuAck = {}  
Proto4z.LeaveGropuAck.__getID = 1103 
Proto4z.LeaveGropuAck.__getName = "LeaveGropuAck" 
Proto4z.LeaveGropuAck[1] = {name="retCode", type="ui16" }  
Proto4z.LeaveGropuAck[2] = {name="chlType", type="ui8" } --channel type 
 
Proto4z.ChatInfo = {} --聊天消息 
Proto4z.ChatInfo.__getName = "ChatInfo" 
Proto4z.ChatInfo[1] = {name="mID", type="ui64" } --msg id 
Proto4z.ChatInfo[2] = {name="chlType", type="ui8" } --channel type 
Proto4z.ChatInfo[3] = {name="srcID", type="ui64" }  
Proto4z.ChatInfo[4] = {name="srcName", type="string" } --src 
Proto4z.ChatInfo[5] = {name="srcIcon", type="i16" } --src 
Proto4z.ChatInfo[6] = {name="dstID", type="ui64" } --userid or groupid 
Proto4z.ChatInfo[7] = {name="dstName", type="string" } --src 
Proto4z.ChatInfo[8] = {name="dstIcon", type="i16" } --src 
Proto4z.ChatInfo[9] = {name="msg", type="string" }  
Proto4z.ChatInfo[10] = {name="sendTime", type="ui32" }  
 
Proto4z.ChatInfoArray = {}  
Proto4z.ChatInfoArray.__getName = "ChatInfoArray" 
Proto4z.ChatInfoArray.__getDesc = "array" 
Proto4z.ChatInfoArray.__getTypeV = "ChatInfo" 
 
Proto4z.register(1104,"ChatReq") 
Proto4z.ChatReq = {} --发送聊天请求 
Proto4z.ChatReq.__getID = 1104 
Proto4z.ChatReq.__getName = "ChatReq" 
Proto4z.ChatReq[1] = {name="chlType", type="ui8" } --channel type 
Proto4z.ChatReq[2] = {name="dstID", type="ui64" } --userID or groupID 
Proto4z.ChatReq[3] = {name="msg", type="string" } --msg 
 
Proto4z.register(1105,"ChatAck") 
Proto4z.ChatAck = {} --发送聊天请求 
Proto4z.ChatAck.__getID = 1105 
Proto4z.ChatAck.__getName = "ChatAck" 
Proto4z.ChatAck[1] = {name="retCode", type="ui16" }  
Proto4z.ChatAck[2] = {name="chlType", type="ui8" } --channel type 
Proto4z.ChatAck[3] = {name="dstID", type="ui64" } --userID or groupID 
Proto4z.ChatAck[4] = {name="msgID", type="ui64" }  
 
Proto4z.register(1106,"ChatNotice") 
Proto4z.ChatNotice = {} --聊天通知 
Proto4z.ChatNotice.__getID = 1106 
Proto4z.ChatNotice.__getName = "ChatNotice" 
Proto4z.ChatNotice[1] = {name="retCode", type="ui16" }  
Proto4z.ChatNotice[2] = {name="msgs", type="ChatInfoArray" }  

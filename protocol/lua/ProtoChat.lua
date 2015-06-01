Proto4z.FRIEND_WAITING = 0--等待好友同意 
Proto4z.FRIEND_REQUESTING = 1--等待确认 
Proto4z.FRIEND_BLACKLIST = 2--黑名单 
Proto4z.FRIEND_ESTABLISHED = 3--好友 
Proto4z.FRIEND_ADDFRIEND = 0--添加好友 
Proto4z.FRIEND_ADDBLACK = 1--添加黑名单 
Proto4z.FRIEND_REMOVEFRIEND = 2--移除好友 
Proto4z.FRIEND_REMOVEBLACK = 3--移除黑名单 
Proto4z.FRIEND_ALLOW = 4--同意 
Proto4z.FRIEND_REJECT = 5--拒绝 
Proto4z.FRIEND_IGNORE = 6--忽略 
Proto4z.CHANNEL_PRIVATE = 0--私聊, 需要指明具体某个uid 
Proto4z.CHANNEL_WORLD = 1--世界 
Proto4z.CHANNEL_GROUP = 2--群组, 需要指明具体某个groupid 
 
Proto4z.FriendInfo = {} --好友信息 
Proto4z.FriendInfo.__getName = "FriendInfo" 
Proto4z.FriendInfo.__getTag = "1111" 
Proto4z.FriendInfo[1] = {name="ownID", type="ui64" }  
Proto4z.FriendInfo[2] = {name="fID", type="ui64" }  
Proto4z.FriendInfo[3] = {name="flag", type="ui8" } --状态标志 
Proto4z.FriendInfo[4] = {name="makeTime", type="ui32" } --建立时间 
 
Proto4z.FriendInfoArray = {}  
Proto4z.FriendInfoArray.__getName = "FriendInfoArray" 
Proto4z.FriendInfoArray.__getDesc = "array" 
Proto4z.FriendInfoArray.__getTypeV = "FriendInfo" 
 
Proto4z.ContactInfo = {} --联系人卡片 
Proto4z.ContactInfo.__getName = "ContactInfo" 
Proto4z.ContactInfo.__getTag = "111111" 
Proto4z.ContactInfo[1] = {name="uID", type="ui64" }  
Proto4z.ContactInfo[2] = {name="nickName", type="string" } --用户昵称 
Proto4z.ContactInfo[3] = {name="iconID", type="i16" } --头像 
Proto4z.ContactInfo[4] = {name="banned", type="ui8" } --禁言 
Proto4z.ContactInfo[5] = {name="groupID", type="ui64" } --加入的群组ID, 0为没有加入任何群组 
Proto4z.ContactInfo[6] = {name="onlineFlag", type="ui8" } --在线状态0离线,1在线 
 
Proto4z.ContactInfoArray = {}  
Proto4z.ContactInfoArray.__getName = "ContactInfoArray" 
Proto4z.ContactInfoArray.__getDesc = "array" 
Proto4z.ContactInfoArray.__getTypeV = "ContactInfo" 
 
Proto4z.ChatInfo = {} --聊天消息 
Proto4z.ChatInfo.__getName = "ChatInfo" 
Proto4z.ChatInfo.__getTag = "1111111111" 
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
 
Proto4z.register(1000,"GetContactInfoReq") 
Proto4z.GetContactInfoReq = {} --获取联系人名片请求 
Proto4z.GetContactInfoReq.__getID = 1000 
Proto4z.GetContactInfoReq.__getName = "GetContactInfoReq" 
Proto4z.GetContactInfoReq.__getTag = "1" 
Proto4z.GetContactInfoReq[1] = {name="uID", type="ui64" }  
 
Proto4z.register(1001,"GetContactInfoAck") 
Proto4z.GetContactInfoAck = {} --获取联系人名片结果 
Proto4z.GetContactInfoAck.__getID = 1001 
Proto4z.GetContactInfoAck.__getName = "GetContactInfoAck" 
Proto4z.GetContactInfoAck.__getTag = "11" 
Proto4z.GetContactInfoAck[1] = {name="retCode", type="ui16" }  
Proto4z.GetContactInfoAck[2] = {name="contact", type="ContactInfo" }  
 
Proto4z.register(1002,"GetSomeStrangersReq") 
Proto4z.GetSomeStrangersReq = {} --获取一些陌生人 
Proto4z.GetSomeStrangersReq.__getID = 1002 
Proto4z.GetSomeStrangersReq.__getName = "GetSomeStrangersReq" 
Proto4z.GetSomeStrangersReq.__getTag = "" 
 
Proto4z.register(1003,"GetSomeStrangersAck") 
Proto4z.GetSomeStrangersAck = {} --获取一些陌生人 
Proto4z.GetSomeStrangersAck.__getID = 1003 
Proto4z.GetSomeStrangersAck.__getName = "GetSomeStrangersAck" 
Proto4z.GetSomeStrangersAck.__getTag = "11" 
Proto4z.GetSomeStrangersAck[1] = {name="retCode", type="ui16" }  
Proto4z.GetSomeStrangersAck[2] = {name="uIDs", type="UserIDArray" }  
 
Proto4z.register(1004,"FriendOperationReq") 
Proto4z.FriendOperationReq = {} --好友操作请求 
Proto4z.FriendOperationReq.__getID = 1004 
Proto4z.FriendOperationReq.__getName = "FriendOperationReq" 
Proto4z.FriendOperationReq.__getTag = "11" 
Proto4z.FriendOperationReq[1] = {name="uID", type="ui64" } --目标ID 
Proto4z.FriendOperationReq[2] = {name="oFlag", type="ui8" } --操作指令 
 
Proto4z.register(1005,"FriendOperationAck") 
Proto4z.FriendOperationAck = {} --好友操作请求结果 
Proto4z.FriendOperationAck.__getID = 1005 
Proto4z.FriendOperationAck.__getName = "FriendOperationAck" 
Proto4z.FriendOperationAck.__getTag = "1111" 
Proto4z.FriendOperationAck[1] = {name="retCode", type="ui16" }  
Proto4z.FriendOperationAck[2] = {name="srcUID", type="ui64" }  
Proto4z.FriendOperationAck[3] = {name="srcFlag", type="ui8" }  
Proto4z.FriendOperationAck[4] = {name="dstUID", type="ui64" }  
 
Proto4z.register(1006,"JoinGropuReq") 
Proto4z.JoinGropuReq = {} --加入群组 
Proto4z.JoinGropuReq.__getID = 1006 
Proto4z.JoinGropuReq.__getName = "JoinGropuReq" 
Proto4z.JoinGropuReq.__getTag = "" 
 
Proto4z.register(1007,"JoinGropuAck") 
Proto4z.JoinGropuAck = {} --加入群组 
Proto4z.JoinGropuAck.__getID = 1007 
Proto4z.JoinGropuAck.__getName = "JoinGropuAck" 
Proto4z.JoinGropuAck.__getTag = "" 
 
Proto4z.register(1008,"ChatReq") 
Proto4z.ChatReq = {} --发送聊天请求 
Proto4z.ChatReq.__getID = 1008 
Proto4z.ChatReq.__getName = "ChatReq" 
Proto4z.ChatReq.__getTag = "111" 
Proto4z.ChatReq[1] = {name="chlType", type="ui8" } --channel type 
Proto4z.ChatReq[2] = {name="dstID", type="ui64" } --userID or groupID 
Proto4z.ChatReq[3] = {name="msg", type="string" } --msg 
 
Proto4z.register(1009,"ChatAck") 
Proto4z.ChatAck = {} --发送聊天请求 
Proto4z.ChatAck.__getID = 1009 
Proto4z.ChatAck.__getName = "ChatAck" 
Proto4z.ChatAck.__getTag = "1111" 
Proto4z.ChatAck[1] = {name="retCode", type="ui16" }  
Proto4z.ChatAck[2] = {name="chlType", type="ui8" } --channel type 
Proto4z.ChatAck[3] = {name="dstID", type="ui64" } --userID or groupID 
Proto4z.ChatAck[4] = {name="msgID", type="ui64" }  
 
Proto4z.register(1010,"ChatNotice") 
Proto4z.ChatNotice = {} --聊天通知 
Proto4z.ChatNotice.__getID = 1010 
Proto4z.ChatNotice.__getName = "ChatNotice" 
Proto4z.ChatNotice.__getTag = "11" 
Proto4z.ChatNotice[1] = {name="retCode", type="ui16" }  
Proto4z.ChatNotice[2] = {name="msgs", type="ChatInfoArray" }  

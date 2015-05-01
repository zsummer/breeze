Protoz.FRIEND_WAITING = 0--等待好友同意 
Protoz.FRIEND_REQUESTING = 1--等待确认 
Protoz.FRIEND_BLACKLIST = 2--黑名单 
Protoz.FRIEND_ESTABLISHED = 3--好友 
Protoz.FRIEND_ADDFRIEND = 0--添加好友 
Protoz.FRIEND_ADDBLACK = 1--添加黑名单 
Protoz.FRIEND_REMOVEFRIEND = 2--移除好友 
Protoz.FRIEND_REMOVEBLACK = 3--移除黑名单 
Protoz.FRIEND_ALLOW = 4--同意 
Protoz.FRIEND_REJECT = 5--拒绝 
Protoz.FRIEND_IGNORE = 6--忽略 
Protoz.CHANNEL_PRIVATE = 0--私聊, 需要指明具体某个uid 
Protoz.CHANNEL_WORLD = 1--世界 
Protoz.CHANNEL_GROUP = 2--群组, 需要指明具体某个groupid 
 
Protoz.FriendInfo = {} --好友信息 
Protoz.FriendInfo.__getName = "FriendInfo" 
Protoz.FriendInfo.__getTag = "111" 
Protoz.FriendInfo[1] = {name="uid", type="ui64" }  
Protoz.FriendInfo[2] = {name="flag", type="ui8" } --状态标志 
Protoz.FriendInfo[3] = {name="makeTime", type="ui32" } --建立时间 
 
Protoz.FriendInfoArray = {}  
Protoz.FriendInfoArray.__getName = "FriendInfoArray" 
Protoz.FriendInfoArray.__getDesc = "array" 
Protoz.FriendInfoArray.__getTypeV = "FriendInfo" 
 
Protoz.ContactInfo = {} --联系人卡片 
Protoz.ContactInfo.__getName = "ContactInfo" 
Protoz.ContactInfo.__getTag = "11111111" 
Protoz.ContactInfo[1] = {name="uID", type="ui64" }  
Protoz.ContactInfo[2] = {name="nickName", type="string" } --用户昵称 
Protoz.ContactInfo[3] = {name="iconID", type="i16" } --头像 
Protoz.ContactInfo[4] = {name="banned", type="ui8" } --禁言 
Protoz.ContactInfo[5] = {name="totalBlacks", type="ui32" } --被拉黑次数 
Protoz.ContactInfo[6] = {name="totalFriends", type="ui32" } --好友个数 
Protoz.ContactInfo[7] = {name="onlineFlag", type="ui8" } --在线状态0离线,1在线 
Protoz.ContactInfo[8] = {name="friends", type="FriendInfoArray" } --好友信息/黑名单信息/好友请求 
 
Protoz.ContactInfoArray = {}  
Protoz.ContactInfoArray.__getName = "ContactInfoArray" 
Protoz.ContactInfoArray.__getDesc = "array" 
Protoz.ContactInfoArray.__getTypeV = "ContactInfo" 
 
Protoz.ChatInfo = {} --聊天消息 
Protoz.ChatInfo.__getName = "ChatInfo" 
Protoz.ChatInfo.__getTag = "1111111111" 
Protoz.ChatInfo[1] = {name="id", type="ui32" } --msg id 
Protoz.ChatInfo[2] = {name="chlType", type="ui8" } --channel type 
Protoz.ChatInfo[3] = {name="srcid", type="ui64" }  
Protoz.ChatInfo[4] = {name="srcName", type="string" } --src 
Protoz.ChatInfo[5] = {name="srcIcon", type="i16" } --src 
Protoz.ChatInfo[6] = {name="dstid", type="ui64" } --userid or groupid 
Protoz.ChatInfo[7] = {name="dstName", type="string" } --src 
Protoz.ChatInfo[8] = {name="dstIcon", type="i16" } --src 
Protoz.ChatInfo[9] = {name="msg", type="string" }  
Protoz.ChatInfo[10] = {name="sendTime", type="ui32" }  
 
Protoz.ChatInfoArray = {}  
Protoz.ChatInfoArray.__getName = "ChatInfoArray" 
Protoz.ChatInfoArray.__getDesc = "array" 
Protoz.ChatInfoArray.__getTypeV = "ChatInfo" 
 
Protoz.register(1000,"GetContactInfoReq") 
Protoz.GetContactInfoReq = {} --获取联系人名片请求 
Protoz.GetContactInfoReq.__getID = 1000 
Protoz.GetContactInfoReq.__getName = "GetContactInfoReq" 
Protoz.GetContactInfoReq.__getTag = "1" 
Protoz.GetContactInfoReq[1] = {name="uid", type="ui64" }  
 
Protoz.register(1001,"GetContactInfoAck") 
Protoz.GetContactInfoAck = {} --获取联系人名片结果 
Protoz.GetContactInfoAck.__getID = 1001 
Protoz.GetContactInfoAck.__getName = "GetContactInfoAck" 
Protoz.GetContactInfoAck.__getTag = "11" 
Protoz.GetContactInfoAck[1] = {name="retCode", type="ui16" }  
Protoz.GetContactInfoAck[2] = {name="contact", type="ContactInfo" }  
 
Protoz.register(1004,"FriendOperationReq") 
Protoz.FriendOperationReq = {} --好友操作请求 
Protoz.FriendOperationReq.__getID = 1004 
Protoz.FriendOperationReq.__getName = "FriendOperationReq" 
Protoz.FriendOperationReq.__getTag = "11" 
Protoz.FriendOperationReq[1] = {name="uid", type="ui64" } --目标ID 
Protoz.FriendOperationReq[2] = {name="oFlag", type="ui8" } --操作指令 
 
Protoz.register(1005,"FriendOperationAck") 
Protoz.FriendOperationAck = {} --好友操作请求结果 
Protoz.FriendOperationAck.__getID = 1005 
Protoz.FriendOperationAck.__getName = "FriendOperationAck" 
Protoz.FriendOperationAck.__getTag = "1111" 
Protoz.FriendOperationAck[1] = {name="retCode", type="ui16" }  
Protoz.FriendOperationAck[2] = {name="srcUID", type="ui64" }  
Protoz.FriendOperationAck[3] = {name="srcFlag", type="ui8" }  
Protoz.FriendOperationAck[4] = {name="dstUID", type="ui64" }  
 
Protoz.register(1006,"ChatReq") 
Protoz.ChatReq = {} --发送聊天请求 
Protoz.ChatReq.__getID = 1006 
Protoz.ChatReq.__getName = "ChatReq" 
Protoz.ChatReq.__getTag = "111" 
Protoz.ChatReq[1] = {name="chlType", type="ui8" } --channel type 
Protoz.ChatReq[2] = {name="dstid", type="ui64" } --userid or groupid 
Protoz.ChatReq[3] = {name="msg", type="string" } --msg 
 
Protoz.register(1007,"ChatAck") 
Protoz.ChatAck = {} --发送聊天请求 
Protoz.ChatAck.__getID = 1007 
Protoz.ChatAck.__getName = "ChatAck" 
Protoz.ChatAck.__getTag = "1111" 
Protoz.ChatAck[1] = {name="retCode", type="ui16" }  
Protoz.ChatAck[2] = {name="chlType", type="ui8" } --channel type 
Protoz.ChatAck[3] = {name="dstid", type="ui64" } --userid or groupid 
Protoz.ChatAck[4] = {name="msgid", type="ui32" }  
 
Protoz.register(1008,"ChatNotice") 
Protoz.ChatNotice = {} --聊天通知 
Protoz.ChatNotice.__getID = 1008 
Protoz.ChatNotice.__getName = "ChatNotice" 
Protoz.ChatNotice.__getTag = "11" 
Protoz.ChatNotice[1] = {name="retCode", type="ui16" }  
Protoz.ChatNotice[2] = {name="msgs", type="ChatInfoArray" }  

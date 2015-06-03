Proto4z.FRIEND_DELETED = 0--已删除好友关系 
Proto4z.FRIEND_WAITING = 1--等待好友确认 
Proto4z.FRIEND_REQUESTING = 2--需要确认 
Proto4z.FRIEND_BLACKLIST = 3--黑名单 
Proto4z.FRIEND_ESTABLISHED = 4--好友 
Proto4z.FRIEND_ADD_FRIEND = 0--添加好友 
Proto4z.FRIEND_REMOVE_FRIEND = 1--移除好友 
Proto4z.FRIEND_ADD_BLACKLIST = 2--添加黑名单 
Proto4z.FRIEND_REMOVE_BLACKLIST = 3--移除黑名单 
Proto4z.FRIEND_ALLOW = 4--同意 
Proto4z.FRIEND_REJECT = 5--拒绝 
Proto4z.FRIEND_IGNORE = 6--忽略 
 
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
 
Proto4z.register(1000,"GetSomeStrangersReq") 
Proto4z.GetSomeStrangersReq = {} --获取一些陌生人 
Proto4z.GetSomeStrangersReq.__getID = 1000 
Proto4z.GetSomeStrangersReq.__getName = "GetSomeStrangersReq" 
Proto4z.GetSomeStrangersReq.__getTag = "" 
 
Proto4z.register(1001,"GetSomeStrangersAck") 
Proto4z.GetSomeStrangersAck = {} --获取一些陌生人 
Proto4z.GetSomeStrangersAck.__getID = 1001 
Proto4z.GetSomeStrangersAck.__getName = "GetSomeStrangersAck" 
Proto4z.GetSomeStrangersAck.__getTag = "11" 
Proto4z.GetSomeStrangersAck[1] = {name="retCode", type="ui16" }  
Proto4z.GetSomeStrangersAck[2] = {name="uIDs", type="UserIDArray" }  
 
Proto4z.register(1002,"FriendOperationReq") 
Proto4z.FriendOperationReq = {} --好友操作请求 
Proto4z.FriendOperationReq.__getID = 1002 
Proto4z.FriendOperationReq.__getName = "FriendOperationReq" 
Proto4z.FriendOperationReq.__getTag = "11" 
Proto4z.FriendOperationReq[1] = {name="uID", type="ui64" } --目标ID 
Proto4z.FriendOperationReq[2] = {name="oFlag", type="ui8" } --操作指令 
 
Proto4z.register(1003,"FriendOperationAck") 
Proto4z.FriendOperationAck = {} --好友操作请求结果 
Proto4z.FriendOperationAck.__getID = 1003 
Proto4z.FriendOperationAck.__getName = "FriendOperationAck" 
Proto4z.FriendOperationAck.__getTag = "1111" 
Proto4z.FriendOperationAck[1] = {name="retCode", type="ui16" }  
Proto4z.FriendOperationAck[2] = {name="srcUID", type="ui64" }  
Proto4z.FriendOperationAck[3] = {name="srcFlag", type="ui8" }  
Proto4z.FriendOperationAck[4] = {name="dstUID", type="ui64" }  

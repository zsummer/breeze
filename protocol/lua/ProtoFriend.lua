Proto4z.FRIEND_DELETED = 0--已删除好友关系 
Proto4z.FRIEND_WAITING = 1--等待好友确认 
Proto4z.FRIEND_REQUESTING = 2--需要确认 
Proto4z.FRIEND_BLACKLIST = 3--黑名单 
Proto4z.FRIEND_ESTABLISHED = 4--好友 
Proto4z.FRIEND_ALLOW = 0--同意 
Proto4z.FRIEND_REJECT = 1--拒绝 
Proto4z.FRIEND_IGNORE = 2--忽略 
 
Proto4z.FriendInfo = {} --好友信息 
Proto4z.FriendInfo.__getName = "FriendInfo" 
Proto4z.FriendInfo.__getTag = "111111" 
Proto4z.FriendInfo[1] = {name="ownID", type="ui64" }  
Proto4z.FriendInfo[2] = {name="fID", type="ui64" }  
Proto4z.FriendInfo[3] = {name="flag", type="ui8" } --状态标志 
Proto4z.FriendInfo[4] = {name="online", type="ui8" } --好友是否在线,不需要存数据库 
Proto4z.FriendInfo[5] = {name="makeTime", type="ui32" } --建立时间 
Proto4z.FriendInfo[6] = {name="lastChanged", type="ui32" } --最后更改时间 
 
Proto4z.FriendInfoArray = {}  
Proto4z.FriendInfoArray.__getName = "FriendInfoArray" 
Proto4z.FriendInfoArray.__getDesc = "array" 
Proto4z.FriendInfoArray.__getTypeV = "FriendInfo" 
 
Proto4z.register(1000,"GetFriendsReq") 
Proto4z.GetFriendsReq = {} --获取好友列表 
Proto4z.GetFriendsReq.__getID = 1000 
Proto4z.GetFriendsReq.__getName = "GetFriendsReq" 
Proto4z.GetFriendsReq.__getTag = "" 
 
Proto4z.register(1001,"UpdateFriendsNotice") 
Proto4z.UpdateFriendsNotice = {} --好友列表推送通知 
Proto4z.UpdateFriendsNotice.__getID = 1001 
Proto4z.UpdateFriendsNotice.__getName = "UpdateFriendsNotice" 
Proto4z.UpdateFriendsNotice.__getTag = "1" 
Proto4z.UpdateFriendsNotice[1] = {name="friends", type="FriendInfoArray" }  
 
Proto4z.register(1002,"AddFriendReq") 
Proto4z.AddFriendReq = {} --添加好友请求 
Proto4z.AddFriendReq.__getID = 1002 
Proto4z.AddFriendReq.__getName = "AddFriendReq" 
Proto4z.AddFriendReq.__getTag = "1" 
Proto4z.AddFriendReq[1] = {name="dst", type="ui64" } --目标ID 
 
Proto4z.register(1003,"AddFriendReply") 
Proto4z.AddFriendReply = {} --答复好友请求 
Proto4z.AddFriendReply.__getID = 1003 
Proto4z.AddFriendReply.__getName = "AddFriendReply" 
Proto4z.AddFriendReply.__getTag = "11" 
Proto4z.AddFriendReply[1] = {name="dst", type="ui64" } --目标ID 
Proto4z.AddFriendReply[2] = {name="flag", type="ui8" } --状态标志 
 
Proto4z.register(1004,"AddFriendAck") 
Proto4z.AddFriendAck = {} --添加好友请求结果 
Proto4z.AddFriendAck.__getID = 1004 
Proto4z.AddFriendAck.__getName = "AddFriendAck" 
Proto4z.AddFriendAck.__getTag = "11" 
Proto4z.AddFriendAck[1] = {name="retCode", type="ui16" }  
Proto4z.AddFriendAck[2] = {name="dst", type="ui64" } --目标ID 
 
Proto4z.register(1005,"DelFriendReq") 
Proto4z.DelFriendReq = {} --删除好友请求 
Proto4z.DelFriendReq.__getID = 1005 
Proto4z.DelFriendReq.__getName = "DelFriendReq" 
Proto4z.DelFriendReq.__getTag = "1" 
Proto4z.DelFriendReq[1] = {name="dst", type="ui64" } --目标ID 
 
Proto4z.register(1006,"DelFriendAck") 
Proto4z.DelFriendAck = {} --删除好友请求结果 
Proto4z.DelFriendAck.__getID = 1006 
Proto4z.DelFriendAck.__getName = "DelFriendAck" 
Proto4z.DelFriendAck.__getTag = "11" 
Proto4z.DelFriendAck[1] = {name="retCode", type="ui16" }  
Proto4z.DelFriendAck[2] = {name="dst", type="ui64" } --目标ID 

Proto4z.FOLLOW_INVALID = 0 
Proto4z.FOLLOW_DELETED = 1--路人 
Proto4z.FOLLOW_HATE = 2--黑 
Proto4z.FOLLOW_FOLLOWING = 3--粉 
 
Proto4z.FollowingInfo = {} --关注 
Proto4z.FollowingInfo.__getName = "FollowingInfo" 
Proto4z.FollowingInfo[1] = {name="following", type="ui64" }  
Proto4z.FollowingInfo[2] = {name="follower", type="ui64" }  
Proto4z.FollowingInfo[3] = {name="status", type="ui8" } --状态标志 
Proto4z.FollowingInfo[4] = {name="makeTime", type="ui32" } --建立时间 
Proto4z.FollowingInfo[5] = {name="lastChanged", type="ui32" } --最后更改时间 
 
Proto4z.FollowingInfoArray = {}  
Proto4z.FollowingInfoArray.__getName = "FollowingInfoArray" 
Proto4z.FollowingInfoArray.__getDesc = "array" 
Proto4z.FollowingInfoArray.__getTypeV = "FollowingInfo" 
 
Proto4z.register(1000,"GetFollowerReq") 
Proto4z.GetFollowerReq = {} --获取粉丝列表 
Proto4z.GetFollowerReq.__getID = 1000 
Proto4z.GetFollowerReq.__getName = "GetFollowerReq" 
Proto4z.GetFollowerReq[1] = {name="uID", type="ui64" }  
Proto4z.GetFollowerReq[2] = {name="status", type="ui8" } --所有/路人/黑/粉 
 
Proto4z.register(1001,"GetFollowerAck") 
Proto4z.GetFollowerAck = {} --获取粉丝列表 
Proto4z.GetFollowerAck.__getID = 1001 
Proto4z.GetFollowerAck.__getName = "GetFollowerAck" 
Proto4z.GetFollowerAck[1] = {name="status", type="ui8" } --所有/路人/黑/粉 
Proto4z.GetFollowerAck[2] = {name="follower", type="FollowingInfoArray" }  
 
Proto4z.register(1010,"GetFollowingReq") 
Proto4z.GetFollowingReq = {} --获取关注列表 
Proto4z.GetFollowingReq.__getID = 1010 
Proto4z.GetFollowingReq.__getName = "GetFollowingReq" 
Proto4z.GetFollowingReq[1] = {name="uID", type="ui64" }  
Proto4z.GetFollowingReq[2] = {name="status", type="ui8" } --所有/路人/黑/粉 
 
Proto4z.register(1011,"GetFollowingAck") 
Proto4z.GetFollowingAck = {} --获取关注列表 
Proto4z.GetFollowingAck.__getID = 1011 
Proto4z.GetFollowingAck.__getName = "GetFollowingAck" 
Proto4z.GetFollowingAck[1] = {name="status", type="ui8" } --所有/路人/黑/粉 
Proto4z.GetFollowingAck[2] = {name="following", type="FollowingInfoArray" }  
 
Proto4z.register(1008,"PokeReq") 
Proto4z.PokeReq = {} --操作 
Proto4z.PokeReq.__getID = 1008 
Proto4z.PokeReq.__getName = "PokeReq" 
Proto4z.PokeReq[1] = {name="dstStatus", type="ui8" } --路人/黑/粉 
Proto4z.PokeReq[2] = {name="following", type="ui64" } --关注目标ID 
 
Proto4z.register(1009,"PokeAck") 
Proto4z.PokeAck = {} --操作 
Proto4z.PokeAck.__getID = 1009 
Proto4z.PokeAck.__getName = "PokeAck" 
Proto4z.PokeAck[1] = {name="follow", type="FollowingInfo" }  

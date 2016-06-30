 
Proto4z.SCENE_STATUS_NONE = 0--无效 
Proto4z.SCENE_STATUS_HOME = 1--主城 
Proto4z.SCENE_STATUS_INSTANCING = 2--副本 
Proto4z.SCENE_STATUS_ARENA = 3--竞技场 
 
Proto4z.register(10000,"SceneStatus") 
Proto4z.SceneStatus = {} --场景状态数据 
Proto4z.SceneStatus.__protoID = 10000 
Proto4z.SceneStatus.__protoName = "SceneStatus" 
Proto4z.SceneStatus[1] = {name="type", type="ui16" } --类型 
Proto4z.SceneStatus[2] = {name="state", type="ui16" } --状态 
Proto4z.SceneStatus[3] = {name="host", type="string" } --服务器host 
Proto4z.SceneStatus[4] = {name="port", type="ui16" } --服务器port 
Proto4z.SceneStatus[5] = {name="spaceID", type="ui32" } --空间(场景,房间,战场)的实例ID 
Proto4z.SceneStatus[6] = {name="token", type="SessionToken" } --令牌 

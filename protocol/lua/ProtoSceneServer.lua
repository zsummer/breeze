 
Proto4z.register(39000,"SceneKnock") 
Proto4z.SceneKnock = {} --战场服务器挂载 
Proto4z.SceneKnock.__protoID = 39000 
Proto4z.SceneKnock.__protoName = "SceneKnock" 
Proto4z.SceneKnock[1] = {name="lineID", type="ui64" } --分线ID 
Proto4z.SceneKnock[2] = {name="pubHost", type="string" }  
Proto4z.SceneKnock[3] = {name="pubPort", type="ui16" }  
 
Proto4z.register(39001,"ScenePulse") 
Proto4z.ScenePulse = {} --集群脉冲 
Proto4z.ScenePulse.__protoID = 39001 
Proto4z.ScenePulse.__protoName = "ScenePulse" 
 
Proto4z.register(39002,"SceneServerJoinGroupIns") 
Proto4z.SceneServerJoinGroupIns = {} --创建/加入编队, 来自docker的指令 
Proto4z.SceneServerJoinGroupIns.__protoID = 39002 
Proto4z.SceneServerJoinGroupIns.__protoName = "SceneServerJoinGroupIns" 
Proto4z.SceneServerJoinGroupIns[1] = {name="groupID", type="ui64" } --编队ID, 0为创建 
Proto4z.SceneServerJoinGroupIns[2] = {name="baseInfo", type="AvatarBaseInfo" } --角色数据 
Proto4z.SceneServerJoinGroupIns[3] = {name="baseProps", type="AvatarPropMap" } --角色属性数据 
 
Proto4z.register(39003,"SceneServerJoinGroupAck") 
Proto4z.SceneServerJoinGroupAck = {} --创建/加入编队响应结果 
Proto4z.SceneServerJoinGroupAck.__protoID = 39003 
Proto4z.SceneServerJoinGroupAck.__protoName = "SceneServerJoinGroupAck" 
Proto4z.SceneServerJoinGroupAck[1] = {name="retCode", type="ui16" }  
Proto4z.SceneServerJoinGroupAck[2] = {name="newGroupID", type="ui64" }  
Proto4z.SceneServerJoinGroupAck[3] = {name="oldGroupID", type="ui64" }  
 
Proto4z.register(39004,"SceneServerEnterSceneIns") 
Proto4z.SceneServerEnterSceneIns = {} --开辟场景 
Proto4z.SceneServerEnterSceneIns.__protoID = 39004 
Proto4z.SceneServerEnterSceneIns.__protoName = "SceneServerEnterSceneIns" 
Proto4z.SceneServerEnterSceneIns[1] = {name="sceneType", type="ui16" } --类型 
Proto4z.SceneServerEnterSceneIns[2] = {name="mapID", type="ui64" }  
Proto4z.SceneServerEnterSceneIns[3] = {name="groups", type="SceneGroupInfoArray" } --多个编队 
 
Proto4z.register(39007,"SceneServerCancelSceneIns") 
Proto4z.SceneServerCancelSceneIns = {} --退出场景 
Proto4z.SceneServerCancelSceneIns.__protoID = 39007 
Proto4z.SceneServerCancelSceneIns.__protoName = "SceneServerCancelSceneIns" 
Proto4z.SceneServerCancelSceneIns[1] = {name="sceneID", type="ui64" } --sceneID 
Proto4z.SceneServerCancelSceneIns[2] = {name="groupID", type="ui64" } --groupID 
 
Proto4z.register(39006,"SceneServerGroupStateChangeIns") 
Proto4z.SceneServerGroupStateChangeIns = {} --scene ==> world 
Proto4z.SceneServerGroupStateChangeIns.__protoID = 39006 
Proto4z.SceneServerGroupStateChangeIns.__protoName = "SceneServerGroupStateChangeIns" 
Proto4z.SceneServerGroupStateChangeIns[1] = {name="sceneID", type="ui64" }  
Proto4z.SceneServerGroupStateChangeIns[2] = {name="groupID", type="ui64" }  
Proto4z.SceneServerGroupStateChangeIns[3] = {name="state", type="ui16" } --如果是NONE 说明离开场景 

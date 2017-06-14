 
Proto4z.register(4000,"SceneKnock") 
Proto4z.SceneKnock = {} --战场服务器挂载 
Proto4z.SceneKnock.__protoID = 4000 
Proto4z.SceneKnock.__protoName = "SceneKnock" 
Proto4z.SceneKnock[1] = {name="lineID", type="ui64" } --分线ID 
Proto4z.SceneKnock[2] = {name="pubHost", type="string" }  
Proto4z.SceneKnock[3] = {name="pubPort", type="ui16" }  
 
Proto4z.register(4001,"ScenePulse") 
Proto4z.ScenePulse = {} --集群脉冲 
Proto4z.ScenePulse.__protoID = 4001 
Proto4z.ScenePulse.__protoName = "ScenePulse" 
 
Proto4z.register(4002,"SceneServerJoinGroupIns") 
Proto4z.SceneServerJoinGroupIns = {} --创建/加入编队, 来自docker的指令 
Proto4z.SceneServerJoinGroupIns.__protoID = 4002 
Proto4z.SceneServerJoinGroupIns.__protoName = "SceneServerJoinGroupIns" 
Proto4z.SceneServerJoinGroupIns[1] = {name="refresh", type="ui64" } --0为客户端请求操作, 1为仅仅刷新数据 
Proto4z.SceneServerJoinGroupIns[2] = {name="groupID", type="ui64" } --编队ID, 0为创建 
Proto4z.SceneServerJoinGroupIns[3] = {name="modelID", type="ui64" } --模型ID 
Proto4z.SceneServerJoinGroupIns[4] = {name="equips", type="DictArrayKey" } --额外装备 
Proto4z.SceneServerJoinGroupIns[5] = {name="avatarID", type="ui64" }  
Proto4z.SceneServerJoinGroupIns[6] = {name="avatarName", type="string" }  
Proto4z.SceneServerJoinGroupIns[7] = {name="rankScore", type="double" } --天梯分数 
 
Proto4z.register(4003,"SceneServerJoinGroupAck") 
Proto4z.SceneServerJoinGroupAck = {} --创建/加入编队响应结果 
Proto4z.SceneServerJoinGroupAck.__protoID = 4003 
Proto4z.SceneServerJoinGroupAck.__protoName = "SceneServerJoinGroupAck" 
Proto4z.SceneServerJoinGroupAck[1] = {name="retCode", type="ui16" }  
Proto4z.SceneServerJoinGroupAck[2] = {name="newGroupID", type="ui64" }  
Proto4z.SceneServerJoinGroupAck[3] = {name="oldGroupID", type="ui64" }  
 
Proto4z.register(4004,"SceneServerEnterSceneIns") 
Proto4z.SceneServerEnterSceneIns = {} --开辟场景 
Proto4z.SceneServerEnterSceneIns.__protoID = 4004 
Proto4z.SceneServerEnterSceneIns.__protoName = "SceneServerEnterSceneIns" 
Proto4z.SceneServerEnterSceneIns[1] = {name="sceneType", type="ui16" } --类型 
Proto4z.SceneServerEnterSceneIns[2] = {name="mapID", type="ui64" }  
Proto4z.SceneServerEnterSceneIns[3] = {name="groups", type="SceneGroupInfoArray" } --多个编队 
 
Proto4z.register(4005,"SceneServerCancelSceneIns") 
Proto4z.SceneServerCancelSceneIns = {} --退出场景 
Proto4z.SceneServerCancelSceneIns.__protoID = 4005 
Proto4z.SceneServerCancelSceneIns.__protoName = "SceneServerCancelSceneIns" 
Proto4z.SceneServerCancelSceneIns[1] = {name="sceneID", type="ui64" } --sceneID 
Proto4z.SceneServerCancelSceneIns[2] = {name="groupID", type="ui64" } --groupID 
 
Proto4z.register(4006,"SceneServerGroupStateFeedback") 
Proto4z.SceneServerGroupStateFeedback = {} --scene ==> world 
Proto4z.SceneServerGroupStateFeedback.__protoID = 4006 
Proto4z.SceneServerGroupStateFeedback.__protoName = "SceneServerGroupStateFeedback" 
Proto4z.SceneServerGroupStateFeedback[1] = {name="sceneID", type="ui64" }  
Proto4z.SceneServerGroupStateFeedback[2] = {name="groupID", type="ui64" }  
Proto4z.SceneServerGroupStateFeedback[3] = {name="state", type="ui16" } --如果是NONE 说明离开场景 
 
Proto4z.register(4008,"EntityScriptNotice") 
Proto4z.EntityScriptNotice = {} --同步给脚本 
Proto4z.EntityScriptNotice.__protoID = 4008 
Proto4z.EntityScriptNotice.__protoName = "EntityScriptNotice" 
Proto4z.EntityScriptNotice[1] = {name="controls", type="EntityControlArray" }  
Proto4z.EntityScriptNotice[2] = {name="skills", type="EntitySkillSystemArray" }  

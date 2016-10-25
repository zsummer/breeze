/*
* breeze License
* Copyright (C) 2015 - 2016 YaweiZhang <yawei.zhang@foxmail.com>.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef _SCENE_H_
#define _SCENE_H_
#include "entity.h"




class Scene : public std::enable_shared_from_this<Scene>
{
    //scene数据
private:
    SceneID _sceneID;
    SceneType _sceneType;
    SceneState _sceneStatus;
    RVO::RVOSimulator *_sim = nullptr;
    EntityID _lastEID;
    double _lastStatusChangeTime;
    double _startTime;
    double _endTime;
    std::map<EntityID, EntityPtr> _entitys;
    std::map<ServiceID, EntityPtr> _players;
    std::queue<std::function<void()>> _asyncs;
    std::map<EntityID, EntityPtr> _monsters;

    double _lastCheckMonstr = 0.0;
public:
    inline SceneID getSceneID() { return _sceneID; }
    inline SceneType getSceneType() { return _sceneType; }
    inline SceneState getSceneState() { return _sceneStatus; }
    inline size_t getEntitysCount() { return _entitys.size(); }
    inline size_t getPlayerCount() { return _players.size(); }
    inline std::map<ServiceID, EntityPtr> & getPlayers() { return _players; }
    GroupID getGroupID(ServiceID avatarID);
    void getSceneSection(SceneSection & ss);
    EntityPtr getEntity(EntityID eID);
    EntityPtr getEntityByAvatarID(ServiceID avatarID);
    EntityPtr addEntity(const AvatarBaseInfo & baseInfo,
        const AvatarPropMap & baseProps,
        EntityCampType camp,
        EntityType etype,
        EntityState state = ENTITY_STATE_ACTIVE,
        GroupID = InvalidGroupID);
    bool removeEntity(EntityID eid);
    bool removePlayer(AvatarID avatarID);
    bool removePlayerByGroupID(GroupID groupID);
    //operator
public:
    void pushAsync(std::function<void()> && func);
    bool doMove(ui64 eid, MoveAction action, double speed, ui64 follow, EPosition clt, EPositionArray dsts);
    bool doSkill(EntityID eid, ui64 skillID);
    bool checkSkillBehaviour();
    bool attackTargets(EntityPtr caster, std::vector<EntityPtr> & targets);
    void checkSceneState();
    bool cleanSkill();
    bool addBuff();
    bool cleanBuff();
    //caster为当前施法者, 如果当前施法者为飞行道具 则搜索目标为self的时候 应当是指master  
    //targetType 如果是none 则忽略该过滤选项  
    //targetSC如果是none 则忽略该选项, 否则取位判断  
    //
    std::vector<EntityPtr> searchTarget(EntityPtr caster, double radian, const SearchInfo & search);
public:
    Scene(SceneID id);
    ~Scene();
    bool cleanScene();
    bool initScene(SceneType sceneType, MapID mapID);
    bool onUpdate();
    void checkStepRVO(bool preCheck);
    void doStepRVO();
    void doMonster();
    void doFollow();
    bool playerAttach(ServiceID avatarID, SessionID sID);
    bool playerDettach(ServiceID avatarID, SessionID sID);
    void onPlayerInstruction(ServiceID avatarID, ReadStream & rs);

public:
    //消息队列 
public:
    template <typename MSG>
    void broadcast(const MSG & msg, ServiceID without = InvalidServiceID);
    template<typename MSG>
    void sendToClient(ServiceID avatarID, const MSG &msg);
};

using ScenePtr = std::shared_ptr<Scene>;





























template<typename MSG>
void Scene::sendToClient(ServiceID avatarID, const MSG &msg)
{
    auto founder = _players.find(avatarID);
    if (founder == _players.end() || founder->second->_clientSessionID == InvalidSessionID)
    {
        return;
    }

    try
    {
        WriteStream ws(MSG::getProtoID());
        ws << msg;
        SessionManager::getRef().sendSessionData(founder->second->_clientSessionID, ws.getStream(), ws.getStreamLen());
    }
    catch (...)
    {
        LOGE("Scene::sendToClient ServiceID=" << avatarID << ",  protoid=" << MSG::getProtoID());
        return;
    }
}


template<typename MSG>
void Scene::broadcast(const MSG &msg, ServiceID without)
{
    try
    {
        WriteStream ws(MSG::getProtoID());
        ws << msg;

        for (auto user : _players)
        {
            if (user.first == without || user.second->_clientSessionID == InvalidSessionID)
            {
                continue;
            }
            SessionManager::getRef().sendSessionData(user.second->_clientSessionID, ws.getStream(), ws.getStreamLen());
        }

    }
    catch (...)
    {
        LOGE("Scene::broadcast protoid=" << MSG::getProtoID());
        return;
    }
}






























#endif

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



class Scene
{
    //scene数据
private:
    SceneID _sceneID;
    SCENE_TYPE _sceneType;
    SCENE_STATUS _sceneStatus;
    RVO::RVOSimulator *_sim = nullptr;
    EntityID _lastEID;
    double _lastStatusChangeTime;
    double _startTime;
    double _endTime;
    std::map<EntityID, EntityPtr> _entitys;
    std::map<ServiceID, EntityPtr> _players;
    std::queue<std::function<void()>> _asyncs;


public:
    inline SceneID getSceneID() { return _sceneID; }
    inline SCENE_TYPE getSceneType() { return _sceneType; }
    inline SCENE_STATUS getSceneStatus() { return _sceneStatus; }
    inline size_t getEntitysCount() { return _entitys.size(); }
    inline size_t getPlayerCount() { return _players.size(); }
    inline std::map<ServiceID, EntityPtr> & getPlayers() { return _players; }
    GroupID getGroupID(ServiceID avatarID);
    void getSceneSection(SceneSection & ss);
    EntityPtr getEntity(EntityID eID);
    EntityPtr getEntityByAvatarID(ServiceID avatarID);

    //operator
public:
    bool pushAsync(std::function<void()> && func);
    bool doMove(ui64 eid, MoveAction action, ui64 follow, EPoint dst, bool clean = true);
    bool doSkill();
    bool cleanSkill();
    bool addBuff();
    bool cleanBuff();
    EntityPtr addEntity(const AvatarBaseInfo & baseInfo,
                        const AvatarPropMap & baseProps,
                        ENTITY_COLOR ecolor,
                        ENTITY_TYPE etype,
                        ENTITY_STATE state = ESTATE_ACTIVE,
                        GroupID = InvalidGroupID);
    bool removeEntity(EntityID eid);
public:
    Scene(SceneID id);
    ~Scene();
    bool cleanScene();
    bool initScene(SCENE_TYPE sceneType, MapID mapID);
    bool onUpdate();
    void doStepRVO();
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

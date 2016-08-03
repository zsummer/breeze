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
    SCENE_TYPE _sceneType;
    SCENE_STATUS _sceneStatus;
    double _lastStatusChangeTime;
    double _startTime;
    double _endTime;

    SceneID _sceneID;
    EntityID _lastEID;
    std::map<EntityID, EntityPtr> _entitys;
    std::map<ServiceID, EntityPtr> _players;
public:
    inline SceneID getSceneID() { return _sceneID; }
    inline SCENE_TYPE getSceneType() { return _sceneType; }
    inline SCENE_STATUS getSceneStatus() { return _sceneStatus; }
    inline size_t getEntitysCount() { return _entitys.size(); }
    inline size_t getUsersCount() { return _players.size(); }
public:
    Scene(SceneID id);
    bool cleanScene();
    bool loadScene(SCENE_TYPE sceneType);
    bool onUpdate();

//    void fillUserProp(const FillUserToSceneReq& req);
    EntityPtr makeNewEntity(const AvatarBaseInfo & base);
    EntityPtr getEntity(EntityID eID);
    EntityPtr getUserEntity(ServiceID avatarID);

    bool addEntity(EntityPtr entity); 
    bool removeEntity(EntityID eid); 
    bool enterScene(ServiceID avatarID, const std::string & token, SessionID sID);
    bool leaveScene(ServiceID avatarID, SessionID sID);

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

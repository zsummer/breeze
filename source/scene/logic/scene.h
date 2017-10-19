/*
* breeze License
* Copyright (C) 2015 - 2017 YaweiZhang <yawei.zhang@foxmail.com>.
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
#include "move.h"
#include "skill.h"
#include "ai.h"
#include "script.h"

class Scene : public std::enable_shared_from_this<Scene>
{
    friend MoveSync;
    friend Skill;
    friend AI;
    friend Script;
    //scene数据
private:
    SceneID _sceneID ;
    MapID _mapID = InvalidMapID;
    SCENE_TYPE _sceneType;
    SCENE_STATE _sceneStatus;
    EntityID _lastEID;
    double _startTime;
    double _endTime;
    std::map<EntityID, EntityPtr> _entitys;
    std::map<ServiceID, EntityPtr> _players;
    std::queue<std::function<void()>> _asyncs;

    
    
public:
    Scene(SceneID sceneID);
    ~Scene();
    bool cleanScene();
    bool initScene(SCENE_TYPE sceneType, MapID mapID);
    bool onUpdate();
public:
    bool playerAttach(ServiceID avatarID, SessionID sID);
    bool playerDettach(ServiceID avatarID, SessionID sID);
    void onPlayerInstruction(ServiceID avatarID, ReadStream & rs);
    //消息队列 
public:
    template <typename MSG>
    void broadcast(const MSG & msg, ServiceID without = InvalidServiceID, bool withScript = true);
    template<typename MSG>
    void sendToClient(ServiceID avatarID, const MSG &msg);
public:
    MoveSyncPtr _move;
    AIPtr _ai;
    SkillPtr _skill;
    ScriptPtr _script;
public:
    inline SceneID getSceneID() { return _sceneID; }
    inline MapID getMapID() { return _mapID; }
    inline SCENE_TYPE getSceneType() { return _sceneType; }
    inline SCENE_STATE getSceneState() { return _sceneStatus; }
    inline size_t getEntitysCount() { return _entitys.size(); }
    inline size_t getPlayerCount() { return _players.size(); }
    inline std::map<ServiceID, EntityPtr> & getPlayers() { return _players; }
    GroupID getGroupID(ServiceID avatarID);
    void getSceneSection(SceneSection & ss);

    EntityPtr getEntity(EntityID eID);
    EntityPtr getEntityByAvatarID(ServiceID avatarID);
    EntityPtr makeEntity(ui64 modelID, ui64 avatarID, std::string avatarName, DictArrayKey equips, GroupID groupID);
    void addEntity(EntityPtr entity);
    bool removeEntity(EntityID eid);
    bool removePlayer(AvatarID avatarID);
    bool removePlayerByGroupID(GroupID groupID);

    void pushAsync(std::function<void()> && func);

    std::vector<std::pair<EntityPtr, double>> searchTarget(EntityPtr caster, EPosition org, EPosition vt, ui64  searchID);
    std::vector<std::pair<EntityPtr, double>> searchTarget(EntityPtr caster, EPosition org, EPosition vt, const AOESearch & search);
    //org起点, vt单位向量, isRect是否为矩形, value1向量单位, value2 矩形前端垂直宽度或者扇形弧度, value3矩形近端垂直宽度或者忽略,  compensate前向偏移原点并修正value1, clip前向裁剪
    std::vector<std::pair<EntityPtr, double>> searchTarget(EPosition org, EPosition vt, ui16 isRect, double value1, double value2, double value3, double compensate, double clip);
    //根据AOESearch中的etype字段和filter过滤方法进行检测当前目标实体是否匹配
    bool searchMatched(const EntityPtr & master, const EntityPtr & caster, const EntityPtr & dst, const AOESearch & search);

    void onSceneInit();
    void onAddEntity(EntityPtr entity);
    void onRemoveEntity(EntityPtr entity);
    void onPlayerAttach(EntityPtr entity);
    void onPlayerDettach(EntityPtr entity);
public:
    
 
    




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
    catch (const std::exception & e)
    {
        LOGE("Scene::sendToClient ServiceID=" << avatarID << ",  protoid=" << MSG::getProtoID() << ", e=" << e.what());
        return;
    }
}


template<typename MSG>
void Scene::broadcast(const MSG &msg, ServiceID without, bool withScript)
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
        if (withScript)
        {
            _script->protoSync(MSG::getProtoName(), ws.getStream(), ws.getStreamLen());
            return;
        }

    }
    catch (const std::exception & e)
    {
        LOGE("Scene::broadcast protoid=" << MSG::getProtoID() << ", e=" << e.what());
        return;
    }
}






























#endif

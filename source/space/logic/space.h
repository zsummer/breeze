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

#ifndef _SPACE_H_
#define _SPACE_H_
#include "entity.h"



class Space
{
    //space数据
private:
    SpaceID _spaceID = InvalidSpaceID;
    EntityID _lastEID = ServerConfig::getRef().getSpaceConfig()._spaceID * 1000 + 1000;
    std::map<EntityID, EntityPtr> _entitys;
    std::map<ServiceID, EntityPtr> _users;
public:
    Space();
    ~Space();
    //消息队列 
public:
    template <typename MSG>
    void broadcast(const MSG & msg, ServiceID without = InvalidServiceID);
    template<typename MSG>
    void sendToClient(ServiceID userID, const MSG &msg);
};

using SpacePtr = std::shared_ptr<Space>;



template<typename MSG>
void Space::sendToClient(ServiceID userID, const MSG &msg)
{
    auto founder = _users.find(userID);
    if (founder == _users.end() || founder->second->_clientSessionID == InvalidSessionID)
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
        LOGE("Space::sendToClient ServiceID=" << userID << ",  protoid=" << MSG::getProtoID());
        return;
    }
}


template<typename MSG>
void Space::broadcast(const MSG &msg, ServiceID without)
{
    try
    {
        WriteStream ws(MSG::getProtoID());
        ws << msg;

        for (auto user : _users)
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
        LOGE("Space::broadcast protoid=" << MSG::getProtoID());
        return;
    }
}






























#endif

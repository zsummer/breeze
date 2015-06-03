#include "userManager.h"
#include "dbManager.h"
#include "mission/eventTrigger.h"
#include <ProtoCommon.h>
#include <ProtoCommon_SQL.h>



UserManager::UserManager()
{
}

bool UserManager::init()
{
    auto build = UserInfo_BUILD();
    if (DBManager::getRef().infoQuery(build[0])->getErrorCode() != QEC_SUCCESS)
    {
        if (DBManager::getRef().infoQuery(build[1])->getErrorCode() != QEC_SUCCESS)
        {
            LOGE("create table error. sql=" << build[1]);
            return false;
        }
    }

    for (size_t i = 2; i < build.size(); i++)
    {
        DBManager::getRef().infoQuery(build[i]);
    }

    
    
    //加载所有用户数据
    unsigned long long curID = 0;
    do
    {
        auto sql = UserInfo_LOAD(curID);
        auto result = DBManager::getRef().infoQuery(sql);
        if (result->getErrorCode() != QEC_SUCCESS)
        {
            LOGE("load contact error. curID:" << curID << ", err=" << result->getLastError());
            return false;
        }
        if (!result->haveRow())
        {
            break;
        }
        auto mapInfo = UserInfo_FETCH(result);
        for (auto & kv : mapInfo)
        {
            addUser(kv.second);
        }
        curID += mapInfo.size();
    } while (true);


    return true;
}


std::shared_ptr<InnerUserInfo> UserManager::getInnerUserInfoBySID(SessionID sID)
{
    auto founder = _mapSession.find(sID);
    if (founder != _mapSession.end())
    {
        return founder->second;
    }
    return nullptr;
}

std::shared_ptr<InnerUserInfo> UserManager::getInnerUserInfo(UserID uID)
{
    auto founder = _mapUser.find(uID);
    if (founder != _mapUser.end())
    {
        return founder->second;
    }
    return nullptr;
}

std::shared_ptr<InnerUserInfo> UserManager::getInnerUserInfoByNickName(const std::string & nickName)
{
    auto founder = _mapNickName.find(nickName);
    if (founder != _mapNickName.end())
    {
        return founder->second;
    }
    return nullptr;
}
void UserManager::broadcast(WriteStream & ws, const UserIDArray uIDs)
{
    if (uIDs.empty())
    {
        for (auto uID :uIDs)
        {
            auto ptr = getInnerUserInfo(uID);
            if (ptr->sID != InvalidSeesionID)
            {
                SessionManager::getRef().sendSessionData(ptr->sID, ws.getStream(), ws.getStreamLen());
            }
        }
        return;
    }
    for (auto &kv : _mapSession)
    {
        if (kv.second->sID != InvalidSeesionID)
        {
            SessionManager::getRef().sendSessionData(kv.second->sID, ws.getStream(), ws.getStreamLen());
        }
    }
}
void UserManager::addUser(const UserInfo & info)
{
    auto inner = std::make_shared<InnerUserInfo>();
    inner->userInfo = info;
    _mapUser.insert(std::make_pair(info.uID, inner));
    _mapNickName.insert(std::make_pair(info.nickName, inner));
}
void UserManager::setUserToken(UserID uID, std::string token, time_t expireTime)
{
    auto inner = getInnerUserInfo(uID);
    if (inner)
    {
        inner->token.token = token;
        inner->token.tokenExpire = (unsigned int)expireTime;
        inner->token.uID = uID;
    }
}
void UserManager::userLogin(std::shared_ptr<InnerUserInfo> innerInfo)
{
    _mapSession[innerInfo->sID] = innerInfo;
    EventTrigger::getRef().trigger(ETRIGGER_USER_LOGIN, innerInfo->userInfo.uID, 1, innerInfo->userInfo.iconID, innerInfo->userInfo.nickName);
}

void UserManager::userLogout(std::shared_ptr<InnerUserInfo> innerInfo)
{
    SessionManager::getRef().kickSession(innerInfo->sID);
    _mapSession.erase(innerInfo->sID);
    EventTrigger::getRef().trigger(ETRIGGER_USER_LOGOUT, innerInfo->userInfo.uID, 1, innerInfo->userInfo.iconID, innerInfo->userInfo.nickName);
}






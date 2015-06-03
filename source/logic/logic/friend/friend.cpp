#include "friend.h"
#include "../userManager.h"
#include "../dbManager.h"
#include <ProtoCommon.h>
#include <ProtoCommon_SQL.h>
#include <ProtoFriend.h>
#include <ProtoFriend_SQL.h>


Friend::Friend()
{
    MessageDispatcher::getRef().registerSessionMessage(ID_FriendOperationReq, std::bind(&Friend::msg_onFriendOperationReq, this, _1, _2));
    MessageDispatcher::getRef().registerSessionMessage(ID_GetSomeStrangersReq, std::bind(&Friend::msg_onGetSomeStrangersReq, this, _1, _2));
}

Friend::~Friend()
{

}

bool Friend::init()
{
    if (!initFriends())
    {
        return false;
    }

    EventTrigger::getRef().watching(ETRIGGER_USER_LOGIN, std::bind(&Friend::onUserLogin, this, _1, _2, _3, _4, _5));
    EventTrigger::getRef().watching(ETRIGGER_USER_LOGOUT, std::bind(&Friend::onUserLogout, this, _1, _2, _3, _4, _5));
    return true;
}

bool Friend::initFriends()
{
    //! 先desc一下FriendInfo表, 不存在则创建
    auto build = FriendInfo_BUILD();
    if (DBManager::getRef().infoQuery(build[0])->getErrorCode() != QEC_SUCCESS)
    {
        if (DBManager::getRef().infoQuery(build[1])->getErrorCode() != QEC_SUCCESS)
        {
            LOGE("create table error. sql=" << build[1]);
            return false;
        }
    }
    //! 无论FriendInfo表的字段是否有增删 都alter一遍. 
    for (size_t i = 2; i < build.size(); i++)
    {
        DBManager::getRef().infoQuery(build[i]);
    }

    //加载所有好友关系
    unsigned long long curID = 0;
    do
    {
        auto sql = FriendInfo_LOAD(curID);
        auto result = DBManager::getRef().infoQuery(sql);
        if (result->getErrorCode() != QEC_SUCCESS)
        {
            LOGE("load FriendInfo error. curID:" << curID << ", err=" << result->getLastError());
            return false;
        }
        auto mapInfo = FriendInfo_FETCH(result);
        if (mapInfo.empty())
        {
            break;
        }

        for (auto kv : mapInfo)
        {
            _friends[kv.first].insert(kv.second.begin(), kv.second.end());
            curID += kv.second.size();
        }
    } while (true);
    return true;
}


void  Friend::onUserLogin(EventTriggerID tID, UserID uID, Any count, Any iconID, Any nick)
{
    auto & friends = _friends[uID];
    for (auto & f : friends)
    {
        //broadcast to all friends
    }
}

void  Friend::onUserLogout(EventTriggerID tID, UserID uID, Any count, Any iconID, Any nick)
{
    auto & friends = _friends[uID];
    for (auto & f : friends)
    {
        //broadcast to all friends
    }
}



//存储好友关系
void Friend::insertFriend(const FriendInfo & info)
{
    auto sql = FriendInfo_INSERT(info);
    if (!sql.empty())
    {
        DBManager::getRef().infoAsyncQuery(sql, std::bind(&Friend::db_onDefaultUpdate, this, _1, "insertFriend"));
    }
}
void Friend::updateFriend(const FriendInfo & info)
{
    auto sql = FriendInfo_UPDATE(info);
    if (!sql.empty())
    {
        DBManager::getRef().infoAsyncQuery(sql, std::bind(&Friend::db_onDefaultUpdate, this, _1, "updateFriend"));
    }
}


void Friend::db_onDefaultUpdate(zsummer::mysql::DBResultPtr result, std::string desc)
{
    if (result->getErrorCode() != QEC_SUCCESS)
    {
        LOGE(desc << " error. msg=" << result->getLastError() << ", sql=" << result->sqlString());
    }
}


void Friend::msg_onFriendOperationReq(TcpSessionPtr session, ReadStream & rs)
{
    FriendOperationReq req;
    rs >> req;
    FriendOperationAck ack;
    ack.retCode = EC_SUCCESS;
    ack.srcFlag = req.oFlag;
    ack.dstUID = req.uID;
    auto inner = UserManager::getRef().getInnerUserInfoBySID(session->getSessionID());
    if (!inner)
    {
        ack.retCode = EC_PERMISSION_DENIED;
        return;
    }
    ack.srcUID = inner->userInfo.uID;

    auto srcFriends = _friends[inner->userInfo.uID];
    auto founderDest = srcFriends.find(req.uID);

    auto dstFriends = _friends[req.uID];
    auto founderSrc = dstFriends.find(inner->userInfo.uID);

    do 
    {
        if (req.oFlag == FRIEND_ADD_FRIEND)
        {
            if (founderDest != srcFriends.end())
            {
                //已经是自己好友了
                if (founderDest != srcFriends.end() && founderDest->second.flag == FRIEND_ESTABLISHED)
                {
                    ack.retCode = EC_OWNER_FRIEND;
                    break;
                }

                //黑名单用户
                if (founderDest != srcFriends.end() && founderDest->second.flag == FRIEND_BLACKLIST)
                {
                    ack.retCode = EC_OWNER_BLACKLIST;
                    break;
                }
            }
            if (founderSrc != dstFriends.end())
            {
                if (founderSrc->second.flag == FRIEND_BLACKLIST)
                {
                    //黑名单用户
                    ack.retCode = EC_TARGET_BLACKLIST;
                    break;
                }
                if (founderSrc->second.flag == FRIEND_REQUESTING)
                {
                    ack.retCode = EC_TARGET_REQUESTING;
                    break;
                }
                
            }
            
            /*

            if (dstStatus == dst->second.friends.end() || dstStatus->second.flag == FRIEND_REQUESTING)
            {
                FriendInfo info;
                info.flag = FRIEND_REQUESTING;
                info.makeTime = (unsigned int)time(NULL);
                info.fID = src->second.info.uID;
                info.ownID = dst->second.info.uID;

                if (dstStatus == dst->second.friends.end())
                {
                    dst->second.friends[info.fID] = info;
                    insertFriend(info);
                }
                else
                {
                    dstStatus->second = info;
                    updateFriend(info);
                }

                info.flag = FRIEND_WAITING;
                info.fID = dst->second.info.uID;
                info.ownID = src->second.info.uID;
                if (srcStatus == src->second.friends.end())
                {
                    src->second.friends[info.fID] = info;
                    insertFriend(info);
                }
                else if (srcStatus->second.flag == FRIEND_WAITING)
                {
                    srcStatus->second = info;
                    updateFriend(info);
                }

            }
            else
            {
                ack.retCode = EC_PARAM_DENIED;
            }*/

        }
        else if (req.oFlag == FRIEND_ADD_BLACKLIST)
        {

        }
        else if (req.oFlag == FRIEND_REMOVE_BLACKLIST)
        {

        }
        else if (req.oFlag == FRIEND_REMOVE_FRIEND)
        {

        }
        else if (req.oFlag == FRIEND_ALLOW)
        {
            /*
            if (srcStatus != src->second.friends.end() && srcStatus->second.flag == FRIEND_REQUESTING)
            {
                srcStatus->second.flag = FRIEND_ESTABLISHED;
                srcStatus->second.makeTime = (unsigned int)time(NULL);
                updateFriend(srcStatus->second);

                if (dstStatus != dst->second.friends.end())
                {
                    dstStatus->second.flag = FRIEND_ESTABLISHED;
                    dstStatus->second.makeTime = (unsigned int)time(NULL);
                    updateFriend(dstStatus->second);
                }
            }
            else
            {
                ack.retCode = EC_PARAM_DENIED;
            }
            */
        }
        else if (req.oFlag == FRIEND_REJECT)
        {

        }
        else if (req.oFlag == FRIEND_IGNORE)
        {

        }
        else
        {
            ack.retCode = EC_PARAM_DENIED;
        }
    } while (0);
    

    
    
    WriteStream ws(ID_FriendOperationAck);
    ws << ack;
    session->doSend(ws.getStream(), ws.getStreamLen()); 
}

void Friend::msg_onGetSomeStrangersReq(TcpSessionPtr session, ReadStream & rs)
{
    /*GetSomeStrangersReq req;
    rs >> req;
    auto inner = UserManager::getRef().getInnerUserInfoBySID(session->getSessionID());
    if (!inner)
    {
        //.
        return;
    }

    GetSomeStrangersAck ack;
    ack.retCode = EC_SUCCESS;
    for (auto & c : _contacts)
    {
        if (ack.uIDs.size() > 10)
        {
            break;
        }
        if (c.first == session->getUserParam())
        {
            continue;
        }
//         if (c.second.onlineFlag != 0)
//         {
             ack.uIDs.push_back(c.first);
//         }
    }

    WriteStream ws(ID_GetSomeStrangersAck);
    ws << ack;
    session->doSend(ws.getStream(), ws.getStreamLen()); */
}

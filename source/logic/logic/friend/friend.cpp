#include "friend.h"
#include "../userManager.h"
#include "../dbManager.h"
#include <ProtoCommon.h>
#include <ProtoCommon_SQL.h>
#include <ProtoFriend.h>
#include <ProtoFriend_SQL.h>


Friend::Friend()
{
    MessageDispatcher::getRef().registerSessionMessage(ID_GetFriendsReq, std::bind(&Friend::msg_onGetFriendsReq, this, _1, _2));
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

//更新好友关系
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

void Friend::msg_onGetFriendsReq(TcpSessionPtr session, ReadStream & rs)
{
    UpdateFriendsNotice notice;
    auto inner = UserManager::getRef().getInnerUserInfoBySID(session->getSessionID());
    if (!inner)
    {
        return;
    }
    auto friends = _friends.find(inner->userInfo.uID);
    if (friends != _friends.end())
    {
        std::for_each(friends->second.begin, friends->second.end, [&notice](const std::pair<UserID, FriendInfo> & info){ notice.friends.push_back(info.second); });
    }
    WriteStream ws(ID_UpdateFriendsNotice);
    ws << notice;
    session->doSend(ws.getStream(), ws.getStreamLen());
}

void Friend::msg_onFriendOperationReq(TcpSessionPtr session, ReadStream & rs)
{
    FriendOperationReq req;
    rs >> req;
    FriendOperationNotice ack;
    ack.retCode = EC_SUCCESS;
    ack.instruct = req.instruct;
    ack.dst = req.dst;
    auto inner = UserManager::getRef().getInnerUserInfoBySID(session->getSessionID());
    if (!inner)
    {
        ack.retCode = EC_PERMISSION_DENIED;
        return;
    }
    ack.src = inner->userInfo.uID;

    auto srcFriends = _friends[inner->userInfo.uID];
    auto founderDest = srcFriends.find(req.dst);


    auto dstFriends = _friends[req.dst];
    auto founderSrc = dstFriends.find(inner->userInfo.uID);
    switch (req.instruct)
    {
        case FRIEND_ADD_FRIEND:
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
                //黑名单用户
                if (founderSrc->second.flag == FRIEND_BLACKLIST)
                {
                    ack.retCode = EC_TARGET_BLACKLIST;
                    break;
                }
                //已在对方的请求列表中
                if (founderSrc->second.flag == FRIEND_REQUESTING)
                {
                    ack.retCode = EC_TARGET_REQUESTING;
                    break;
                }
                //直接添加到好友中
                if (founderSrc->second.flag == FRIEND_ESTABLISHED || founderSrc->second.flag == FRIEND_WAITING)
                {
                    if (founderDest == srcFriends.end())
                    {
                        FriendInfo info;
                        info.fID = req.dst;
                        info.flag = FRIEND_ESTABLISHED;
                        info.makeTime = (unsigned int)time(NULL);
                        info.ownID = inner->userInfo.uID;
                        srcFriends.insert(std::make_pair(info.fID, info));
                        insertFriend(info);
                    }
                    else
                    {
                        FriendInfo &info = founderDest->second;
                        info.flag = FRIEND_ESTABLISHED;
                        info.makeTime = (unsigned int)time(NULL);
                        updateFriend(info);
                    }
                    //对方在等自己确认的话 好友互加成功
                    if (founderSrc->second.flag == FRIEND_WAITING)
                    {
                        founderSrc->second.flag = FRIEND_ESTABLISHED;
                        founderSrc->second.makeTime = (unsigned int)time(NULL);
                        updateFriend(founderSrc->second);
                    }
                    break;
                }
            }
            if (founderDest == srcFriends.end())
            {
                FriendInfo info;
                info.fID = req.dst;
                info.flag = FRIEND_WAITING;
                info.makeTime = (unsigned int)time(NULL);
                info.ownID = inner->userInfo.uID;
                srcFriends.insert(std::make_pair(info.fID, info));
                insertFriend(info);
            }
            else
            {
                FriendInfo &info = founderDest->second;
                info.flag = FRIEND_WAITING;
                info.makeTime = (unsigned int)time(NULL);
                updateFriend(info);
            }
            if (founderSrc == dstFriends.end())
            {
                FriendInfo info;
                info.fID = req.dst;
                info.flag = FRIEND_REQUESTING;
                info.makeTime = (unsigned int)time(NULL);
                info.ownID = inner->userInfo.uID;
                dstFriends.insert(std::make_pair(info.fID, info));
                insertFriend(info);
            }
            else
            {
                FriendInfo &info = founderSrc->second;
                info.flag = FRIEND_REQUESTING;
                info.makeTime = (unsigned int)time(NULL);
                updateFriend(info);
            }
        }
    	break;
        case FRIEND_ALLOW:
        {
            if (founderDest != srcFriends.end() && founderDest->second.flag == FRIEND_REQUESTING)
            {
                founderDest->second.flag = FRIEND_DELETED;
                founderDest->second.makeTime = (unsigned int)time(NULL);
                updateFriend(founderDest->second);

                if (founderSrc == dstFriends.end())
                {
                    ack.retCode = EC_REQUEST_EXPIRE;
                    break;
                }
                founderSrc->second.flag = FRIEND_ESTABLISHED;
                founderSrc->second.makeTime = (unsigned int)time(NULL);
                updateFriend(founderSrc->second);
            }
            else
            {
                ack.retCode = EC_TARGET_NOT_EXIST;
                break;
            }
        }
        break;
        default:
        {
            ack.retCode = EC_PARAM_DENIED;
            break;
        }
    }
    




    

    
    
    WriteStream ws(ID_FriendOperationNotice);
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

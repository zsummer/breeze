#include "friend.h"
#include "../userManager.h"
#include "../dbMgr.h"
#include <ProtoCommon.h>
#include <ProtoCommon_SQL.h>
#include <ProtoFriend.h>
#include <ProtoFriend_SQL.h>


Friend::Friend()
{
    MessageDispatcher::getRef().addListener(ID_GetFriendsReq, std::bind(&Friend::msg_onGetFriendsReq, this, _1, _2));
    MessageDispatcher::getRef().addListener(ID_AddFriendReq, std::bind(&Friend::msg_onAddFriendReq, this, _1, _2));
    MessageDispatcher::getRef().addListener(ID_AddFriendReply, std::bind(&Friend::msg_onAddFriendReply, this, _1, _2));
    MessageDispatcher::getRef().addListener(ID_DelFriendReq, std::bind(&Friend::msg_onDelFriendReq, this, _1, _2));
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
    if (DBMgr::getRef().infoQuery(build[0])->getErrorCode() != QEC_SUCCESS)
    {
        if (DBMgr::getRef().infoQuery(build[1])->getErrorCode() != QEC_SUCCESS)
        {
            LOGE("create table error. sql=" << build[1]);
            return false;
        }
    }
    //! 无论FriendInfo表的字段是否有增删 都alter一遍. 
    for (size_t i = 2; i < build.size(); i++)
    {
        DBMgr::getRef().infoQuery(build[i]);
    }

    //加载所有好友关系
    unsigned long long curID = 0;
    do
    {
        auto sql = FriendInfo_LOAD(curID);
        auto result = DBMgr::getRef().infoQuery(sql);
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
    UpdateFriendsNotice notice;
    notice.friends.resize(1);
    auto & info = notice.friends[0];
    for (auto & f : friends)
    {
        if (f.second.flag != FRIEND_DELETED)
        {
            auto frd = _friends.find(f.second.fID);
            if (frd == _friends.end())
            {
                break;
            }
            auto inf = frd->second.find(uID);
            if (inf == frd->second.end())
            {
                break;
            }
            if (inf->second.flag != FRIEND_DELETED)
            {
                inf->second.online = true;
                
                auto dstInner = UserManager::getRef().getInnerUserInfo(f.second.fID);
                if (dstInner && dstInner->sID != InvalidSeesionID)
                {
                    info = inf->second;
                    sendMessage(dstInner->sID, notice);
                }
            }
        }
    }
}

void  Friend::onUserLogout(EventTriggerID tID, UserID uID, Any count, Any iconID, Any nick)
{
    auto & friends = _friends[uID];
    UpdateFriendsNotice notice;
    notice.friends.resize(1);
    auto & info = notice.friends[0];
    for (auto & f : friends)
    {
        if (f.second.flag != FRIEND_DELETED)
        {
            auto frd = _friends.find(f.second.fID);
            if (frd == _friends.end())
            {
                break;
            }
            auto inf = frd->second.find(uID);
            if (inf == frd->second.end())
            {
                break;
            }
            if (inf->second.flag != FRIEND_DELETED)
            {
                inf->second.online = false;

                auto dstInner = UserManager::getRef().getInnerUserInfo(f.second.fID);
                if (dstInner && dstInner->sID != InvalidSeesionID)
                {
                    info = inf->second;
                    sendMessage(dstInner->sID, notice);
                }
            }
        }
    }
}



//存储好友关系
void Friend::insertFriend(const FriendInfo & info)
{
    auto sql = FriendInfo_INSERT(info);
    if (!sql.empty())
    {
        DBMgr::getRef().infoAsyncQuery(sql, std::bind(&Friend::db_onDefaultUpdate, this, _1, "insertFriend"));
    }
}

//更新好友关系
void Friend::updateFriend(const FriendInfo & info)
{
    auto sql = FriendInfo_UPDATE(info);
    if (!sql.empty())
    {
        DBMgr::getRef().infoAsyncQuery(sql, std::bind(&Friend::db_onDefaultUpdate, this, _1, "updateFriend"));
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
    auto friends = _friends.find(inner->base.uID);
    if (friends != _friends.end())
    {
        std::for_each(friends->second.begin(), friends->second.end(), [&notice](const std::pair<UserID, FriendInfo> & info){ notice.friends.push_back(info.second); });
    }
    WriteStream ws(ID_UpdateFriendsNotice);
    ws << notice;
    session->send(ws.getStream(), ws.getStreamLen());
}

void Friend::msg_onAddFriendReq(TcpSessionPtr session, ReadStream & rs)
{
    AddFriendReq req;
    rs >> req;
    AddFriendAck ack;
    ack.dst = req.dst;
    ack.retCode = EC_ERROR;
    UpdateFriendsNotice notice;
    do 
    {
        UserID srcID = InvalidUserID;
        {
            auto inner = UserManager::getRef().getInnerUserInfoBySID(session->getSessionID());
            if (!inner)
            {
                break;
            }
            srcID = inner->base.uID;
        }

        auto src = _friends.find(srcID);
        if (src == _friends.end())
        {
            _friends[srcID];
            src = _friends.find(srcID);
        }

        int friendCount = 0;
        std::for_each(src->second.begin(), src->second.end(), [&friendCount](const std::pair<UserID,FriendInfo> & kv){ if (kv.second.flag != FRIEND_DELETED) friendCount++; });
        if (friendCount > 50)
        {
            ack.retCode = EC_FRIEND_CEILING;
            break;
        }

        auto srcExist = src->second.find(req.dst);
        if (srcExist != src->second.end() && srcExist->second.flag != FRIEND_DELETED)
        {
            ack.retCode = EC_FRIEND_DUPLICATE;
            break;
        }

        auto dst = _friends.find(req.dst);
        if (dst != _friends.end())
        {
            auto checkRight = dst->second.find(srcID);
            if (checkRight != dst->second.end())
            {
                //直接加好友
                if (checkRight->second.flag == FRIEND_REQUESTING || checkRight->second.flag == FRIEND_ESTABLISHED)
                {
                    FriendInfo info;
                    info.fID = req.dst;
                    info.ownID = srcID;
                    info.flag = FRIEND_ESTABLISHED;
                    info.makeTime = (unsigned int)time(NULL);
                    info.lastChanged = info.makeTime;
                    if (srcExist != src->second.end())
                    {
                        info.makeTime = srcExist->second.makeTime;
                        updateFriend(info);
                    }
                    else
                    {
                        src->second[info.fID] = info;
                        insertFriend(info);
                    }
                    notice.friends.clear();
                    notice.friends.push_back(info);
                    sendMessage(session, notice);

                    info.fID = srcID;
                    info.ownID = req.dst;
                    info.makeTime = checkRight->second.makeTime;
                    updateFriend(info);
                    auto dstInner = UserManager::getRef().getInnerUserInfo(req.dst);
                    if (dstInner && dstInner->sID != InvalidSeesionID)
                    {
                        notice.friends.clear();
                        notice.friends.push_back(info);
                        sendMessage(dstInner->sID, notice);
                    }
                    break;
                }
                else if (checkRight->second.flag == FRIEND_BLACKLIST)
                {
                    ack.retCode = EC_FRIEND_REFUSE;
                    break;
                }
            }
            
        }
        

        FriendInfo info;
        info.fID = req.dst;
        info.ownID = srcID;
        info.flag = FRIEND_WAITING;
        info.makeTime = (unsigned int)time(NULL);
        info.lastChanged = info.makeTime;
        if (srcExist != src->second.end())
        {
            info.makeTime = srcExist->second.makeTime;
            srcExist->second = info;
            updateFriend(info);
        }
        else
        {
            src->second[info.fID] = info;
            insertFriend(info);
        }
        notice.friends.clear();
        notice.friends.push_back(info);
        sendMessage(session, notice);

        if (dst == _friends.end())
        {
            _friends[req.dst];
            dst = _friends.find(req.dst);
        }
        auto dstExist = dst->second.find(srcID);

        info.fID = srcID;
        info.ownID = req.dst;
        info.flag = FRIEND_REQUESTING;
        if (dstExist != dst->second.end())
        {
            info.makeTime = dstExist->second.makeTime;
            dstExist->second = info;
            updateFriend(info);
        }
        else
        {
            dst->second[info.fID] = info;
            insertFriend(info);
        }
        auto dstInner = UserManager::getRef().getInnerUserInfo(req.dst);
        if (dstInner && dstInner->sID != InvalidSeesionID)
        {
            notice.friends.clear();
            notice.friends.push_back(info);
            sendMessage(dstInner->sID, notice);
        }
        ack.retCode = EC_SUCCESS;
    } while (false);
    sendMessage(session, ack);
}


void Friend::msg_onAddFriendReply(TcpSessionPtr session, ReadStream & rs)
{
    AddFriendReply reply;
    rs >> reply;
    AddFriendAck ack;
    ack.dst = reply.dst;
    ack.retCode = EC_ERROR;
    UpdateFriendsNotice notice;
    do
    {
        UserID srcID = InvalidUserID;
        {
            auto inner = UserManager::getRef().getInnerUserInfoBySID(session->getSessionID());
            if (!inner)
            {
                break;
            }
            srcID = inner->base.uID;
        }
        auto src = _friends.find(srcID);
        if (src == _friends.end())
        {
            ack.retCode = EC_PERMISSION_DENIED;
            break;
        }
        auto checkOwner = src->second.find(reply.dst);
        if (checkOwner == src->second.end() || checkOwner->second.flag != FRIEND_REQUESTING)
        {
            ack.retCode = EC_PERMISSION_DENIED;
            break;
        }
        auto dst = _friends.find(reply.dst);
        if (dst == _friends.end())
        {
            ack.retCode = EC_PERMISSION_DENIED;
            break;
        }
        auto checkRight = dst->second.find(srcID);
        if (checkRight == src->second.end() || checkRight->second.flag != FRIEND_WAITING)
        {
            ack.retCode = EC_PERMISSION_DENIED;
            break;
        }
       
        checkOwner->second.flag = FRIEND_ESTABLISHED;
        checkOwner->second.lastChanged = (unsigned int)time(NULL);

        updateFriend(checkOwner->second);
        notice.friends.clear();
        notice.friends.push_back(checkOwner->second);
        sendMessage(session, notice);


        checkRight->second.flag = FRIEND_ESTABLISHED;
        checkRight->second.lastChanged = checkOwner->second.lastChanged;
        updateFriend(checkRight->second);
        auto dstInner = UserManager::getRef().getInnerUserInfo(reply.dst);
        if (dstInner && dstInner->sID != InvalidSeesionID)
        {
            notice.friends.clear();
            notice.friends.push_back(checkRight->second);
            sendMessage(dstInner->sID, notice);
        }
        ack.retCode = EC_SUCCESS;
    }
    while (false);
    sendMessage(session, ack);
}



void Friend::msg_onDelFriendReq(TcpSessionPtr session, ReadStream & rs)
{
    DelFriendReq req;
    rs >> req;
    DelFriendAck ack;
    ack.dst = req.dst;
    ack.retCode = EC_ERROR;
    UpdateFriendsNotice notice;
    do
    {
        UserID srcID = InvalidUserID;
        {
            auto inner = UserManager::getRef().getInnerUserInfoBySID(session->getSessionID());
            if (!inner)
            {
                break;
            }
            srcID = inner->base.uID;
        }
        auto src = _friends.find(srcID);
        if (src == _friends.end())
        {
            ack.retCode = EC_FRIEND_NOT_EXIST;
            break;
        }
        auto checkOwner = src->second.find(req.dst);
        if (checkOwner == src->second.end() || checkOwner->second.flag == FRIEND_DELETED)
        {
            ack.retCode = EC_FRIEND_NOT_EXIST;
            break;
        }
       
        checkOwner->second.flag = FRIEND_DELETED;
        checkOwner->second.lastChanged = (unsigned int)time(NULL);

        updateFriend(checkOwner->second);
        notice.friends.clear();
        notice.friends.push_back(checkOwner->second);
        sendMessage(session, notice);
        ack.retCode = EC_SUCCESS;


        //如果该好友在线 设置为隐身
        auto dst = _friends.find(req.dst);
        if (dst == _friends.end())
        {
            break;
        }
        auto checkDst = dst->second.find(srcID);
        if (checkDst == dst->second.end())
        {
            break;
        }
        checkDst->second.online = false;
        auto dstInner = UserManager::getRef().getInnerUserInfo(req.dst);
        if (dstInner && dstInner->sID != InvalidSeesionID)
        {
            notice.friends.clear();
            notice.friends.push_back(checkDst->second);
            sendMessage(dstInner->sID, notice);
        }
    }
    while (false);
    sendMessage(session, ack);
}




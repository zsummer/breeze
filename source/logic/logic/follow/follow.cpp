#include "follow.h"
#include "../dbMgr.h"
#include "../netMgr.h"
#include <ProtoCommon.h>
#include <ProtoCommon_SQL.h>
#include <ProtoFollow.h>
#include <ProtoFollow_SQL.h>


Follow::Follow()
{
    MessageDispatcher::getRef().addListener(ID_GetFollowingReq, std::bind(&Follow::msg_onGetFollowingReq, this, _1, _2));
    MessageDispatcher::getRef().addListener(ID_GetFollowerReq, std::bind(&Follow::msg_onGetFollowerReq, this, _1, _2));
    MessageDispatcher::getRef().addListener(ID_PokeReq, std::bind(&Follow::msg_onPokeReq, this, _1, _2));
}

Follow::~Follow()
{

}

bool Follow::init()
{
    if (!buildFollow() || !loadFollow())
    {
        return false;
    }
    
    return true;
}

bool Follow::buildFollow()
{
    auto build = FollowingInfo_BUILD();
    if (DBMgr::getRef().infoQuery(build[0])->getErrorCode() != QEC_SUCCESS)
    {
        if (DBMgr::getRef().infoQuery(build[1])->getErrorCode() != QEC_SUCCESS)
        {
            LOGE("create table error. sql=" << build[1]);
            return false;
        }
    }
    for (size_t i = 2; i < build.size(); i++)
    {
        DBMgr::getRef().infoQuery(build[i]);
    }
    return true;
}

bool Follow::loadFollow()
{
    unsigned long long curID = 0;
    do
    {
        auto sql = FollowingInfo_LOAD(curID);
        auto result = DBMgr::getRef().infoQuery(sql);
        if (result->getErrorCode() != QEC_SUCCESS)
        {
            LOGE("load FollowInfo error. curID:" << curID << ", err=" << result->getLastError());
            return false;
        }

        //<following ID, <follower ID, follow> >
        auto mapInfo = FollowingInfo_FETCH(result);
        if (mapInfo.empty())
        {
            break;
        }

        for (auto kv : mapInfo)
        {
            _follower[kv.first].insert(kv.second.begin(), kv.second.end());
            for (auto pr : kv.second)
            {
                _following[pr.second.follower].insert(std::make_pair(pr.second.following, pr.second));
            }
            curID += kv.second.size();
        }
    } while (true);
    return true;
}





//更新好友关系
void Follow::updateFollowingInfo(FollowingInfo & info)
{
    auto my = _following.find(info.follower);
    if (my != _following.end())
    {
        auto following = my->second.find(info.following);
        if (following != my->second.end())
        {
            info.makeTime = following->second.makeTime;
            auto sql = FollowingInfo_UPDATE(info);
            if (!sql.empty())
            {
                DBMgr::getRef().infoAsyncQuery(sql, std::bind(&Follow::db_onDefaultUpdate, this, _1, "updateFollow"));
            }
            _following[info.follower][info.following] = info;
            _follower[info.following][info.follower] = info;
            return;
        }
    }
    auto sql = FollowingInfo_INSERT(info);
    if (!sql.empty())
    {
        DBMgr::getRef().infoAsyncQuery(sql, std::bind(&Follow::db_onDefaultUpdate, this, _1, "insertFollow"));
    }
    _following[info.follower][info.following] = info;
    _follower[info.following][info.follower] = info;
    return;
    

}


void Follow::db_onDefaultUpdate(zsummer::mysql::DBResultPtr result, std::string desc)
{
    if (result->getErrorCode() != QEC_SUCCESS)
    {
        LOGE(desc << " error. msg=" << result->getLastError() << ", sql=" << result->sqlString());
    }
}

void Follow::msg_onGetFollowerReq(TcpSessionPtr session, ReadStream & rs)
{
    GetFollowerReq req;
    rs >> req;
    GetFollowerAck ack;
    ack.status = req.status;
    auto follower = _follower.find(req.uID);
    if (follower != _follower.end())
    {
        for (auto kv : follower->second)
        {
            if (kv.second.status == req.status || req.status == FOLLOW_INVALID)
            {
                ack.follower.push_back(kv.second);
            }
        }
    }
    sendMessage(session, ack);
}



void Follow::msg_onGetFollowingReq(TcpSessionPtr session, ReadStream & rs)
{
    GetFollowingReq req;
    rs >> req;
    GetFollowingAck ack;
    ack.status = req.status;
    auto following = _following.find(req.uID);
    if (following != _following.end())
    {
        for (auto kv : following->second)
        {
            if (kv.second.status == req.status || req.status == FOLLOW_INVALID)
            {
                ack.following.push_back(kv.second);
            }
        }
    }
    sendMessage(session, ack);
}


void Follow::msg_onPokeReq(TcpSessionPtr session, ReadStream & rs)
{
    PokeReq req;
    rs >> req;

    if (req.dstStatus != FOLLOW_DELETED
        && req.dstStatus != FOLLOW_HATE
        && req.dstStatus != FOLLOW_FOLLOWING)
    {
        return;
    }
    if (!NetMgr::getRef().getUserInfo(req.following))
    {
        return;
    }


    PokeAck ack;
    ack.follow.follower = session->getUserParam(UPARAM_USER_ID).getNumber();
    ack.follow.following = req.following;
    ack.follow.makeTime = (unsigned int)time(NULL);
    ack.follow.lastChanged = ack.follow.makeTime;
    ack.follow.status = req.dstStatus;
    updateFollowingInfo(ack.follow);
    sendMessage(session, ack);
}








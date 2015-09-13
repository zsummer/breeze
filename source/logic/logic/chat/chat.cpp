#include "chat.h"
#include "../dbMgr.h"
#include "../netMgr.h"
#include <ProtoCommon.h>
#include "ProtoChat.h"
#include "ProtoChat_SQL.h"

Chat::Chat()
{
    MessageDispatcher::getRef().addListener(ID_ChatReq, std::bind(&Chat::msg_onChatReq, this, _1, _2));
}

Chat::~Chat()
{
    if (_filter)
    {
        match_tree_free(_filter);
        _filter = nullptr;
    }
}

bool Chat::init()
{
    _genID.initConfig(ServerConfig::getRef().getPlatID(), ServerConfig::getRef().getAreaID());
    if (!buildMessage() || !loadMessage())
    {
        return false;
    }

    if (!initGenerator())
    {
        return false;
    }
    
    if (!loadFilter())
    {
        return false;
    }
    if (!buildMessage()|| ! loadMessage())
    {
        return false;
    }
    
    return true;
}

bool Chat::loadFilter()
{
    _filter = match_tree_init_from_file("../filter.txt", ".....", 5);
    if (_filter == nullptr)
    {
        LOGE("match_tree_init_from_file error");
        return false;
    }
    LOGI("init filter configure success. filter patterns=" << _filter->_tree_pattern_count << ", min pattern="
        << _filter->_tree_pattern_minimum_len << ", max pattern=" << _filter->_tree_pattern_maximum_len << ", used memory=" << _filter->_tree_memory_used / 1024 << "KB");
    return true;
}

bool Chat::buildMessage()
{
    auto build = ChatInfo_BUILD();
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

bool Chat::initGenerator()
{
    DBQuery q("select mID from tb_ChatInfo where mID >= ? and mID < ?  order by mID desc limit 1;");
    q << _genID.getMinObjID();
    q << _genID.getMaxObjID();
    auto result = DBMgr::getRef().infoQuery(q.popSQL());
    if (result->getErrorCode() != QEC_SUCCESS)
    {
        LOGE("Chat::init() init error.  can't get current tb_ChatInfo id.  error=" << result->getLastError() << ", sql=" << result->sqlString());
        return false;
    }
    if (result->haveRow())
    {
        try
        {
            UserID lastChatID = 0;
            *result >> lastChatID;
            _genID.setCurObjID(lastChatID);
        }
        catch (...)
        {
            LOGE("Chat::init() catch error.  can't get current tb_ChatInfo .  error=" << result->getLastError() << ", sql=" << result->sqlString());
            return false;
        }
    }
    return true;
}


bool Chat::loadMessage()
{
    return true;
}


//存储聊天消息
void Chat::insertMessage(const ChatInfo & info)
{
    auto sql = ChatInfo_INSERT(info);
    if (!sql.empty())
    {
        DBMgr::getRef().infoAsyncQuery(sql, std::bind(&Chat::db_onDefaultUpdate, this, _1, "insertMessage"));
    }
}
void Chat::updateMessage(const ChatInfo & info)
{
    auto sql = ChatInfo_UPDATE(info);
    if (!sql.empty())
    {
        DBMgr::getRef().infoAsyncQuery(sql, std::bind(&Chat::db_onDefaultUpdate, this, _1, "updateMessage"));
    }
}




void Chat::db_onDefaultUpdate(zsummer::mysql::DBResultPtr result, std::string desc)
{
    if (result->getErrorCode() != QEC_SUCCESS)
    {
        LOGE(desc << " error. msg=" << result->getLastError() << ", sql=" << result->sqlString());
    }
}

void Chat::msg_onChatReq(TcpSessionPtr session, ReadStream & rs)
{
    ChatReq req;
    rs >> req;
    ChatAck ack;
    ack.retCode = EC_ERROR;
    ack.msgID = 0;
    ack.chlType = req.chlType;
    ack.dstID = req.dstID;
    do 
    {
        auto infoPtr = NetMgr::getRef().getUserInfo(session->getUserParam(UPARAM_USER_ID).getNumber());
        if (!infoPtr)
        {
            break;
        }
        ChatInfo info;
        info.chlType = req.chlType;
        info.dstID = req.dstID;
        info.mID = _genID.genNewObjID();
        info.msg = req.msg;
        info.sendTime = (unsigned int)time(NULL);
        info.srcIcon = infoPtr->base.iconID;
        info.srcID = infoPtr->base.uID;
        info.srcName = infoPtr->base.nickName;
        ack.msgID = info.mID;
        //塞进数据库
        auto chatsql = ChatInfo_INSERT(info);
        DBMgr::getRef().infoAsyncQuery(chatsql, std::bind(&Chat::db_onDefaultUpdate, this, _1, "ChatInfo_INSERT"));

        //过滤掉脏字
        match_tree_translate(_filter, &info.msg[0], (unsigned int)info.msg.length(), 1, '*');

        //通知下去
        if (info.chlType == CHANNEL_PRIVATE)
        {
            auto dstPtr = NetMgr::getRef().getUserInfo(req.dstID);
            if (!dstPtr)
            {
                ack.retCode = EC_USER_NOT_FOUND;
                return;
            }
            info.dstIcon = dstPtr->base.iconID;
            info.dstName = dstPtr->base.nickName;
            if (dstPtr->sID != InvalidSessionID)
            {
                
                ChatNotice notice;
                notice.msgs.push_back(info);
                sendMessage(dstPtr->sID, notice);
                ack.retCode = EC_SUCCESS;
                break;
            }
            else
            {
                ack.retCode = EC_USER_OFFLINE;
                break;
            }
        }
        else if (info.chlType == CHANNEL_GROUP || info.chlType == CHANNEL_WORLD)
        {
            ChatNotice notice;
            notice.msgs.push_back(info);

            if (info.chlType == CHANNEL_GROUP)
            {
                auto founder = _channels.find(info.dstID);
                if (founder != _channels.end())
                {
                    NetMgr::getRef().broadcast(notice, founder->second);
                    ack.retCode = EC_SUCCESS;
                    break;
                }
                else
                {
                    ack.retCode = EC_TARGET_NOT_EXIST;
                    break;
                }
            }
            else
            {
                NetMgr::getRef().broadcast(notice);
                ack.retCode = EC_SUCCESS;
                break;
            }
        }
        else
        {
            ack.retCode = EC_PARAM_DENIED;
            break;
        }
    } while (false);
    
    sendMessage(session, ack);
}
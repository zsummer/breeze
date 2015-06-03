#include "application.h"
#include "logic/dbManager.h"
#include "logic/userManager.h"
#include "logic/netManager.h"
#include "logic/mission/eventTrigger.h"
#include "logic/mission/dailyMission.h"
#include "logic/testBlob/testBlob.h"
#include "logic/chat/chat.h"
#include "logic/friend/friend.h"
#include "logic/login/login.h"


#define LogicInit(logic) do  \
{ \
    bool ret = logic::getRef().init(); \
    if (!ret) \
    { \
        LOGE("LogicInit " << #logic << " error!"); \
        return false; \
    } \
    LOGI("LogicInit " << #logic << " success!"); \
} while (0) 


#define LogicStart(logic) do  \
{\
    bool ret = logic::getRef().start(); \
    if (!ret) \
    { \
        LOGE("LogicStart " << #logic << " error!"); \
        return false; \
    } \
    LOGI("LogicStart " << #logic << " success!"); \
} while (0)


Appliction::Appliction()
{
    
}

Appliction::~Appliction()
{

}




bool Appliction::init(std::string filename, unsigned int index)
{
    bool ret = false;
    SessionManager::getRef().setStopClientsHandler(std::bind(&Appliction::_onSigalStop, this));
    ret = ServerConfig::getRef().parse(filename, LogicNode, index);
    if (!ret)
    {
        LOGE("parse ServerConfig failed.");
        return ret;
    }
    LOGI("parse ServerConfig success. configFile=" << filename << ", node=" << LogicNode << ", index=" << index);

    LogicStart(SessionManager);
    LogicStart(DBManager);
    
    LogicInit(UserManager);
    LogicInit(EventTrigger);
    LogicInit(DailyMission);
    LogicInit(TestBlob);
    LogicInit(Chat);
    LogicInit(Login);
    LogicInit(Friend);

    LogicStart(NetManager);


    LOGI("Appliction init success.");
    return ret;
}

void Appliction::run()
{
     SessionManager::getRef().run();
}

void Appliction::stop()
{
    SessionManager::getRef().stopClients();
}

void Appliction::_onSigalStop()
{
    LOGA("Appliction::_onSigalStop(): waiting all session safe close ...");
    NetManager::getRef().stop(std::bind(&Appliction::_onNetClosed, this));
}

void Appliction::_onNetClosed()
{
    LOGA("Appliction::_onNetClosed(): waiting DBManager stop ...");
    DBManager::getRef().stop(std::bind(&Appliction::_onDBClosed, this));
}

void Appliction::_onDBClosed()
{
    LOGA("Appliction::_onDBClosed(): stop main thread ...");
    SessionManager::getRef().stop(); //exit main thread.
    SessionManager::getRef().stopAccept();
}










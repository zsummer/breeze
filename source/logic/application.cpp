#include "application.h"
#include "logic/dbManager.h"
#include "logic/userManager.h"
#include "logic/netManager.h"
#include "logic/mission/eventTrigger.h"
#include "logic/mission/dailyMission.h"
#include "logic/testBlob/testBlob.h"
#include "logic/testBlob/createTestAuthInfo.h"
#include "logic/chat/chatManager.h"
#include "logic/login/login.h"



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

	ret = SessionManager::getRef().start();
	if (!ret)
	{
		LOGE("SessionManager start false.");
		return ret;
	}
	LOGI("SessionManager start success.");

	ret = DBManager::getRef().start();
	if (!ret)
	{
		LOGE("DBManager start false.");
		return ret;
	}
	LOGI("DBManager start success.");
	ret = UserManager::getRef().init();
	if (!ret)
	{
		LOGE("UserManager init false.");
		return ret;
	}
	LOGI("UserManager init success.");

	ret = EventTrigger::getRef().init();
	if (!ret)
	{
		LOGE("EventTrigger init false.");
		return ret;
	}
	LOGI("EventTrigger init success.");

	ret = DailyMission::getRef().init();
	if (!ret)
	{
		LOGE("DailyMission init false.");
		return ret;
	}
	LOGI("DailyMission init success.");

	ret = TestBlob::getRef().init();
	if (!ret)
	{
		LOGE("TestBlob init false.");
		return ret;
	}
	LOGI("TestBlob init success.");

	ret = CreateTestAuthInfo::getRef().init();
	if (!ret)
	{
		LOGE("CreateTestAuthInfo init false.");
		return ret;
	}
	LOGI("CreateTestAuthInfo init success.");

	ret = ChatManager::getRef().init();
	if (!ret)
	{
		LOGE("ChatManager init false.");
		return ret;
	}
	LOGI("ChatManager init success.");


	ret = Login::getRef().init();
	if (!ret)
	{
		LOGE("Login init false.");
		return ret;
	}
	LOGI("Login init success.");







	//open network
	if (!NetManager::getRef().start())
	{
		LOGE("NetManager start false.");
		return ret;
	}
	LOGI("NetManager start Success.");

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










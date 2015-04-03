#include "application.h"
#include "logic/dbManager.h"
#include "logic/userManager.h"
#include "logic/netManager.h"
#include "logic/mission/eventTrigger.h"
using namespace zsummer::log4z;


Appliction::Appliction()
{
	
}

Appliction::~Appliction()
{
}




bool Appliction::init(std::string filename, unsigned int index)
{
	bool ret = false;

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
	return SessionManager::getRef().run();
}

void Appliction::stop()
{
	LOGA("Appliction::stop()");
	SessionManager::getRef().post(std::bind(&Appliction::_onSigalStop, this));
}

void Appliction::_onSigalStop()
{
	LOGA("Appliction::_onSigalStop(): waiting all session safe close ...");
	NetManager::getRef().stop(std::bind(&Appliction::_onNetClosed, this));
}

void Appliction::_onNetClosed()
{
	LOGA("Appliction::_onNetClosed(): waiting DBManager stop ...");
	DBManager::getRef().stop();// DBManager will wait all data store.
	LOGA("Appliction::_onNetClosed(): stop main thread ...");
	SessionManager::getRef().stop(); //exit main thread.
}


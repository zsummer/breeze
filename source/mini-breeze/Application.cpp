#include "Application.h"
#include <log4z/log4z.h>
#include "logic/NetManager.h"
#include <DBHelper.h>
using namespace zsummer::log4z;


Appliction::Appliction()
{
	
}

Appliction::~Appliction()
{
}




bool Appliction::Init(std::string filename, unsigned int index)
{
	bool ret = false;

	ret = ServerConfig::getRef().Parse(filename, MiniBreezeNode, index);
	if (!ret)
	{
		LOGE("Parse ServerConfig failed.");
		return ret;
	}
	LOGI("Parse ServerConfig success. configFile=" << filename << ", node=" << MiniBreezeNode << ", index=" << index);

	if (!CDBClientManager::getRef().Start())
	{
		LOGE("DBManager Start false. ");
		return false;
	}
	LOGI("DBManager Start success. ");


	CDBClientManager::getRef().getAuthDB()->Init(ServerConfig::getRef().getAuthDBConfig());
	CDBClientManager::getRef().getInfoDB()->Init(ServerConfig::getRef().getInfoDBConfig());
	CDBClientManager::getRef().getLogDB()->Init(ServerConfig::getRef().getLogDBConfig());

	if (!CDBClientManager::getRef().getAuthDB()->Connect())
	{
		LOGE("Connect Auth DB false. db config=" << ServerConfig::getRef().getAuthDBConfig());
		return false;
	}
	LOGI("Connect Auth DB success. db config=" << ServerConfig::getRef().getAuthDBConfig());

	if (!CDBClientManager::getRef().getInfoDB()->Connect())
	{
		LOGE("Connect Info DB false. db config=" << ServerConfig::getRef().getInfoDBConfig());
		return false;
	}
	LOGI("Connect Info DB success. db config=" << ServerConfig::getRef().getInfoDBConfig());

	if (!CDBClientManager::getRef().getLogDB()->Connect())
	{
		LOGE("Connect Log DB false. db config=" << ServerConfig::getRef().getLogDBConfig());
		return false;
	}
	LOGI("Connect Log DB success. db config=" << ServerConfig::getRef().getLogDBConfig());




	ret = CTcpSessionManager::getRef().Start();
	if (!ret)
	{
		LOGE("CTcpSessionManager Start false.");
		return ret;
	}
	LOGI("CTcpSessionManager Start success.");


	if (!CNetManager::getRef().Start())
	{
		LOGE("NetManager Start false.");
		return ret;
	}
	LOGI("NetManager Start Success.");

	LOGI("Appliction Init success.");
	return ret;
}

void Appliction::Run()
{
	return CTcpSessionManager::getRef().Run();
}

void Appliction::Stop()
{
	CTcpSessionManager::getRef().CreateTimer(100, std::bind(&Appliction::_Stop, this));
}

void Appliction::_Stop()
{
	CNetManager::getRef().Stop();
	CDBClientManager::getRef().Stop();
}

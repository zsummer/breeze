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
}

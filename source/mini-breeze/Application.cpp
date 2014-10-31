#include "Application.h"


#include <log4z/log4z.h>
#include <BaseHander.h>
#include <ServerConfig.h>
#include "core/NetManager.h"
#include "core/GlobalFacade.h"
using namespace zsummer::log4z;
//文件说明
//应用程序类
//封装程序启动-初始化-运行-结束的功能
Appliction::Appliction()
{
	
}

Appliction::~Appliction()
{
}

Appliction & Appliction::getRef()
{
	static Appliction g_facade;
	return g_facade;
}


bool Appliction::Init(std::string filename, unsigned int index)
{
	bool ret = false;


	ret = GlobalFacade::getRef().getServerConfig().Parse(filename, AgentNode, index);
	if (!ret)
	{
		LOGE("getServerConfig failed.");
		return ret;
	}
	ret = CTcpSessionManager::getRef().Start();
	if (!ret)
	{
		LOGE("CTcpSessionManager Start false.");
		return ret;
	}
	ret = GlobalFacade::getRef().getNetManger().Start();
	if (!ret)
	{
		LOGE("NetManager Start false.");
		return ret;
	}


	std::vector<CBaseHandler*> handlers;
	for (auto ptr : handlers)
	{
		if (!ptr->Init())
		{
			LOGW("Appliction Init handler false");
			return false;
		}
	}

	LOGI("Appliction Init success.");
	return true;
}

void Appliction::RunPump()
{
	return CTcpSessionManager::getRef().Run();
}

void Appliction::Stop()
{
	CTcpSessionManager::getRef().CreateTimer(100, std::bind(&Appliction::_Stop, this));
}

void Appliction::_Stop()
{
	GlobalFacade::getRef().getNetManger().Stop();
}

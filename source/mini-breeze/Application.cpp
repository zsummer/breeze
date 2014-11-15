#include "Application.h"
#include <log4z/log4z.h>
#include "core/NetManager.h"
#include "core/GlobalFacade.h"
#include <DBHelper.h>
using namespace zsummer::log4z;


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
	bool ret = GlobalFacade::getRef().init(filename, MiniBreezeNode, index);
	if (ret)
	{
		LOGI("Appliction Init success.");
	}
	else
	{
		LOGE("Appliction Init fales.");
	}
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
	GlobalFacade::getRef().getNetManger().Stop();
	GlobalFacade::getRef().getDBManager().Stop();
}

#include "GlobalFacade.h"
#include <ServerConfig.h>
#include "NetManager.h"

GlobalFacade::GlobalFacade()
{
	m_serverConfig = new ServerConfig;
	m_netManger = new CNetManager();
}

GlobalFacade::~GlobalFacade()
{
}

GlobalFacade & GlobalFacade::getRef()
{
	static GlobalFacade g_facade;
	return g_facade;
}

bool GlobalFacade::init(std::string configFile, ServerNode node, NodeIndex index)
{
	bool ret = false;

	ret = m_serverConfig->Parse(configFile, node, index);
	if (!ret)
	{
		LOGE("Parse ServerConfig failed.");
		return ret;
	}
	LOGI("Parse ServerConfig success. configFile=" << configFile << ", node=" <<node << ", index=" << index);


	std::vector<CBaseHandler*> handlers;
	for (auto ptr : handlers)
	{
		if (!ptr->Init())
		{
			LOGW("Init handler false");
			return false;
		}
	}
	LOGI("Init handler all Success. handler size=" << handlers.size());

	ret = CTcpSessionManager::getRef().Start();
	if (!ret)
	{
		LOGE("CTcpSessionManager Start false.");
		return ret;
	}
	LOGI("CTcpSessionManager Start success.");


	ret = m_netManger->Start();
	if (!ret)
	{
		LOGE("NetManager Start false.");
		return ret;
	}
	LOGI("NetManager Start Success.");

	LOGI("GlobalFacade Init success.");
}
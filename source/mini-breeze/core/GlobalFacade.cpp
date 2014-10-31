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
#include "GlobalFacade.h"
#include "NetManager.h"
#include <DBHelper.h>


GlobalFacade::GlobalFacade()
{
	m_serverConfig = new ServerConfig;
	m_netManger = new CNetManager();
	m_dbclient = new zsummer::mysql::CDBClientManager();
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




	if (!getDBManager().Start())
	{
		LOGE("DBManager Start false. " );
		return false;
	}
	LOGI("DBManager Start success. ");
	
	
	getDBManager().getAuthDB()->Init(getServerConfig().getAuthDBConfig());
	getDBManager().getInfoDB()->Init(getServerConfig().getInfoDBConfig());
	getDBManager().getLogDB()->Init(getServerConfig().getLogDBConfig());

	if (!getDBManager().getAuthDB()->Connect())
	{
		LOGE("Connect Auth DB false. db config=" << getServerConfig().getAuthDBConfig());
		return false;
	}
	LOGI("Connect Auth DB success. db config=" << getServerConfig().getAuthDBConfig());

	if (!getDBManager().getInfoDB()->Connect())
	{
		LOGE("Connect Info DB false. db config=" << getServerConfig().getInfoDBConfig());
		return false;
	}
	LOGI("Connect Info DB success. db config=" << getServerConfig().getInfoDBConfig());

	if (!getDBManager().getLogDB()->Connect())
	{
		LOGE("Connect Log DB false. db config=" << getServerConfig().getLogDBConfig());
		return false;
	}
	LOGI("Connect Log DB success. db config=" << getServerConfig().getLogDBConfig());


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
	return true;
}
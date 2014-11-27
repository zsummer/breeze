#include "NetManager.h"
#include "DBManager.h"
using namespace zsummer::mysql;

CDBManager::CDBManager()
{
	m_authDB = std::make_shared<DBHelper>();
	m_infoDB = std::make_shared<DBHelper>();
	m_logDB = std::make_shared<DBHelper>();
}
CDBManager::~CDBManager()
{
	CDBAsync::getRef().Stop();
	m_authDB->Stop();
	m_infoDB->Stop();
	m_logDB->Stop();
}

bool CDBManager::Init()
{

	if (!CDBAsync::Instantiate()->Start())
	{
		LOGE("DBManager Start false. ");
		return false;
	}
	LOGI("DBManager Start success. ");


	m_authDB->Init(ServerConfig::getRef().getAuthDBConfig());
	m_infoDB->Init(ServerConfig::getRef().getInfoDBConfig());
	m_logDB->Init(ServerConfig::getRef().getLogDBConfig());

	if (!m_authDB->Connect())
	{
		LOGE("Connect Auth DB false. db config=" << ServerConfig::getRef().getAuthDBConfig());
		return false;
	}
	LOGI("Connect Auth DB success. db config=" << ServerConfig::getRef().getAuthDBConfig());

	if (!m_infoDB->Connect())
	{
		LOGE("Connect Info DB false. db config=" << ServerConfig::getRef().getInfoDBConfig());
		return false;
	}
	LOGI("Connect Info DB success. db config=" << ServerConfig::getRef().getInfoDBConfig());

	if (!m_logDB->Connect())
	{
		LOGE("Connect Log DB false. db config=" << ServerConfig::getRef().getLogDBConfig());
		return false;
	}
	LOGI("Connect Log DB success. db config=" << ServerConfig::getRef().getLogDBConfig());
	return true;
}
void CDBManager::CharLogin(std::shared_ptr<InnerCharInfo> iinfoPtr)
{

}
void CDBManager::CharLogout(std::shared_ptr<InnerCharInfo> iinfoPtr)
{

}

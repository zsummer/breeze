
/*
* breeze License
* Copyright (C) 2014 YaweiZhang <yawei_zhang@foxmail.com>.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/


#include "DBHelper.h"
using namespace zsummer::mysql;


CDBClientManager::CDBClientManager()
{
	m_authDB = std::make_shared<DBHelper>(m_bRuning);
	m_infoDB = std::make_shared<DBHelper>(m_bRuning);
	m_logDB = std::make_shared<DBHelper>(m_bRuning);
	m_summer = std::make_shared<zsummer::network::ZSummer>();
}

CDBClientManager::~CDBClientManager()
{
	Stop();
}

bool CDBClientManager::Start()
{
	bool ret = m_summer->Initialize();
	if (!ret)
	{
		return false;
	}
	if (m_thread)
	{
		return false;
	}
	m_bRuning = true;
	m_uPostCount.store(0);
	m_uFinalCount.store(0);
	m_thread = std::shared_ptr<std::thread>(new std::thread(std::bind(&CDBClientManager::Run, this)));
	return true;
}
bool CDBClientManager::Stop()
{
	if (m_thread)
	{
		m_bRuning = false;
		m_thread->join();
		m_thread.reset();
		return true;
	}
	return false;
}


void CDBClientManager::async_query(DBHelperPtr &dbhelper, const string &sql,
	const std::function<void(DBResultPtr)> & handler)
{
	m_uPostCount++;
	m_summer->Post(std::bind(&CDBClientManager::_async_query, this, dbhelper, sql, handler));
}

void CDBClientManager::_async_query(DBHelperPtr &dbhelper, const string &sql,
	const std::function<void(DBResultPtr)> & handler)
{
	DBResultPtr ret = dbhelper->Query(sql);
	m_uPostCount--;
	CTcpSessionManager::getRef().Post(std::bind(handler, ret));
}



















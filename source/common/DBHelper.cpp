
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


const char * DBResult::ExtractOneField()
{
	if (!m_row)
	{
		throw std::string("result have not any row.");
	}
	const char * fieldptr = m_row[m_fieldCursor];
	m_fieldCursor++;
	if (m_fieldCursor == m_fieldCount)
	{
		m_row = mysql_fetch_row(m_res);
		m_fieldCursor = 0;
	}
	return fieldptr ? fieldptr : "";
}


void DBResult::_SetQueryResult(QueryErrorCode qec, const std::string & sql, MYSQL * db)
{
	m_ec = qec;
	m_sql = sql;
	if (qec == QueryErrorCode::QEC_MYSQLERROR)
	{
		m_lastErrorMsg = "[MYSQL_ERRNO:";
		m_lastErrorMsg += _ToString(mysql_errno(db));
		m_lastErrorMsg += "]";
		const char * msg = mysql_error(db);
		m_lastErrorMsg += msg == NULL ? "" : msg;
	}
	else if (qec == QueryErrorCode::QEC_SUCCESS)
	{
		m_res = mysql_store_result(db);
		m_affectedRows = mysql_affected_rows(db);
		if (m_res)
		{
			m_fieldCount = mysql_num_fields(m_res);
			m_row = mysql_fetch_row(m_res);
			if (m_fieldCount == 0)
			{
				m_row = nullptr;
			}
		}
	}
}


bool DBHelper::Connect()
{
	if (m_mysql)
	{
		mysql_close(m_mysql);
		m_mysql = nullptr;
	}
	m_mysql = mysql_init(nullptr);
	if (!m_mysql)
	{
		LOGE("mysql_init false. mysql config=" << m_config);
		return false;
	}
	mysql_options(m_mysql, MYSQL_OPT_CONNECT_TIMEOUT, "5");
	mysql_options(m_mysql, MYSQL_SET_CHARSET_NAME, "UTF8");
	mysql_set_character_set(m_mysql, "UTF8");
	MYSQL * ret = mysql_real_connect(m_mysql, m_config.ip.c_str(), m_config.user.c_str(), m_config.pwd.c_str(), m_config.db.c_str(),
		m_config.port, nullptr, 0);
	if (!ret)
	{
		return false;
	}
	return true;
}

bool DBHelper::WaitEnable()
{
	if (!m_isRuning)
	{
		return false;
	}
	size_t lastTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	do
	{
		LOGE("try reconnect mysql. mysql=" << m_mysql);
		if (Connect())
		{
			return true;
		}
		size_t now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		if (now - lastTime < 5000)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(now - lastTime));
		}
		lastTime += now - lastTime;
	} while (m_isRuning);
	return false;
}

DBResultPtr DBHelper::Query(const std::string & sql)
{
	auto ret = std::make_shared<DBResult>();
	if (m_mysql == nullptr)
	{
		return ret;
	}
	if (mysql_real_query(m_mysql, sql.c_str(), (unsigned long)sql.length()) != 0)
	{
		//retry
		if (mysql_errno(m_mysql) == CR_SERVER_LOST || mysql_errno(m_mysql) == CR_SERVER_GONE_ERROR)
		{
			if (WaitEnable())
			{
				if (mysql_real_query(m_mysql, sql.c_str(), (unsigned long)sql.length()) == 0)
				{
					ret->_SetQueryResult(QueryErrorCode::QEC_SUCCESS, sql, m_mysql);
					return ret;
				}
			}
		}
		ret->_SetQueryResult(QueryErrorCode::QEC_MYSQLERROR, sql, m_mysql);
	}
	ret->_SetQueryResult(QueryErrorCode::QEC_SUCCESS, sql, m_mysql);
	return ret;
}






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


void CDBClientManager::Run()
{
	do
	{
		if (!m_bRuning)
		{
			break;
		}
		try
		{
			m_summer->RunOnce();
		}
		catch (...)
		{
		}

	} while (true);
}
















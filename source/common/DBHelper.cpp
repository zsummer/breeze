
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


#include "dbhelper.h"
using namespace zsummer::mysql;


const std::string& DBResult::extractOneField()
{
	if (_curIter == _result.end())
	{
		throw std::string("result have not any row.");
	}
	if (_fieldCursor >= _curIter->size())
	{
		throw std::string("result read field over");
	}
	
	const std::string & field = _curIter->at(_fieldCursor);
	_fieldCursor++;
	if (_fieldCursor == _curIter->size())
	{
		_curIter++;
		_fieldCursor = 0;
	}
	return field;
}


void DBResult::_setQueryResult(QueryErrorCode qec, const std::string & sql, MYSQL * db)
{
	_ec = qec;
	_sql = sql;
	if (qec == QueryErrorCode::QEC_MYSQLERROR)
	{
		_lastErrorMsg = "[MYSQL_ERRNO:";
		_lastErrorMsg += _toString(mysql_errno(db));
		_lastErrorMsg += "]";
		const char * msg = mysql_error(db);
		_lastErrorMsg += msg == NULL ? "" : msg;
	}
	else if (qec == QueryErrorCode::QEC_SUCCESS)
	{
		_affectedRows = mysql_affected_rows(db);
		MYSQL_RES * res = mysql_store_result(db);
		if (res)
		{
			unsigned int fieldCount = mysql_num_fields(res);
			MYSQL_ROW row;
			while ((row = mysql_fetch_row(res)) != NULL)
			{
				_result.push_back(std::vector<std::string>());
				auto & vct = _result.back();
				for (unsigned int i = 0; i < fieldCount; ++i)
				{
					vct.push_back(row[i] == nullptr ? "" : row[i]);
				}
			}
			mysql_free_result(res);
			res = nullptr;
		}
		while (!mysql_next_result(db))
		{
			res = mysql_store_result(db);
			mysql_free_result(res);
			res = nullptr;
			//LOGW("db have other result (multi-result).");
		}
		
	}
	else
	{
		LOGA("db have error.");
	}
	_curIter = _result.begin();
	_fieldCursor = 0;
}


bool DBHelper::connect()
{
	if (_mysql)
	{
		mysql_close(_mysql);
		_mysql = nullptr;
	}
	_mysql = mysql_init(nullptr);
	if (!_mysql)
	{
		LOGE("mysql_init false. mysql config=" << _config);
		return false;
	}
	mysql_options(_mysql, MYSQL_OPT_CONNECT_TIMEOUT, "5");
	mysql_options(_mysql, MYSQL_SET_CHARSET_NAME, "UTF8");
	mysql_set_character_set(_mysql, "UTF8");
	MYSQL * ret = mysql_real_connect(_mysql, _config.ip.c_str(), _config.user.c_str(), _config.pwd.c_str(), _config.db.c_str(),
		_config.port, nullptr, 0);
	if (!ret)
	{
		return false;
	}
	return true;
}

bool DBHelper::waitEnable()
{
	if (!_isRuning)
	{
		return false;
	}
	size_t lastTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	do
	{
		LOGE("try reconnect mysql. mysql=" << _mysql);
		if (connect())
		{
			return true;
		}
		size_t now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		if (now - lastTime < 5000)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(now - lastTime));
		}
		lastTime += now - lastTime;
	} while (_isRuning);
	return false;
}

DBResultPtr DBHelper::query(const std::string & sql)
{
	auto ret = std::make_shared<DBResult>();
	if (_mysql == nullptr)
	{
		return ret;
	}
	if (mysql_real_query(_mysql, sql.c_str(), (unsigned long)sql.length()) != 0)
	{
		//retry
		if (mysql_errno(_mysql) == CR_SERVER_LOST || mysql_errno(_mysql) == CR_SERVER_GONE_ERROR)
		{
			if (waitEnable())
			{
				if (mysql_real_query(_mysql, sql.c_str(), (unsigned long)sql.length()) == 0)
				{
					ret->_setQueryResult(QueryErrorCode::QEC_SUCCESS, sql, _mysql);
					return ret;
				}
			}
		}
		ret->_setQueryResult(QueryErrorCode::QEC_MYSQLERROR, sql, _mysql);
		return ret;
	}
	ret->_setQueryResult(QueryErrorCode::QEC_SUCCESS, sql, _mysql);
	return ret;
}






DBAsync::DBAsync()
{
	_summer = std::make_shared<zsummer::network::ZSummer>();
}

DBAsync::~DBAsync()
{
	stop();
}

bool DBAsync::start()
{
	bool ret = _summer->initialize();
	if (!ret)
	{
		return false;
	}
	if (_thread)
	{
		return false;
	}
	_bRuning = true;
	_uPostCount.store(0);
	_uFinalCount.store(0);
	_thread = std::shared_ptr<std::thread>(new std::thread(std::bind(&DBAsync::run, this)));
	return true;
}
bool DBAsync::stop()
{
	if (_thread)
	{
		_bRuning = false;
		_thread->join();
		_thread.reset();
		return true;
	}
	return false;
}


void DBAsync::asyncQuery(DBHelperPtr &dbhelper, const string &sql,
	const std::function<void(DBResultPtr)> & handler)
{
	_uPostCount++;
	_summer->post(std::bind(&DBAsync::_asyncQuery, this, dbhelper, sql, handler));
}

void DBAsync::_asyncQuery(DBHelperPtr &dbhelper, const string &sql,
	const std::function<void(DBResultPtr)> & handler)
{
	DBResultPtr ret = dbhelper->query(sql);
	_uPostCount--;
	TcpSessionManager::getRef().post(std::bind(handler, ret));
}


void DBAsync::run()
{
	do
	{
		if (!_bRuning)
		{
			break;
		}
		try
		{
			_summer->runOnce();
		}
		catch (...)
		{
		}

	} while (true);
}
















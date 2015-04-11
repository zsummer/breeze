
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


#include "dbAsync.h"
using namespace zsummer::mysql;




DBAsync::DBAsync()
{
	_event = std::make_shared<zsummer::network::EventLoop>();
	_uFinalCount = 0;
	_uPostCount = 0;
}

DBAsync::~DBAsync()
{
	stop();
}

bool DBAsync::start()
{
	bool ret = _event->initialize();
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


void DBAsync::asyncQuery(DBHelperPtr &dbhelper, const std::string &sql,
	const std::function<void(DBResultPtr)> & handler)
{
	_uPostCount++;
	_event->post(std::bind(&DBAsync::_asyncQuery, this, dbhelper, sql, handler));
}

void DBAsync::_asyncQuery(DBHelperPtr &dbhelper, const std::string &sql,
	const std::function<void(DBResultPtr)> & handler)
{
	DBResultPtr ret = dbhelper->query(sql);
	_uFinalCount++;
	SessionManager::getRef().post(std::bind(handler, ret));
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
			_event->runOnce();
		}
		catch (...)
		{
		}

	} while (true);
}

















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


#include "MongoManager.h"
#include <ProtoDefine.h>
#include <boost/lexical_cast.hpp>

CMongoManager::CMongoManager()
{
	m_summer = std::make_shared<zsummer::network::ZSummer>();
}

CMongoManager::~CMongoManager()
{
	StopPump();
}

bool CMongoManager::StartPump()
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
	m_thread = std::shared_ptr<std::thread>(new std::thread(std::bind(&CMongoManager::Run, this)));
	return true;
}
bool CMongoManager::StopPump()
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
bool CMongoManager::ConnectMongo(MongoPtr & mongoPtr, const MongoConfig & mc)
{
	if (mongoPtr)
	{
		return false;
	}
	mongoPtr = std::shared_ptr<mongo::DBClientConnection>(new mongo::DBClientConnection(true));
	try
	{
		std::string dbhost = mc.ip + ":" + boost::lexical_cast<std::string>(mc.port);
		mongoPtr->connect(dbhost);
		if (mc.needAuth)
		{
			std::string errorMsg;
			if (!mongoPtr->auth(mc.db, mc.user, mc.pwd, errorMsg))
			{
				LOGI("ConnectAuth failed. db=" << mc.db << ", user=" << mc.user << ", pwd=" << mc.pwd << ", errMSG=" << errorMsg);
				return false;
			}
		}

	}
	catch (const mongo::DBException &e)
	{
		LOGE("ConnectAuth caught:" << e.what());
		return false;
	}
	catch (...)
	{
		LOGE("ConnectAuth mongo auth UNKNOWN ERROR");
		return false;
	}
	LOGI("ConnectAuth mongo Success");
	return true;
}


void CMongoManager::async_query(MongoPtr & mongoPtr, const string &ns, const mongo::Query  &query,
	const std::function<void(std::shared_ptr<MongoRetDatas> , std::string )> &handler)
{
	m_uPostCount++;
	m_summer->Post(std::bind(&CMongoManager::_async_query, this, mongoPtr, ns, query, handler));
}


void CMongoManager::_async_query(MongoPtr & mongoPtr, const string &ns, const mongo::Query &query,
	std::function<void(std::shared_ptr<MongoRetDatas> , std::string )>  &handler)
{
	std::string ret;
	std::shared_ptr<MongoRetDatas> retData(new MongoRetDatas());
	try
	{
		auto cursor =mongoPtr->query(ns, query);
		while (cursor->more())
		{
			mongo::BSONObj obj = cursor->next();
			mongo::BSONObjBuilder buider;
			buider.appendElements(obj);
			mongo::BSONObj obj2 = buider.obj();
			retData->push_back(obj2);
		}
	}
	catch (const mongo::DBException &e)
	{
		ret += "mongodb async_query catch error. ns=" + ns + ", query=" + query.toString() + ", error=" + e.what();
	}
	catch (...)
	{
		ret += "mongodb async_query unknown error. ns=" + ns + ", query=" + query.toString();
	}
	CTcpSessionManager::getRef().Post(std::bind(handler, retData, ret));
	m_uFinalCount++;
}



void CMongoManager::async_update(MongoPtr &mongoPtr, const string &ns, const mongo::Query &query, const mongo::BSONObj &obj, bool upsert,
	const std::function<void(std::string )> & handler)
{
	m_uPostCount++;
	m_summer->Post(std::bind(&CMongoManager::_async_update, this, mongoPtr, ns, query, obj, upsert, handler));
}



void CMongoManager::_async_update(MongoPtr &mongoPtr, const string &ns, const mongo::Query &query, const mongo::BSONObj &obj, bool upsert,
	const std::function<void(std::string )> & handler)
{
	std::string ret;
	try
	{
		mongoPtr->update(ns, query, obj, upsert);
		ret = mongoPtr->getLastError();
	}
	catch (const mongo::DBException &e)
	{
		ret += "mongodb _async_update catch error. ns=" + ns + ", query=" + query.toString() + ", error=" + e.what();
	}
	catch (...)
	{
		ret += "mongodb _async_update unknown error. ns=" + ns + ", query=" + query.toString();
	}
	CTcpSessionManager::getRef().Post(std::bind(handler, ret));
	m_uFinalCount++;
}

void CMongoManager::async_insert(MongoPtr &mongoPtr, const string &ns, const mongo::BSONObj &obj,
	const std::function<void(std::string )> & handler)
{
	m_uPostCount++;
	m_summer->Post(std::bind(&CMongoManager::_async_insert, this, mongoPtr, ns, obj, handler));
}

void CMongoManager::_async_insert(MongoPtr &mongoPtr, const string &ns, const mongo::BSONObj &obj,
	const std::function<void(std::string )> & handler)
{
	std::string ret;
	try
	{
		mongoPtr->insert(ns, obj);
		ret = mongoPtr->getLastError();
	}
	catch (const mongo::DBException &e)
	{
		ret += "mongodb _async_insert catch error. ns=" + ns + ", obj=" + obj.toString() + ", error=" + e.what();
	}
	catch (...)
	{
		ret += "mongodb _async_insert unknown error. ns=" + ns + ", obj=" + obj.toString();
	}
	CTcpSessionManager::getRef().Post(std::bind(handler, ret));
	m_uFinalCount++;
}


















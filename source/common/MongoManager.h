
/*
* mini-breeze License
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

/*
*  文件说明
*  CMongoManager为mongodb的操作管理类, 并提供一个简单的异步操作mongodb方案.
*  如果某个服务节点需要访问mongodb 可以在这里添加一个mongodb句柄 并进行相应的初始化.
*  该服务开辟一个单独的线程去做mongodb的阻塞操作, 因此程序使用该类的时候 要进行启动, 并在程序退出时调用停止接口.
*  该服务提供的异步方式是并非为完全隔离的异步封装, 为了简化逻辑书写, 只对query,update等操作的阻塞部分进行异步, 实现方式为在调用原生query时候 
*    把原生querry所需的参数和mongodb句柄,handler回调句柄一起传给async_query. 在回调中得到的数据为原生query返回后的所有数据.
*  
*/


#ifndef _MONGO_MANAGER_H_
#define _MONGO_MANAGER_H_

#include <ProtoDefine.h>
#include <ServerConfig.h>


class CMongoManager
{
public:
	typedef std::shared_ptr<mongo::DBClientConnection> MongoPtr;
	typedef std::vector<mongo::BSONObj> MongoRetDatas;
public:
	CMongoManager();
	~CMongoManager();
	bool StartPump();
	bool StopPump();
	bool ConnectMongo(MongoPtr &mongoPtr, const MongoConfig & mc);

public:
	inline MongoPtr & getAuthMongo(){ return m_authMongo; }
	inline MongoPtr & getInfoMongo(){ return m_infoMongo; }
	inline MongoPtr & getLogMongo(){ return m_logMongo; }
	inline const std::atomic_ullong & getPostCount(){ return m_uPostCount; }
	inline const std::atomic_ullong & getFinalCount(){ return m_uFinalCount; }
public:
	void async_query(MongoPtr &mongoPtr, const string &ns, const mongo::Query &query,
		const std::function<void(std::shared_ptr<MongoRetDatas> , std::string )> & handler);
	void async_update(MongoPtr &mongoPtr, const string &ns, const mongo::Query &query, const mongo::BSONObj &obj, bool upsert,
		const std::function<void(std::string )> & handler);
	void async_insert(MongoPtr &mongoPtr, const string &ns, const mongo::BSONObj &obj, 
		const std::function<void(std::string )> & handler);

protected:
	void _async_query(MongoPtr &mongoPtr, const string &ns, const mongo::Query &query,
		std::function<void(std::shared_ptr<MongoRetDatas>, std::string )> &handler);

	void _async_update(MongoPtr &mongoPtr, const string &ns, const mongo::Query &query, const mongo::BSONObj &obj, bool upsert,
		const std::function<void(std::string )> & handler);

	void _async_insert(MongoPtr &mongoPtr, const string &ns, const mongo::BSONObj &obj, 
		const std::function<void(std::string )> & handler);

	inline void Run();

private:
	std::shared_ptr<mongo::DBClientConnection> m_authMongo;
	std::shared_ptr<mongo::DBClientConnection> m_infoMongo;
	std::shared_ptr<mongo::DBClientConnection> m_logMongo;
	std::shared_ptr<std::thread> m_thread;
	zsummer::network::ZSummerPtr m_summer;

	bool m_bRuning = false;
	char __tmpAlignas1[128];
	std::atomic_ullong m_uPostCount;
	char __tmpAlignas2[128];
	std::atomic_ullong m_uFinalCount;
	char __tmpAlignas3[128];
};









void CMongoManager::Run()
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




















#endif

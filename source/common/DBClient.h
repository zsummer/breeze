
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
*  如果某个服务节点需要访问db 可以在这里添加一个db句柄 并进行相应的初始化.
*  该服务开辟一个单独的线程去做mongodb的阻塞操作, 因此程序使用该类的时候 要进行启动, 并在程序退出时调用停止接口.
*  该服务提供的异步方式是并非为完全隔离的异步封装, 为了简化逻辑书写, 只对query,update等操作的阻塞部分进行异步, 实现方式为在调用原生query时候 
*    把原生querry所需的参数和mongodb句柄,handler回调句柄一起传给async_query. 在回调中得到的数据为原生query返回后的所有数据.
*  
*/


#ifndef _MONGO_MANAGER_H_
#define _MONGO_MANAGER_H_

#include <Common.h>
#include <mysqlclient/errmsg.h>
#include <mysqlclient/mysql.h>

class CDBHelper :public std::enable_shared_from_this<CDBHelper>
{
public:
	CDBHelper(const bool & isRuning): m_isRuning(isRuning)
	{
	}
	~CDBHelper()
	{
		if (m_mysql)
		{
			mysql_close(m_mysql);
			m_mysql = nullptr;
		}
	}
	inline void Init(const DBConfig & dbconfig){ m_config = dbconfig; }
	inline bool Connect()
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
	inline bool WaitEnable()
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

	inline std::string EscapeString(std::string const & str){ return EscapeString(str.c_str(), str.length()); }
	inline std::string EscapeString(const char * str, size_t len)
	{
		std::string ret;
		if (len == 0 || !m_mysql)
		{
			return ret;
		}
		ret.resize(len * 2 + 10, '\0');
		unsigned long newlen = mysql_real_escape_string(m_mysql, &ret[0], str, (unsigned long)len);
		ret.assign(ret.c_str(), newlen);
		return ret;
	}

	inline bool Query(const char * sql, unsigned long length)
	{
		if (m_mysql == NULL)
		{
			return false;
		}
		if (mysql_real_query(m_mysql, sql, length) != 0)
		{
			//retry
			if (mysql_errno(m_mysql) == CR_SERVER_LOST || mysql_errno(m_mysql) == CR_SERVER_GONE_ERROR)
			{
				if (WaitEnable())
				{
					if (mysql_real_query(m_mysql, sql, length) == 0)
					{
						return true;
					}
				}
			}
			return false;
		}
		return true;
	}

	inline MYSQL_RES * getResult(){return mysql_store_result(m_mysql);}

	inline unsigned long long getAffectedRows(){return mysql_affected_rows(m_mysql);}

	inline std::string getLastError(){return mysql_error(m_mysql);}
	inline unsigned int getLastErrNo(){ return mysql_errno(m_mysql); }

	//后续会完善这套操作封装 现在暂时没时间继续搞
	inline void ExampleFore()
	{
		MYSQL_RES * res = getResult();
		if (!res)
		{
			return;
		}
		int num_fields = mysql_num_fields(res);
		MYSQL_ROW row;
		while (row = mysql_fetch_row(res))
		{
			for (int i = 0; i < num_fields; ++i)
			{
				const char * field = row[i] ? row[i] : "";
				//dosomething.
			}
		}
		mysql_free_result(res); // must call this method to free memmory.
	}
protected:
private:
	MYSQL * m_mysql = nullptr;
	DBConfig m_config;
	const bool & m_isRuning;
};
typedef std::shared_ptr<CDBHelper> CDBHelperPtr;

class CDBClientManager
{
public:
	CDBClientManager();
	~CDBClientManager();
	bool Start();
	bool Stop();
public:
	inline CDBHelper & getAuthDB(){ return m_authDB; }
	inline CDBHelper & getInfoDB(){ return m_infoDB; }
	inline CDBHelper & getLogDB(){ return m_logDB; }

	inline const std::atomic_ullong & getPostCount(){ return m_uPostCount; }
	inline const std::atomic_ullong & getFinalCount(){ return m_uFinalCount; }
public:
	void async_query(CDBHelper &dbhelper, const string &sql, 
		const std::function<void(MYSQL_RES *, unsigned long long, unsigned int, std::string)> & handler);
protected:
	void _async_query(CDBHelper &dbhelper, const string &sql,
		const std::function<void(MYSQL_RES *, unsigned long long, unsigned int, std::string)> & handler);

	inline void Run();

private:
	CDBHelperPtr m_infoDB;
	CDBHelperPtr m_logDB;
	CDBHelperPtr m_authDB;
	std::shared_ptr<std::thread> m_thread;
	zsummer::network::ZSummerPtr m_summer;

	bool m_bRuning = false;
	char __tmpAlignas1[128];
	std::atomic_ullong m_uPostCount;
	char __tmpAlignas2[128];
	std::atomic_ullong m_uFinalCount;
	char __tmpAlignas3[128];
};









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




















#endif

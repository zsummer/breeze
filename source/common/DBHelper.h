
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


#ifndef _DB_HELPER_H_
#define _DB_HELPER_H_
#include <Common.h>
#include <mysqlclient/errmsg.h>
#include <mysqlclient/mysql.h>

namespace  zsummer
{
	namespace mysql
	{
		enum class QueryErrorCode : unsigned short
		{
			QEC_SUCCESS = 0,
			QEC_UNQUERY,
			QEC_MYSQLERROR,
		};
		

		inline std::string EscapeString(const char * orgBuff, size_t lenght);
		inline std::string EscapeString(const std::string &orgField){ return EscapeString(orgField.c_str(), orgField.length()); }
		
		class DBResult : public std::enable_shared_from_this<DBResult>
		{
		public:
			DBResult(){}
			~DBResult()
			{
				if (m_res)
				{
					mysql_free_result(m_res);
					m_res = nullptr;
				}
			}
			inline QueryErrorCode GetErrorCode(){ return m_ec; }
			inline std::string GetLastError(){ return m_lastErrorMsg; }
			inline unsigned long long GetAffectedRows(){ return m_affectedRows; }
			inline bool HaveRow(){ return m_row != nullptr; }
			const std::string & SQLString(){ return m_sql; }

			inline const char * ExtractOneField()
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
			inline void SetQueryResult(QueryErrorCode qec, const std::string & sql,  MYSQL * db)
			{
				m_ec = qec;
				m_sql = sql;
				if (qec == QueryErrorCode::QEC_MYSQLERROR)
				{
					const char * msg = mysql_error(db);
					m_lastErrorMsg = msg == NULL ? "" : msg;
					m_lastErrorNo = mysql_errno(db);
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
		protected:
			QueryErrorCode m_ec = QueryErrorCode::QEC_UNQUERY;
			//sql
			std::string m_sql;
			//error
			std::string m_lastErrorMsg;
			unsigned int m_lastErrorNo = 0;

			//res
			MYSQL_RES * m_res = nullptr;
			MYSQL_ROW  m_row = nullptr;
			unsigned long long m_affectedRows = 0;
			unsigned int m_fieldCount = 0;
			unsigned int m_fieldCursor = 0;
		};
		typedef std::shared_ptr<DBResult> DBResultPtr;



		
		class DBHelper :public std::enable_shared_from_this<DBHelper>
		{
		public:
			DBHelper(const bool & isRuning) : m_isRuning(isRuning)
			{
			}
			~DBHelper()
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

			inline DBResultPtr Query(const std::string & sql)
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
								ret->SetQueryResult(QueryErrorCode::QEC_SUCCESS, sql, m_mysql);
								return ret;
							}
						}
					}
					ret->SetQueryResult(QueryErrorCode::QEC_MYSQLERROR, sql, m_mysql);
				}
				ret->SetQueryResult(QueryErrorCode::QEC_SUCCESS, sql, m_mysql);
				return ret;
			}
		private:
			MYSQL * m_mysql = nullptr;
			DBConfig m_config;
			const bool & m_isRuning;
		};
		typedef std::shared_ptr<DBHelper> DBHelperPtr;




		class CDBClientManager
		{
		public:
			CDBClientManager();
			~CDBClientManager();
			bool Start();
			bool Stop();
		public:
			inline DBHelperPtr & getAuthDB(){ return m_authDB; }
			inline DBHelperPtr & getInfoDB(){ return m_infoDB; }
			inline DBHelperPtr & getLogDB(){ return m_logDB; }

			inline const std::atomic_ullong & getPostCount(){ return m_uPostCount; }
			inline const std::atomic_ullong & getFinalCount(){ return m_uFinalCount; }
		public:
			void async_query(DBHelperPtr &dbhelper, const string &sql,
				const std::function<void(DBResultPtr)> & handler);
		protected:
			void _async_query(DBHelperPtr &dbhelper, const string &sql,
				const std::function<void(DBResultPtr)> & handler);

			inline void Run();

		private:
			DBHelperPtr m_infoDB;
			DBHelperPtr m_logDB;
			DBHelperPtr m_authDB;
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



		inline std::string EscapeString(const char * orgBuff, size_t lenght)
		{
			std::string ret;
			if (lenght == 0)
			{
				return std::move(ret);
			}
			for (size_t i = 0; i < lenght; ++i)
			{
				char ch = orgBuff[i];
				switch (ch)
				{
				case 0:
					ret += "\\0";
					break;
				case '\n':
					ret += "\\n";
					break;
				case '\r':
					ret += "\\r";
					break;
				case '\\':
					ret += "\\\\";
					break;
				case '\'':
					ret += "\\\'";
					break;
				case '"':
					ret += "\\\"";
					break;
				case '\032':
					ret += "Z";
					break;
				default:
					ret += ch;
				}
			}
			return std::move(ret);
		}

	};
};
















#endif

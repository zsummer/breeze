
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
*  file desc
*  asynchronous operate db via multi-thread.
*  利用线程异步化DB操作。
*  
*/


#ifndef _DB_HELPER_H_
#define _DB_HELPER_H_
#include <inner_defined.h>
#include <base_message_handler.h>
#include <single.h>
#include <serverconfig.h>
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
		

		inline std::string escapeString(const char * orgBuff, size_t lenght);
		inline std::string escapeString(const std::string &orgField){ return escapeString(orgField.c_str(), orgField.length()); }
		
		class DBResult : public std::enable_shared_from_this<DBResult>
		{
		public:
			DBResult(){}
			~DBResult(){}
		public:
			inline QueryErrorCode getErrorCode(){ return _ec; }
			inline std::string getLastError(){ return _lastErrorMsg; }
			inline unsigned long long getAffectedRows(){ return _affectedRows; }
			inline bool haveRow(){ return _curIter != _result.end(); }
			const std::string & sqlString(){ return _sql; }
			template<class T>
			inline DBResult & operator >>(T & t){t = _fromeString<T>(extractOneField());return *this;}

		public:
			void _setQueryResult(QueryErrorCode qec, const std::string & sql, MYSQL * db);
		private:
			const std::string& extractOneField();
			template<class RET>
			inline RET _fromeString(const std::string& field)
			{
				std::stringstream ss(field);
				RET ret;
				ss >> ret;
				return std::move(ret);
			}
			template<class T>
			inline std::string _toString(const T & t)
			{
				std::stringstream ss;
				ss << t;
				return ss.str();
			}
		private:
			QueryErrorCode _ec = QueryErrorCode::QEC_UNQUERY;
			//sql
			std::string _sql;
			//error
			std::string _lastErrorMsg;

			//res
			unsigned long long _affectedRows = 0;

			typedef std::list<std::vector<std::string> > MysqlResult;
			MysqlResult _result;
			MysqlResult::iterator _curIter = _result.begin();
			unsigned int _fieldCursor = 0;
			
			

		};
		typedef std::shared_ptr<DBResult> DBResultPtr;



		
		class DBHelper :public std::enable_shared_from_this<DBHelper>
		{
		public:
			DBHelper(){}
			~DBHelper(){if (_mysql){ mysql_close(_mysql); _mysql = nullptr; } }
			inline void init(const DBConfig & dbconfig){ _config = dbconfig; }
			bool connect();
			bool waitEnable();
			DBResultPtr query(const std::string & sql);
		public:
			void stop(){ _isRuning = false; }
		private:
			DBHelper(const DBHelper &) = delete;
			MYSQL * _mysql = nullptr;
			DBConfig _config;
			bool  _isRuning = true;
		};
		typedef std::shared_ptr<DBHelper> DBHelperPtr;




		class DBAsync : public Singleton<DBAsync>
		{
		public:
			DBAsync();
			~DBAsync();
			bool start();
			bool stop();
		public:

			inline const std::atomic_ullong & getPostCount(){ return _uPostCount; }
			inline const std::atomic_ullong & getFinalCount(){ return _uFinalCount; }
		public:
			void asyncQuery(DBHelperPtr &dbhelper, const string &sql,
				const std::function<void(DBResultPtr)> & handler);
		protected:
			void _asyncQuery(DBHelperPtr &dbhelper, const string &sql,
				const std::function<void(DBResultPtr)> & handler);

			inline void run();

		private:
			std::shared_ptr<std::thread> _thread;
			zsummer::network::ZSummerPtr _summer;
			bool _bRuning = false;
			std::atomic_ullong _uPostCount;
			std::atomic_ullong _uFinalCount;
		};













		inline std::string escapeString(const char * orgBuff, size_t lenght)
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

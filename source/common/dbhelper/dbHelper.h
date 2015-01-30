
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
*  mysql operations helper 
*  
*/


#ifndef _DB_HELPER_H_
#define _DB_HELPER_H_
#include <mysqlclient/errmsg.h>
#include <mysqlclient/mysql.h>
#include <string>
#include <iostream>
#include <functional>
#include <memory>
#include <list>
#include <vector>
#include <chrono>
#include <log4z/log4z.h>
#include <thread>

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

		// db request
		class DBRequest
		{
		public:
			DBRequest(const std::string & init)
			{
				_sql = init;
			}
			template <class T>
			inline bool add(T t)
			{
				std::stringstream ss;
				ss << t;
				return insertParam(ss.str());
			}
			template <>
			inline bool add(const char * param)
			{
				return insertParam(escapeString(param, strlen(param)), true);
			}
			template <>
			inline bool add(const std::string & param)
			{
				return insertParam(escapeString(param), true);
			}
			inline const std::string & genSQL()
			{
				size_t pos = _sql.find('?');
				if (pos != std::string::npos)
				{
					LOGE("DBRequest param is not enough. current sql=" << _sql);
				}
				return _sql;
			}
		protected:
			inline bool insertParam(const std::string & param, bool isString)
			{
				size_t pos = _sql.find('?');
				if (pos != std::string::npos)
				{
					std::string after = _sql.substr(pos + 1);
					_sql.erase(pos);
					if (isString)
					{
						_sql += "\"";
						_sql += param;
						_sql += "\"";
					}
					else
					{
						_sql += param;
					}
					_sql += after;
				}
				else
				{
					LOGE("DBRequest insert param error. too many param. current sql=" << _sql);
					return false;
				}
				return true;
			}
		private:
			std::string _sql;
		};
		
		
		// db operations result
		class DBResult : public std::enable_shared_from_this<DBResult>
		{
		public:
			DBResult(){}
			~DBResult(){}
		public:
			//get sql string
			const std::string & sqlString(){ return _sql; }

			//get error info
			inline QueryErrorCode getErrorCode(){ return _ec; }
			inline std::string getLastError(){ return _lastErrorMsg; }

			//get affected rows
			inline unsigned long long getAffectedRows(){ return _affectedRows; }

			//get result
			inline bool haveRow(){ return _curIter != _result.end(); }
			
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
			inline void init(const std::string & ip, unsigned short port, const std::string & db, const std::string & user, const std::string & pwd)
			{
				_ip = ip;
				_port = port;
				_db = db;
				_user = user;
				_pwd = pwd;
			}
			bool connect();
			bool waitEnable();
			DBResultPtr query(const std::string & sql);
		public:
			void stop(){ _waiting = false; }
		private:
			DBHelper(const DBHelper &) = delete;
			MYSQL * _mysql = nullptr;
			bool  _waiting = true;
			std::string _ip;
			unsigned short _port = 3306;
			std::string _db;
			std::string _user;
			std::string _pwd;
		};
		typedef std::shared_ptr<DBHelper> DBHelperPtr;




		











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

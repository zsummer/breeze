
/*
* dbHelper License
* Copyright (C) 2014-2016 YaweiZhang <yawei.zhang@foxmail.com>.
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
#include <errmsg.h>
#include <mysql.h>
#include <log4z/log4z.h>
#include <string>
#include <iostream>
#include <functional>
#include <memory>
#include <list>
#include <vector>
#include <chrono>
#include <thread>
#include <string.h>

namespace  zsummer
{
    namespace mysql
    {
        //! the result error code when excute mysql querys.
        enum QueryErrorCode
        {
            QEC_SUCCESS = 0,
            QEC_UNQUERY,
            QEC_MYSQLERROR,
        };

        inline std::string   escapeString(const char * orgBuff, size_t lenght);
        inline std::string   escapeString(const std::string &orgField){ return escapeString(orgField.c_str(), orgField.length()); }

        //! --------------------------------------------------------
        //! db query
        class DBQuery
        {
        private:
            inline bool insertParam(const std::string & param, bool isString);
        public:
            DBQuery(){}
            DBQuery(const std::string & init) :_sql(init){}
            DBQuery(DBQuery && q){ this->_sql = std::move(q._sql); this->_fmtPos = q._fmtPos; q._fmtPos = 0; }
            DBQuery(const DBQuery & q){ this->_sql = q._sql; this->_fmtPos = q._fmtPos;}

            inline void init(const std::string & init){ _sql = init; _fmtPos = 0; }

            inline bool add(long long data);
            inline bool add(unsigned long long data);
            inline bool add(double data);

            inline bool add(char data){ return add((long long)data); } // char [i8] type is the same as as long long
            inline bool add(unsigned char data){ return add((unsigned long long)data); }//unsigned char [ui8] type is the same as as long long
            inline bool add(short data){ return add((long long)data); }
            inline bool add(unsigned short data){ return add((unsigned long long)data); }
            inline bool add(int data){ return add((long long)data); }
            inline bool add(unsigned int data){ return add((unsigned long long)data); }
            inline bool add(float data){ return add((double)data); }
            inline bool add(const char *  param, size_t len){ return insertParam(escapeString(param, len), true); }
            inline bool add(const std::string & param){return insertParam(escapeString(param), true);}
            template<class T>
            inline DBQuery & operator << (const T & t){add(t);return *this;}
            inline std::string pickSQL();
            inline std::string peekSQL();
        private:
            std::string _sql;
            std::string::size_type _fmtPos = 0;
        };



        //! --------------------------------------------------------
        //! db result
        class DBResult : public std::enable_shared_from_this<DBResult>
        {
        public:
            DBResult(){}
            ~DBResult(){}
            typedef std::vector<std::string> MysqlResult;
        public:
            inline void buildResult(QueryErrorCode qec, const std::string & errMsg, const std::string & sql, unsigned long long affected, MysqlResult & result);
            inline void buildResult(QueryErrorCode qec, const std::string & sql, MYSQL * db);
        public:
            inline const std::string & peekSQL(){ return _sql; }
            inline QueryErrorCode getErrorCode(){ return _ec; }
            inline std::string getErrorMsg(){ return _errMsg; }
            inline unsigned long long getAffectedRows(){ return _affectedRows; }
            inline bool haveRow(){ return _curIter != _result.end(); }

        public:
            inline MysqlResult && popResult(){ return std::move(_result); }
            inline std::string popOrgField();
        private:
            QueryErrorCode _ec = QueryErrorCode::QEC_UNQUERY;
            std::string _errMsg;
            std::string _sql;
            unsigned long long _affectedRows = 0;
            MysqlResult _result;
            MysqlResult::iterator _curIter = _result.begin();
        };
        typedef std::shared_ptr<DBResult> DBResultPtr;




        class DBHelper :public std::enable_shared_from_this<DBHelper>
        {
        public:
            DBHelper(){}
            ~DBHelper(){ if (_mysql){ mysql_close(_mysql); _mysql = nullptr; } }
            inline void init(const std::string & ip, unsigned short port, const std::string & db, const std::string & user, const std::string & pwd, bool autoBuildDB = false)
            {
                _ip = ip;
                _port = port;
                _db = db;
                _user = user;
                _pwd = pwd;
                _autobuild = autoBuildDB;
            }
            inline bool connect();
            inline bool waitEnable();
            inline DBResultPtr query(const std::string & sql);
        public:
            inline void stop(){ _waiting = false; }
        private:
            DBHelper(const DBHelper &) = delete;
            MYSQL * _mysql = nullptr;
            bool  _waiting = false;
            std::string _ip;
            unsigned short _port = 3306;
            std::string _db;
            std::string _user;
            std::string _pwd;
            bool _autobuild = false;
        };
        typedef std::shared_ptr<DBHelper> DBHelperPtr;



        inline std::string   escapeString(const char * orgBuff, size_t lenght)
        {
            std::string ret;
            if (lenght == 0)
            {
                return ret;
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
                default:
                    ret += ch;
                }
            }
            return ret;
        }

        inline bool DBQuery::add(double data)
        {
            char buf[64];
            buf[0] = '\0';
            sprintf(buf, "%lf", data);
            return insertParam(buf, false);
        }

        inline bool DBQuery::add(long long data)
        {
            char buf[64];
            buf[0] = '\0';
#ifdef WIN32  
            sprintf(buf, "%I64d", data);
#else
            sprintf(buf, "%lld", data);
#endif
            return insertParam(buf, false);
        }
        inline bool DBQuery::add(unsigned long long data)
        {
            char buf[64];
            buf[0] = '\0';
#ifdef WIN32  
            sprintf(buf, "%I64u", data);
#else
            sprintf(buf, "%llu", data);
#endif
            return insertParam(buf, false);
        }
        inline bool DBQuery::insertParam(const std::string & param, bool isString)
        {
            size_t pos = _sql.find('?', _fmtPos);
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
                _fmtPos = _sql.length();
                _sql += after;
            }
            else
            {
                LOGE("DBQuery insert param error. too many param. current sql=" << _sql);
                return false;
            }
            return true;
        }
        inline std::string DBQuery::pickSQL()
        {
            size_t pos = _sql.find('?', _fmtPos);
            if (pos != std::string::npos)
            {
                LOGE("DBQuery param is not enough. current sql=" << _sql);
            }
            return std::move(_sql);
        }
        inline std::string DBQuery::peekSQL()
        {
            size_t pos = _sql.find('?', _fmtPos);
            if (pos != std::string::npos)
            {
                LOGE("DBQuery param is not enough. current sql=" << _sql);
            }
            return _sql;
        }


        inline std::string DBResult::popOrgField()
        {
            if (_curIter == _result.end())
            {
                throw std::runtime_error("result have not any row.");
            }
            auto curIter = _curIter++;
            return std::move(*curIter);
        }

        void DBResult::buildResult(QueryErrorCode qec, const std::string & errMsg, const std::string & sql, unsigned long long affected, MysqlResult & result)
        {
            _ec = qec;
            _errMsg = errMsg;
            _sql = sql;
            _affectedRows = affected;
            _result = std::move(result);
            _curIter = _result.begin();
        }

        void DBResult::buildResult(QueryErrorCode qec, const std::string & sql, MYSQL * db)
        {
            _ec = qec;
            _sql = sql;
            if (qec == QueryErrorCode::QEC_MYSQLERROR)
            {
                char buf[20];
                sprintf(buf, "%d", mysql_errno(db));
                _errMsg = "[MYSQL_ERRNO:";
                _errMsg += buf;
                _errMsg += "]";
                const char * msg = mysql_error(db);
                _errMsg += msg == NULL ? "" : msg;
            }
            else if (qec == QueryErrorCode::QEC_SUCCESS)
            {
                _affectedRows = mysql_affected_rows(db);
                MYSQL_RES * res = mysql_store_result(db);
                if (res)
                {
                    unsigned int fieldCount = mysql_num_fields(res);
                    //MYSQL_FIELD * fieldDesc = mysql_fetch_field(res);
                    MYSQL_ROW row;
                    while ((row = mysql_fetch_row(res)) != NULL)
                    {
                        unsigned long * fieldLength = mysql_fetch_lengths(res);
                        for (unsigned int i = 0; i < fieldCount; ++i)
                        {
                            if (fieldLength[i] == 0 || row[i] == nullptr)
                            {
                                _result.push_back("");
                            }
                            else
                            {
                                _result.push_back(std::string(row[i], fieldLength[i]));
                            }
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
                LOGE("mysql_init false. mysql ip = " << _ip << ", _port = " << _port << ", _user = " << _user << ", _pwd = " << _pwd << ", _db=" << _db);
                return false;
            }
            mysql_options(_mysql, MYSQL_OPT_CONNECT_TIMEOUT, "5");
            mysql_options(_mysql, MYSQL_SET_CHARSET_NAME, "UTF8");
            mysql_set_character_set(_mysql, "UTF8");
            if (!_autobuild)
            {
                MYSQL * ret = mysql_real_connect(_mysql, _ip.c_str(), _user.c_str(), _pwd.c_str(), _db.c_str(), _port, nullptr, 0);
                if (ret)
                {
                    _waiting = true;
                    return true;
                }
            }
            else
            {
                MYSQL * ret = mysql_real_connect(_mysql, _ip.c_str(), _user.c_str(), _pwd.c_str(), "mysql", _port, nullptr, 0);
                if (ret)
                {
                    std::string sql = "use `" + _db + "`";
                    auto result = query(sql);
                    if (result->getErrorCode() == QEC_SUCCESS)
                    {
                        _waiting = true;
                        return true;
                    }
                    else
                    {
                        sql = "create database `" + _db + "`";
                        result = query(sql);
                        if (result->getErrorCode() == QEC_SUCCESS)
                        {
                            sql = "use `" + _db + "`";
                            result = query(sql);
                            if (result->getErrorCode() == QEC_SUCCESS)
                            {
                                _waiting = true;
                                return true;
                            }
                        }
                    }
                }
                
            }
            if (_mysql)
            {
                mysql_close(_mysql);
                _mysql = nullptr;
            }
            return false;
        }

        bool DBHelper::waitEnable()
        {
            if (!_waiting)
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
            } while (_waiting);
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
                            ret->buildResult(QueryErrorCode::QEC_SUCCESS, sql, _mysql);
                            return ret;
                        }
                    }
                }
                ret->buildResult(QueryErrorCode::QEC_MYSQLERROR, sql, _mysql);
                return ret;
            }
            ret->buildResult(QueryErrorCode::QEC_SUCCESS, sql, _mysql);
            return ret;
        }




        inline DBResult & operator >>(DBResult &result, long long & t)
        {
            std::string  field = result.popOrgField();
            if (field.empty())
            {
                t = 0;
            }
            else
            {
                t = atoll(field.c_str());
            }
            return result;
        }
        inline DBResult & operator >>(DBResult &result, int & t)
        {
            long long tt;
            result >> tt;
            t = (int)tt;
            return result;
        }
        inline DBResult & operator >>(DBResult &result, short & t)
        {
            long long tt;
            result >> tt;
            t = (short)tt;
            return result;
        }
        inline DBResult & operator >>(DBResult &result, char & t)
        {
            long long tt;
            result >> tt;
            t = (char)tt;
            return result;
        }
        inline DBResult & operator >>(DBResult &result, unsigned long long & t)
        {
            std::string  field = result.popOrgField();
            if (field.empty())
            {
                t = 0;
            }
            else
            {
                char *cursor = nullptr;
                t = strtoull(field.c_str(), &cursor, 10);
            }
            return result;
        }
        inline DBResult & operator >>(DBResult &result, unsigned int & t)
        {
            unsigned long long tt;
            result >> tt;
            t = (unsigned int)tt;
            return result;
        }
        inline DBResult & operator >>(DBResult &result, unsigned short & t)
        {
            unsigned long long tt;
            result >> tt;
            t = (unsigned short)tt;
            return result;
        }
        inline DBResult & operator >>(DBResult &result, unsigned char & t)
        {
            unsigned long long tt;
            result >> tt;
            t = (unsigned char)tt;
            return result;
        }

        inline DBResult & operator >>(DBResult &result, double & t)
        {
            std::string field = result.popOrgField();
            if (field.empty())
            {
                t = 0.0;
            }
            else
            {
                char *cursor = nullptr;
                t = strtold(field.c_str(), &cursor);
            }
            return result;
        }
        inline DBResult & operator >>(DBResult &result, float & t)
        {
            double tt;
            result >> tt;
            t = (float)tt;
            return result;
        }
        inline DBResult & operator >>(DBResult &result, std::string & t)
        {
            t = result.popOrgField();
            return result;
        }







    };
};

#endif

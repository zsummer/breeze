
/*
* breeze License
* Copyright (C) 2015 YaweiZhang <yawei_zhang@foxmail.com>.
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
*  db manager
*/




#ifndef _DB_MANAGER_H_
#define _DB_MANAGER_H_
#include <common.h>





class DBManager : public Singleton<DBManager>
{
public:
	DBManager();
	~DBManager();
	//在启动连接所有需要访问的数据库.
	bool start();
	bool stop();
public:
	inline zsummer::mysql::DBHelperPtr & getAuthDB(){ return _authDB; }
	inline zsummer::mysql::DBHelperPtr & getInfoDB(){ return _infoDB; }
	inline zsummer::mysql::DBHelperPtr & getLogDB(){ return _logDB; }
	inline zsummer::mysql::DBAsyncPtr & getAsync(){ return _dbAsync; }
private:
	zsummer::mysql::DBHelperPtr _infoDB;
	zsummer::mysql::DBHelperPtr _logDB;
	zsummer::mysql::DBHelperPtr _authDB;

	zsummer::mysql::DBAsyncPtr _dbAsync;
};




































#endif

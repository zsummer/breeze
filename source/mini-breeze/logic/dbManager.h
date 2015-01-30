
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
*  db manager
*/




#ifndef _DB_MANAGER_H_
#define _DB_MANAGER_H_
#include <common.h>
#include <unordered_map>
#include <DBAsync.h>



class DBManager :public BaseMessageHandler, public Singleton<DBManager>
{
public:
	DBManager();
	~DBManager();
	virtual bool init() final override;
	virtual void userLogin(std::shared_ptr<InnerUserInfo> innerInfo) final override;
	virtual void userLogout(std::shared_ptr<InnerUserInfo> innerInfo) final override;
public:
	inline DBHelperPtr & getAuthDB(){ return _authDB; }
	inline DBHelperPtr & getInfoDB(){ return _infoDB; }
	inline DBHelperPtr & getLogDB(){ return _logDB; }
private:
	DBHelperPtr _infoDB;
	DBHelperPtr _logDB;
	DBHelperPtr _authDB;
};




































#endif

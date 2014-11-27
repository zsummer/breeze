
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
#include <Common.h>
#include <unordered_map>
#include <DBHelper.h>



class CDBManager :public CBaseHandler, public Singleton<CDBManager>
{
public:
	CDBManager();
	~CDBManager();
	virtual bool Init() final override;
	virtual void CharLogin(std::shared_ptr<InnerCharInfo> iinfoPtr) final override;
	virtual void CharLogout(std::shared_ptr<InnerCharInfo> iinfoPtr) final override;
public:
	inline DBHelperPtr & getAuthDB(){ return m_authDB; }
	inline DBHelperPtr & getInfoDB(){ return m_infoDB; }
	inline DBHelperPtr & getLogDB(){ return m_logDB; }
private:
	DBHelperPtr m_infoDB;
	DBHelperPtr m_logDB;
	DBHelperPtr m_authDB;
};




































#endif

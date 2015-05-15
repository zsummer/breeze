
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
*  user manager
*/




#ifndef _USER_MANAGER_H_
#define _USER_MANAGER_H_
#include <common.h>
#include <ProtoLogin.h>




class UserManager :public Singleton<UserManager>
{
public:
	UserManager();
	bool init();

public:
	//interface
	std::shared_ptr<InnerUserInfo> getInnerUserInfo(UserID uID);
	std::shared_ptr<InnerUserInfo> getInnerUserInfoBySID(SessionID sID);
	std::shared_ptr<InnerUserInfo> getInnerUserInfoByNickName(const std::string & nickName);
    
	inline size_t getAllOnlineUserCount() { return _mapSession.size(); }
	inline size_t getAllUserCount() { return _mapUser.size(); }

    
    
public:
	void addUser(std::shared_ptr<InnerUserInfo> innerInfo);
	void userLogin(std::shared_ptr<InnerUserInfo> innerInfo);
	void userLogout(std::shared_ptr<InnerUserInfo> innerInfo);
protected:
	
private:
	//sessionID和userID索引
	//服务器启动时加载所有用户数据
	//用户退出后不释放该用户的内存, 仅仅对InnerUserInfo中的sessionID赋值为Invalid标记, 并删除_mapUserSession中的索引. 因此可以很方便的做快速重连的功能.
	//用户所有私有数据应当以扩展InnerUserInfo结构的形式去做. 比如添加装备,背包,任务进度 等.
	std::unordered_map<SessionID, std::shared_ptr<InnerUserInfo>> _mapSession;
	std::unordered_map<UserID, std::shared_ptr<InnerUserInfo>> _mapUser;
	std::unordered_map<std::string, std::shared_ptr<InnerUserInfo>> _mapNickName;
};




































#endif


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
 *  global facade 
 *
 */


#ifndef _GLOBAL_FACADE_H_
#define _GLOBAL_FACADE_H_
#include <ProtoDefine.h>
#include <BaseHander.h>
class ServerConfig;
class CNetManager;

class GlobalFacade
{
public:
	GlobalFacade();
	~GlobalFacade();
	static GlobalFacade & getRef();
	static GlobalFacade * getPtr(){ return &getRef(); }
	
	bool init(std::string configFile, ServerNode node, NodeIndex index);
	inline ServerConfig & getServerConfig(){ return *m_serverConfig; }

	inline CNetManager & getNetManger(){ return *m_netManger; }

	std::vector<CBaseHandler*> & getAllHandler(){ return m_vctHandler; }
private:
	ServerConfig * m_serverConfig;
	CNetManager * m_netManger;
	std::vector<CBaseHandler*> m_vctHandler;
};




































#endif

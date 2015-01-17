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


//! 测试

#include <Common.h>
#include <ProtoLogin.h>
#include <unordered_map>
extern "C"
{
#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lpack.h"
}

#include "lua/summer.h"

using namespace zsummer::log4z;

//! 默认启动参数

unsigned short g_agentIndex = 0; //
unsigned short g_maxClient = 1; //如启动的客户端总数.

enum StressType
{
	ST_NORMAL = 0,
	ST_LOGIN,
};
StressType g_stressType = ST_NORMAL;


//!收发包测试统计数据
unsigned long long g_totalEchoCount = 0;
unsigned long long g_lastEchoCount = 0;
unsigned long long g_totalSendCount = 0;
unsigned long long g_totalRecvCount = 0;
void MonitorFunc()
{
	LOGI("per seconds Echos Count=" << (g_totalEchoCount - g_lastEchoCount) / 5
		<< ", g_totalSendCount[" << g_totalSendCount << "] g_totalRecvCount[" << g_totalRecvCount << "]");
	g_lastEchoCount = g_totalEchoCount;
	TcpSessionManager::getRef().createTimer(5000, MonitorFunc);
};


class StressHeartbeatManager
{
public:
	StressHeartbeatManager()
	{
		//! 注册事件和消息
		MessageDispatcher::getRef().registerOnSessionEstablished(std::bind(&StressHeartbeatManager::onSessionEstablished, this,
			std::placeholders::_1));
		MessageDispatcher::getRef().registerOnSessionPulse(std::bind(&StressHeartbeatManager::onSessionPulse, this,
			std::placeholders::_1, std::placeholders::_2));
		MessageDispatcher::getRef().registerOnSessionDisconnect(std::bind(&StressHeartbeatManager::onSessionDisconnect, this,
			std::placeholders::_1));
	}
	
	void onSessionEstablished(SessionID sID)
	{
		LOGI("connect sucess. sID=" << sID);
	}
	void onSessionPulse(SessionID sID, unsigned int pulseInterval)
	{
		WriteStreamPack ws(ID_C2AS_ClientPulse);
		ws << C2AS_ClientPulse();
		TcpSessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
		g_totalSendCount++;
	}
	void onSessionDisconnect(SessionID sID)
	{
		LOGI("Disconnect. sID=" << sID);
	}
};



class StressClientHandler
{
public:
	StressClientHandler()
	{
		MessageDispatcher::getRef().registerOnSessionEstablished(std::bind(&StressClientHandler::onConnected, this, std::placeholders::_1));
		MessageDispatcher::getRef().registerSessionMessage(ID_LS2C_LoginAck,
			std::bind(&StressClientHandler::msg_onLoginAck, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		MessageDispatcher::getRef().registerSessionMessage(ID_LS2C_CreateUserAck,
			std::bind(&StressClientHandler::msg_onCreateUserAck, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		
		MessageDispatcher::getRef().registerOnSessionDisconnect(std::bind(&StressClientHandler::onConnectDisconnect, this, std::placeholders::_1));
	}

	void onConnected(SessionID sID)
	{
		LOGD("onConnected. SessionID=" << sID);
		char userName[100];
		sprintf(userName, "zhangyawei%04d", (unsigned int)sID - __MIDDLE_SEGMENT_VALUE);
		WriteStreamPack ws(ID_C2LS_LoginReq);
		C2LS_LoginReq req;
		req.user = userName;
		req.passwd = "123";
		ws << req;
		TcpSessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
		LOGD("onConnected. Send C2LS_LoginReq. sID=" << sID << ", user=" << req.user << ", passwd=" << req.passwd);
		g_totalSendCount++;
	};
	void onConnectDisconnect(SessionID sID)
	{
		_sessionStatus[sID] = false;
	}

	inline void msg_onLoginAck(SessionID sID, ProtoID pID, ReadStreamPack & rs)
	{

		LS2C_LoginAck ack;
		rs >> ack;
		if (ack.retCode == BEC_SUCCESS)
		{
			LOGD("msg_onLoginAck Success. sID=" << sID);
		}
		else
		{
			LOGE("msg_onLoginAck Failed. sID=" << sID);
			return;
		}


		g_totalRecvCount++;
		g_totalEchoCount++;


		if (ack.needCreateUser)
		{
			C2LS_CreateUserReq req;
			req.nickName = "summer";
			req.nickName += toString(rand() % 100);
			req.iconID = 100;
			WriteStreamPack ws(ID_C2LS_CreateUserReq);
			ws << req;
			TcpSessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
			g_totalSendCount++;
		}
		else
		{
			LOGD("login success. sID=" << sID << ", nickname=" << ack.info.nickName);
			if (g_stressType == ST_LOGIN)
			{
				char userName[100];
				sprintf(userName, "zhangyawei%04d", (unsigned int)sID - __MIDDLE_SEGMENT_VALUE);
				WriteStreamPack ws(ID_C2LS_LoginReq);
				C2LS_LoginReq req;
				req.user = userName;
				req.passwd = "123";
				ws << req;
				TcpSessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
				LOGD("onConnected. Send C2LS_LoginReq. sID=" << sID << ", user=" << req.user << ", passwd=" << req.passwd);
				g_totalSendCount++;
			}
			
		}
	}

	inline void msg_onCreateUserAck(SessionID sID, ProtoID pID, ReadStreamPack & rs)
	{
		LS2C_CreateUserAck ack;
		rs >> ack;
		g_totalRecvCount++;
		g_totalEchoCount++;

		if (ack.retCode != BEC_SUCCESS)
		{
			LOGE("msg_onCreateUserAck Failed. sID=" << sID << ", retCode=" << ack.retCode);
			return;
		}
	

		if (ack.needCreateUser)
		{
			C2LS_CreateUserReq req;
			req.nickName = "summer";
			req.nickName += toString(rand() % 100);
			req.iconID = 100;
			WriteStreamPack ws(ID_C2LS_CreateUserReq);
			ws << req;
			TcpSessionManager::getRef().sendOrgSessionData(sID, ws.getStream(), ws.getStreamLen());
			g_totalSendCount++;
		}
		else
		{
			LOGD("msg_onCreateUserAck Success. sID=" << sID << ", nickname=" << ack.info.nickName << ", uid=" << ack.info.uid);
		}
	}
	

private:
	std::unordered_map<SessionID, bool> _sessionStatus;
};

void sigInt(int sig)
{
	LOGI("catch SIGINT.");
	TcpSessionManager::getRef().stop();
}


int main(int argc, char* argv[])
{

#ifndef _WIN32
	//! linux下需要屏蔽的一些信号
	signal( SIGHUP, SIG_IGN );
	signal( SIGALRM, SIG_IGN ); 
	signal( SIGPIPE, SIG_IGN );
	signal( SIGXCPU, SIG_IGN );
	signal( SIGXFSZ, SIG_IGN );
	signal( SIGPROF, SIG_IGN ); 
	signal( SIGVTALRM, SIG_IGN );
	signal( SIGQUIT, SIG_IGN );
	signal( SIGCHLD, SIG_IGN);
#endif
// 	signal(SIGINT, &sigInt);
// 	signal(SIGTERM, &sigInt);

		
	ILog4zManager::getPtr()->config("log.config");
	ILog4zManager::getPtr()->start();
	ILog4zManager::getRef().setLoggerFileLine(LOG4Z_MAIN_LOGGER_ID, false);
	int status;
	lua_State *L = luaL_newstate();  /* create state */
	if (L == NULL)
	{
		return EXIT_FAILURE;
	}

	lua_gc(L, LUA_GCSTOP, 0);  /* stop collector during initialization */
	luaL_openlibs(L);  /* open libraries */
	luaopen_summer(L);
	luaopen_pack(L);

	lua_gc(L, LUA_GCRESTART, 0);
	status = luaL_dofile(L, "./main.lua");

	if (status && !lua_isnil(L, -1))
	{
		const char *msg = lua_tostring(L, -1);
		if (msg == NULL) msg = "(error object is not a string)";
		LOGE(msg);
		lua_pop(L, 1);
	}
	lua_close(L);
	return (status) ? EXIT_FAILURE : EXIT_SUCCESS;


	ServerConfig serverConfig;
	if (!serverConfig.parse("../ServerConfig.xml", MiniBreezeNode, g_agentIndex))
	{
		LOGE("serverConfig.parse failed");
		return 0;
	}
	LOGI("g_remoteIP=" << "127.0.0.1" << ", g_remotePort=" << serverConfig.getConfigListen(MiniBreezeNode).port << ", g_maxClient=" << g_maxClient);


// 	CMongoManager mongoMgr;
// 	if (!mongoMgr.ConnectMongo(mongoMgr.getAuthMongo(), serverConfig.getAuthMongoDB()))
// 	{
// 		LOGE("connect mongo error");
// 		return 0;
// 	}
// 
// 	for (size_t i = 0; i < 6000; i++)
// 	{
// 		char buf[100];
// 		sprintf(buf, "zhangyawei%04d", (int)i);
// 		std::string dbcl = serverConfig.getAuthMongoDB().db;
// 		dbcl += ".cl_auth";
// 		mongoMgr.getAuthMongo()->update(dbcl, QUERY("_id" << buf), BSON("pwd" << "123" << "accID" << (long long)i), true);
// 		std::string errMsg = mongoMgr.getAuthMongo()->getLastError();
// 		if (!errMsg.empty())
// 		{
// 			LOGE("update auth db error: " << errMsg);
// 			return 0;
// 		}
// 	}
	
	



	TcpSessionManager::getRef().start();
	
	TcpSessionManager::getRef().createTimer(5000, MonitorFunc);

	//创建心跳管理handler的实例 只要创建即可, 构造函数中会注册对应事件
	StressHeartbeatManager statusManager;

	//这里创建服务handler和客户端handler 根据启动参数不同添加不同角色.
	StressClientHandler client;
	
	//添加多个connector.
	for (int i = 0; i < g_maxClient; ++i)
	{
		tagConnctorConfigTraits traits;
		traits.remoteIP = "127.0.0.1";
		traits.remotePort = serverConfig.getConfigListen(MiniBreezeNode).port;
		traits.reconnectInterval = 5000;
		traits.reconnectMaxCount = 50;
		TcpSessionManager::getRef().addConnector(traits);
	}
	
	//启动主循环.
	TcpSessionManager::getRef().run();

	return 0;
}


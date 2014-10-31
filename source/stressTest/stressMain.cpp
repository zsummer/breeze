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
#include <MongoManager.h>
#include <ServerConfig.h>
#include <ProtoDefine.h>
#include <ProtoCommon.h>
#include <ProtoAuth.h>
#include <ProtoLogin.h>
#include <unordered_map>

using namespace zsummer::log4z;

//! 默认启动参数

unsigned short g_agentIndex = 0; //
unsigned short g_maxClient = 1; //如启动的客户端总数.

enum StressType
{
	ST_NORMAL = 0,
	ST_AUTH,
	ST_LOAD_ACCOUNT,
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
	CTcpSessionManager::getRef().CreateTimer(5000, MonitorFunc);
};


class CStressHeartBeatManager
{
public:
	CStressHeartBeatManager()
	{
		//! 注册事件和消息
		CMessageDispatcher::getRef().RegisterOnSessionEstablished(std::bind(&CStressHeartBeatManager::OnConnecotrConnected, this,
			std::placeholders::_1));
		CMessageDispatcher::getRef().RegisterOnSessionPulse(std::bind(&CStressHeartBeatManager::OnConnecotrPulse, this,
			std::placeholders::_1, std::placeholders::_2));
		CMessageDispatcher::getRef().RegisterOnSessionDisconnect(std::bind(&CStressHeartBeatManager::OnConnecotrDisconnect, this,
			std::placeholders::_1));
	}
	
	void OnConnecotrConnected(SessionID cID)
	{
		LOGI("connect sucess. cID=" << cID);
	}
	void OnConnecotrPulse(SessionID cID, unsigned int pulseInterval)
	{
		WriteStreamPack ws;
		ws << ID_C2AS_ClientPulse << C2AS_ClientPulse();
		CTcpSessionManager::getRef().SendOrgSessionData(cID, ws.GetStream(), ws.GetStreamLen());
		g_totalSendCount++;
	}
	void OnConnecotrDisconnect(SessionID cID)
	{
		LOGI("Disconnect. cID=" << cID);
	}
};



class CStressClientHandler
{
public:
	CStressClientHandler()
	{
		CMessageDispatcher::getRef().RegisterOnSessionEstablished(std::bind(&CStressClientHandler::OnConnected, this, std::placeholders::_1));
		CMessageDispatcher::getRef().RegisterSessionMessage(ID_AS2C_AuthAck,
			std::bind(&CStressClientHandler::msg_AuthAck_fun, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		CMessageDispatcher::getRef().RegisterSessionMessage(ID_LS2C_LoadAccountInfoAck,
			std::bind(&CStressClientHandler::msg_LoadAccountInfoAck_fun, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		CMessageDispatcher::getRef().RegisterSessionMessage(ID_LS2C_CreateCharacterAck,
			std::bind(&CStressClientHandler::msg_CreateCharacterAck_fun, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		CMessageDispatcher::getRef().RegisterSessionMessage(ID_LS2C_CharacterLoginAck,
			std::bind(&CStressClientHandler::msg_CharacterLoginAck_fun, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		CMessageDispatcher::getRef().RegisterOnSessionDisconnect(std::bind(&CStressClientHandler::OnConnectDisconnect, this, std::placeholders::_1));
	}

	void OnConnected(SessionID cID)
	{
		LOGI("OnConnected. ConnectorID=" << cID);
		char userName[100];
		sprintf(userName, "zhangyawei%04d", (unsigned int)cID - __MIDDLE_SEGMENT_VALUE);
		WriteStreamPack ws;
		C2AS_AuthReq req;
		req.info.user = userName;
		req.info.pwd = "123";
		ws << ID_C2AS_AuthReq << req;
		CTcpSessionManager::getRef().SendOrgSessionData(cID, ws.GetStream(), ws.GetStreamLen());
		LOGI("OnConnected. Send AuthReq. cID=" << cID << ", user=" << req.info.user << ", pwd=" << req.info.pwd);
		g_totalSendCount++;
	};
	void OnConnectDisconnect(SessionID cID)
	{
		m_sessionStatus[cID] = false;
	}

	inline void msg_AuthAck_fun(SessionID cID, ProtoID pID, ReadStreamPack & rs)
	{

		AS2C_AuthAck ack;
		rs >> ack;
		if (ack.retCode == EC_SUCCESS)
		{
			LOGD("Auth Success. cID=" << cID);
		}
		else
		{
			LOGE("Auth Failed. cID=" << cID);
			return;
		}


		g_totalRecvCount++;
		g_totalEchoCount++;

		if (g_stressType == ST_NORMAL)
		{
			WriteStreamPack ws;
			C2LS_LoadAccountInfoReq req;
			ws << ID_C2LS_LoadAccountInfoReq << req;
			CTcpSessionManager::getRef().SendOrgSessionData(cID, ws.GetStream(), ws.GetStreamLen());
			LOGD("msg_AuthAck. Send LoginReq. cID=" << cID);
			g_totalSendCount++;
		}
		else if (g_stressType == ST_AUTH)
		{
			char userName[100];
			sprintf(userName, "zhangyawei%04d", (int)cID);
			WriteStreamPack ws;
			C2AS_AuthReq req;
			req.info.user = userName;
			req.info.pwd = "123";
			ws << ID_C2AS_AuthReq << req;
			CTcpSessionManager::getRef().SendOrgSessionData(cID, ws.GetStream(), ws.GetStreamLen());
			LOGD("msg_AuthAck. Send AuthReq. cID=" << cID << ", user=" << req.info.user << ", pwd=" << req.info.pwd);
			g_totalSendCount++;
			return;
		}

	};

	inline void msg_LoadAccountInfoAck_fun(SessionID cID, ProtoID pID, ReadStreamPack & rs)
	{
		LS2C_LoadAccountInfoAck ack;
		rs >> ack;

		g_totalRecvCount++;
		g_totalEchoCount++;
		if (ack.retCode != EC_SUCCESS)
		{
			LOGE("msg_LoadAccountInfoAck_fun Failed. cID=" << cID << ", retCode=" <<ack.retCode);
			return;
		}

		LOGD("msg_LoadAccountInfoAck_fun Success. cID=" << cID << ", accID=" << ack.info.accID << ", diamond=" << ack.info.diamond);
		if (g_stressType == ST_NORMAL)
		{
			//create character
			if (ack.info.charInfos.empty())
			{
				WriteStreamPack ws(zsummer::proto4z::UBT_STATIC_AUTO);
				C2LS_CreateCharacterReq req;
				req.charName = "test";
				ws << ID_C2LS_CreateCharacterReq << req;
				CTcpSessionManager::getRef().SendOrgSessionData(cID, ws.GetStream(), ws.GetStreamLen());
				LOGD("msg_LoadAccountInfoAck_fun. Send ID_C2LS_CreateCharacterReq. cID=" << cID);
				g_totalSendCount++;
			}
			//login
			else
			{
				WriteStreamPack ws(zsummer::proto4z::UBT_STATIC_AUTO);
				C2LS_CharacterLoginReq req;
				req.charID = ack.info.charInfos.at(0).charID;
				ws << ID_C2LS_CharacterLoginReq << req;
				CTcpSessionManager::getRef().SendOrgSessionData(cID, ws.GetStream(), ws.GetStreamLen());
				LOGD("msg_LoadAccountInfoAck_fun. Send ID_C2LS_CharacterLoginReq. cID=" << cID);
				g_totalSendCount++;
			}
		}
		else if (g_stressType == ST_LOAD_ACCOUNT)
		{
			WriteStreamPack ws(zsummer::proto4z::UBT_STATIC_AUTO);
			C2LS_LoadAccountInfoReq req;
			ws << ID_C2LS_LoadAccountInfoReq << req;
			CTcpSessionManager::getRef().SendOrgSessionData(cID, ws.GetStream(), ws.GetStreamLen());
			LOGD("msg_LoadAccountInfoAck_fun. Send ID_C2LS_LoadAccountInfoReq. cID=" << cID);
			g_totalSendCount++;
		}
	}
	inline void msg_CreateCharacterAck_fun(SessionID cID, ProtoID pID, ReadStreamPack & rs)
	{
		LS2C_CreateCharacterAck ack;
		rs >> ack;

		g_totalRecvCount++;
		g_totalEchoCount++;

		if (ack.retCode != EC_SUCCESS)
		{
			LOGE("msg_CreateCharacterAck_fun Failed. cID=" << cID << ", retCode=" << ack.retCode);
			return;
		}

		LOGD("msg_CreateCharacterAck_fun Success. cID=" << cID << ", charName=" << ack.lci.charName << ", charID=" << ack.lci.charID);
		if (g_stressType == ST_NORMAL)
		{
			WriteStreamPack ws(zsummer::proto4z::UBT_STATIC_AUTO);
			C2LS_CharacterLoginReq req;
			req.charID = ack.lci.charID;
			ws << ID_C2LS_CharacterLoginReq << req;
			CTcpSessionManager::getRef().SendOrgSessionData(cID, ws.GetStream(), ws.GetStreamLen());
			LOGD("msg_CreateCharacterAck_fun. Send ID_C2LS_CharacterLoginReq. cID=" << cID);
			g_totalSendCount++;
		}
	}
	inline void msg_CharacterLoginAck_fun(SessionID cID, ProtoID pID, ReadStreamPack & rs)
	{
		LS2C_CharacterLoginAck ack;
		rs >> ack;

		g_totalRecvCount++;
		g_totalEchoCount++;

		if (ack.retCode != EC_SUCCESS)
		{
			LOGE("msg_CharacterLoginAck_fun Failed. cID=" << cID << ", retCode=" << ack.retCode);
			return;
		}

		LOGD("msg_CharacterLoginAck_fun Success. cID=" << cID << ", charName=" << ack.info.charName << ", charID=" << ack.info.charID);
	}

private:
	std::unordered_map<SessionID, bool> m_sessionStatus;
};

void sigInt(int sig)
{
	LOGI("catch SIGINT.");
	CTcpSessionManager::getRef().Stop();
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
	signal(SIGINT, &sigInt);
	signal(SIGTERM, &sigInt);

	if (argc == 2 && 
		(strcmp(argv[1], "--help") == 0 
		|| strcmp(argv[1], "/?") == 0))
	{
		cout << "please input like example:" << endl;
		cout << "tcpTest agentIndex maxClient" << endl;
		cout << "./tcpTest 0 1" << endl;
		cout << "maxClient: limit max" << endl;
		return 0;
	}
	if (argc > 1)
		g_agentIndex = atoi(argv[1]);
	if (argc > 2)
		g_maxClient = atoi(argv[2]);
	if (g_maxClient > 6000)
	{
		g_maxClient = 6000;
	}
	
		
		


	ILog4zManager::GetInstance()->Config("../log.config");
	ILog4zManager::GetInstance()->Start();





	ServerConfig serverConfig;
	if (!serverConfig.Parse("../ServerConfig.xml", AgentNode, g_agentIndex))
	{
		LOGE("serverConfig.Parse failed");
		return 0;
	}
	LOGI("g_remoteIP=" << "127.0.0.1" << ", g_remotePort=" << serverConfig.getConfigListen(AgentNode).port << ", g_maxClient=" << g_maxClient);


	CMongoManager mongoMgr;
	if (!mongoMgr.ConnectMongo(mongoMgr.getAuthMongo(), serverConfig.getAuthMongoDB()))
	{
		LOGE("connect mongo error");
		return 0;
	}

	for (size_t i = 0; i < 6000; i++)
	{
		char buf[100];
		sprintf(buf, "zhangyawei%04d", (int)i);
		std::string dbcl = serverConfig.getAuthMongoDB().db;
		dbcl += ".cl_auth";
		mongoMgr.getAuthMongo()->update(dbcl, QUERY("_id" << buf), BSON("pwd" << "123" << "accID" << (long long)i), true);
		std::string errMsg = mongoMgr.getAuthMongo()->getLastError();
		if (!errMsg.empty())
		{
			LOGE("update auth db error: " << errMsg);
			return 0;
		}
	}
	
	



	CTcpSessionManager::getRef().Start();
	
	CTcpSessionManager::getRef().CreateTimer(5000, MonitorFunc);

	//创建心跳管理handler的实例 只要创建即可, 构造函数中会注册对应事件
	CStressHeartBeatManager statusManager;

	//这里创建服务handler和客户端handler 根据启动参数不同添加不同角色.
	CStressClientHandler client;
	
	//添加多个connector.
	for (int i = 0; i < g_maxClient; ++i)
	{
		tagConnctorConfigTraits traits;
		traits.remoteIP = "127.0.0.1";
		traits.remotePort = serverConfig.getConfigListen(AgentNode).port;
		traits.reconnectInterval = 5000;
		traits.reconnectMaxCount = 50;
		CTcpSessionManager::getRef().AddConnector(traits);
	}
	
	//启动主循环.
	CTcpSessionManager::getRef().Run();

	return 0;
}


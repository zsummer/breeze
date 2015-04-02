
/*
* breeze License
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
*  network manager
*/




#ifndef _NET_MANAGER_H_
#define _NET_MANAGER_H_
#include <common.h>
#include <ProtoLogin.h>
using namespace zsummer::mysql;



class NetManager :public Singleton<NetManager>
{
public:
	NetManager();
	//启动
	bool start();
	//关闭
	bool stop();

protected:
	//! ---- callback --------------------------------------------


	//底层session建立和断开通知
	void event_onSessionEstablished(SessionID);
	void event_onSessionDisconnect(SessionID);
	
	//检测发包频度,发包权限,登录权限等.
	bool on_preMessageProcess(SessionID sID, const char * blockBegin, zsummer::proto4z::Integer blockSize);


	//! ---- message --------------------------------------------
	//////////////////////////////////////////////////////////////////////////
	//登录流程(集成认证流程和用户数据拉取流程)
	void msg_onLoginReq(SessionID sID, ProtoID pID, ReadStream & rs);
	void db_onAuthSelect(DBResultPtr res, SessionID sID);


	//创建用户流程
	void msg_onCreateUserReq(SessionID sID, ProtoID pID, ReadStream &rs);
	void db_onUserCreate(DBResultPtr res, SessionID sID);

	//测试mysql存储blob
	void db_onTestBlog(DBResultPtr res, bool isRead);


	//session存活脉冲, 这个由zsummerX网络库维护, 每个session建立后都会定时调用该回调.
	//由registerOnSessionPulse进行注册的定时脉冲. 用于检测session异常断线. 定时周期在ListenConfig中配置
	void event_onPulse(SessionID sID, unsigned int pulseInterval);

	//在协议中定义的一个脉冲消息, 定时发送一个脉冲, 配合event_onPulse完成异常断线检测.
	void msg_onServerPulseEcho(SessionID sID, ProtoID pID, ReadStream & rs);

private:
	std::map<UserID, SessionInfo> _clients;
	//监听配置.
	zsummer::network::ListenConfig _configListen; 
	bool _bListening = false;
	AccepterID _accepterID = InvalidAccepterID;
};




































#endif

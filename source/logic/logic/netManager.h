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
	bool stop(std::function<void()> onSafeClosed);

protected:
	//! ---- callback --------------------------------------------


	//底层session建立和断开通知
	void event_onSessionEstablished(TcpSessionPtr session);
	void event_onSessionDisconnect(TcpSessionPtr session);
	
	//检测发包频度,发包权限,登录权限等.
	bool on_preMessageProcess(TcpSessionPtr session, const char * blockBegin, zsummer::proto4z::Integer blockSize);

	//! ---- message --------------------------------------------
	//////////////////////////////////////////////////////////////////////////
	//登录流程(集成认证流程和用户数据拉取流程)
	void msg_onLoginReq(TcpSessionPtr session, ProtoID pID, ReadStream & rs);

	//脉冲检测.
	void event_onSessionPulse(TcpSessionPtr session, unsigned int pulseInterval);

	//在协议中定义的一个脉冲消息, 定时发送一个脉冲, 配合event_onPulse完成异常断线检测.
	void msg_onHeartbeatEcho(TcpSessionPtr session, ProtoID pID, ReadStream & rs);

private:
	//监听配置.
	zsummer::network::ListenConfig _configListen;
	AccepterID _accepterID = InvalidAccepterID;
	//内部token
	std::map<UserID, std::string> _token;
	//进程退出时候的回调
	std::function<void()> _onSafeClosed;
};




































#endif

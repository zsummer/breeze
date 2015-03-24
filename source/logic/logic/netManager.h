
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
#include <dbAsync.h>
#include <unordered_map>
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

	//用户登录成功
	void userLogin(std::shared_ptr<InnerUserInfo> innerInfo);
	//用户退出.
	void userLogout(std::shared_ptr<InnerUserInfo> innerInfo);

	//底层session建立和断开通知
	void event_onSessionEstablished(SessionID);
	void event_onSessionDisconnect(SessionID);


	//登录流程(集成认证流程和用户数据拉取流程)
	void msg_onLoginReq(SessionID sID, ProtoID pID, ReadStream & rs);
	void db_onAuthSelect(DBResultPtr res, SessionID sID);
	void db_onUserSelect(DBResultPtr res, SessionID sID, bool isCreateUser);

	void db_updateUserInfo(const UserInfo & ui);

	//创建用户流程
	void msg_onCreateUserReq(SessionID sID, ProtoID pID, ReadStream &rs);
	void db_onUserCreate(DBResultPtr res, SessionID sID);

	//测试mysql存储blob
	void db_onTestBlog(DBResultPtr res, bool isRead);


	//session存活脉冲, 这个由zsummerX网络库维护, 每个session建立后都会定时调用该回调.
	//由registerOnSessionPulse进行注册的定时脉冲. 用于检测session异常断线. 定时周期在ListenConfig中配置
	void event_onPulse(SessionID sID, unsigned int pulseInterval);

	//在协议中定义的一个脉冲消息, 定时发送一个脉冲, 配合event_onPulse完成异常断线检测.
	void msg_onServerPulse(SessionID sID, ProtoID pID, ReadStream & rs);

private:

	//所有MessageHandler派生类都要塞进这个数组中, 服务开启时的初始化以及玩家登录退出的通知均依靠这个数组进行派发.
	std::vector<MessageHandler*> _handlers;

	//sessionID和userID索引
	//服务器启动时不加载用户数据, 用户第一次登录才去数据库拉取数据 并判断是否需要创建用户信息
	//用户退出后不释放该用户的内存, 仅仅对InnerUserInfo中的sessionID赋值为Invalid标记, 并删除_mapUserSession中的索引. 因此可以很方便的做快速重连的功能.
	//用户所有私有数据应当以扩展InnerUserInfo结构的形式去做. 比如添加装备,背包,任务进度 等.
	std::unordered_map<SessionID, std::shared_ptr<InnerUserInfo>> _mapUserSession;
	std::unordered_map<UserID, std::shared_ptr<InnerUserInfo>> _mapUserInfo;

	//监听配置.
	zsummer::network::ListenConfig _configListen; 
	bool _bListening = false;
	AccepterID _accepterID = InvalidAccepterID;
};




































#endif

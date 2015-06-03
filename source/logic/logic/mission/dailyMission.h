
/*
* breeze License
* Copyright (C) 2015 YaweiZhang <yawei.zhang@foxmail.com>.
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
*  DailyMission
*/




#ifndef _DAILY_MISSION_H_
#define _DAILY_MISSION_H_
#include <common.h>
#include "eventTrigger.h"



struct DailyMissionConfig
{
    MissionID configID;
    int limitLevelMin;
    int limitLevelMax;
    int initValue;
    int finishValue;
    unsigned char clientRight; //客户端控制进度.
    unsigned char visible; //是否客户端可见 一些辅助任务客户端不需要展示

    //reward
};

struct DailyMissionInfo 
{
    MissionID id;
    unsigned int configID;
    unsigned char status; //0 进行中, 1 已完成, 2已领奖
    int progress; //进度
};


class  DailyMission :public Singleton<DailyMission>
{
public:
    DailyMission();
    ~DailyMission();
    bool init();

    bool loadConfig();// 可热更新
    bool loadInfo();
    bool updateToDB();
    bool writeToLog();
    bool flushMissionList(); //如果有条件限制 则在条件发生变化时候刷新下可接任务
    bool checkAndRefresh(bool bForce); //每日刷新 可在用户
public:
    void on_msgGetDailyMissionList();
    void on_msgChangeDailyMissionProcess();
    void on_msgTakeDailyMissionReward();

protected:
    void onUserLogin(EventTriggerID tID, UserID uID, Any, Any, Any);

private:
    std::map<MissionID, DailyMissionInfo> _infos;
    std::map<MissionID, DailyMissionConfig> _configs;
    std::unordered_map<UserID, std::vector<MissionID> > _userMission;
    std::unordered_map<UserID, std::map<EventTriggerID, MissionID> > _triggers; //完成一个删一个.
};




































#endif

 
#ifndef _PROTOSCENECOMMON_H_ 
#define _PROTOSCENECOMMON_H_ 
 
 
enum SCENE_TYPE : unsigned short 
{ 
    SCENE_NONE = 0, //无效  
    SCENE_HOME = 1, //主城  
    SCENE_MELEE = 2, //乱斗场  
    SCENE_ARENA = 3, //竞技场  
    SCENE_GUILD = 4, //公会  
    SCENE_MASTER_INSTANCING = 5, //主线副本  
    SCENE_BRANCH_INSTANCING = 6, //支线副本  
    SCENE_MAX = 7, //最大类型数值. 扩展类型在该枚举之前插入新类型.  
}; 
 
enum SCENE_STATE : unsigned short 
{ 
    SCENE_STATE_NONE = 0, //不存在  
    SCENE_STATE_MATCHING = 1, //匹配中  
    SCENE_STATE_CHOISE = 2, //选择英雄  
    SCENE_STATE_ALLOCATE = 3, //服务器分配场景中  
    SCENE_STATE_WAIT = 4, //等待玩家加入战场  
    SCENE_STATE_ACTIVE = 5, //战斗中  
}; 
 
struct SceneGroupAvatarInfo 
{ 
    static const unsigned short getProtoID() { return 2000;} 
    static const std::string getProtoName() { return "SceneGroupAvatarInfo";} 
    unsigned long long areaID; //考虑混服情况,必须指定该玩家来自哪个当前区  
    unsigned long long modelID; //模型ID  
    DictArrayKey equips; //额外装备  
    unsigned long long avatarID;  
    std::string avatarName;  
    double rankScore; //天梯分数  
    unsigned short powerType; //组队权限: 0普通,1leader,2master  
    std::string token; //scene服务器的口令, 该字段在广播给客户端时需要清空非自己所属的token,否则将会造成token公开.  
    SceneGroupAvatarInfo() 
    { 
        areaID = 0; 
        modelID = 0; 
        avatarID = 0; 
        rankScore = 0.0; 
        powerType = 0; 
    } 
    SceneGroupAvatarInfo(const unsigned long long & areaID, const unsigned long long & modelID, const DictArrayKey & equips, const unsigned long long & avatarID, const std::string & avatarName, const double & rankScore, const unsigned short & powerType, const std::string & token) 
    { 
        this->areaID = areaID; 
        this->modelID = modelID; 
        this->equips = equips; 
        this->avatarID = avatarID; 
        this->avatarName = avatarName; 
        this->rankScore = rankScore; 
        this->powerType = powerType; 
        this->token = token; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneGroupAvatarInfo & data) 
{ 
    ws << data.areaID;  
    ws << data.modelID;  
    ws << data.equips;  
    ws << data.avatarID;  
    ws << data.avatarName;  
    ws << data.rankScore;  
    ws << data.powerType;  
    ws << data.token;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneGroupAvatarInfo & data) 
{ 
    rs >> data.areaID;  
    rs >> data.modelID;  
    rs >> data.equips;  
    rs >> data.avatarID;  
    rs >> data.avatarName;  
    rs >> data.rankScore;  
    rs >> data.powerType;  
    rs >> data.token;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneGroupAvatarInfo & info) 
{ 
    stm << "["; 
    stm << "areaID=" << info.areaID << ","; 
    stm << "modelID=" << info.modelID << ","; 
    stm << "equips=" << info.equips << ","; 
    stm << "avatarID=" << info.avatarID << ","; 
    stm << "avatarName=" << info.avatarName << ","; 
    stm << "rankScore=" << info.rankScore << ","; 
    stm << "powerType=" << info.powerType << ","; 
    stm << "token=" << info.token << ","; 
    stm << "]"; 
    return stm; 
} 
 
 
typedef std::vector<SceneGroupAvatarInfo> SceneGroupAvatarInfoArray;  
 
 
typedef std::map<unsigned long long, SceneGroupAvatarInfo> SceneGroupAvatarInfoMap;  
 
struct SceneGroupInfo //编队数据  
{ 
    static const unsigned short getProtoID() { return 2001;} 
    static const std::string getProtoName() { return "SceneGroupInfo";} 
    unsigned long long groupID;  
    unsigned short sceneType; //场景类型  
    unsigned short sceneState; //状态  
    unsigned long long mapID;  
    unsigned long long lineID; //分线ID  
    unsigned long long sceneID; //场景实例ID  
    std::string host; //服务器host  
    unsigned short port; //服务器port  
    SceneGroupAvatarInfoMap members; //队友数据  
    ServiceIDMap invitees; //邀请列表, 如果需要丰富该功能可扩展类型信息  
    SceneGroupInfo() 
    { 
        groupID = 0; 
        sceneType = 0; 
        sceneState = 0; 
        mapID = 0; 
        lineID = 0; 
        sceneID = 0; 
        port = 0; 
    } 
    SceneGroupInfo(const unsigned long long & groupID, const unsigned short & sceneType, const unsigned short & sceneState, const unsigned long long & mapID, const unsigned long long & lineID, const unsigned long long & sceneID, const std::string & host, const unsigned short & port, const SceneGroupAvatarInfoMap & members, const ServiceIDMap & invitees) 
    { 
        this->groupID = groupID; 
        this->sceneType = sceneType; 
        this->sceneState = sceneState; 
        this->mapID = mapID; 
        this->lineID = lineID; 
        this->sceneID = sceneID; 
        this->host = host; 
        this->port = port; 
        this->members = members; 
        this->invitees = invitees; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneGroupInfo & data) 
{ 
    ws << data.groupID;  
    ws << data.sceneType;  
    ws << data.sceneState;  
    ws << data.mapID;  
    ws << data.lineID;  
    ws << data.sceneID;  
    ws << data.host;  
    ws << data.port;  
    ws << data.members;  
    ws << data.invitees;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneGroupInfo & data) 
{ 
    rs >> data.groupID;  
    rs >> data.sceneType;  
    rs >> data.sceneState;  
    rs >> data.mapID;  
    rs >> data.lineID;  
    rs >> data.sceneID;  
    rs >> data.host;  
    rs >> data.port;  
    rs >> data.members;  
    rs >> data.invitees;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneGroupInfo & info) 
{ 
    stm << "["; 
    stm << "groupID=" << info.groupID << ","; 
    stm << "sceneType=" << info.sceneType << ","; 
    stm << "sceneState=" << info.sceneState << ","; 
    stm << "mapID=" << info.mapID << ","; 
    stm << "lineID=" << info.lineID << ","; 
    stm << "sceneID=" << info.sceneID << ","; 
    stm << "host=" << info.host << ","; 
    stm << "port=" << info.port << ","; 
    stm << "members=" << info.members << ","; 
    stm << "invitees=" << info.invitees << ","; 
    stm << "]"; 
    return stm; 
} 
 
 
typedef std::vector<SceneGroupInfo> SceneGroupInfoArray;  
 
 
typedef std::map<unsigned long long, SceneGroupInfo> SceneGroupInfoMap;  
 
 
typedef std::vector<unsigned long long> EntityIDArray;  
 
struct EPosition 
{ 
    static const unsigned short getProtoID() { return 2002;} 
    static const std::string getProtoName() { return "EPosition";} 
    double x;  
    double y;  
    EPosition() 
    { 
        x = 0.0; 
        y = 0.0; 
    } 
    EPosition(const double & x, const double & y) 
    { 
        this->x = x; 
        this->y = y; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const EPosition & data) 
{ 
    ws << data.x;  
    ws << data.y;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, EPosition & data) 
{ 
    rs >> data.x;  
    rs >> data.y;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const EPosition & info) 
{ 
    stm << "["; 
    stm << "x=" << info.x << ","; 
    stm << "y=" << info.y << ","; 
    stm << "]"; 
    return stm; 
} 
 
 
typedef std::vector<EPosition> EPositionArray;  
 
 
typedef std::vector<unsigned long long> SkillIDArray; //技能ID数组  
 
 
typedef std::vector<unsigned long long> BuffIDArray; //buff ID 数组  
 
enum ENTITY_STATE : unsigned short 
{ 
    ENTITY_STATE_NONE = 0, //无效  
    ENTITY_STATE_FREEZING = 1, //冻结, 不可被攻击,不可主动移动,攻击等  
    ENTITY_STATE_ACTIVE = 2, //活跃状态  
    ENTITY_STATE_LIE = 3, //跪, 不计死亡次数  
    ENTITY_STATE_DIED = 4, //死, 记死亡次数  
}; 
 
enum ENTITY_TYPE : unsigned short 
{ 
    ENTITY_NONE = 0,  
    ENTITY_PLAYER = 1,  
    ENTITY_AI = 2,  
    ENTITY_FLIGHT = 3, //飞行道具  
}; 
 
enum ENTITY_CAMP : unsigned long long 
{ 
    ENTITY_CAMP_NONE = 0,  
    ENTITY_CAMP_RED = 1, //红方  
    ENTITY_CAMP_BLUE = 2, //蓝方  
    ENTITY_CAMP_NEUTRAL = 1000, //[0~ENTITY_CAMP_NEUTRAL)阵营相互敌对, [ENTITY_CAMP_NEUTRAL~)中立温和阵营  
}; 
 
enum MOVE_ACTION : unsigned short 
{ 
    MOVE_ACTION_IDLE = 0, //空闲  
    MOVE_ACTION_FOLLOW = 1, //跟随  
    MOVE_ACTION_PATH = 2, //路径  
    MOVE_ACTION_PASV_PATH = 3, //不可取消, 直线移动一次.  
    MOVE_ACTION_FORCE_PATH = 4, //不可取消&穿越地形, 直线移动一次  
}; 
 
enum SCENE_EVENT : unsigned short 
{ 
    SCENE_EVENT_LIE = 0,  
    SCENE_EVENT_DIED = 1,  
    SCENE_EVENT_FREEZE = 2,  
    SCENE_EVENT_REBIRTH = 3,  
    SCENE_EVENT_HARM_ATTACK = 4,  
    SCENE_EVENT_HARM_HILL = 5,  
    SCENE_EVENT_HARM_MISS = 6,  
    SCENE_EVENT_HARM_CRITICAL = 7,  
}; 
 
struct SceneEventInfo //伤害数据  
{ 
    static const unsigned short getProtoID() { return 2003;} 
    static const std::string getProtoName() { return "SceneEventInfo";} 
    unsigned long long src; //eid  
    unsigned long long dst; //eid  
    unsigned short ev; //事件类型  
    double val; //数值  
    std::string mix; //数值  
    SceneEventInfo() 
    { 
        src = 0; 
        dst = 0; 
        ev = 0; 
        val = 0.0; 
    } 
    SceneEventInfo(const unsigned long long & src, const unsigned long long & dst, const unsigned short & ev, const double & val, const std::string & mix) 
    { 
        this->src = src; 
        this->dst = dst; 
        this->ev = ev; 
        this->val = val; 
        this->mix = mix; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneEventInfo & data) 
{ 
    ws << data.src;  
    ws << data.dst;  
    ws << data.ev;  
    ws << data.val;  
    ws << data.mix;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneEventInfo & data) 
{ 
    rs >> data.src;  
    rs >> data.dst;  
    rs >> data.ev;  
    rs >> data.val;  
    rs >> data.mix;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneEventInfo & info) 
{ 
    stm << "["; 
    stm << "src=" << info.src << ","; 
    stm << "dst=" << info.dst << ","; 
    stm << "ev=" << info.ev << ","; 
    stm << "val=" << info.val << ","; 
    stm << "mix=" << info.mix << ","; 
    stm << "]"; 
    return stm; 
} 
 
 
typedef std::vector<SceneEventInfo> SceneEventInfoArray;  
 
struct EntityState //EntityState  
{ 
    static const unsigned short getProtoID() { return 2004;} 
    static const std::string getProtoName() { return "EntityState";} 
    unsigned long long eid;  
    unsigned long long avatarID;  
    std::string avatarName;  
    unsigned long long modelID;  
    unsigned short camp; //阵营  
    unsigned long long groupID; //组队ID  
    unsigned short etype; //实体类型  
    unsigned short state; //状态  
    unsigned long long foe; //锁定的敌人  
    unsigned long long master; //如果是飞行道具 这个指向施放飞行道具的人  
    double curHP; //当前的血量  
    double maxHP; //当前的血量上限  
    EntityState() 
    { 
        eid = 0; 
        avatarID = 0; 
        modelID = 0; 
        camp = 0; 
        groupID = 0; 
        etype = 0; 
        state = 0; 
        foe = 0; 
        master = 0; 
        curHP = 0.0; 
        maxHP = 0.0; 
    } 
    EntityState(const unsigned long long & eid, const unsigned long long & avatarID, const std::string & avatarName, const unsigned long long & modelID, const unsigned short & camp, const unsigned long long & groupID, const unsigned short & etype, const unsigned short & state, const unsigned long long & foe, const unsigned long long & master, const double & curHP, const double & maxHP) 
    { 
        this->eid = eid; 
        this->avatarID = avatarID; 
        this->avatarName = avatarName; 
        this->modelID = modelID; 
        this->camp = camp; 
        this->groupID = groupID; 
        this->etype = etype; 
        this->state = state; 
        this->foe = foe; 
        this->master = master; 
        this->curHP = curHP; 
        this->maxHP = maxHP; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const EntityState & data) 
{ 
    ws << data.eid;  
    ws << data.avatarID;  
    ws << data.avatarName;  
    ws << data.modelID;  
    ws << data.camp;  
    ws << data.groupID;  
    ws << data.etype;  
    ws << data.state;  
    ws << data.foe;  
    ws << data.master;  
    ws << data.curHP;  
    ws << data.maxHP;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, EntityState & data) 
{ 
    rs >> data.eid;  
    rs >> data.avatarID;  
    rs >> data.avatarName;  
    rs >> data.modelID;  
    rs >> data.camp;  
    rs >> data.groupID;  
    rs >> data.etype;  
    rs >> data.state;  
    rs >> data.foe;  
    rs >> data.master;  
    rs >> data.curHP;  
    rs >> data.maxHP;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const EntityState & info) 
{ 
    stm << "["; 
    stm << "eid=" << info.eid << ","; 
    stm << "avatarID=" << info.avatarID << ","; 
    stm << "avatarName=" << info.avatarName << ","; 
    stm << "modelID=" << info.modelID << ","; 
    stm << "camp=" << info.camp << ","; 
    stm << "groupID=" << info.groupID << ","; 
    stm << "etype=" << info.etype << ","; 
    stm << "state=" << info.state << ","; 
    stm << "foe=" << info.foe << ","; 
    stm << "master=" << info.master << ","; 
    stm << "curHP=" << info.curHP << ","; 
    stm << "maxHP=" << info.maxHP << ","; 
    stm << "]"; 
    return stm; 
} 
 
 
typedef std::vector<EntityState> EntityStateArray;  
 
struct EntityMove //EntityMove  
{ 
    static const unsigned short getProtoID() { return 2005;} 
    static const std::string getProtoName() { return "EntityMove";} 
    unsigned long long eid; //eid  
    EPosition position; //当前坐标  
    unsigned short action; //移动状态  
    double realSpeed; //实时速度  
    double expectSpeed; //期望速度  
    EPositionArray waypoints; //移动路点  
    unsigned long long follow; //eid  
    EntityMove() 
    { 
        eid = 0; 
        action = 0; 
        realSpeed = 0.0; 
        expectSpeed = 0.0; 
        follow = 0; 
    } 
    EntityMove(const unsigned long long & eid, const EPosition & position, const unsigned short & action, const double & realSpeed, const double & expectSpeed, const EPositionArray & waypoints, const unsigned long long & follow) 
    { 
        this->eid = eid; 
        this->position = position; 
        this->action = action; 
        this->realSpeed = realSpeed; 
        this->expectSpeed = expectSpeed; 
        this->waypoints = waypoints; 
        this->follow = follow; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const EntityMove & data) 
{ 
    ws << data.eid;  
    ws << data.position;  
    ws << data.action;  
    ws << data.realSpeed;  
    ws << data.expectSpeed;  
    ws << data.waypoints;  
    ws << data.follow;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, EntityMove & data) 
{ 
    rs >> data.eid;  
    rs >> data.position;  
    rs >> data.action;  
    rs >> data.realSpeed;  
    rs >> data.expectSpeed;  
    rs >> data.waypoints;  
    rs >> data.follow;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const EntityMove & info) 
{ 
    stm << "["; 
    stm << "eid=" << info.eid << ","; 
    stm << "position=" << info.position << ","; 
    stm << "action=" << info.action << ","; 
    stm << "realSpeed=" << info.realSpeed << ","; 
    stm << "expectSpeed=" << info.expectSpeed << ","; 
    stm << "waypoints=" << info.waypoints << ","; 
    stm << "follow=" << info.follow << ","; 
    stm << "]"; 
    return stm; 
} 
 
 
typedef std::vector<EntityMove> EntityMoveArray;  
 
struct EntityReport //EntityReport  
{ 
    static const unsigned short getProtoID() { return 2006;} 
    static const std::string getProtoName() { return "EntityReport";} 
    unsigned long long eid; //eid  
    unsigned long long killOtherCount; //杀死其他玩家次数  
    unsigned long long killOtherTime; //杀死其他玩家的时间  
    unsigned long long diedCount; //死亡次数  
    unsigned long long topMultiKills; //最高连杀次数  
    unsigned long long curMultiKills; //当前连杀次数  
    EntityReport() 
    { 
        eid = 0; 
        killOtherCount = 0; 
        killOtherTime = 0; 
        diedCount = 0; 
        topMultiKills = 0; 
        curMultiKills = 0; 
    } 
    EntityReport(const unsigned long long & eid, const unsigned long long & killOtherCount, const unsigned long long & killOtherTime, const unsigned long long & diedCount, const unsigned long long & topMultiKills, const unsigned long long & curMultiKills) 
    { 
        this->eid = eid; 
        this->killOtherCount = killOtherCount; 
        this->killOtherTime = killOtherTime; 
        this->diedCount = diedCount; 
        this->topMultiKills = topMultiKills; 
        this->curMultiKills = curMultiKills; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const EntityReport & data) 
{ 
    ws << data.eid;  
    ws << data.killOtherCount;  
    ws << data.killOtherTime;  
    ws << data.diedCount;  
    ws << data.topMultiKills;  
    ws << data.curMultiKills;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, EntityReport & data) 
{ 
    rs >> data.eid;  
    rs >> data.killOtherCount;  
    rs >> data.killOtherTime;  
    rs >> data.diedCount;  
    rs >> data.topMultiKills;  
    rs >> data.curMultiKills;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const EntityReport & info) 
{ 
    stm << "["; 
    stm << "eid=" << info.eid << ","; 
    stm << "killOtherCount=" << info.killOtherCount << ","; 
    stm << "killOtherTime=" << info.killOtherTime << ","; 
    stm << "diedCount=" << info.diedCount << ","; 
    stm << "topMultiKills=" << info.topMultiKills << ","; 
    stm << "curMultiKills=" << info.curMultiKills << ","; 
    stm << "]"; 
    return stm; 
} 
 
 
typedef std::vector<EntityReport> EntityReportArray;  
 
struct EntityControl //EntityControl  
{ 
    static const unsigned short getProtoID() { return 2007;} 
    static const std::string getProtoName() { return "EntityControl";} 
    unsigned long long eid;  
    unsigned long long agentNo;  
    double collision;  
    double stateChageTime;  
    EPosition spawnpoint;  
    double blockMoveCount;  
    EntityControl() 
    { 
        eid = 0; 
        agentNo = 0; 
        collision = 0.0; 
        stateChageTime = 0.0; 
        blockMoveCount = 0.0; 
    } 
    EntityControl(const unsigned long long & eid, const unsigned long long & agentNo, const double & collision, const double & stateChageTime, const EPosition & spawnpoint, const double & blockMoveCount) 
    { 
        this->eid = eid; 
        this->agentNo = agentNo; 
        this->collision = collision; 
        this->stateChageTime = stateChageTime; 
        this->spawnpoint = spawnpoint; 
        this->blockMoveCount = blockMoveCount; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const EntityControl & data) 
{ 
    ws << data.eid;  
    ws << data.agentNo;  
    ws << data.collision;  
    ws << data.stateChageTime;  
    ws << data.spawnpoint;  
    ws << data.blockMoveCount;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, EntityControl & data) 
{ 
    rs >> data.eid;  
    rs >> data.agentNo;  
    rs >> data.collision;  
    rs >> data.stateChageTime;  
    rs >> data.spawnpoint;  
    rs >> data.blockMoveCount;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const EntityControl & info) 
{ 
    stm << "["; 
    stm << "eid=" << info.eid << ","; 
    stm << "agentNo=" << info.agentNo << ","; 
    stm << "collision=" << info.collision << ","; 
    stm << "stateChageTime=" << info.stateChageTime << ","; 
    stm << "spawnpoint=" << info.spawnpoint << ","; 
    stm << "blockMoveCount=" << info.blockMoveCount << ","; 
    stm << "]"; 
    return stm; 
} 
 
 
typedef std::vector<EntityControl> EntityControlArray;  
 
struct EntityClientSync //EntityClientSync  
{ 
    static const unsigned short getProtoID() { return 2008;} 
    static const std::string getProtoName() { return "EntityClientSync";} 
    DictProp props; //战斗属性  
    EntityState state;  
    EntityMove mv;  
    EntityReport report;  
    EntityClientSync() 
    { 
    } 
    EntityClientSync(const DictProp & props, const EntityState & state, const EntityMove & mv, const EntityReport & report) 
    { 
        this->props = props; 
        this->state = state; 
        this->mv = mv; 
        this->report = report; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const EntityClientSync & data) 
{ 
    ws << data.props;  
    ws << data.state;  
    ws << data.mv;  
    ws << data.report;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, EntityClientSync & data) 
{ 
    rs >> data.props;  
    rs >> data.state;  
    rs >> data.mv;  
    rs >> data.report;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const EntityClientSync & info) 
{ 
    stm << "["; 
    stm << "props=" << info.props << ","; 
    stm << "state=" << info.state << ","; 
    stm << "mv=" << info.mv << ","; 
    stm << "report=" << info.report << ","; 
    stm << "]"; 
    return stm; 
} 
 
 
typedef std::vector<EntityClientSync> EntityClientSyncArray;  
 
struct SceneSection //场景全景切片数据  
{ 
    static const unsigned short getProtoID() { return 2009;} 
    static const std::string getProtoName() { return "SceneSection";} 
    unsigned long long sceneID;  
    unsigned short sceneType;  
    unsigned short sceneState;  
    double sceneStartTime; //服务器战场开始时间  
    double sceneEndTime; //服务器战场结束时间  
    double serverTime; //服务器当前时间  
    SceneSection() 
    { 
        sceneID = 0; 
        sceneType = 0; 
        sceneState = 0; 
        sceneStartTime = 0.0; 
        sceneEndTime = 0.0; 
        serverTime = 0.0; 
    } 
    SceneSection(const unsigned long long & sceneID, const unsigned short & sceneType, const unsigned short & sceneState, const double & sceneStartTime, const double & sceneEndTime, const double & serverTime) 
    { 
        this->sceneID = sceneID; 
        this->sceneType = sceneType; 
        this->sceneState = sceneState; 
        this->sceneStartTime = sceneStartTime; 
        this->sceneEndTime = sceneEndTime; 
        this->serverTime = serverTime; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneSection & data) 
{ 
    ws << data.sceneID;  
    ws << data.sceneType;  
    ws << data.sceneState;  
    ws << data.sceneStartTime;  
    ws << data.sceneEndTime;  
    ws << data.serverTime;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneSection & data) 
{ 
    rs >> data.sceneID;  
    rs >> data.sceneType;  
    rs >> data.sceneState;  
    rs >> data.sceneStartTime;  
    rs >> data.sceneEndTime;  
    rs >> data.serverTime;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneSection & info) 
{ 
    stm << "["; 
    stm << "sceneID=" << info.sceneID << ","; 
    stm << "sceneType=" << info.sceneType << ","; 
    stm << "sceneState=" << info.sceneState << ","; 
    stm << "sceneStartTime=" << info.sceneStartTime << ","; 
    stm << "sceneEndTime=" << info.sceneEndTime << ","; 
    stm << "serverTime=" << info.serverTime << ","; 
    stm << "]"; 
    return stm; 
} 
 
enum ENTITY_SKILL_STATE : unsigned short 
{ 
    ENTITY_SKILL_NONE = 0, //无效  
    ENTITY_SKILL_PREFIX = 1, //前摇  
    ENTITY_SKILL_ACTIVE = 2, //执行中  
    ENTITY_SKILL_CD = 3, //冷却中  
}; 
 
struct EntitySkillInfo //技能  
{ 
    static const unsigned short getProtoID() { return 2010;} 
    static const std::string getProtoName() { return "EntitySkillInfo";} 
    unsigned long long skillID;  
    EPosition activeDst;  
    unsigned short activeFoeFirst;  
    double lastActiveTime;  
    double lastTriggerTime;  
    unsigned short activeState; //ENTITY_SKILL_STATE  
    double activeCount;  
    DictSkill dict;  
    EntitySkillInfo() 
    { 
        skillID = 0; 
        activeFoeFirst = 0; 
        lastActiveTime = 0.0; 
        lastTriggerTime = 0.0; 
        activeState = 0; 
        activeCount = 0.0; 
    } 
    EntitySkillInfo(const unsigned long long & skillID, const EPosition & activeDst, const unsigned short & activeFoeFirst, const double & lastActiveTime, const double & lastTriggerTime, const unsigned short & activeState, const double & activeCount, const DictSkill & dict) 
    { 
        this->skillID = skillID; 
        this->activeDst = activeDst; 
        this->activeFoeFirst = activeFoeFirst; 
        this->lastActiveTime = lastActiveTime; 
        this->lastTriggerTime = lastTriggerTime; 
        this->activeState = activeState; 
        this->activeCount = activeCount; 
        this->dict = dict; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const EntitySkillInfo & data) 
{ 
    ws << data.skillID;  
    ws << data.activeDst;  
    ws << data.activeFoeFirst;  
    ws << data.lastActiveTime;  
    ws << data.lastTriggerTime;  
    ws << data.activeState;  
    ws << data.activeCount;  
    ws << data.dict;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, EntitySkillInfo & data) 
{ 
    rs >> data.skillID;  
    rs >> data.activeDst;  
    rs >> data.activeFoeFirst;  
    rs >> data.lastActiveTime;  
    rs >> data.lastTriggerTime;  
    rs >> data.activeState;  
    rs >> data.activeCount;  
    rs >> data.dict;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const EntitySkillInfo & info) 
{ 
    stm << "["; 
    stm << "skillID=" << info.skillID << ","; 
    stm << "activeDst=" << info.activeDst << ","; 
    stm << "activeFoeFirst=" << info.activeFoeFirst << ","; 
    stm << "lastActiveTime=" << info.lastActiveTime << ","; 
    stm << "lastTriggerTime=" << info.lastTriggerTime << ","; 
    stm << "activeState=" << info.activeState << ","; 
    stm << "activeCount=" << info.activeCount << ","; 
    stm << "dict=" << info.dict << ","; 
    stm << "]"; 
    return stm; 
} 
 
 
typedef std::map<unsigned long long, EntitySkillInfo> EntitySkillInfoMap; //已装备的SKILL ID, 技能执行数据  
 
 
typedef std::map<unsigned long long, unsigned long long> EntityEquippedSkillMap; //已装备的SKILL ID, value保留  
 
struct EntityBuffInfo //BUFF  
{ 
    static const unsigned short getProtoID() { return 2011;} 
    static const std::string getProtoName() { return "EntityBuffInfo";} 
    unsigned long long buffID;  
    EPosition activeOrg;  
    unsigned long long activeOrgEID;  
    EPosition activeDst;  
    unsigned long long activeDstEID;  
    double lastActiveTime;  
    double lastTriggerTime;  
    double activeCount;  
    DictBuff dict;  
    EntityBuffInfo() 
    { 
        buffID = 0; 
        activeOrgEID = 0; 
        activeDstEID = 0; 
        lastActiveTime = 0.0; 
        lastTriggerTime = 0.0; 
        activeCount = 0.0; 
    } 
    EntityBuffInfo(const unsigned long long & buffID, const EPosition & activeOrg, const unsigned long long & activeOrgEID, const EPosition & activeDst, const unsigned long long & activeDstEID, const double & lastActiveTime, const double & lastTriggerTime, const double & activeCount, const DictBuff & dict) 
    { 
        this->buffID = buffID; 
        this->activeOrg = activeOrg; 
        this->activeOrgEID = activeOrgEID; 
        this->activeDst = activeDst; 
        this->activeDstEID = activeDstEID; 
        this->lastActiveTime = lastActiveTime; 
        this->lastTriggerTime = lastTriggerTime; 
        this->activeCount = activeCount; 
        this->dict = dict; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const EntityBuffInfo & data) 
{ 
    ws << data.buffID;  
    ws << data.activeOrg;  
    ws << data.activeOrgEID;  
    ws << data.activeDst;  
    ws << data.activeDstEID;  
    ws << data.lastActiveTime;  
    ws << data.lastTriggerTime;  
    ws << data.activeCount;  
    ws << data.dict;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, EntityBuffInfo & data) 
{ 
    rs >> data.buffID;  
    rs >> data.activeOrg;  
    rs >> data.activeOrgEID;  
    rs >> data.activeDst;  
    rs >> data.activeDstEID;  
    rs >> data.lastActiveTime;  
    rs >> data.lastTriggerTime;  
    rs >> data.activeCount;  
    rs >> data.dict;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const EntityBuffInfo & info) 
{ 
    stm << "["; 
    stm << "buffID=" << info.buffID << ","; 
    stm << "activeOrg=" << info.activeOrg << ","; 
    stm << "activeOrgEID=" << info.activeOrgEID << ","; 
    stm << "activeDst=" << info.activeDst << ","; 
    stm << "activeDstEID=" << info.activeDstEID << ","; 
    stm << "lastActiveTime=" << info.lastActiveTime << ","; 
    stm << "lastTriggerTime=" << info.lastTriggerTime << ","; 
    stm << "activeCount=" << info.activeCount << ","; 
    stm << "dict=" << info.dict << ","; 
    stm << "]"; 
    return stm; 
} 
 
 
typedef std::map<unsigned long long, EntityBuffInfo> EntityBuffInfoMap; //附加到entity上的buff  
 
struct EntitySkillSystem //EntitySkillSystem  
{ 
    static const unsigned short getProtoID() { return 2012;} 
    static const std::string getProtoName() { return "EntitySkillSystem";} 
    unsigned long long eid;  
    EntitySkillInfoMap activeSkills;  
    EntityBuffInfoMap activeBuffs;  
    EntityEquippedSkillMap dictEquippedSkills;  
    unsigned short combating; //战斗中  
    unsigned long long readySkillID;  
    unsigned long long normalSkillID;  
    double breakoffAttackTime;  
    EntitySkillSystem() 
    { 
        eid = 0; 
        combating = 0; 
        readySkillID = 0; 
        normalSkillID = 0; 
        breakoffAttackTime = 0.0; 
    } 
    EntitySkillSystem(const unsigned long long & eid, const EntitySkillInfoMap & activeSkills, const EntityBuffInfoMap & activeBuffs, const EntityEquippedSkillMap & dictEquippedSkills, const unsigned short & combating, const unsigned long long & readySkillID, const unsigned long long & normalSkillID, const double & breakoffAttackTime) 
    { 
        this->eid = eid; 
        this->activeSkills = activeSkills; 
        this->activeBuffs = activeBuffs; 
        this->dictEquippedSkills = dictEquippedSkills; 
        this->combating = combating; 
        this->readySkillID = readySkillID; 
        this->normalSkillID = normalSkillID; 
        this->breakoffAttackTime = breakoffAttackTime; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const EntitySkillSystem & data) 
{ 
    ws << data.eid;  
    ws << data.activeSkills;  
    ws << data.activeBuffs;  
    ws << data.dictEquippedSkills;  
    ws << data.combating;  
    ws << data.readySkillID;  
    ws << data.normalSkillID;  
    ws << data.breakoffAttackTime;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, EntitySkillSystem & data) 
{ 
    rs >> data.eid;  
    rs >> data.activeSkills;  
    rs >> data.activeBuffs;  
    rs >> data.dictEquippedSkills;  
    rs >> data.combating;  
    rs >> data.readySkillID;  
    rs >> data.normalSkillID;  
    rs >> data.breakoffAttackTime;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const EntitySkillSystem & info) 
{ 
    stm << "["; 
    stm << "eid=" << info.eid << ","; 
    stm << "activeSkills=" << info.activeSkills << ","; 
    stm << "activeBuffs=" << info.activeBuffs << ","; 
    stm << "dictEquippedSkills=" << info.dictEquippedSkills << ","; 
    stm << "combating=" << info.combating << ","; 
    stm << "readySkillID=" << info.readySkillID << ","; 
    stm << "normalSkillID=" << info.normalSkillID << ","; 
    stm << "breakoffAttackTime=" << info.breakoffAttackTime << ","; 
    stm << "]"; 
    return stm; 
} 
 
 
typedef std::vector<EntitySkillSystem> EntitySkillSystemArray;  
 
#endif 

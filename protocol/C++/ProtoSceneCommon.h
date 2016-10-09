 
#ifndef _PROTOSCENECOMMON_H_ 
#define _PROTOSCENECOMMON_H_ 
 
 
enum SceneType : unsigned short 
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
 
enum SceneState : unsigned short 
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
    static const unsigned short getProtoID() { return 10000;} 
    static const std::string getProtoName() { return "SceneGroupAvatarInfo";} 
    unsigned long long areaID; //考虑混服情况,必须指定该玩家来自哪个当前区  
    AvatarBaseInfo baseInfo; //玩家基础数据  
    AvatarPropMap baseProps; //角色属性数据  
    unsigned short powerType; //组队权限: 0普通,1leader,2master  
    std::string token; //scene服务器的口令, 该字段在广播给客户端时需要清空非自己所属的token,否则将会造成token公开.  
    SceneGroupAvatarInfo() 
    { 
        areaID = 0; 
        powerType = 0; 
    } 
    SceneGroupAvatarInfo(const unsigned long long & areaID, const AvatarBaseInfo & baseInfo, const AvatarPropMap & baseProps, const unsigned short & powerType, const std::string & token) 
    { 
        this->areaID = areaID; 
        this->baseInfo = baseInfo; 
        this->baseProps = baseProps; 
        this->powerType = powerType; 
        this->token = token; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneGroupAvatarInfo & data) 
{ 
    ws << data.areaID;  
    ws << data.baseInfo;  
    ws << data.baseProps;  
    ws << data.powerType;  
    ws << data.token;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneGroupAvatarInfo & data) 
{ 
    rs >> data.areaID;  
    rs >> data.baseInfo;  
    rs >> data.baseProps;  
    rs >> data.powerType;  
    rs >> data.token;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneGroupAvatarInfo & info) 
{ 
    stm << "[\n"; 
    stm << "areaID=" << info.areaID << "\n"; 
    stm << "baseInfo=" << info.baseInfo << "\n"; 
    stm << "baseProps=" << info.baseProps << "\n"; 
    stm << "powerType=" << info.powerType << "\n"; 
    stm << "token=" << info.token << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
 
typedef std::vector<SceneGroupAvatarInfo> SceneGroupAvatarInfoArray;  
 
 
typedef std::map<unsigned long long, SceneGroupAvatarInfo> SceneGroupAvatarInfoMap;  
 
struct SceneGroupInfo //编队数据  
{ 
    static const unsigned short getProtoID() { return 10001;} 
    static const std::string getProtoName() { return "SceneGroupInfo";} 
    unsigned long long groupID;  
    unsigned short sceneType; //场景类型  
    unsigned short sceneStatus; //状态  
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
        sceneStatus = 0; 
        mapID = 0; 
        lineID = 0; 
        sceneID = 0; 
        port = 0; 
    } 
    SceneGroupInfo(const unsigned long long & groupID, const unsigned short & sceneType, const unsigned short & sceneStatus, const unsigned long long & mapID, const unsigned long long & lineID, const unsigned long long & sceneID, const std::string & host, const unsigned short & port, const SceneGroupAvatarInfoMap & members, const ServiceIDMap & invitees) 
    { 
        this->groupID = groupID; 
        this->sceneType = sceneType; 
        this->sceneStatus = sceneStatus; 
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
    ws << data.sceneStatus;  
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
    rs >> data.sceneStatus;  
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
    stm << "[\n"; 
    stm << "groupID=" << info.groupID << "\n"; 
    stm << "sceneType=" << info.sceneType << "\n"; 
    stm << "sceneStatus=" << info.sceneStatus << "\n"; 
    stm << "mapID=" << info.mapID << "\n"; 
    stm << "lineID=" << info.lineID << "\n"; 
    stm << "sceneID=" << info.sceneID << "\n"; 
    stm << "host=" << info.host << "\n"; 
    stm << "port=" << info.port << "\n"; 
    stm << "members=" << info.members << "\n"; 
    stm << "invitees=" << info.invitees << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
 
typedef std::vector<SceneGroupInfo> SceneGroupInfoArray;  
 
 
typedef std::map<unsigned long long, SceneGroupInfo> SceneGroupInfoMap;  
 
 
typedef std::vector<unsigned long long> EntityIDArray;  
 
struct EPoint 
{ 
    static const unsigned short getProtoID() { return 10002;} 
    static const std::string getProtoName() { return "EPoint";} 
    double x;  
    double y;  
    EPoint() 
    { 
        x = 0.0; 
        y = 0.0; 
    } 
    EPoint(const double & x, const double & y) 
    { 
        this->x = x; 
        this->y = y; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const EPoint & data) 
{ 
    ws << data.x;  
    ws << data.y;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, EPoint & data) 
{ 
    rs >> data.x;  
    rs >> data.y;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const EPoint & info) 
{ 
    stm << "[\n"; 
    stm << "x=" << info.x << "\n"; 
    stm << "y=" << info.y << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
 
typedef std::vector<EPoint> EPoints;  
 
 
typedef std::vector<unsigned long long> SkillIDArray; //技能ID数组  
 
 
typedef std::vector<unsigned long long> BuffIDArray; //buff ID 数组  
 
enum EntityState : unsigned short 
{ 
    ENTITY_STATE_NONE = 0, //无效  
    ENTITY_STATE_FREEZING = 1, //冻结, 不可被攻击,不可主动移动,攻击等  
    ENTITY_STATE_ACTIVE = 2, //活跃状态  
    ENTITY_STATE_LIE = 3, //跪, 不计死亡次数  
    ENTITY_STATE_DIED = 4, //死, 记死亡次数  
}; 
 
enum EntityType : unsigned short 
{ 
    ENTITY_NONE = 0,  
    ENTITY_AVATAR = 1,  
    ENTITY_AI = 2,  
    ENTITY_FLIGHT = 3, //飞行道具  
}; 
 
enum EntityCampType : unsigned short 
{ 
    ENTITY_CAMP_NONE = 0,  
    ENTITY_CAMP_RED = 1, //红方  
    ENTITY_CAMP_BLUE = 2, //蓝方  
    ENTITY_CAMP_NEUTRAL = 1000, //[0~ENTITY_CAMP_NEUTRAL)阵营相互敌对, [ENTITY_CAMP_NEUTRAL~)中立温和阵营  
}; 
 
enum MoveAction : unsigned short 
{ 
    MOVE_ACTION_IDLE = 0, //空闲  
    MOVE_ACTION_FACE = 1, //朝向  
    MOVE_ACTION_FOLLOW = 2, //跟随  
    MOVE_ACTION_PATH = 3, //路径  
    MOVE_ACTION_PASV_PATH = 4, //不可取消  
    MOVE_ACTION_FORCE_PATH = 5, //不可取消&穿越地形  
}; 
 
enum SearchMethodType : unsigned short 
{ 
    SEARCH_METHOD_DISTANCE = 0, //org 半径,360度扇形的优化  
    SEARCH_METHOD_SEACTOR = 1, //org 扇形  
    SEARCH_METHOD_RECT = 2, //org 矩形  
}; 
 
enum SearchTarget : unsigned long long 
{ 
    SEARCH_TARGET_NONE = 0, //无  
    SEARCH_TARGET_SELF = 1, //自身, 玩家或者AI  
    SEARCH_TARGET_ENEMY = 2, //敌人  
    SEARCH_TARGET_FRIEND = 3, //友方  
    SEARCH_TARGET_NEUTRAL = 4, //中立  
}; 
 
enum SkillType : unsigned long long 
{ 
    SKILL_NONE = 0,  
    SKILL_AUTO = 1, //普攻  
    SKILL_PASSIVE = 2, //被动技能  
    SKILL_CAN_BREAK = 3, //可被中断  
    SKILL_CAN_MOVE = 4, //可移动  
    SKILL_PHYSICAL = 5, //物理攻击  
    SKILL_MAGIC = 6, //魔法攻击  
}; 
 
enum SkillBehaviourType : unsigned long long 
{ 
    SKILL_BEHAVIOUR_NONE = 0,  
    SKILL_BEHAVIOUR_HIT = 1, //攻击  
    SKILL_BEHAVIOUR_TELEPORT_TARGET = 2, //瞬移到目标  
    SKILL_BEHAVIOUR_BREAK_MOVE = 3, //打断移动  
    SKILL_BEHAVIOUR_BREAK_SKILL = 4, //打断技能  
    SKILL_BEHAVIOUR_REMOVE_DEBUFF = 5, //驱散减益BUFF  
    SKILL_BEHAVIOUR_REMOVE_BUFF = 6, //驱散增益BUFF  
    SKILL_BEHAVIOUR_TRIGGER_BUFF = 7, //触发buff  
    SKILL_BEHAVIOUR_TRIGGER_SKILL = 8, //触发技能  
}; 
 
enum BuffType : unsigned long long 
{ 
    BUFF_HALO = 1, //非表达可检索类型: 光环  
    BUFF_BUFF = 2, //非表达可检索类型: 增益buff  
    BUFF_DEBUFF = 3, //非表达可检索类型: 减益BUFF  
    BUFF_HIDE = 4, //非表达可检索类型: 客户端不表现  
    BUFF_SNEAK = 5, //潜行类型: 潜行 不会被非己方阵营的任何AOE技能搜索到  
    BUFF_HOLD_MOVE = 15, //控制: 禁止移动  
    BUFF_REVERSE_MOVE = 16, //控制: 移动反向  
    BUFF_SILENCE_AUTO_ATTACK = 17, //控制: 沉默普攻  
    BUFF_SILENCE_WITHOUT_AUTO_ATTACK = 18, //控制: 沉默非普攻技能  
    BUFF_SILENCE_PHYSICAL = 19, //控制: 沉默物理攻击  
    BUFF_SILENCE_MAGIC = 20, //控制: 沉默魔法攻击  
    BUFF_IMMUNE_MOVE = 25, //免疫: 免疫移动类控制  
    BUFF_IMMUNE_SILENCE = 26, //免疫: 免疫沉默  
    BUFF_IMMUNE_DEBUFF = 27, //免疫: 免疫添加DEBUFF, 指被地方添加不利buff  
    BUFF_IMMUNE_REMOVE_BUFF = 28, //免疫: 免疫驱散BUFF,指被敌方移除有益buff  
    BUFF_IMMUNE_PHYSICAL = 29, //免疫: 物攻免疫  
    BUFF_IMMUNE_MAGIC = 30, //免疫: 法攻免疫  
    BUFF_INC_HARM = 35, //属性加成: 最终扣血加成, value1加法, value2乘法  
    BUFF_INC_DAMAGE = 36, //属性加成: 伤害加成, value1加法, value2乘法  
    BUFF_INC_SPEED = 37, //属性加成: 速度加成, value1加法, value2乘法  
    BUFF_INC_SUCK_BLOOD = 38, //属性加成: 吸血加成 value1加法  
    BUFF_LIGHT_SKILL = 50, //持续性触发: value1为技能ID, value2为间隔, 用于光环类,持续触发类buff实现  
}; 
 
struct SearchInfo 
{ 
    static const unsigned short getProtoID() { return 10003;} 
    static const std::string getProtoName() { return "SearchInfo";} 
    unsigned short searchMethod;  
    unsigned long long searchTarget;  
    double rate; //概率  
    double distance; //伤害距离  
    double radian; //弧度或者宽度  
    double offsetX; //坐标偏移量, 正数为x = x + offset  
    double offsetY; //坐标偏移量, 正数为y = y + offset  
    unsigned long long targetMaxCount; //最大目标数  
    SearchInfo() 
    { 
        searchMethod = 0; 
        searchTarget = 0; 
        rate = 0.0; 
        distance = 0.0; 
        radian = 0.0; 
        offsetX = 0.0; 
        offsetY = 0.0; 
        targetMaxCount = 0; 
    } 
    SearchInfo(const unsigned short & searchMethod, const unsigned long long & searchTarget, const double & rate, const double & distance, const double & radian, const double & offsetX, const double & offsetY, const unsigned long long & targetMaxCount) 
    { 
        this->searchMethod = searchMethod; 
        this->searchTarget = searchTarget; 
        this->rate = rate; 
        this->distance = distance; 
        this->radian = radian; 
        this->offsetX = offsetX; 
        this->offsetY = offsetY; 
        this->targetMaxCount = targetMaxCount; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SearchInfo & data) 
{ 
    ws << data.searchMethod;  
    ws << data.searchTarget;  
    ws << data.rate;  
    ws << data.distance;  
    ws << data.radian;  
    ws << data.offsetX;  
    ws << data.offsetY;  
    ws << data.targetMaxCount;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SearchInfo & data) 
{ 
    rs >> data.searchMethod;  
    rs >> data.searchTarget;  
    rs >> data.rate;  
    rs >> data.distance;  
    rs >> data.radian;  
    rs >> data.offsetX;  
    rs >> data.offsetY;  
    rs >> data.targetMaxCount;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SearchInfo & info) 
{ 
    stm << "[\n"; 
    stm << "searchMethod=" << info.searchMethod << "\n"; 
    stm << "searchTarget=" << info.searchTarget << "\n"; 
    stm << "rate=" << info.rate << "\n"; 
    stm << "distance=" << info.distance << "\n"; 
    stm << "radian=" << info.radian << "\n"; 
    stm << "offsetX=" << info.offsetX << "\n"; 
    stm << "offsetY=" << info.offsetY << "\n"; 
    stm << "targetMaxCount=" << info.targetMaxCount << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct SkillBehaviour //技能触发行为  
{ 
    static const unsigned short getProtoID() { return 10004;} 
    static const std::string getProtoName() { return "SkillBehaviour";} 
    unsigned long long behaviour;  
    double delay;  
    SearchInfo search;  
    SkillIDArray skills;  
    BuffIDArray buffs;  
    SkillBehaviour() 
    { 
        behaviour = 0; 
        delay = 0.0; 
    } 
    SkillBehaviour(const unsigned long long & behaviour, const double & delay, const SearchInfo & search, const SkillIDArray & skills, const BuffIDArray & buffs) 
    { 
        this->behaviour = behaviour; 
        this->delay = delay; 
        this->search = search; 
        this->skills = skills; 
        this->buffs = buffs; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SkillBehaviour & data) 
{ 
    ws << data.behaviour;  
    ws << data.delay;  
    ws << data.search;  
    ws << data.skills;  
    ws << data.buffs;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SkillBehaviour & data) 
{ 
    rs >> data.behaviour;  
    rs >> data.delay;  
    rs >> data.search;  
    rs >> data.skills;  
    rs >> data.buffs;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SkillBehaviour & info) 
{ 
    stm << "[\n"; 
    stm << "behaviour=" << info.behaviour << "\n"; 
    stm << "delay=" << info.delay << "\n"; 
    stm << "search=" << info.search << "\n"; 
    stm << "skills=" << info.skills << "\n"; 
    stm << "buffs=" << info.buffs << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
 
typedef std::vector<SkillBehaviour> SkillBehaviourArray;  
 
struct SkillData //技能  
{ 
    static const unsigned short getProtoID() { return 10005;} 
    static const std::string getProtoName() { return "SkillData";} 
    unsigned long long skillID; //skillID  
    unsigned long long skillType; //SkillType  
    SkillBehaviourArray behaviours;  
    double cd;  
    SkillData() 
    { 
        skillID = 0; 
        skillType = 0; 
        cd = 0.0; 
    } 
    SkillData(const unsigned long long & skillID, const unsigned long long & skillType, const SkillBehaviourArray & behaviours, const double & cd) 
    { 
        this->skillID = skillID; 
        this->skillType = skillType; 
        this->behaviours = behaviours; 
        this->cd = cd; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SkillData & data) 
{ 
    ws << data.skillID;  
    ws << data.skillType;  
    ws << data.behaviours;  
    ws << data.cd;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SkillData & data) 
{ 
    rs >> data.skillID;  
    rs >> data.skillType;  
    rs >> data.behaviours;  
    rs >> data.cd;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SkillData & info) 
{ 
    stm << "[\n"; 
    stm << "skillID=" << info.skillID << "\n"; 
    stm << "skillType=" << info.skillType << "\n"; 
    stm << "behaviours=" << info.behaviours << "\n"; 
    stm << "cd=" << info.cd << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct BuffData //buff  
{ 
    static const unsigned short getProtoID() { return 10006;} 
    static const std::string getProtoName() { return "BuffData";} 
    unsigned long long buffID;  
    unsigned long long buffType; //buff类型  
    double piletime; //最大叠加时间  
    double keepTime; //保持时间  
    double value1;  
    double value2;  
    BuffData() 
    { 
        buffID = 0; 
        buffType = 0; 
        piletime = 0.0; 
        keepTime = 0.0; 
        value1 = 0.0; 
        value2 = 0.0; 
    } 
    BuffData(const unsigned long long & buffID, const unsigned long long & buffType, const double & piletime, const double & keepTime, const double & value1, const double & value2) 
    { 
        this->buffID = buffID; 
        this->buffType = buffType; 
        this->piletime = piletime; 
        this->keepTime = keepTime; 
        this->value1 = value1; 
        this->value2 = value2; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const BuffData & data) 
{ 
    ws << data.buffID;  
    ws << data.buffType;  
    ws << data.piletime;  
    ws << data.keepTime;  
    ws << data.value1;  
    ws << data.value2;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, BuffData & data) 
{ 
    rs >> data.buffID;  
    rs >> data.buffType;  
    rs >> data.piletime;  
    rs >> data.keepTime;  
    rs >> data.value1;  
    rs >> data.value2;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const BuffData & info) 
{ 
    stm << "[\n"; 
    stm << "buffID=" << info.buffID << "\n"; 
    stm << "buffType=" << info.buffType << "\n"; 
    stm << "piletime=" << info.piletime << "\n"; 
    stm << "keepTime=" << info.keepTime << "\n"; 
    stm << "value1=" << info.value1 << "\n"; 
    stm << "value2=" << info.value2 << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
enum HarmType : unsigned short 
{ 
    HARM_GENERAL = 0, //普通伤害  
    HARM_MISS = 1, //闪避  
    HARM_CRITICAL = 2, //暴击  
    HARM_HILL = 3, //治疗  
}; 
 
struct HarmData //伤害数据  
{ 
    static const unsigned short getProtoID() { return 10007;} 
    static const std::string getProtoName() { return "HarmData";} 
    unsigned long long eid; //目标eid  
    unsigned short type; //伤害类型HarmType  
    double harm; //如果为正是伤害, 为负则是回血  
    HarmData() 
    { 
        eid = 0; 
        type = 0; 
        harm = 0.0; 
    } 
    HarmData(const unsigned long long & eid, const unsigned short & type, const double & harm) 
    { 
        this->eid = eid; 
        this->type = type; 
        this->harm = harm; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const HarmData & data) 
{ 
    ws << data.eid;  
    ws << data.type;  
    ws << data.harm;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, HarmData & data) 
{ 
    rs >> data.eid;  
    rs >> data.type;  
    rs >> data.harm;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const HarmData & info) 
{ 
    stm << "[\n"; 
    stm << "eid=" << info.eid << "\n"; 
    stm << "type=" << info.type << "\n"; 
    stm << "harm=" << info.harm << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
 
typedef std::vector<HarmData> HarmDataArray;  
 
struct SkillInfo 
{ 
    static const unsigned short getProtoID() { return 10008;} 
    static const std::string getProtoName() { return "SkillInfo";} 
    unsigned long long skillID;  
    double startTime;  
    double lastHitTime;  
    unsigned long long seq; //hit seq  
    EPoint dst; //目标位置  
    unsigned long long foe; //锁定的目标  
    SkillData data; //配置数据  
    SkillInfo() 
    { 
        skillID = 0; 
        startTime = 0.0; 
        lastHitTime = 0.0; 
        seq = 0; 
        foe = 0; 
    } 
    SkillInfo(const unsigned long long & skillID, const double & startTime, const double & lastHitTime, const unsigned long long & seq, const EPoint & dst, const unsigned long long & foe, const SkillData & data) 
    { 
        this->skillID = skillID; 
        this->startTime = startTime; 
        this->lastHitTime = lastHitTime; 
        this->seq = seq; 
        this->dst = dst; 
        this->foe = foe; 
        this->data = data; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SkillInfo & data) 
{ 
    ws << data.skillID;  
    ws << data.startTime;  
    ws << data.lastHitTime;  
    ws << data.seq;  
    ws << data.dst;  
    ws << data.foe;  
    ws << data.data;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SkillInfo & data) 
{ 
    rs >> data.skillID;  
    rs >> data.startTime;  
    rs >> data.lastHitTime;  
    rs >> data.seq;  
    rs >> data.dst;  
    rs >> data.foe;  
    rs >> data.data;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SkillInfo & info) 
{ 
    stm << "[\n"; 
    stm << "skillID=" << info.skillID << "\n"; 
    stm << "startTime=" << info.startTime << "\n"; 
    stm << "lastHitTime=" << info.lastHitTime << "\n"; 
    stm << "seq=" << info.seq << "\n"; 
    stm << "dst=" << info.dst << "\n"; 
    stm << "foe=" << info.foe << "\n"; 
    stm << "data=" << info.data << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
 
typedef std::vector<SkillInfo> SkillInfoArray;  
 
struct BuffInfo 
{ 
    static const unsigned short getProtoID() { return 10009;} 
    static const std::string getProtoName() { return "BuffInfo";} 
    unsigned long long eid; //施放该buff的entity id  
    unsigned long long skillID; //如果该buff是被技能触发的 则记录该技能, 被动技能是0  
    unsigned long long buffID;  
    double start; //start (server)tick  
    double lastTrigerTick; //lastTrigerTick  
    BuffData data; //配置数据  
    BuffInfo() 
    { 
        eid = 0; 
        skillID = 0; 
        buffID = 0; 
        start = 0.0; 
        lastTrigerTick = 0.0; 
    } 
    BuffInfo(const unsigned long long & eid, const unsigned long long & skillID, const unsigned long long & buffID, const double & start, const double & lastTrigerTick, const BuffData & data) 
    { 
        this->eid = eid; 
        this->skillID = skillID; 
        this->buffID = buffID; 
        this->start = start; 
        this->lastTrigerTick = lastTrigerTick; 
        this->data = data; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const BuffInfo & data) 
{ 
    ws << data.eid;  
    ws << data.skillID;  
    ws << data.buffID;  
    ws << data.start;  
    ws << data.lastTrigerTick;  
    ws << data.data;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, BuffInfo & data) 
{ 
    rs >> data.eid;  
    rs >> data.skillID;  
    rs >> data.buffID;  
    rs >> data.start;  
    rs >> data.lastTrigerTick;  
    rs >> data.data;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const BuffInfo & info) 
{ 
    stm << "[\n"; 
    stm << "eid=" << info.eid << "\n"; 
    stm << "skillID=" << info.skillID << "\n"; 
    stm << "buffID=" << info.buffID << "\n"; 
    stm << "start=" << info.start << "\n"; 
    stm << "lastTrigerTick=" << info.lastTrigerTick << "\n"; 
    stm << "data=" << info.data << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
 
typedef std::vector<BuffInfo> BuffInfoArray;  
 
struct EntityInfo //EntityInfo  
{ 
    static const unsigned short getProtoID() { return 10010;} 
    static const std::string getProtoName() { return "EntityInfo";} 
    unsigned long long eid; //eid  
    unsigned short color; //阵营  
    unsigned long long groupID; //组队ID  
    unsigned short etype; //实体类型  
    unsigned short state; //状态  
    unsigned long long foe; //锁定的敌人  
    unsigned long long leader; //实体的老大, 如果是飞行道具 这个指向施放飞行道具的人  
    double curHP; //当前的血量  
    EntityInfo() 
    { 
        eid = 0; 
        color = 0; 
        groupID = 0; 
        etype = 0; 
        state = 0; 
        foe = 0; 
        leader = 0; 
        curHP = 0.0; 
    } 
    EntityInfo(const unsigned long long & eid, const unsigned short & color, const unsigned long long & groupID, const unsigned short & etype, const unsigned short & state, const unsigned long long & foe, const unsigned long long & leader, const double & curHP) 
    { 
        this->eid = eid; 
        this->color = color; 
        this->groupID = groupID; 
        this->etype = etype; 
        this->state = state; 
        this->foe = foe; 
        this->leader = leader; 
        this->curHP = curHP; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const EntityInfo & data) 
{ 
    ws << data.eid;  
    ws << data.color;  
    ws << data.groupID;  
    ws << data.etype;  
    ws << data.state;  
    ws << data.foe;  
    ws << data.leader;  
    ws << data.curHP;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, EntityInfo & data) 
{ 
    rs >> data.eid;  
    rs >> data.color;  
    rs >> data.groupID;  
    rs >> data.etype;  
    rs >> data.state;  
    rs >> data.foe;  
    rs >> data.leader;  
    rs >> data.curHP;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const EntityInfo & info) 
{ 
    stm << "[\n"; 
    stm << "eid=" << info.eid << "\n"; 
    stm << "color=" << info.color << "\n"; 
    stm << "groupID=" << info.groupID << "\n"; 
    stm << "etype=" << info.etype << "\n"; 
    stm << "state=" << info.state << "\n"; 
    stm << "foe=" << info.foe << "\n"; 
    stm << "leader=" << info.leader << "\n"; 
    stm << "curHP=" << info.curHP << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
 
typedef std::vector<EntityInfo> EntityInfoArray;  
 
struct EntityMove //EntityMove  
{ 
    static const unsigned short getProtoID() { return 10011;} 
    static const std::string getProtoName() { return "EntityMove";} 
    unsigned long long eid; //eid  
    EPoint pos; //当前坐标  
    unsigned short moveAction; //状态  
    EPoints movePath; //当前的移动路径  
    unsigned long long follow; //移动跟随的实体  
    EntityMove() 
    { 
        eid = 0; 
        moveAction = 0; 
        follow = 0; 
    } 
    EntityMove(const unsigned long long & eid, const EPoint & pos, const unsigned short & moveAction, const EPoints & movePath, const unsigned long long & follow) 
    { 
        this->eid = eid; 
        this->pos = pos; 
        this->moveAction = moveAction; 
        this->movePath = movePath; 
        this->follow = follow; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const EntityMove & data) 
{ 
    ws << data.eid;  
    ws << data.pos;  
    ws << data.moveAction;  
    ws << data.movePath;  
    ws << data.follow;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, EntityMove & data) 
{ 
    rs >> data.eid;  
    rs >> data.pos;  
    rs >> data.moveAction;  
    rs >> data.movePath;  
    rs >> data.follow;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const EntityMove & info) 
{ 
    stm << "[\n"; 
    stm << "eid=" << info.eid << "\n"; 
    stm << "pos=" << info.pos << "\n"; 
    stm << "moveAction=" << info.moveAction << "\n"; 
    stm << "movePath=" << info.movePath << "\n"; 
    stm << "follow=" << info.follow << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
 
typedef std::vector<EntityMove> EntityMoveArray;  
 
struct EntityControl //EntityControl  
{ 
    static const unsigned short getProtoID() { return 10012;} 
    static const std::string getProtoName() { return "EntityControl";} 
    unsigned long long eid; //eid  
    unsigned long long agentNo; //agentNo. -1为无效  
    double stateChageTick; //状态改变时间  
    double extSpeed; //扩展速度  
    double extBeginTime; //扩展速度的开始时间  
    double extKeepTime; //扩展速度的保持时间  
    EPoint spawnpoint; //出生点  
    EPoint lastPos; //上一帧实体坐标, 如果是瞬移 则和pos相同  
    SkillInfoArray skills; //技能数据  
    BuffInfoArray buffs; //BUFF数据, 小标ID对应bufftype  
    double diedTime; //实体死亡时间点 -1为永久, 仅飞行道具类有效  
    int hitTimes; //实体碰撞 -1为永久, 仅飞行道具类有效  
    double lastMoveTime; //最后一次移动时间  
    EPoint lastClientPos; //最后一次客户端提交的坐标  
    EntityControl() 
    { 
        eid = 0; 
        agentNo = 0; 
        stateChageTick = 0.0; 
        extSpeed = 0.0; 
        extBeginTime = 0.0; 
        extKeepTime = 0.0; 
        diedTime = 0.0; 
        hitTimes = 0; 
        lastMoveTime = 0.0; 
    } 
    EntityControl(const unsigned long long & eid, const unsigned long long & agentNo, const double & stateChageTick, const double & extSpeed, const double & extBeginTime, const double & extKeepTime, const EPoint & spawnpoint, const EPoint & lastPos, const SkillInfoArray & skills, const BuffInfoArray & buffs, const double & diedTime, const int & hitTimes, const double & lastMoveTime, const EPoint & lastClientPos) 
    { 
        this->eid = eid; 
        this->agentNo = agentNo; 
        this->stateChageTick = stateChageTick; 
        this->extSpeed = extSpeed; 
        this->extBeginTime = extBeginTime; 
        this->extKeepTime = extKeepTime; 
        this->spawnpoint = spawnpoint; 
        this->lastPos = lastPos; 
        this->skills = skills; 
        this->buffs = buffs; 
        this->diedTime = diedTime; 
        this->hitTimes = hitTimes; 
        this->lastMoveTime = lastMoveTime; 
        this->lastClientPos = lastClientPos; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const EntityControl & data) 
{ 
    ws << data.eid;  
    ws << data.agentNo;  
    ws << data.stateChageTick;  
    ws << data.extSpeed;  
    ws << data.extBeginTime;  
    ws << data.extKeepTime;  
    ws << data.spawnpoint;  
    ws << data.lastPos;  
    ws << data.skills;  
    ws << data.buffs;  
    ws << data.diedTime;  
    ws << data.hitTimes;  
    ws << data.lastMoveTime;  
    ws << data.lastClientPos;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, EntityControl & data) 
{ 
    rs >> data.eid;  
    rs >> data.agentNo;  
    rs >> data.stateChageTick;  
    rs >> data.extSpeed;  
    rs >> data.extBeginTime;  
    rs >> data.extKeepTime;  
    rs >> data.spawnpoint;  
    rs >> data.lastPos;  
    rs >> data.skills;  
    rs >> data.buffs;  
    rs >> data.diedTime;  
    rs >> data.hitTimes;  
    rs >> data.lastMoveTime;  
    rs >> data.lastClientPos;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const EntityControl & info) 
{ 
    stm << "[\n"; 
    stm << "eid=" << info.eid << "\n"; 
    stm << "agentNo=" << info.agentNo << "\n"; 
    stm << "stateChageTick=" << info.stateChageTick << "\n"; 
    stm << "extSpeed=" << info.extSpeed << "\n"; 
    stm << "extBeginTime=" << info.extBeginTime << "\n"; 
    stm << "extKeepTime=" << info.extKeepTime << "\n"; 
    stm << "spawnpoint=" << info.spawnpoint << "\n"; 
    stm << "lastPos=" << info.lastPos << "\n"; 
    stm << "skills=" << info.skills << "\n"; 
    stm << "buffs=" << info.buffs << "\n"; 
    stm << "diedTime=" << info.diedTime << "\n"; 
    stm << "hitTimes=" << info.hitTimes << "\n"; 
    stm << "lastMoveTime=" << info.lastMoveTime << "\n"; 
    stm << "lastClientPos=" << info.lastClientPos << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
 
typedef std::vector<EntityControl> EntityControlArray;  
 
struct EntityReport //EntityReport  
{ 
    static const unsigned short getProtoID() { return 10013;} 
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
    stm << "[\n"; 
    stm << "eid=" << info.eid << "\n"; 
    stm << "killOtherCount=" << info.killOtherCount << "\n"; 
    stm << "killOtherTime=" << info.killOtherTime << "\n"; 
    stm << "diedCount=" << info.diedCount << "\n"; 
    stm << "topMultiKills=" << info.topMultiKills << "\n"; 
    stm << "curMultiKills=" << info.curMultiKills << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
 
typedef std::vector<EntityReport> EntityReportArray;  
 
struct EntityFullData //EntityFullData  
{ 
    static const unsigned short getProtoID() { return 10014;} 
    static const std::string getProtoName() { return "EntityFullData";} 
    AvatarBaseInfo baseInfo;  
    AvatarPropMap baseProps;  
    EntityInfo entityInfo;  
    EntityMove entityPoint;  
    EntityReport report;  
    EntityFullData() 
    { 
    } 
    EntityFullData(const AvatarBaseInfo & baseInfo, const AvatarPropMap & baseProps, const EntityInfo & entityInfo, const EntityMove & entityPoint, const EntityReport & report) 
    { 
        this->baseInfo = baseInfo; 
        this->baseProps = baseProps; 
        this->entityInfo = entityInfo; 
        this->entityPoint = entityPoint; 
        this->report = report; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const EntityFullData & data) 
{ 
    ws << data.baseInfo;  
    ws << data.baseProps;  
    ws << data.entityInfo;  
    ws << data.entityPoint;  
    ws << data.report;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, EntityFullData & data) 
{ 
    rs >> data.baseInfo;  
    rs >> data.baseProps;  
    rs >> data.entityInfo;  
    rs >> data.entityPoint;  
    rs >> data.report;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const EntityFullData & info) 
{ 
    stm << "[\n"; 
    stm << "baseInfo=" << info.baseInfo << "\n"; 
    stm << "baseProps=" << info.baseProps << "\n"; 
    stm << "entityInfo=" << info.entityInfo << "\n"; 
    stm << "entityPoint=" << info.entityPoint << "\n"; 
    stm << "report=" << info.report << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
 
typedef std::vector<EntityFullData> EntityFullDataArray;  
 
struct SceneSection //场景全景切片数据  
{ 
    static const unsigned short getProtoID() { return 10015;} 
    static const std::string getProtoName() { return "SceneSection";} 
    unsigned long long sceneID;  
    unsigned short sceneType;  
    unsigned short sceneStatus;  
    double sceneStartTime; //服务器战场开始时间  
    double sceneEndTime; //服务器战场结束时间  
    double serverTime; //服务器当前时间  
    EntityFullDataArray entitys; //这里包含有所有当前场景下的实体属性和状态数据  
    SceneSection() 
    { 
        sceneID = 0; 
        sceneType = 0; 
        sceneStatus = 0; 
        sceneStartTime = 0.0; 
        sceneEndTime = 0.0; 
        serverTime = 0.0; 
    } 
    SceneSection(const unsigned long long & sceneID, const unsigned short & sceneType, const unsigned short & sceneStatus, const double & sceneStartTime, const double & sceneEndTime, const double & serverTime, const EntityFullDataArray & entitys) 
    { 
        this->sceneID = sceneID; 
        this->sceneType = sceneType; 
        this->sceneStatus = sceneStatus; 
        this->sceneStartTime = sceneStartTime; 
        this->sceneEndTime = sceneEndTime; 
        this->serverTime = serverTime; 
        this->entitys = entitys; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneSection & data) 
{ 
    ws << data.sceneID;  
    ws << data.sceneType;  
    ws << data.sceneStatus;  
    ws << data.sceneStartTime;  
    ws << data.sceneEndTime;  
    ws << data.serverTime;  
    ws << data.entitys;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneSection & data) 
{ 
    rs >> data.sceneID;  
    rs >> data.sceneType;  
    rs >> data.sceneStatus;  
    rs >> data.sceneStartTime;  
    rs >> data.sceneEndTime;  
    rs >> data.serverTime;  
    rs >> data.entitys;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneSection & info) 
{ 
    stm << "[\n"; 
    stm << "sceneID=" << info.sceneID << "\n"; 
    stm << "sceneType=" << info.sceneType << "\n"; 
    stm << "sceneStatus=" << info.sceneStatus << "\n"; 
    stm << "sceneStartTime=" << info.sceneStartTime << "\n"; 
    stm << "sceneEndTime=" << info.sceneEndTime << "\n"; 
    stm << "serverTime=" << info.serverTime << "\n"; 
    stm << "entitys=" << info.entitys << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
#endif 

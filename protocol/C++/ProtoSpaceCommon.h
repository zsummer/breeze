 
#ifndef _PROTOSPACECOMMON_H_ 
#define _PROTOSPACECOMMON_H_ 
 
 
 
typedef std::vector<unsigned int> EntityIDArray;  
 
struct EPoint 
{ 
    static const unsigned short getProtoID() { return 10018;} 
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
 
 
typedef std::vector<unsigned int> SkillIDArray; //技能ID数组  
 
 
typedef std::vector<unsigned int> BuffIDArray; //buff ID 数组  
 
enum SCENE_TYPE : unsigned short 
{ 
    SCENE_TYPE_NONE = 0, //无效  
    SCENE_TYPE_HOME = 1, //主城  
    SCENE_TYPE_SOME_INSTANCING = 2, //一些副本  
    SCENE_TYPE_ARENA = 3, //竞技场  
    SCENE_TYPE_GUILD = 4, //公会  
}; 
 
enum SCENE_STATUS : unsigned short 
{ 
    SCENE_STATUS_NONE = 0, //不存在  
    SCENE_STATUS_MATCHING = 1, //正在匹配  
    SCENE_STATUS_CHOISE = 2, //匹配成功,选择英雄  
    SCENE_STATUS_WAITING = 3, //匹配成功,等待玩家进入  
    SCENE_STATUS_INSTANCING = 4, //场景中  
}; 
 
struct SceneInfo //场景信息  
{ 
    static const unsigned short getProtoID() { return 10000;} 
    static const std::string getProtoName() { return "SceneInfo";} 
    unsigned short sceneType; //类型  
    unsigned short spaceStatus; //状态  
    std::string host; //服务器host  
    unsigned short port; //服务器port  
    unsigned int spaceID; //空间(场景,房间,战场,INSTANCING ID)的实例ID  
    std::string token; //令牌  
    unsigned char isActive; //当前活跃场景, 用于场景切换过渡,或者同时多个场景存在的情况  
    UserBaseInfoArray involeds; //匹配列表中的玩家  
    SceneInfo() 
    { 
        sceneType = 0; 
        spaceStatus = 0; 
        port = 0; 
        spaceID = 0; 
        isActive = 0; 
    } 
    SceneInfo(const unsigned short & sceneType, const unsigned short & spaceStatus, const std::string & host, const unsigned short & port, const unsigned int & spaceID, const std::string & token, const unsigned char & isActive, const UserBaseInfoArray & involeds) 
    { 
        this->sceneType = sceneType; 
        this->spaceStatus = spaceStatus; 
        this->host = host; 
        this->port = port; 
        this->spaceID = spaceID; 
        this->token = token; 
        this->isActive = isActive; 
        this->involeds = involeds; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneInfo & data) 
{ 
    ws << data.sceneType;  
    ws << data.spaceStatus;  
    ws << data.host;  
    ws << data.port;  
    ws << data.spaceID;  
    ws << data.token;  
    ws << data.isActive;  
    ws << data.involeds;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneInfo & data) 
{ 
    rs >> data.sceneType;  
    rs >> data.spaceStatus;  
    rs >> data.host;  
    rs >> data.port;  
    rs >> data.spaceID;  
    rs >> data.token;  
    rs >> data.isActive;  
    rs >> data.involeds;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneInfo & info) 
{ 
    stm << "[\n"; 
    stm << "sceneType=" << info.sceneType << "\n"; 
    stm << "spaceStatus=" << info.spaceStatus << "\n"; 
    stm << "host=" << info.host << "\n"; 
    stm << "port=" << info.port << "\n"; 
    stm << "spaceID=" << info.spaceID << "\n"; 
    stm << "token=" << info.token << "\n"; 
    stm << "isActive=" << info.isActive << "\n"; 
    stm << "involeds=" << info.involeds << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
 
typedef std::vector<SceneInfo> SceneInfoArray;  
 
enum SPACE_STATUS : unsigned short 
{ 
    SPACE_STATUS_NONE = 0, //不存在  
    SPACE_STATUS_WAIT = 1, //等待  
    SCENE_STATUS_ACTIVE = 2, //活跃  
    SCENE_STATUS_LINGER = 3, //驻留  
}; 
 
struct SpaceInfo //空间信息  
{ 
    static const unsigned short getProtoID() { return 10017;} 
    static const std::string getProtoName() { return "SpaceInfo";} 
    unsigned int spaceID;  
    unsigned short sceneType; //类型  
    unsigned short spaceStatus; //状态  
    unsigned int users; //目前负载  
    SpaceInfo() 
    { 
        spaceID = 0; 
        sceneType = 0; 
        spaceStatus = 0; 
        users = 0; 
    } 
    SpaceInfo(const unsigned int & spaceID, const unsigned short & sceneType, const unsigned short & spaceStatus, const unsigned int & users) 
    { 
        this->spaceID = spaceID; 
        this->sceneType = sceneType; 
        this->spaceStatus = spaceStatus; 
        this->users = users; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SpaceInfo & data) 
{ 
    ws << data.spaceID;  
    ws << data.sceneType;  
    ws << data.spaceStatus;  
    ws << data.users;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SpaceInfo & data) 
{ 
    rs >> data.spaceID;  
    rs >> data.sceneType;  
    rs >> data.spaceStatus;  
    rs >> data.users;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SpaceInfo & info) 
{ 
    stm << "[\n"; 
    stm << "spaceID=" << info.spaceID << "\n"; 
    stm << "sceneType=" << info.sceneType << "\n"; 
    stm << "spaceStatus=" << info.spaceStatus << "\n"; 
    stm << "users=" << info.users << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
 
typedef std::vector<SpaceInfo> SpaceInfoArray;  
 
enum ENTITY_STATE : unsigned short 
{ 
    ESTATE_NONE = 0, //无效  
    ESTATE_FREEZING = 1, //冻结, 不可被攻击,不可主动移动,攻击等  
    ESTATE_ACTIVE = 2, //活跃状态  
    ESTATE_LIE = 3, //跪, 不计死亡次数  
    ESTATE_DIED = 4, //死, 记死亡次数  
}; 
 
enum ENTITY_TYPE : unsigned short 
{ 
    ETYPE_NONE = 0,  
    ETYPE_AVATAR = 1,  
    ETYPE_AI = 2,  
    ETYPE_FLIGHT = 3, //飞行道具  
}; 
 
enum ENTITY_COLOR : unsigned short 
{ 
    ECOLOR_NONE = 0,  
    ECOLOR_RED = 1, //红方  
    ECOLOR_BLUE = 2, //蓝方  
    ECOLOR_NEUTRAL = 1000, //[0~ECOLOR_NEUTRAL)阵营相互敌对, [ECOLOR_NEUTRAL~)中立温和阵营  
}; 
 
enum MoveAction : unsigned short 
{ 
    MACTION_IDLE = 0, //空闲  
    MACTION_FACE = 1, //朝向  
    MACTION_FOLLOW = 2, //跟随  
    MACTION_PATH = 3, //路径  
}; 
 
enum SEARCH_METHOD : unsigned short 
{ 
    SEARCH_METHOD_DISTANCE = 0, //org 半径,360度扇形的优化  
    SEARCH_METHOD_SEACTOR = 1, //org 扇形  
    SEARCH_METHOD_RECT = 2, //org 矩形  
}; 
 
enum SEARCH_TARGET : unsigned long long 
{ 
    SEARCH_TARGET_NONE = 0, //无  
    SEARCH_TARGET_SELF = 1, //自身, 玩家或者AI  
    SEARCH_TARGET_ENEMY = 2, //敌人  
    SEARCH_TARGET_FRIEND = 3, //友方  
    SEARCH_TARGET_NEUTRAL = 4, //中立  
}; 
 
enum SKILL_TYPE : unsigned long long 
{ 
    SKILL_NONE = 0,  
    SKILL_AUTO = 1, //普攻  
    SKILL_PASSIVE = 2, //被动技能  
    SKILL_CAN_BREAK = 3, //可被中断  
    SKILL_CAN_MOVE = 4, //可移动  
    SKILL_PHYSICAL = 5, //物理攻击  
    SKILL_MAGIC = 6, //魔法攻击  
}; 
 
enum SKILL_BEHAVIOUR : unsigned long long 
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
 
enum BUFF_TYPE : unsigned long long 
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
    static const unsigned short getProtoID() { return 10015;} 
    static const std::string getProtoName() { return "SearchInfo";} 
    unsigned short searchMethod;  
    unsigned long long searchTarget;  
    double rate; //概率  
    double distance; //伤害距离  
    double radian; //弧度或者宽度  
    double offsetX; //坐标偏移量, 正数为x = x + offset  
    double offsetY; //坐标偏移量, 正数为y = y + offset  
    unsigned int targetMaxCount; //最大目标数  
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
    SearchInfo(const unsigned short & searchMethod, const unsigned long long & searchTarget, const double & rate, const double & distance, const double & radian, const double & offsetX, const double & offsetY, const unsigned int & targetMaxCount) 
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
    static const unsigned short getProtoID() { return 10016;} 
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
    static const unsigned short getProtoID() { return 10004;} 
    static const std::string getProtoName() { return "SkillData";} 
    unsigned int skillID; //skillID  
    unsigned long long skillType; //SKILL_TYPE  
    SkillBehaviourArray behaviours;  
    double cd;  
    SkillData() 
    { 
        skillID = 0; 
        skillType = 0; 
        cd = 0.0; 
    } 
    SkillData(const unsigned int & skillID, const unsigned long long & skillType, const SkillBehaviourArray & behaviours, const double & cd) 
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
    static const unsigned short getProtoID() { return 10005;} 
    static const std::string getProtoName() { return "BuffData";} 
    unsigned int buffID;  
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
    BuffData(const unsigned int & buffID, const unsigned long long & buffType, const double & piletime, const double & keepTime, const double & value1, const double & value2) 
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
 
enum HARM_TYPE : unsigned short 
{ 
    HARM_TYPE_GENERAL = 0, //普通伤害  
    HARM_TYPE_MISS = 1, //闪避  
    HARM_TYPE_CRITICAL = 2, //暴击  
    HARM_TYPE_HILL = 3, //治疗  
}; 
 
struct HarmData //伤害数据  
{ 
    static const unsigned short getProtoID() { return 10006;} 
    static const std::string getProtoName() { return "HarmData";} 
    unsigned int eid; //目标eid  
    unsigned short type; //伤害类型HARM_TYPE  
    double harm; //如果为正是伤害, 为负则是回血  
    HarmData() 
    { 
        eid = 0; 
        type = 0; 
        harm = 0.0; 
    } 
    HarmData(const unsigned int & eid, const unsigned short & type, const double & harm) 
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
    static const unsigned short getProtoID() { return 10007;} 
    static const std::string getProtoName() { return "SkillInfo";} 
    unsigned int skillID;  
    double startTime;  
    double lastHitTime;  
    unsigned int seq; //hit seq  
    EPoint dst; //目标位置  
    unsigned int foe; //锁定的目标  
    SkillData data; //配置数据  
    SkillInfo() 
    { 
        skillID = 0; 
        startTime = 0.0; 
        lastHitTime = 0.0; 
        seq = 0; 
        foe = 0; 
    } 
    SkillInfo(const unsigned int & skillID, const double & startTime, const double & lastHitTime, const unsigned int & seq, const EPoint & dst, const unsigned int & foe, const SkillData & data) 
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
    static const unsigned short getProtoID() { return 10008;} 
    static const std::string getProtoName() { return "BuffInfo";} 
    unsigned int eid; //施放该buff的entity id  
    unsigned int skillID; //如果该buff是被技能触发的 则记录该技能, 被动技能是0  
    unsigned int buffID;  
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
    BuffInfo(const unsigned int & eid, const unsigned int & skillID, const unsigned int & buffID, const double & start, const double & lastTrigerTick, const BuffData & data) 
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
    static const unsigned short getProtoID() { return 10011;} 
    static const std::string getProtoName() { return "EntityInfo";} 
    unsigned int eid; //eid  
    unsigned short color; //阵营  
    unsigned short state; //状态  
    EPoint pos; //当前坐标  
    unsigned short moveAction; //状态  
    EPoints movePath; //当前的移动路径  
    unsigned int foe; //锁定的敌人  
    unsigned int leader; //实体的老大, 如果是飞行道具 这个指向施放飞行道具的人  
    unsigned int follow; //移动跟随的实体  
    double curHP; //当前的血量  
    EntityInfo() 
    { 
        eid = 0; 
        color = 0; 
        state = 0; 
        moveAction = 0; 
        foe = 0; 
        leader = 0; 
        follow = 0; 
        curHP = 0.0; 
    } 
    EntityInfo(const unsigned int & eid, const unsigned short & color, const unsigned short & state, const EPoint & pos, const unsigned short & moveAction, const EPoints & movePath, const unsigned int & foe, const unsigned int & leader, const unsigned int & follow, const double & curHP) 
    { 
        this->eid = eid; 
        this->color = color; 
        this->state = state; 
        this->pos = pos; 
        this->moveAction = moveAction; 
        this->movePath = movePath; 
        this->foe = foe; 
        this->leader = leader; 
        this->follow = follow; 
        this->curHP = curHP; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const EntityInfo & data) 
{ 
    ws << data.eid;  
    ws << data.color;  
    ws << data.state;  
    ws << data.pos;  
    ws << data.moveAction;  
    ws << data.movePath;  
    ws << data.foe;  
    ws << data.leader;  
    ws << data.follow;  
    ws << data.curHP;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, EntityInfo & data) 
{ 
    rs >> data.eid;  
    rs >> data.color;  
    rs >> data.state;  
    rs >> data.pos;  
    rs >> data.moveAction;  
    rs >> data.movePath;  
    rs >> data.foe;  
    rs >> data.leader;  
    rs >> data.follow;  
    rs >> data.curHP;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const EntityInfo & info) 
{ 
    stm << "[\n"; 
    stm << "eid=" << info.eid << "\n"; 
    stm << "color=" << info.color << "\n"; 
    stm << "state=" << info.state << "\n"; 
    stm << "pos=" << info.pos << "\n"; 
    stm << "moveAction=" << info.moveAction << "\n"; 
    stm << "movePath=" << info.movePath << "\n"; 
    stm << "foe=" << info.foe << "\n"; 
    stm << "leader=" << info.leader << "\n"; 
    stm << "follow=" << info.follow << "\n"; 
    stm << "curHP=" << info.curHP << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
 
typedef std::vector<EntityInfo> EntityInfoArray;  
 
struct EntityControl //EntityControl  
{ 
    static const unsigned short getProtoID() { return 10012;} 
    static const std::string getProtoName() { return "EntityControl";} 
    unsigned int eid; //eid  
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
        stateChageTick = 0.0; 
        extSpeed = 0.0; 
        extBeginTime = 0.0; 
        extKeepTime = 0.0; 
        diedTime = 0.0; 
        hitTimes = 0; 
        lastMoveTime = 0.0; 
    } 
    EntityControl(const unsigned int & eid, const double & stateChageTick, const double & extSpeed, const double & extBeginTime, const double & extKeepTime, const EPoint & spawnpoint, const EPoint & lastPos, const SkillInfoArray & skills, const BuffInfoArray & buffs, const double & diedTime, const int & hitTimes, const double & lastMoveTime, const EPoint & lastClientPos) 
    { 
        this->eid = eid; 
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
    unsigned int eid; //eid  
    unsigned int killOtherCount; //杀死其他玩家次数  
    unsigned int killOtherTime; //杀死其他玩家的时间  
    unsigned int diedCount; //死亡次数  
    unsigned int topMultiKills; //最高连杀次数  
    unsigned int curMultiKills; //当前连杀次数  
    EntityReport() 
    { 
        eid = 0; 
        killOtherCount = 0; 
        killOtherTime = 0; 
        diedCount = 0; 
        topMultiKills = 0; 
        curMultiKills = 0; 
    } 
    EntityReport(const unsigned int & eid, const unsigned int & killOtherCount, const unsigned int & killOtherTime, const unsigned int & diedCount, const unsigned int & topMultiKills, const unsigned int & curMultiKills) 
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
 
struct EntityFullInfo //EntityFullInfo  
{ 
    static const unsigned short getProtoID() { return 10014;} 
    static const std::string getProtoName() { return "EntityFullInfo";} 
    UserBaseInfo base;  
    EntityInfo info;  
    EntityReport report;  
    EntityFullInfo() 
    { 
    } 
    EntityFullInfo(const UserBaseInfo & base, const EntityInfo & info, const EntityReport & report) 
    { 
        this->base = base; 
        this->info = info; 
        this->report = report; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const EntityFullInfo & data) 
{ 
    ws << data.base;  
    ws << data.info;  
    ws << data.report;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, EntityFullInfo & data) 
{ 
    rs >> data.base;  
    rs >> data.info;  
    rs >> data.report;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const EntityFullInfo & info) 
{ 
    stm << "[\n"; 
    stm << "base=" << info.base << "\n"; 
    stm << "info=" << info.info << "\n"; 
    stm << "report=" << info.report << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
 
typedef std::vector<EntityFullInfo> EntityFullInfoArray;  
 
#endif 

 
#ifndef _PROTOSPACECOMMON_H_ 
#define _PROTOSPACECOMMON_H_ 
 
 
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
    SCENE_STATUS_WAITING = 2, //匹配成功,等待玩家进入  
    SCENE_STATUS_INSTANCING = 3, //场景中  
}; 
 
struct SceneInfo //场景信息  
{ 
    static const unsigned short getProtoID() { return 10000;} 
    static const std::string getProtoName() { return "SceneInfo";} 
    unsigned short type; //类型  
    unsigned short status; //状态  
    std::string host; //服务器host  
    unsigned short port; //服务器port  
    unsigned int spaceID; //空间(场景,房间,战场,INSTANCING ID)的实例ID  
    SessionToken token; //令牌  
    unsigned char isActive; //当前活跃场景, 用于场景切换过渡,或者同时多个场景存在的情况  
    SceneInfo() 
    { 
        type = 0; 
        status = 0; 
        port = 0; 
        spaceID = 0; 
        isActive = 0; 
    } 
    SceneInfo(const unsigned short & type, const unsigned short & status, const std::string & host, const unsigned short & port, const unsigned int & spaceID, const SessionToken & token, const unsigned char & isActive) 
    { 
        this->type = type; 
        this->status = status; 
        this->host = host; 
        this->port = port; 
        this->spaceID = spaceID; 
        this->token = token; 
        this->isActive = isActive; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneInfo & data) 
{ 
    ws << data.type;  
    ws << data.status;  
    ws << data.host;  
    ws << data.port;  
    ws << data.spaceID;  
    ws << data.token;  
    ws << data.isActive;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneInfo & data) 
{ 
    rs >> data.type;  
    rs >> data.status;  
    rs >> data.host;  
    rs >> data.port;  
    rs >> data.spaceID;  
    rs >> data.token;  
    rs >> data.isActive;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneInfo & info) 
{ 
    stm << "[\n"; 
    stm << "type=" << info.type << "\n"; 
    stm << "status=" << info.status << "\n"; 
    stm << "host=" << info.host << "\n"; 
    stm << "port=" << info.port << "\n"; 
    stm << "spaceID=" << info.spaceID << "\n"; 
    stm << "token=" << info.token << "\n"; 
    stm << "isActive=" << info.isActive << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
 
typedef std::vector<SceneInfo> SceneInfoArray;  
 
enum ENTITY_STATE : unsigned short 
{ 
    ESTATE_FREEZING = 0, //冻结, 不能移动,不能操作, 100%免伤  
    ESTATE_ACTIVE = 1, //活跃状态  
    ESTATE_PRE_DIED = 2, //进入死亡流程  
    ESTATE_DIED = 3, //死亡状态  
}; 
 
enum ENTITY_TYPE : unsigned short 
{ 
    ETYPE_INVALID = 0,  
    ETYPE_AVATAR = 1,  
    ETYPE_AI = 2,  
    ETYPE_FLIGHT = 3, //飞行道具  
}; 
 
enum ENTITY_COLOR : unsigned short 
{ 
    ECOLOR_INVALID = 0, //红方  
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
 
enum SEARCH_TYPE : unsigned short 
{ 
    SEARCH_DISTANCE = 1, //org 半径  
    SEARCH_SEACTOR = 2, //org 扇形  
    SEARCH_RECT = 3, //org 矩形  
}; 
 
enum SEARCH_TARGET_TYPE : unsigned int 
{ 
    SEARCH_TARGET_SELF = 1, //自身, 玩家或者AI  
    SEARCH_TARGET_AVATAR = 2, //施法者, 玩家或者AI  
    SEARCH_TARGET_AI = 3, //施法者, 玩家或者AI  
    SEARCH_TARGET_BARRIER = 4, //障碍  
    SEARCH_TARGET_FLIGHT = 5, //飞行道具  
    SEARCH_TARGET_ENEMY = 6, //敌人  
    SEARCH_TARGET_FRIEND = 7, //全体友方  
    SEARCH_TARGET_NEUTRAL = 8, //中立  
}; 
 
enum SKILL_TYPE : unsigned long long 
{ 
    SKILL_NORMAL_ATTACK = 1, //普通攻击  
    SKILL_AUTO = 2, //被动技能  
    SKILL_CAN_BREAK = 3, //可被中断  
    SKILL_CAN_MOVE = 4, //可移动  
    SKILL_PHYSICAL = 5, //物理攻击  
    SKILL_MAGIC = 6, //魔法攻击  
    SKILL_HARM = 7, //进行伤害计算  
    SKILL_BREAK_SELF_MOVE = 8, //打断自己移动  
    SKILL_BREAK_SELF_SKILL = 9, //打断自己的技能  
    SKILL_BREAK_TARGET_MOVE = 10, //打断目标移动  
    SKILL_BREAK_TARGET_SKILL = 11, //打断目标技能  
    SKILL_BREAK_TARGET_DEBUFF = 12, //驱散目标减益BUFF  
    SKILL_BREAK_TARGET_BUFF = 13, //驱散目标增益BUFF  
}; 
 
enum BUFF_TYPE : unsigned long long 
{ 
    BUFF_HALO = 1, //组合类型: 光环  
    BUFF_BUFF = 2, //组合类型: 增益buff  
    BUFF_DEBUFF = 3, //组合类型: 减益BUFF  
    BUFF_HIDE = 4, //组合类型: 客户端不表现  
    BUFF_SNEAK = 5, //组合类型: 潜行 不会被非己方阵营的任何AOE技能搜索到  
    BUFF_HOLD_MOVE = 15, //控制: 禁止移动  
    BUFF_REVERSE_MOVE = 16, //控制: 移动反向  
    BUFF_SILENCE = 17, //控制: 沉默所有技能  
    BUFF_SILENCE_WITHOUT_NORMAL = 18, //控制: 沉默非普通攻击  
    BUFF_SILENCE_PHYSICAL = 19, //控制: 沉默物理攻击  
    BUFF_SILENCE_MAGIC = 20, //控制: 沉默魔法攻击  
    BUFF_IMMUNE_MOVE = 25, //免疫: 免疫被控 移动禁止  
    BUFF_IMMUNE_SILENCE = 26, //免疫: 免疫沉默  
    BUFF_IMMUNE_DEBUFF = 27, //免疫: 免疫DEBUFF  
    BUFF_IMMUNE_PHYSICAL = 28, //免疫: 物攻免疫  
    BUFF_IMMUNE_MAGIC = 29, //免疫: 法攻免疫  
    BUFF_IMMUNE_BREAK = 30, //免疫: 不可被技能驱散  
    BUFF_INC_DAMAGE = 35, //属性加成: 加增伤率 万分比(除以10000)  value1为基础概率, value2为成长概率   
    BUFF_SUB_DAMAGE = 36, //属性加成: 减伤率 万分比(除以10000)  value1为基础概率, value2为成长概率   
    BUFF_INC_SPEED = 41, //属性加成: 加速度  万分比(除以10000) value1为固定速度加成, value2为概率加成  
    BUFF_INC_SUCK_BLOOD = 42, //属性加成: 吸血率 万分比(除以10000)  value1为基础概率, value2为成长概率   
    BUFF_LIGHT_LIFE = 50, //持续性触发: 治疗(生命), 点燃(生命)   value1为每秒固定值, value2为每秒恢复/扣除相对于自己最大血量的万分比(除以10000)  
    BUFF_LIGHT_RUNSKILL = 51, //持续性触发: 触发一个技能,  光环BUFF,   配置:value填写要触发的技能ID, value1为间隔时间  
}; 
 
 
typedef std::vector<unsigned int> SkillIDArray; //技能ID数组  
 
 
typedef std::vector<unsigned int> BuffIDArray; //buff ID 数组  
 
struct TargetSearch 
{ 
    static const unsigned short getProtoID() { return 10001;} 
    static const std::string getProtoName() { return "TargetSearch";} 
    unsigned short searchType;  
    unsigned long long targetType;  
    float distance; //伤害距离  
    float radian; //弧度或者宽度  
    float offsetX; //坐标偏移量  
    float offsetY; //坐标偏移量  
    unsigned int targetMaxCount; //最大目标数  
    TargetSearch() 
    { 
        searchType = 0; 
        targetType = 0; 
        distance = 0.0; 
        radian = 0.0; 
        offsetX = 0.0; 
        offsetY = 0.0; 
        targetMaxCount = 0; 
    } 
    TargetSearch(const unsigned short & searchType, const unsigned long long & targetType, const float & distance, const float & radian, const float & offsetX, const float & offsetY, const unsigned int & targetMaxCount) 
    { 
        this->searchType = searchType; 
        this->targetType = targetType; 
        this->distance = distance; 
        this->radian = radian; 
        this->offsetX = offsetX; 
        this->offsetY = offsetY; 
        this->targetMaxCount = targetMaxCount; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const TargetSearch & data) 
{ 
    ws << data.searchType;  
    ws << data.targetType;  
    ws << data.distance;  
    ws << data.radian;  
    ws << data.offsetX;  
    ws << data.offsetY;  
    ws << data.targetMaxCount;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, TargetSearch & data) 
{ 
    rs >> data.searchType;  
    rs >> data.targetType;  
    rs >> data.distance;  
    rs >> data.radian;  
    rs >> data.offsetX;  
    rs >> data.offsetY;  
    rs >> data.targetMaxCount;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const TargetSearch & info) 
{ 
    stm << "[\n"; 
    stm << "searchType=" << info.searchType << "\n"; 
    stm << "targetType=" << info.targetType << "\n"; 
    stm << "distance=" << info.distance << "\n"; 
    stm << "radian=" << info.radian << "\n"; 
    stm << "offsetX=" << info.offsetX << "\n"; 
    stm << "offsetY=" << info.offsetY << "\n"; 
    stm << "targetMaxCount=" << info.targetMaxCount << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct TargetAddSkillBuff //目标上技能和buff  
{ 
    static const unsigned short getProtoID() { return 10002;} 
    static const std::string getProtoName() { return "TargetAddSkillBuff";} 
    TargetSearch search;  
    SkillIDArray skills;  
    BuffIDArray buffs;  
    TargetAddSkillBuff() 
    { 
    } 
    TargetAddSkillBuff(const TargetSearch & search, const SkillIDArray & skills, const BuffIDArray & buffs) 
    { 
        this->search = search; 
        this->skills = skills; 
        this->buffs = buffs; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const TargetAddSkillBuff & data) 
{ 
    ws << data.search;  
    ws << data.skills;  
    ws << data.buffs;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, TargetAddSkillBuff & data) 
{ 
    rs >> data.search;  
    rs >> data.skills;  
    rs >> data.buffs;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const TargetAddSkillBuff & info) 
{ 
    stm << "[\n"; 
    stm << "search=" << info.search << "\n"; 
    stm << "skills=" << info.skills << "\n"; 
    stm << "buffs=" << info.buffs << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
 
typedef std::vector<TargetAddSkillBuff> TargetAddSkillBuffArray;  
 
struct HitData //技能  
{ 
    static const unsigned short getProtoID() { return 10003;} 
    static const std::string getProtoName() { return "HitData";} 
    unsigned short act; //序列  
    float rate; //概率  
    unsigned int buffID;  
    unsigned int delay; //序列延迟  
    HitData() 
    { 
        act = 0; 
        rate = 0.0; 
        buffID = 0; 
        delay = 0; 
    } 
    HitData(const unsigned short & act, const float & rate, const unsigned int & buffID, const unsigned int & delay) 
    { 
        this->act = act; 
        this->rate = rate; 
        this->buffID = buffID; 
        this->delay = delay; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const HitData & data) 
{ 
    ws << data.act;  
    ws << data.rate;  
    ws << data.buffID;  
    ws << data.delay;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, HitData & data) 
{ 
    rs >> data.act;  
    rs >> data.rate;  
    rs >> data.buffID;  
    rs >> data.delay;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const HitData & info) 
{ 
    stm << "[\n"; 
    stm << "act=" << info.act << "\n"; 
    stm << "rate=" << info.rate << "\n"; 
    stm << "buffID=" << info.buffID << "\n"; 
    stm << "delay=" << info.delay << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
 
typedef std::vector<HitData> HitDataArray;  
 
struct SkillData //技能  
{ 
    static const unsigned short getProtoID() { return 10004;} 
    static const std::string getProtoName() { return "SkillData";} 
    unsigned int skillID; //skillID  
    unsigned long long skillType; //SKILL_TYPE  
    unsigned int cd;  
    HitDataArray hitActions; //动作触发序列  
    TargetAddSkillBuffArray targetAddSkillBuffs; //上技能或者buff, 每个动作触发一次  
    TargetSearch targetDamage; //触发伤害  
    float teleportDistance; //瞬移  
    SkillData() 
    { 
        skillID = 0; 
        skillType = 0; 
        cd = 0; 
        teleportDistance = 0.0; 
    } 
    SkillData(const unsigned int & skillID, const unsigned long long & skillType, const unsigned int & cd, const HitDataArray & hitActions, const TargetAddSkillBuffArray & targetAddSkillBuffs, const TargetSearch & targetDamage, const float & teleportDistance) 
    { 
        this->skillID = skillID; 
        this->skillType = skillType; 
        this->cd = cd; 
        this->hitActions = hitActions; 
        this->targetAddSkillBuffs = targetAddSkillBuffs; 
        this->targetDamage = targetDamage; 
        this->teleportDistance = teleportDistance; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SkillData & data) 
{ 
    ws << data.skillID;  
    ws << data.skillType;  
    ws << data.cd;  
    ws << data.hitActions;  
    ws << data.targetAddSkillBuffs;  
    ws << data.targetDamage;  
    ws << data.teleportDistance;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SkillData & data) 
{ 
    rs >> data.skillID;  
    rs >> data.skillType;  
    rs >> data.cd;  
    rs >> data.hitActions;  
    rs >> data.targetAddSkillBuffs;  
    rs >> data.targetDamage;  
    rs >> data.teleportDistance;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SkillData & info) 
{ 
    stm << "[\n"; 
    stm << "skillID=" << info.skillID << "\n"; 
    stm << "skillType=" << info.skillType << "\n"; 
    stm << "cd=" << info.cd << "\n"; 
    stm << "hitActions=" << info.hitActions << "\n"; 
    stm << "targetAddSkillBuffs=" << info.targetAddSkillBuffs << "\n"; 
    stm << "targetDamage=" << info.targetDamage << "\n"; 
    stm << "teleportDistance=" << info.teleportDistance << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct BuffData //buff  
{ 
    static const unsigned short getProtoID() { return 10005;} 
    static const std::string getProtoName() { return "BuffData";} 
    unsigned int buffID;  
    unsigned int piletime; //最大叠加时间  
    unsigned int keepTime; //保持时间  
    unsigned long long buffType; //buff类型  
    int value1; //值1  
    int value2; //值2  
    BuffData() 
    { 
        buffID = 0; 
        piletime = 0; 
        keepTime = 0; 
        buffType = 0; 
        value1 = 0; 
        value2 = 0; 
    } 
    BuffData(const unsigned int & buffID, const unsigned int & piletime, const unsigned int & keepTime, const unsigned long long & buffType, const int & value1, const int & value2) 
    { 
        this->buffID = buffID; 
        this->piletime = piletime; 
        this->keepTime = keepTime; 
        this->buffType = buffType; 
        this->value1 = value1; 
        this->value2 = value2; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const BuffData & data) 
{ 
    ws << data.buffID;  
    ws << data.piletime;  
    ws << data.keepTime;  
    ws << data.buffType;  
    ws << data.value1;  
    ws << data.value2;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, BuffData & data) 
{ 
    rs >> data.buffID;  
    rs >> data.piletime;  
    rs >> data.keepTime;  
    rs >> data.buffType;  
    rs >> data.value1;  
    rs >> data.value2;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const BuffData & info) 
{ 
    stm << "[\n"; 
    stm << "buffID=" << info.buffID << "\n"; 
    stm << "piletime=" << info.piletime << "\n"; 
    stm << "keepTime=" << info.keepTime << "\n"; 
    stm << "buffType=" << info.buffType << "\n"; 
    stm << "value1=" << info.value1 << "\n"; 
    stm << "value2=" << info.value2 << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
enum HARM_TYPE : unsigned short 
{ 
    HARMTYPE_GENERAL = 0, //普通伤害  
    HARMTYPE_MISS = 1, //闪避  
    HARMTYPE_CRITICAL = 2, //暴击  
    HARMTYPE_HILL = 3, //治疗  
}; 
 
struct HarmData //伤害数据  
{ 
    static const unsigned short getProtoID() { return 10006;} 
    static const std::string getProtoName() { return "HarmData";} 
    unsigned int eid; //目标eid  
    float harm; //如果为正是伤害, 为负则是回血  
    unsigned short type; //伤害类型HARM_TYPE  
    HarmData() 
    { 
        eid = 0; 
        harm = 0.0; 
        type = 0; 
    } 
    HarmData(const unsigned int & eid, const float & harm, const unsigned short & type) 
    { 
        this->eid = eid; 
        this->harm = harm; 
        this->type = type; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const HarmData & data) 
{ 
    ws << data.eid;  
    ws << data.harm;  
    ws << data.type;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, HarmData & data) 
{ 
    rs >> data.eid;  
    rs >> data.harm;  
    rs >> data.type;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const HarmData & info) 
{ 
    stm << "[\n"; 
    stm << "eid=" << info.eid << "\n"; 
    stm << "harm=" << info.harm << "\n"; 
    stm << "type=" << info.type << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
 
typedef std::vector<HarmData> HarmDataArray;  
 
struct SkillInfo 
{ 
    static const unsigned short getProtoID() { return 10007;} 
    static const std::string getProtoName() { return "SkillInfo";} 
    unsigned int skillID;  
    unsigned int start; //start (server)tick  
    unsigned int lastHitTick; //lastHitTick  
    unsigned int seq; //hit seq  
    EPosition dst; //目标位置,只有需要用到的这个参数的技能才会读这个字段  
    unsigned int foe; //锁定的目标  
    SkillData data; //配置数据  
    SkillInfo() 
    { 
        skillID = 0; 
        start = 0; 
        lastHitTick = 0; 
        seq = 0; 
        foe = 0; 
    } 
    SkillInfo(const unsigned int & skillID, const unsigned int & start, const unsigned int & lastHitTick, const unsigned int & seq, const EPosition & dst, const unsigned int & foe, const SkillData & data) 
    { 
        this->skillID = skillID; 
        this->start = start; 
        this->lastHitTick = lastHitTick; 
        this->seq = seq; 
        this->dst = dst; 
        this->foe = foe; 
        this->data = data; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SkillInfo & data) 
{ 
    ws << data.skillID;  
    ws << data.start;  
    ws << data.lastHitTick;  
    ws << data.seq;  
    ws << data.dst;  
    ws << data.foe;  
    ws << data.data;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SkillInfo & data) 
{ 
    rs >> data.skillID;  
    rs >> data.start;  
    rs >> data.lastHitTick;  
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
    stm << "start=" << info.start << "\n"; 
    stm << "lastHitTick=" << info.lastHitTick << "\n"; 
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
    unsigned int start; //start (server)tick  
    unsigned int lastTrigerTick; //lastTrigerTick  
    BuffData data; //配置数据  
    BuffInfo() 
    { 
        eid = 0; 
        skillID = 0; 
        buffID = 0; 
        start = 0; 
        lastTrigerTick = 0; 
    } 
    BuffInfo(const unsigned int & eid, const unsigned int & skillID, const unsigned int & buffID, const unsigned int & start, const unsigned int & lastTrigerTick, const BuffData & data) 
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
 
struct EntityDict //字典属性  
{ 
    static const unsigned short getProtoID() { return 10009;} 
    static const std::string getProtoName() { return "EntityDict";} 
    unsigned long long serviceID; //用户ID, 非用户为InvalidServiceID  
    UserBaseInfo base;  
    DictFightEffect fight; //战斗属性  
    EntityDict() 
    { 
        serviceID = 0; 
    } 
    EntityDict(const unsigned long long & serviceID, const UserBaseInfo & base, const DictFightEffect & fight) 
    { 
        this->serviceID = serviceID; 
        this->base = base; 
        this->fight = fight; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const EntityDict & data) 
{ 
    ws << data.serviceID;  
    ws << data.base;  
    ws << data.fight;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, EntityDict & data) 
{ 
    rs >> data.serviceID;  
    rs >> data.base;  
    rs >> data.fight;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const EntityDict & info) 
{ 
    stm << "[\n"; 
    stm << "serviceID=" << info.serviceID << "\n"; 
    stm << "base=" << info.base << "\n"; 
    stm << "fight=" << info.fight << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
 
typedef std::vector<EntityDict> EntityDictArray;  
 
struct EPosition 
{ 
    static const unsigned short getProtoID() { return 10010;} 
    static const std::string getProtoName() { return "EPosition";} 
    double x;  
    double y;  
    double face;  
    EPosition() 
    { 
        x = 0.0; 
        y = 0.0; 
        face = 0.0; 
    } 
    EPosition(const double & x, const double & y, const double & face) 
    { 
        this->x = x; 
        this->y = y; 
        this->face = face; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const EPosition & data) 
{ 
    ws << data.x;  
    ws << data.y;  
    ws << data.face;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, EPosition & data) 
{ 
    rs >> data.x;  
    rs >> data.y;  
    rs >> data.face;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const EPosition & info) 
{ 
    stm << "[\n"; 
    stm << "x=" << info.x << "\n"; 
    stm << "y=" << info.y << "\n"; 
    stm << "face=" << info.face << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
 
typedef std::vector<EPosition> EPositions;  
 
struct EntityInfo //EntityInfo  
{ 
    static const unsigned short getProtoID() { return 10011;} 
    static const std::string getProtoName() { return "EntityInfo";} 
    unsigned int eid; //eid  
    unsigned short color; //阵营  
    unsigned short state; //状态  
    EPosition pos; //当前坐标  
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
    EntityInfo(const unsigned int & eid, const unsigned short & color, const unsigned short & state, const EPosition & pos, const unsigned short & moveAction, const EPoints & movePath, const unsigned int & foe, const unsigned int & leader, const unsigned int & follow, const double & curHP) 
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
    unsigned int stateChageTick; //状态改变时间  
    double extSpeed; //扩展速度  
    unsigned int extBeginTick; //扩展速度的开始时间  
    unsigned int extKeepTick; //扩展速度的保持时间  
    EPosition spawnpoint; //出生点  
    EPoint lastPos; //上一帧实体坐标, 如果是瞬移 则和pos相同  
    SkillInfoArray skills; //技能数据  
    BuffInfoArray buffs; //BUFF数据, 小标ID对应bufftype  
    unsigned int diedTick; //实体死亡时间点 -1为永久, 仅飞行道具类有效  
    int hitTimes; //实体碰撞 -1为永久, 仅飞行道具类有效  
    unsigned int lastMoveTick; //最后一次移动时间  
    EPosition lastClientPos; //最后一次客户端提交的坐标  
    EntityControl() 
    { 
        eid = 0; 
        stateChageTick = 0; 
        extSpeed = 0.0; 
        extBeginTick = 0; 
        extKeepTick = 0; 
        diedTick = 0; 
        hitTimes = 0; 
        lastMoveTick = 0; 
    } 
    EntityControl(const unsigned int & eid, const unsigned int & stateChageTick, const double & extSpeed, const unsigned int & extBeginTick, const unsigned int & extKeepTick, const EPosition & spawnpoint, const EPoint & lastPos, const SkillInfoArray & skills, const BuffInfoArray & buffs, const unsigned int & diedTick, const int & hitTimes, const unsigned int & lastMoveTick, const EPosition & lastClientPos) 
    { 
        this->eid = eid; 
        this->stateChageTick = stateChageTick; 
        this->extSpeed = extSpeed; 
        this->extBeginTick = extBeginTick; 
        this->extKeepTick = extKeepTick; 
        this->spawnpoint = spawnpoint; 
        this->lastPos = lastPos; 
        this->skills = skills; 
        this->buffs = buffs; 
        this->diedTick = diedTick; 
        this->hitTimes = hitTimes; 
        this->lastMoveTick = lastMoveTick; 
        this->lastClientPos = lastClientPos; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const EntityControl & data) 
{ 
    ws << data.eid;  
    ws << data.stateChageTick;  
    ws << data.extSpeed;  
    ws << data.extBeginTick;  
    ws << data.extKeepTick;  
    ws << data.spawnpoint;  
    ws << data.lastPos;  
    ws << data.skills;  
    ws << data.buffs;  
    ws << data.diedTick;  
    ws << data.hitTimes;  
    ws << data.lastMoveTick;  
    ws << data.lastClientPos;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, EntityControl & data) 
{ 
    rs >> data.eid;  
    rs >> data.stateChageTick;  
    rs >> data.extSpeed;  
    rs >> data.extBeginTick;  
    rs >> data.extKeepTick;  
    rs >> data.spawnpoint;  
    rs >> data.lastPos;  
    rs >> data.skills;  
    rs >> data.buffs;  
    rs >> data.diedTick;  
    rs >> data.hitTimes;  
    rs >> data.lastMoveTick;  
    rs >> data.lastClientPos;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const EntityControl & info) 
{ 
    stm << "[\n"; 
    stm << "eid=" << info.eid << "\n"; 
    stm << "stateChageTick=" << info.stateChageTick << "\n"; 
    stm << "extSpeed=" << info.extSpeed << "\n"; 
    stm << "extBeginTick=" << info.extBeginTick << "\n"; 
    stm << "extKeepTick=" << info.extKeepTick << "\n"; 
    stm << "spawnpoint=" << info.spawnpoint << "\n"; 
    stm << "lastPos=" << info.lastPos << "\n"; 
    stm << "skills=" << info.skills << "\n"; 
    stm << "buffs=" << info.buffs << "\n"; 
    stm << "diedTick=" << info.diedTick << "\n"; 
    stm << "hitTimes=" << info.hitTimes << "\n"; 
    stm << "lastMoveTick=" << info.lastMoveTick << "\n"; 
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
    unsigned int killCount; //杀死其他玩家次数  
    unsigned int killTick; //杀死其他玩家的时间  
    unsigned int diedCount; //死亡次数  
    unsigned int topMultiKills; //最高连杀次数  
    unsigned int curMultiKills; //当前连杀次数  
    EntityReport() 
    { 
        eid = 0; 
        killCount = 0; 
        killTick = 0; 
        diedCount = 0; 
        topMultiKills = 0; 
        curMultiKills = 0; 
    } 
    EntityReport(const unsigned int & eid, const unsigned int & killCount, const unsigned int & killTick, const unsigned int & diedCount, const unsigned int & topMultiKills, const unsigned int & curMultiKills) 
    { 
        this->eid = eid; 
        this->killCount = killCount; 
        this->killTick = killTick; 
        this->diedCount = diedCount; 
        this->topMultiKills = topMultiKills; 
        this->curMultiKills = curMultiKills; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const EntityReport & data) 
{ 
    ws << data.eid;  
    ws << data.killCount;  
    ws << data.killTick;  
    ws << data.diedCount;  
    ws << data.topMultiKills;  
    ws << data.curMultiKills;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, EntityReport & data) 
{ 
    rs >> data.eid;  
    rs >> data.killCount;  
    rs >> data.killTick;  
    rs >> data.diedCount;  
    rs >> data.topMultiKills;  
    rs >> data.curMultiKills;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const EntityReport & info) 
{ 
    stm << "[\n"; 
    stm << "eid=" << info.eid << "\n"; 
    stm << "killCount=" << info.killCount << "\n"; 
    stm << "killTick=" << info.killTick << "\n"; 
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
    EntityDict dict;  
    EntityInfo info;  
    EntityReport report;  
    EntityFullInfo() 
    { 
    } 
    EntityFullInfo(const EntityDict & dict, const EntityInfo & info, const EntityReport & report) 
    { 
        this->dict = dict; 
        this->info = info; 
        this->report = report; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const EntityFullInfo & data) 
{ 
    ws << data.dict;  
    ws << data.info;  
    ws << data.report;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, EntityFullInfo & data) 
{ 
    rs >> data.dict;  
    rs >> data.info;  
    rs >> data.report;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const EntityFullInfo & info) 
{ 
    stm << "[\n"; 
    stm << "dict=" << info.dict << "\n"; 
    stm << "info=" << info.info << "\n"; 
    stm << "report=" << info.report << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
 
typedef std::vector<EntityFullInfo> EntityFullInfoArray;  
 
#endif 

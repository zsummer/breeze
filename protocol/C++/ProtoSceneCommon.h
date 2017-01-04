 
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
 
struct EntityModel 
{ 
    static const unsigned short getProtoID() { return 2000;} 
    static const std::string getProtoName() { return "EntityModel";} 
    inline std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned long long eid;  
    unsigned long long modelID;  
    std::string modelName;  
    unsigned long long avatarID;  
    std::string avatarName;  
    unsigned long long iconID; //头像  
    double level; //等级  
    double exp; //经验  
    double gold; //金币  
    unsigned short camp;  
    unsigned short etype;  
    unsigned short state;  
    EntityModel() 
    { 
        eid = 0; 
        modelID = 0; 
        avatarID = 0; 
        iconID = 0; 
        level = 0.0; 
        exp = 0.0; 
        gold = 0.0; 
        camp = 0; 
        etype = 0; 
        state = 0; 
    } 
    EntityModel(const unsigned long long & eid, const unsigned long long & modelID, const std::string & modelName, const unsigned long long & avatarID, const std::string & avatarName, const unsigned long long & iconID, const double & level, const double & exp, const double & gold, const unsigned short & camp, const unsigned short & etype, const unsigned short & state) 
    { 
        this->eid = eid; 
        this->modelID = modelID; 
        this->modelName = modelName; 
        this->avatarID = avatarID; 
        this->avatarName = avatarName; 
        this->iconID = iconID; 
        this->level = level; 
        this->exp = exp; 
        this->gold = gold; 
        this->camp = camp; 
        this->etype = etype; 
        this->state = state; 
    } 
}; 
 
std::vector<std::string>  EntityModel::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_EntityModel` (        `modelID` bigint(20) unsigned NOT NULL DEFAULT '0' ,        PRIMARY KEY(`modelID`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_EntityModel` add `eid`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_EntityModel` change `eid`  `eid`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_EntityModel` add `modelID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_EntityModel` change `modelID`  `modelID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_EntityModel` add `modelName`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_EntityModel` change `modelName`  `modelName`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_EntityModel` add `avatarID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_EntityModel` change `avatarID`  `avatarID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_EntityModel` add `avatarName`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_EntityModel` change `avatarName`  `avatarName`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_EntityModel` add `iconID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_EntityModel` change `iconID`  `iconID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_EntityModel` add `level`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_EntityModel` change `level`  `level`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_EntityModel` add `exp`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_EntityModel` change `exp`  `exp`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_EntityModel` add `gold`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_EntityModel` change `gold`  `gold`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_EntityModel` add `camp`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_EntityModel` change `camp`  `camp`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_EntityModel` add `etype`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_EntityModel` change `etype`  `etype`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_EntityModel` add `state`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_EntityModel` change `state`  `state`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    return ret; 
} 
std::string  EntityModel::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `eid`,`modelID`,`modelName`,`avatarID`,`avatarName`,`iconID`,`level`,`exp`,`gold`,`camp`,`etype`,`state` from `tb_EntityModel` where `modelID` = ? "); 
    q << this->modelID; 
    return q.pickSQL(); 
} 
std::string  EntityModel::getDBSelectPure() 
{ 
    return "select `eid`,`modelID`,`modelName`,`avatarID`,`avatarName`,`iconID`,`level`,`exp`,`gold`,`camp`,`etype`,`state` from `tb_EntityModel` "; 
} 
std::string  EntityModel::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_EntityModel`(`eid`,`modelID`,`modelName`,`avatarID`,`avatarName`,`iconID`,`level`,`exp`,`gold`,`camp`,`etype`,`state`) values(?,?,?,?,?,?,?,?,?,?,?,?)"); 
    q << this->eid; 
    q << this->modelID; 
    q << this->modelName; 
    q << this->avatarID; 
    q << this->avatarName; 
    q << this->iconID; 
    q << this->level; 
    q << this->exp; 
    q << this->gold; 
    q << this->camp; 
    q << this->etype; 
    q << this->state; 
    return q.pickSQL(); 
} 
std::string  EntityModel::getDBDelete() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("delete from `tb_EntityModel` where `modelID` = ? "); 
    q << this->modelID; 
    return q.pickSQL(); 
} 
std::string  EntityModel::getDBUpdate() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_EntityModel`(modelID) values(? ) on duplicate key update `eid` = ?,`modelName` = ?,`avatarID` = ?,`avatarName` = ?,`iconID` = ?,`level` = ?,`exp` = ?,`gold` = ?,`camp` = ?,`etype` = ?,`state` = ? "); 
    q << this->modelID; 
    q << this->eid; 
    q << this->modelName; 
    q << this->avatarID; 
    q << this->avatarName; 
    q << this->iconID; 
    q << this->level; 
    q << this->exp; 
    q << this->gold; 
    q << this->camp; 
    q << this->etype; 
    q << this->state; 
    return q.pickSQL(); 
} 
bool EntityModel::fetchFromDBResult(zsummer::mysql::DBResult &result) 
{ 
    if (result.getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("error fetch EntityModel from table `tb_EntityModel` . ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    try 
    { 
        if (result.haveRow()) 
        { 
            result >> this->eid; 
            result >> this->modelID; 
            result >> this->modelName; 
            result >> this->avatarID; 
            result >> this->avatarName; 
            result >> this->iconID; 
            result >> this->level; 
            result >> this->exp; 
            result >> this->gold; 
            result >> this->camp; 
            result >> this->etype; 
            result >> this->state; 
            return true;  
        } 
    } 
    catch(const std::exception & e) 
    { 
        LOGE("catch one except error when fetch EntityModel from table `tb_EntityModel` . what=" << e.what() << "  ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    return false; 
} 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const EntityModel & data) 
{ 
    ws << data.eid;  
    ws << data.modelID;  
    ws << data.modelName;  
    ws << data.avatarID;  
    ws << data.avatarName;  
    ws << data.iconID;  
    ws << data.level;  
    ws << data.exp;  
    ws << data.gold;  
    ws << data.camp;  
    ws << data.etype;  
    ws << data.state;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, EntityModel & data) 
{ 
    rs >> data.eid;  
    rs >> data.modelID;  
    rs >> data.modelName;  
    rs >> data.avatarID;  
    rs >> data.avatarName;  
    rs >> data.iconID;  
    rs >> data.level;  
    rs >> data.exp;  
    rs >> data.gold;  
    rs >> data.camp;  
    rs >> data.etype;  
    rs >> data.state;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const EntityModel & info) 
{ 
    stm << "["; 
    stm << "eid=" << info.eid << ","; 
    stm << "modelID=" << info.modelID << ","; 
    stm << "modelName=" << info.modelName << ","; 
    stm << "avatarID=" << info.avatarID << ","; 
    stm << "avatarName=" << info.avatarName << ","; 
    stm << "iconID=" << info.iconID << ","; 
    stm << "level=" << info.level << ","; 
    stm << "exp=" << info.exp << ","; 
    stm << "gold=" << info.gold << ","; 
    stm << "camp=" << info.camp << ","; 
    stm << "etype=" << info.etype << ","; 
    stm << "state=" << info.state << ","; 
    stm << "]"; 
    return stm; 
} 
 
 
typedef std::vector<EntityModel> EntityModelArray;  
 
 
typedef std::map<unsigned long long, EntityModel> EntityModelMap;  
 
struct SceneGroupAvatarInfo 
{ 
    static const unsigned short getProtoID() { return 2001;} 
    static const std::string getProtoName() { return "SceneGroupAvatarInfo";} 
    unsigned long long areaID; //考虑混服情况,必须指定该玩家来自哪个当前区  
    EntityModel model; //玩家基础数据  
    DictProp fixedProps; //基础固定属性  
    DictProp growthProps; //成长基础属性  
    DictProp growths; //成长系数  
    unsigned short powerType; //组队权限: 0普通,1leader,2master  
    std::string token; //scene服务器的口令, 该字段在广播给客户端时需要清空非自己所属的token,否则将会造成token公开.  
    SceneGroupAvatarInfo() 
    { 
        areaID = 0; 
        powerType = 0; 
    } 
    SceneGroupAvatarInfo(const unsigned long long & areaID, const EntityModel & model, const DictProp & fixedProps, const DictProp & growthProps, const DictProp & growths, const unsigned short & powerType, const std::string & token) 
    { 
        this->areaID = areaID; 
        this->model = model; 
        this->fixedProps = fixedProps; 
        this->growthProps = growthProps; 
        this->growths = growths; 
        this->powerType = powerType; 
        this->token = token; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const SceneGroupAvatarInfo & data) 
{ 
    ws << data.areaID;  
    ws << data.model;  
    ws << data.fixedProps;  
    ws << data.growthProps;  
    ws << data.growths;  
    ws << data.powerType;  
    ws << data.token;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, SceneGroupAvatarInfo & data) 
{ 
    rs >> data.areaID;  
    rs >> data.model;  
    rs >> data.fixedProps;  
    rs >> data.growthProps;  
    rs >> data.growths;  
    rs >> data.powerType;  
    rs >> data.token;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const SceneGroupAvatarInfo & info) 
{ 
    stm << "["; 
    stm << "areaID=" << info.areaID << ","; 
    stm << "model=" << info.model << ","; 
    stm << "fixedProps=" << info.fixedProps << ","; 
    stm << "growthProps=" << info.growthProps << ","; 
    stm << "growths=" << info.growths << ","; 
    stm << "powerType=" << info.powerType << ","; 
    stm << "token=" << info.token << ","; 
    stm << "]"; 
    return stm; 
} 
 
 
typedef std::vector<SceneGroupAvatarInfo> SceneGroupAvatarInfoArray;  
 
 
typedef std::map<unsigned long long, SceneGroupAvatarInfo> SceneGroupAvatarInfoMap;  
 
struct SceneGroupInfo //编队数据  
{ 
    static const unsigned short getProtoID() { return 2002;} 
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
    static const unsigned short getProtoID() { return 2003;} 
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
    static const unsigned short getProtoID() { return 2008;} 
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
    static const unsigned short getProtoID() { return 2011;} 
    static const std::string getProtoName() { return "EntityState";} 
    unsigned long long eid; //eid  
    unsigned short camp; //阵营  
    unsigned long long groupID; //组队ID  
    unsigned short etype; //实体类型  
    unsigned short state; //状态  
    unsigned long long foe; //锁定的敌人  
    unsigned long long leader; //实体的老大, 如果是飞行道具 这个指向施放飞行道具的人  
    double curHP; //当前的血量  
    EntityState() 
    { 
        eid = 0; 
        camp = 0; 
        groupID = 0; 
        etype = 0; 
        state = 0; 
        foe = 0; 
        leader = 0; 
        curHP = 0.0; 
    } 
    EntityState(const unsigned long long & eid, const unsigned short & camp, const unsigned long long & groupID, const unsigned short & etype, const unsigned short & state, const unsigned long long & foe, const unsigned long long & leader, const double & curHP) 
    { 
        this->eid = eid; 
        this->camp = camp; 
        this->groupID = groupID; 
        this->etype = etype; 
        this->state = state; 
        this->foe = foe; 
        this->leader = leader; 
        this->curHP = curHP; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const EntityState & data) 
{ 
    ws << data.eid;  
    ws << data.camp;  
    ws << data.groupID;  
    ws << data.etype;  
    ws << data.state;  
    ws << data.foe;  
    ws << data.leader;  
    ws << data.curHP;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, EntityState & data) 
{ 
    rs >> data.eid;  
    rs >> data.camp;  
    rs >> data.groupID;  
    rs >> data.etype;  
    rs >> data.state;  
    rs >> data.foe;  
    rs >> data.leader;  
    rs >> data.curHP;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const EntityState & info) 
{ 
    stm << "["; 
    stm << "eid=" << info.eid << ","; 
    stm << "camp=" << info.camp << ","; 
    stm << "groupID=" << info.groupID << ","; 
    stm << "etype=" << info.etype << ","; 
    stm << "state=" << info.state << ","; 
    stm << "foe=" << info.foe << ","; 
    stm << "leader=" << info.leader << ","; 
    stm << "curHP=" << info.curHP << ","; 
    stm << "]"; 
    return stm; 
} 
 
 
typedef std::vector<EntityState> EntityStateArray;  
 
struct EntityMove //EntityMove  
{ 
    static const unsigned short getProtoID() { return 2012;} 
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
    static const unsigned short getProtoID() { return 2013;} 
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
 
struct EntityFullData //EntityFullData  
{ 
    static const unsigned short getProtoID() { return 2014;} 
    static const std::string getProtoName() { return "EntityFullData";} 
    EntityModel model; //玩家基础数据  
    DictProp fixedProps; //基础固定属性  
    DictProp growthProps; //成长基础属性  
    DictProp growths; //成长系数  
    DictProp props; //当前  
    EntityState state;  
    EntityMove mv;  
    EntityReport report;  
    EntityFullData() 
    { 
    } 
    EntityFullData(const EntityModel & model, const DictProp & fixedProps, const DictProp & growthProps, const DictProp & growths, const DictProp & props, const EntityState & state, const EntityMove & mv, const EntityReport & report) 
    { 
        this->model = model; 
        this->fixedProps = fixedProps; 
        this->growthProps = growthProps; 
        this->growths = growths; 
        this->props = props; 
        this->state = state; 
        this->mv = mv; 
        this->report = report; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const EntityFullData & data) 
{ 
    ws << data.model;  
    ws << data.fixedProps;  
    ws << data.growthProps;  
    ws << data.growths;  
    ws << data.props;  
    ws << data.state;  
    ws << data.mv;  
    ws << data.report;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, EntityFullData & data) 
{ 
    rs >> data.model;  
    rs >> data.fixedProps;  
    rs >> data.growthProps;  
    rs >> data.growths;  
    rs >> data.props;  
    rs >> data.state;  
    rs >> data.mv;  
    rs >> data.report;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const EntityFullData & info) 
{ 
    stm << "["; 
    stm << "model=" << info.model << ","; 
    stm << "fixedProps=" << info.fixedProps << ","; 
    stm << "growthProps=" << info.growthProps << ","; 
    stm << "growths=" << info.growths << ","; 
    stm << "props=" << info.props << ","; 
    stm << "state=" << info.state << ","; 
    stm << "mv=" << info.mv << ","; 
    stm << "report=" << info.report << ","; 
    stm << "]"; 
    return stm; 
} 
 
 
typedef std::vector<EntityFullData> EntityFullDataArray;  
 
struct SceneSection //场景全景切片数据  
{ 
    static const unsigned short getProtoID() { return 2015;} 
    static const std::string getProtoName() { return "SceneSection";} 
    unsigned long long sceneID;  
    unsigned short sceneType;  
    unsigned short sceneState;  
    double sceneStartTime; //服务器战场开始时间  
    double sceneEndTime; //服务器战场结束时间  
    double serverTime; //服务器当前时间  
    EntityFullDataArray entitys; //这里包含有所有当前场景下的实体属性和状态数据  
    SceneSection() 
    { 
        sceneID = 0; 
        sceneType = 0; 
        sceneState = 0; 
        sceneStartTime = 0.0; 
        sceneEndTime = 0.0; 
        serverTime = 0.0; 
    } 
    SceneSection(const unsigned long long & sceneID, const unsigned short & sceneType, const unsigned short & sceneState, const double & sceneStartTime, const double & sceneEndTime, const double & serverTime, const EntityFullDataArray & entitys) 
    { 
        this->sceneID = sceneID; 
        this->sceneType = sceneType; 
        this->sceneState = sceneState; 
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
    ws << data.sceneState;  
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
    rs >> data.sceneState;  
    rs >> data.sceneStartTime;  
    rs >> data.sceneEndTime;  
    rs >> data.serverTime;  
    rs >> data.entitys;  
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
    stm << "entitys=" << info.entitys << ","; 
    stm << "]"; 
    return stm; 
} 
 
#endif 

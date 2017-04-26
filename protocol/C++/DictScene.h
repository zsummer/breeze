 
#ifndef _DICTSCENE_H_ 
#define _DICTSCENE_H_ 
 
 
struct DictProp //战斗属性  
{ 
    static const unsigned short getProtoID() { return 11000;} 
    static const std::string getProtoName() { return "DictProp";} 
    inline std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned long long id;  
    double hp; //血量值  
    double attack; //伤害  
    double moveSpeed; //移动速度  
    double attackSpeed; //攻击速度  
    std::string desc;  
    DictProp() 
    { 
        id = 0; 
        hp = 0.0; 
        attack = 0.0; 
        moveSpeed = 0.0; 
        attackSpeed = 0.0; 
    } 
    DictProp(const unsigned long long & id, const double & hp, const double & attack, const double & moveSpeed, const double & attackSpeed, const std::string & desc) 
    { 
        this->id = id; 
        this->hp = hp; 
        this->attack = attack; 
        this->moveSpeed = moveSpeed; 
        this->attackSpeed = attackSpeed; 
        this->desc = desc; 
    } 
}; 
 
std::vector<std::string>  DictProp::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_DictProp` (        `id` bigint(20) unsigned NOT NULL DEFAULT '0' ,        PRIMARY KEY(`id`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_DictProp` add `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictProp` change `id`  `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictProp` add `hp`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictProp` change `hp`  `hp`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictProp` add `attack`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictProp` change `attack`  `attack`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictProp` add `moveSpeed`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictProp` change `moveSpeed`  `moveSpeed`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictProp` add `attackSpeed`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictProp` change `attackSpeed`  `attackSpeed`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictProp` add `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictProp` change `desc`  `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    return ret; 
} 
std::string  DictProp::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `id`,`hp`,`attack`,`moveSpeed`,`attackSpeed`,`desc` from `tb_DictProp` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictProp::getDBSelectPure() 
{ 
    return "select `id`,`hp`,`attack`,`moveSpeed`,`attackSpeed`,`desc` from `tb_DictProp` "; 
} 
std::string  DictProp::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictProp`(`id`,`hp`,`attack`,`moveSpeed`,`attackSpeed`,`desc`) values(?,?,?,?,?,?)"); 
    q << this->id; 
    q << this->hp; 
    q << this->attack; 
    q << this->moveSpeed; 
    q << this->attackSpeed; 
    q << this->desc; 
    return q.pickSQL(); 
} 
std::string  DictProp::getDBDelete() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("delete from `tb_DictProp` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictProp::getDBUpdate() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictProp`(id) values(? ) on duplicate key update `hp` = ?,`attack` = ?,`moveSpeed` = ?,`attackSpeed` = ?,`desc` = ? "); 
    q << this->id; 
    q << this->hp; 
    q << this->attack; 
    q << this->moveSpeed; 
    q << this->attackSpeed; 
    q << this->desc; 
    return q.pickSQL(); 
} 
bool DictProp::fetchFromDBResult(zsummer::mysql::DBResult &result) 
{ 
    if (result.getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("error fetch DictProp from table `tb_DictProp` . ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    try 
    { 
        if (result.haveRow()) 
        { 
            result >> this->id; 
            result >> this->hp; 
            result >> this->attack; 
            result >> this->moveSpeed; 
            result >> this->attackSpeed; 
            result >> this->desc; 
            return true;  
        } 
    } 
    catch(const std::exception & e) 
    { 
        LOGE("catch one except error when fetch DictProp from table `tb_DictProp` . what=" << e.what() << "  ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    return false; 
} 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const DictProp & data) 
{ 
    ws << data.id;  
    ws << data.hp;  
    ws << data.attack;  
    ws << data.moveSpeed;  
    ws << data.attackSpeed;  
    ws << data.desc;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DictProp & data) 
{ 
    rs >> data.id;  
    rs >> data.hp;  
    rs >> data.attack;  
    rs >> data.moveSpeed;  
    rs >> data.attackSpeed;  
    rs >> data.desc;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DictProp & info) 
{ 
    stm << "["; 
    stm << "id=" << info.id << ","; 
    stm << "hp=" << info.hp << ","; 
    stm << "attack=" << info.attack << ","; 
    stm << "moveSpeed=" << info.moveSpeed << ","; 
    stm << "attackSpeed=" << info.attackSpeed << ","; 
    stm << "desc=" << info.desc << ","; 
    stm << "]"; 
    return stm; 
} 
 
 
typedef std::vector<DictProp> DictPropArray;  
 
 
typedef std::map<unsigned long long, DictProp> DictPropMap;  
 
struct AOESearch 
{ 
    static const unsigned short getProtoID() { return 11003;} 
    static const std::string getProtoName() { return "AOESearch";} 
    inline std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned long long id;  
    unsigned short etype; //实体类型, 玩家/AI 或者是NONE忽略该选项  
    unsigned long long camp; //0忽略阵营, 1自己, 2同阵营非自己, 3敌方,  4中立  
    std::string campText;  
    unsigned short isRect; //0扇形, 其他矩形  
    double distance; //伤害距离  
    double radian; //弧度或者宽度  
    double offsetX; //坐标偏移量, 以caster为原点, 朝向为y轴  
    double offsetY; //坐标偏移量, 以caster为原点, 朝向为y轴  
    unsigned long long limitEntitys; //最大目标数, 距离优先  
    AOESearch() 
    { 
        id = 0; 
        etype = 0; 
        camp = 0; 
        isRect = 0; 
        distance = 0.0; 
        radian = 0.0; 
        offsetX = 0.0; 
        offsetY = 0.0; 
        limitEntitys = 0; 
    } 
    AOESearch(const unsigned long long & id, const unsigned short & etype, const unsigned long long & camp, const std::string & campText, const unsigned short & isRect, const double & distance, const double & radian, const double & offsetX, const double & offsetY, const unsigned long long & limitEntitys) 
    { 
        this->id = id; 
        this->etype = etype; 
        this->camp = camp; 
        this->campText = campText; 
        this->isRect = isRect; 
        this->distance = distance; 
        this->radian = radian; 
        this->offsetX = offsetX; 
        this->offsetY = offsetY; 
        this->limitEntitys = limitEntitys; 
    } 
}; 
 
std::vector<std::string>  AOESearch::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_AOESearch` (        `id` bigint(20) unsigned NOT NULL DEFAULT '0' ,        PRIMARY KEY(`id`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_AOESearch` add `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AOESearch` change `id`  `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AOESearch` add `etype`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AOESearch` change `etype`  `etype`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AOESearch` add `campText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_AOESearch` change `campText`  `campText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_AOESearch` add `isRect`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AOESearch` change `isRect`  `isRect`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AOESearch` add `distance`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AOESearch` change `distance`  `distance`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AOESearch` add `radian`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AOESearch` change `radian`  `radian`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AOESearch` add `offsetX`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AOESearch` change `offsetX`  `offsetX`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AOESearch` add `offsetY`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AOESearch` change `offsetY`  `offsetY`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AOESearch` add `limitEntitys`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AOESearch` change `limitEntitys`  `limitEntitys`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    return ret; 
} 
std::string  AOESearch::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `id`,`etype`,`campText`,`isRect`,`distance`,`radian`,`offsetX`,`offsetY`,`limitEntitys` from `tb_AOESearch` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  AOESearch::getDBSelectPure() 
{ 
    return "select `id`,`etype`,`campText`,`isRect`,`distance`,`radian`,`offsetX`,`offsetY`,`limitEntitys` from `tb_AOESearch` "; 
} 
std::string  AOESearch::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_AOESearch`(`id`,`etype`,`campText`,`isRect`,`distance`,`radian`,`offsetX`,`offsetY`,`limitEntitys`) values(?,?,?,?,?,?,?,?,?)"); 
    q << this->id; 
    q << this->etype; 
    q << this->campText; 
    q << this->isRect; 
    q << this->distance; 
    q << this->radian; 
    q << this->offsetX; 
    q << this->offsetY; 
    q << this->limitEntitys; 
    return q.pickSQL(); 
} 
std::string  AOESearch::getDBDelete() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("delete from `tb_AOESearch` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  AOESearch::getDBUpdate() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_AOESearch`(id) values(? ) on duplicate key update `etype` = ?,`campText` = ?,`isRect` = ?,`distance` = ?,`radian` = ?,`offsetX` = ?,`offsetY` = ?,`limitEntitys` = ? "); 
    q << this->id; 
    q << this->etype; 
    q << this->campText; 
    q << this->isRect; 
    q << this->distance; 
    q << this->radian; 
    q << this->offsetX; 
    q << this->offsetY; 
    q << this->limitEntitys; 
    return q.pickSQL(); 
} 
bool AOESearch::fetchFromDBResult(zsummer::mysql::DBResult &result) 
{ 
    if (result.getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("error fetch AOESearch from table `tb_AOESearch` . ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    try 
    { 
        if (result.haveRow()) 
        { 
            result >> this->id; 
            result >> this->etype; 
            result >> this->campText; 
            result >> this->isRect; 
            result >> this->distance; 
            result >> this->radian; 
            result >> this->offsetX; 
            result >> this->offsetY; 
            result >> this->limitEntitys; 
            return true;  
        } 
    } 
    catch(const std::exception & e) 
    { 
        LOGE("catch one except error when fetch AOESearch from table `tb_AOESearch` . what=" << e.what() << "  ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    return false; 
} 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const AOESearch & data) 
{ 
    ws << data.id;  
    ws << data.etype;  
    ws << data.camp;  
    ws << data.campText;  
    ws << data.isRect;  
    ws << data.distance;  
    ws << data.radian;  
    ws << data.offsetX;  
    ws << data.offsetY;  
    ws << data.limitEntitys;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AOESearch & data) 
{ 
    rs >> data.id;  
    rs >> data.etype;  
    rs >> data.camp;  
    rs >> data.campText;  
    rs >> data.isRect;  
    rs >> data.distance;  
    rs >> data.radian;  
    rs >> data.offsetX;  
    rs >> data.offsetY;  
    rs >> data.limitEntitys;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const AOESearch & info) 
{ 
    stm << "["; 
    stm << "id=" << info.id << ","; 
    stm << "etype=" << info.etype << ","; 
    stm << "camp=" << info.camp << ","; 
    stm << "campText=" << info.campText << ","; 
    stm << "isRect=" << info.isRect << ","; 
    stm << "distance=" << info.distance << ","; 
    stm << "radian=" << info.radian << ","; 
    stm << "offsetX=" << info.offsetX << ","; 
    stm << "offsetY=" << info.offsetY << ","; 
    stm << "limitEntitys=" << info.limitEntitys << ","; 
    stm << "]"; 
    return stm; 
} 
 
enum SKILL_TRIGGER_STAMP : unsigned long long 
{ 
    SKILL_TRIGGER_WHEN_LOAD_BUFF = 5, //加载buff立刻触发  
    SKILL_TRIGGER_WHEN_UNLOAD_BUFF = 6, //卸载buff立刻触发  
    SKILL_TRIGGER_PRE_DEATH = 10, //死亡前触发  
    SKILL_TRIGGER_AFT_DEATH = 11, //死亡后触发  
    SKILL_TRIGGER_WHEN_GENERAL = 15, //攻击触发  
    SKILL_TRIGGER_WHEN_PHYSICAL = 16, //攻击触发  
    SKILL_TRIGGER_WHEN_MAGIC = 17, //攻击触发  
    SKILL_TRIGGER_ON_GENERAL = 20, //被攻击触发  
    SKILL_TRIGGER_ON_PHYSICAL = 21, //被攻击触发  
    SKILL_TRIGGER_ON_MAGIC = 22, //被攻击触发  
    SKILL_TRIGGER_WHEN_ATTACH_GENERAL = 30, //攻击触发  
    SKILL_TRIGGER_WHEN_ON_ATTACH = 31, //被攻击触发  
}; 
 
enum BUFF_STAMP : unsigned long long 
{ 
    BUFF_HALO = 1, //描述性类型: 光环  
    BUFF_BUFF = 2, //描述性类型: 增益buff  
    BUFF_DEBUFF = 3, //描述性类型: 减益BUFF  
    BUFF_HIDE = 4, //描述性类型: 客户端不表现  
    BUFF_PASSIVE = 5, //描述性类型: 被动技能, 无法永久存在, 但死亡会停止任何触发  
    BUFF_HOLD_MOVE = 10, //控制: 禁止移动  
    BUFF_REVERSE_MOVE = 11, //控制: 移动反向  
    BUFF_SILENCE_GENERAL = 12, //控制: 沉默普攻  
    BUFF_SILENCE_PHYSICAL = 13, //控制: 沉默物攻  
    BUFF_SILENCE_MAGIC = 14, //控制: 沉默法攻  
    BUFF_IMMUNE_MOVE = 20, //免疫: 免疫移动类控制  
    BUFF_IMMUNE_SILENCE_GENERAL = 21, //免疫: 免疫普攻沉默  
    BUFF_IMMUNE_SILENCE_PHYSICAL = 22, //免疫: 免疫物攻沉默  
    BUFF_IMMUNE_SILENCE_MAGIC = 23, //免疫: 免疫法攻沉默  
    BUFF_IMMUNE_DEBUFF = 30, //免疫: 免疫DEBUFF  
    BUFF_IMMUNE_BUFF = 31, //免疫: 免疫增益BUFF  
    BUFF_IMMUNE_OCCUPIED = 32, //免疫: 免疫占据  
    BUFF_IMMUNE_FLOAT = 33, //免疫: 免疫击飞  
    BUFF_IMMUNE_MOVEBACK = 34, //免疫: 免疫击退  
    BUFF_IMMUNE_BREAK = 35, //免疫: 免疫技能中断  
}; 
 
struct DictBuffEffect 
{ 
    static const unsigned short getProtoID() { return 11004;} 
    static const std::string getProtoName() { return "DictBuffEffect";} 
    inline std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned long long id;  
    unsigned long long listenTriggerStamp;  
    std::string listenTriggerStampText;  
    unsigned long long propID; //提升的属性效果, 求积方式的参数是基础属性 不算其他装备  
    DictArrayKey skills; //触发技能  
    std::string skillsText; //触发技能 格式id,id,id   
    DictArrayKey buffs; //触发buff  
    std::string buffsText; //触发buff 格式id,id,id  
    double areaTrigger; //距离触发, 0为无效  
    double timerTrigger; //定时器触发间隔  
    double intervalLimit; //最小触发间隔时间, 0为无效  
    double triggerCountLimit; //触发次数限制  
    double autoUnloadBuff; //超出触发次数后自动移除buff  
    std::string desc;  
    DictBuffEffect() 
    { 
        id = 0; 
        listenTriggerStamp = 0; 
        propID = 0; 
        areaTrigger = 0.0; 
        timerTrigger = 0.0; 
        intervalLimit = 0.0; 
        triggerCountLimit = 0.0; 
        autoUnloadBuff = 0.0; 
    } 
    DictBuffEffect(const unsigned long long & id, const unsigned long long & listenTriggerStamp, const std::string & listenTriggerStampText, const unsigned long long & propID, const DictArrayKey & skills, const std::string & skillsText, const DictArrayKey & buffs, const std::string & buffsText, const double & areaTrigger, const double & timerTrigger, const double & intervalLimit, const double & triggerCountLimit, const double & autoUnloadBuff, const std::string & desc) 
    { 
        this->id = id; 
        this->listenTriggerStamp = listenTriggerStamp; 
        this->listenTriggerStampText = listenTriggerStampText; 
        this->propID = propID; 
        this->skills = skills; 
        this->skillsText = skillsText; 
        this->buffs = buffs; 
        this->buffsText = buffsText; 
        this->areaTrigger = areaTrigger; 
        this->timerTrigger = timerTrigger; 
        this->intervalLimit = intervalLimit; 
        this->triggerCountLimit = triggerCountLimit; 
        this->autoUnloadBuff = autoUnloadBuff; 
        this->desc = desc; 
    } 
}; 
 
std::vector<std::string>  DictBuffEffect::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_DictBuffEffect` (        `id` bigint(20) unsigned NOT NULL DEFAULT '0' ,        PRIMARY KEY(`id`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_DictBuffEffect` add `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuffEffect` change `id`  `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuffEffect` add `listenTriggerStampText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictBuffEffect` change `listenTriggerStampText`  `listenTriggerStampText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictBuffEffect` add `propID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuffEffect` change `propID`  `propID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuffEffect` add `skillsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictBuffEffect` change `skillsText`  `skillsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictBuffEffect` add `buffsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictBuffEffect` change `buffsText`  `buffsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictBuffEffect` add `areaTrigger`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuffEffect` change `areaTrigger`  `areaTrigger`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuffEffect` add `timerTrigger`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuffEffect` change `timerTrigger`  `timerTrigger`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuffEffect` add `intervalLimit`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuffEffect` change `intervalLimit`  `intervalLimit`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuffEffect` add `triggerCountLimit`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuffEffect` change `triggerCountLimit`  `triggerCountLimit`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuffEffect` add `autoUnloadBuff`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuffEffect` change `autoUnloadBuff`  `autoUnloadBuff`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuffEffect` add `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictBuffEffect` change `desc`  `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    return ret; 
} 
std::string  DictBuffEffect::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `id`,`listenTriggerStampText`,`propID`,`skillsText`,`buffsText`,`areaTrigger`,`timerTrigger`,`intervalLimit`,`triggerCountLimit`,`autoUnloadBuff`,`desc` from `tb_DictBuffEffect` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictBuffEffect::getDBSelectPure() 
{ 
    return "select `id`,`listenTriggerStampText`,`propID`,`skillsText`,`buffsText`,`areaTrigger`,`timerTrigger`,`intervalLimit`,`triggerCountLimit`,`autoUnloadBuff`,`desc` from `tb_DictBuffEffect` "; 
} 
std::string  DictBuffEffect::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictBuffEffect`(`id`,`listenTriggerStampText`,`propID`,`skillsText`,`buffsText`,`areaTrigger`,`timerTrigger`,`intervalLimit`,`triggerCountLimit`,`autoUnloadBuff`,`desc`) values(?,?,?,?,?,?,?,?,?,?,?)"); 
    q << this->id; 
    q << this->listenTriggerStampText; 
    q << this->propID; 
    q << this->skillsText; 
    q << this->buffsText; 
    q << this->areaTrigger; 
    q << this->timerTrigger; 
    q << this->intervalLimit; 
    q << this->triggerCountLimit; 
    q << this->autoUnloadBuff; 
    q << this->desc; 
    return q.pickSQL(); 
} 
std::string  DictBuffEffect::getDBDelete() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("delete from `tb_DictBuffEffect` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictBuffEffect::getDBUpdate() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictBuffEffect`(id) values(? ) on duplicate key update `listenTriggerStampText` = ?,`propID` = ?,`skillsText` = ?,`buffsText` = ?,`areaTrigger` = ?,`timerTrigger` = ?,`intervalLimit` = ?,`triggerCountLimit` = ?,`autoUnloadBuff` = ?,`desc` = ? "); 
    q << this->id; 
    q << this->listenTriggerStampText; 
    q << this->propID; 
    q << this->skillsText; 
    q << this->buffsText; 
    q << this->areaTrigger; 
    q << this->timerTrigger; 
    q << this->intervalLimit; 
    q << this->triggerCountLimit; 
    q << this->autoUnloadBuff; 
    q << this->desc; 
    return q.pickSQL(); 
} 
bool DictBuffEffect::fetchFromDBResult(zsummer::mysql::DBResult &result) 
{ 
    if (result.getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("error fetch DictBuffEffect from table `tb_DictBuffEffect` . ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    try 
    { 
        if (result.haveRow()) 
        { 
            result >> this->id; 
            result >> this->listenTriggerStampText; 
            result >> this->propID; 
            result >> this->skillsText; 
            result >> this->buffsText; 
            result >> this->areaTrigger; 
            result >> this->timerTrigger; 
            result >> this->intervalLimit; 
            result >> this->triggerCountLimit; 
            result >> this->autoUnloadBuff; 
            result >> this->desc; 
            return true;  
        } 
    } 
    catch(const std::exception & e) 
    { 
        LOGE("catch one except error when fetch DictBuffEffect from table `tb_DictBuffEffect` . what=" << e.what() << "  ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    return false; 
} 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const DictBuffEffect & data) 
{ 
    ws << data.id;  
    ws << data.listenTriggerStamp;  
    ws << data.listenTriggerStampText;  
    ws << data.propID;  
    ws << data.skills;  
    ws << data.skillsText;  
    ws << data.buffs;  
    ws << data.buffsText;  
    ws << data.areaTrigger;  
    ws << data.timerTrigger;  
    ws << data.intervalLimit;  
    ws << data.triggerCountLimit;  
    ws << data.autoUnloadBuff;  
    ws << data.desc;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DictBuffEffect & data) 
{ 
    rs >> data.id;  
    rs >> data.listenTriggerStamp;  
    rs >> data.listenTriggerStampText;  
    rs >> data.propID;  
    rs >> data.skills;  
    rs >> data.skillsText;  
    rs >> data.buffs;  
    rs >> data.buffsText;  
    rs >> data.areaTrigger;  
    rs >> data.timerTrigger;  
    rs >> data.intervalLimit;  
    rs >> data.triggerCountLimit;  
    rs >> data.autoUnloadBuff;  
    rs >> data.desc;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DictBuffEffect & info) 
{ 
    stm << "["; 
    stm << "id=" << info.id << ","; 
    stm << "listenTriggerStamp=" << info.listenTriggerStamp << ","; 
    stm << "listenTriggerStampText=" << info.listenTriggerStampText << ","; 
    stm << "propID=" << info.propID << ","; 
    stm << "skills=" << info.skills << ","; 
    stm << "skillsText=" << info.skillsText << ","; 
    stm << "buffs=" << info.buffs << ","; 
    stm << "buffsText=" << info.buffsText << ","; 
    stm << "areaTrigger=" << info.areaTrigger << ","; 
    stm << "timerTrigger=" << info.timerTrigger << ","; 
    stm << "intervalLimit=" << info.intervalLimit << ","; 
    stm << "triggerCountLimit=" << info.triggerCountLimit << ","; 
    stm << "autoUnloadBuff=" << info.autoUnloadBuff << ","; 
    stm << "desc=" << info.desc << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct DictBuff 
{ 
    static const unsigned short getProtoID() { return 11005;} 
    static const std::string getProtoName() { return "DictBuff";} 
    inline std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned long long id;  
    unsigned long long stamp; //BUFF_STAMP  
    std::string stampText;  
    DictArrayKey effects; //DictBuffEffect ID  
    std::string effectsText;  
    double keepTime;  
    double limitStackTime; //相同buff叠加时间并且刷新触发次数  
    std::string desc;  
    DictBuff() 
    { 
        id = 0; 
        stamp = 0; 
        keepTime = 0.0; 
        limitStackTime = 0.0; 
    } 
    DictBuff(const unsigned long long & id, const unsigned long long & stamp, const std::string & stampText, const DictArrayKey & effects, const std::string & effectsText, const double & keepTime, const double & limitStackTime, const std::string & desc) 
    { 
        this->id = id; 
        this->stamp = stamp; 
        this->stampText = stampText; 
        this->effects = effects; 
        this->effectsText = effectsText; 
        this->keepTime = keepTime; 
        this->limitStackTime = limitStackTime; 
        this->desc = desc; 
    } 
}; 
 
std::vector<std::string>  DictBuff::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_DictBuff` (        `id` bigint(20) unsigned NOT NULL DEFAULT '0' ,        PRIMARY KEY(`id`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_DictBuff` add `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuff` change `id`  `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuff` add `stampText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictBuff` change `stampText`  `stampText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictBuff` add `effectsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictBuff` change `effectsText`  `effectsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictBuff` add `keepTime`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuff` change `keepTime`  `keepTime`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuff` add `limitStackTime`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuff` change `limitStackTime`  `limitStackTime`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuff` add `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictBuff` change `desc`  `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    return ret; 
} 
std::string  DictBuff::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `id`,`stampText`,`effectsText`,`keepTime`,`limitStackTime`,`desc` from `tb_DictBuff` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictBuff::getDBSelectPure() 
{ 
    return "select `id`,`stampText`,`effectsText`,`keepTime`,`limitStackTime`,`desc` from `tb_DictBuff` "; 
} 
std::string  DictBuff::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictBuff`(`id`,`stampText`,`effectsText`,`keepTime`,`limitStackTime`,`desc`) values(?,?,?,?,?,?)"); 
    q << this->id; 
    q << this->stampText; 
    q << this->effectsText; 
    q << this->keepTime; 
    q << this->limitStackTime; 
    q << this->desc; 
    return q.pickSQL(); 
} 
std::string  DictBuff::getDBDelete() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("delete from `tb_DictBuff` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictBuff::getDBUpdate() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictBuff`(id) values(? ) on duplicate key update `stampText` = ?,`effectsText` = ?,`keepTime` = ?,`limitStackTime` = ?,`desc` = ? "); 
    q << this->id; 
    q << this->stampText; 
    q << this->effectsText; 
    q << this->keepTime; 
    q << this->limitStackTime; 
    q << this->desc; 
    return q.pickSQL(); 
} 
bool DictBuff::fetchFromDBResult(zsummer::mysql::DBResult &result) 
{ 
    if (result.getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("error fetch DictBuff from table `tb_DictBuff` . ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    try 
    { 
        if (result.haveRow()) 
        { 
            result >> this->id; 
            result >> this->stampText; 
            result >> this->effectsText; 
            result >> this->keepTime; 
            result >> this->limitStackTime; 
            result >> this->desc; 
            return true;  
        } 
    } 
    catch(const std::exception & e) 
    { 
        LOGE("catch one except error when fetch DictBuff from table `tb_DictBuff` . what=" << e.what() << "  ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    return false; 
} 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const DictBuff & data) 
{ 
    ws << data.id;  
    ws << data.stamp;  
    ws << data.stampText;  
    ws << data.effects;  
    ws << data.effectsText;  
    ws << data.keepTime;  
    ws << data.limitStackTime;  
    ws << data.desc;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DictBuff & data) 
{ 
    rs >> data.id;  
    rs >> data.stamp;  
    rs >> data.stampText;  
    rs >> data.effects;  
    rs >> data.effectsText;  
    rs >> data.keepTime;  
    rs >> data.limitStackTime;  
    rs >> data.desc;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DictBuff & info) 
{ 
    stm << "["; 
    stm << "id=" << info.id << ","; 
    stm << "stamp=" << info.stamp << ","; 
    stm << "stampText=" << info.stampText << ","; 
    stm << "effects=" << info.effects << ","; 
    stm << "effectsText=" << info.effectsText << ","; 
    stm << "keepTime=" << info.keepTime << ","; 
    stm << "limitStackTime=" << info.limitStackTime << ","; 
    stm << "desc=" << info.desc << ","; 
    stm << "]"; 
    return stm; 
} 
 
enum SKILL_STAMP : unsigned long long 
{ 
    SKILL_NONE = 0,  
    SKILL_AUTO_USE = 1, //自动施法  
    SKILL_PASSIVE = 2, //被动技能  
    SKILL_ON_HIT_BREAK = 3, //可被中断  
    SKILL_ON_MOVE_BREAK = 4, //可被中断  
    SKILL_CAN_MOVE = 5, //可移动  
    SKILL_PHYSICAL = 6, //物理类型  
    SKILL_MAGIC = 7, //魔法类型  
    SKILL_HIT = 8, //攻击  
    SKILL_HILL = 9, //治疗  
    SKILL_REMOVE_DEBUFF = 10, //驱散减益BUFF  
    SKILL_REMOVE_BUFF = 11, //驱散增益BUFF  
}; 
 
struct DictSkill 
{ 
    static const unsigned short getProtoID() { return 11007;} 
    static const std::string getProtoName() { return "DictSkill";} 
    inline std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned long long id;  
    unsigned long long stamp;  
    unsigned long long searchID; //锁敌  
    unsigned long long aoeID; //AOI伤害  
    unsigned long long appBuffID; //上buff的searchid  
    double delay; //前摇  
    double keep; //持续时间  
    double cd; //冷却  
    double hpAdd; //附加真实伤害  
    double hpAddScaleRemanent;  
    double hpAddScaleLost;  
    unsigned long long propID; //附加属性提升  
    double dstTeleport; //目标闪现到自己  
    double selfTeleport; //自己闪现到目标  
    double dstMoveTime; //附加给目标朝向自己的位移时间  
    double dstMoveSpeed; //附加给目标朝向自己的位移速度  
    double selfMoveTime; //附加给自己朝向目标的位移时间  
    double selfMoveSpeed; //附加给自己朝向目标的位移速度  
    DictArrayKey appendBuffs;  
    std::string appendBuffsText; //触发buff 格式 k,k,k,   
    DictArrayKey harmBuffs;  
    std::string harmBuffsText; //触发buff 格式 k,k,k,   
    unsigned long long nextSkillID; //技能结束释放下个技能  
    std::string desc;  
    DictSkill() 
    { 
        id = 0; 
        stamp = 0; 
        searchID = 0; 
        aoeID = 0; 
        appBuffID = 0; 
        delay = 0.0; 
        keep = 0.0; 
        cd = 0.0; 
        hpAdd = 0.0; 
        hpAddScaleRemanent = 0.0; 
        hpAddScaleLost = 0.0; 
        propID = 0; 
        dstTeleport = 0.0; 
        selfTeleport = 0.0; 
        dstMoveTime = 0.0; 
        dstMoveSpeed = 0.0; 
        selfMoveTime = 0.0; 
        selfMoveSpeed = 0.0; 
        nextSkillID = 0; 
    } 
    DictSkill(const unsigned long long & id, const unsigned long long & stamp, const unsigned long long & searchID, const unsigned long long & aoeID, const unsigned long long & appBuffID, const double & delay, const double & keep, const double & cd, const double & hpAdd, const double & hpAddScaleRemanent, const double & hpAddScaleLost, const unsigned long long & propID, const double & dstTeleport, const double & selfTeleport, const double & dstMoveTime, const double & dstMoveSpeed, const double & selfMoveTime, const double & selfMoveSpeed, const DictArrayKey & appendBuffs, const std::string & appendBuffsText, const DictArrayKey & harmBuffs, const std::string & harmBuffsText, const unsigned long long & nextSkillID, const std::string & desc) 
    { 
        this->id = id; 
        this->stamp = stamp; 
        this->searchID = searchID; 
        this->aoeID = aoeID; 
        this->appBuffID = appBuffID; 
        this->delay = delay; 
        this->keep = keep; 
        this->cd = cd; 
        this->hpAdd = hpAdd; 
        this->hpAddScaleRemanent = hpAddScaleRemanent; 
        this->hpAddScaleLost = hpAddScaleLost; 
        this->propID = propID; 
        this->dstTeleport = dstTeleport; 
        this->selfTeleport = selfTeleport; 
        this->dstMoveTime = dstMoveTime; 
        this->dstMoveSpeed = dstMoveSpeed; 
        this->selfMoveTime = selfMoveTime; 
        this->selfMoveSpeed = selfMoveSpeed; 
        this->appendBuffs = appendBuffs; 
        this->appendBuffsText = appendBuffsText; 
        this->harmBuffs = harmBuffs; 
        this->harmBuffsText = harmBuffsText; 
        this->nextSkillID = nextSkillID; 
        this->desc = desc; 
    } 
}; 
 
std::vector<std::string>  DictSkill::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_DictSkill` (        `id` bigint(20) unsigned NOT NULL DEFAULT '0' ,        PRIMARY KEY(`id`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_DictSkill` add `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` change `id`  `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` add `stamp`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` change `stamp`  `stamp`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` add `searchID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` change `searchID`  `searchID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` add `aoeID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` change `aoeID`  `aoeID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` add `appBuffID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` change `appBuffID`  `appBuffID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` add `delay`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` change `delay`  `delay`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` add `keep`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` change `keep`  `keep`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` add `cd`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` change `cd`  `cd`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` add `hpAdd`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` change `hpAdd`  `hpAdd`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` add `hpAddScaleRemanent`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` change `hpAddScaleRemanent`  `hpAddScaleRemanent`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` add `hpAddScaleLost`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` change `hpAddScaleLost`  `hpAddScaleLost`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` add `propID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` change `propID`  `propID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` add `dstTeleport`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` change `dstTeleport`  `dstTeleport`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` add `selfTeleport`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` change `selfTeleport`  `selfTeleport`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` add `dstMoveTime`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` change `dstMoveTime`  `dstMoveTime`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` add `dstMoveSpeed`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` change `dstMoveSpeed`  `dstMoveSpeed`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` add `selfMoveTime`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` change `selfMoveTime`  `selfMoveTime`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` add `selfMoveSpeed`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` change `selfMoveSpeed`  `selfMoveSpeed`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` add `appendBuffsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictSkill` change `appendBuffsText`  `appendBuffsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictSkill` add `harmBuffsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictSkill` change `harmBuffsText`  `harmBuffsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictSkill` add `nextSkillID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` change `nextSkillID`  `nextSkillID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` add `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictSkill` change `desc`  `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    return ret; 
} 
std::string  DictSkill::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `id`,`stamp`,`searchID`,`aoeID`,`appBuffID`,`delay`,`keep`,`cd`,`hpAdd`,`hpAddScaleRemanent`,`hpAddScaleLost`,`propID`,`dstTeleport`,`selfTeleport`,`dstMoveTime`,`dstMoveSpeed`,`selfMoveTime`,`selfMoveSpeed`,`appendBuffsText`,`harmBuffsText`,`nextSkillID`,`desc` from `tb_DictSkill` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictSkill::getDBSelectPure() 
{ 
    return "select `id`,`stamp`,`searchID`,`aoeID`,`appBuffID`,`delay`,`keep`,`cd`,`hpAdd`,`hpAddScaleRemanent`,`hpAddScaleLost`,`propID`,`dstTeleport`,`selfTeleport`,`dstMoveTime`,`dstMoveSpeed`,`selfMoveTime`,`selfMoveSpeed`,`appendBuffsText`,`harmBuffsText`,`nextSkillID`,`desc` from `tb_DictSkill` "; 
} 
std::string  DictSkill::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictSkill`(`id`,`stamp`,`searchID`,`aoeID`,`appBuffID`,`delay`,`keep`,`cd`,`hpAdd`,`hpAddScaleRemanent`,`hpAddScaleLost`,`propID`,`dstTeleport`,`selfTeleport`,`dstMoveTime`,`dstMoveSpeed`,`selfMoveTime`,`selfMoveSpeed`,`appendBuffsText`,`harmBuffsText`,`nextSkillID`,`desc`) values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)"); 
    q << this->id; 
    q << this->stamp; 
    q << this->searchID; 
    q << this->aoeID; 
    q << this->appBuffID; 
    q << this->delay; 
    q << this->keep; 
    q << this->cd; 
    q << this->hpAdd; 
    q << this->hpAddScaleRemanent; 
    q << this->hpAddScaleLost; 
    q << this->propID; 
    q << this->dstTeleport; 
    q << this->selfTeleport; 
    q << this->dstMoveTime; 
    q << this->dstMoveSpeed; 
    q << this->selfMoveTime; 
    q << this->selfMoveSpeed; 
    q << this->appendBuffsText; 
    q << this->harmBuffsText; 
    q << this->nextSkillID; 
    q << this->desc; 
    return q.pickSQL(); 
} 
std::string  DictSkill::getDBDelete() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("delete from `tb_DictSkill` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictSkill::getDBUpdate() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictSkill`(id) values(? ) on duplicate key update `stamp` = ?,`searchID` = ?,`aoeID` = ?,`appBuffID` = ?,`delay` = ?,`keep` = ?,`cd` = ?,`hpAdd` = ?,`hpAddScaleRemanent` = ?,`hpAddScaleLost` = ?,`propID` = ?,`dstTeleport` = ?,`selfTeleport` = ?,`dstMoveTime` = ?,`dstMoveSpeed` = ?,`selfMoveTime` = ?,`selfMoveSpeed` = ?,`appendBuffsText` = ?,`harmBuffsText` = ?,`nextSkillID` = ?,`desc` = ? "); 
    q << this->id; 
    q << this->stamp; 
    q << this->searchID; 
    q << this->aoeID; 
    q << this->appBuffID; 
    q << this->delay; 
    q << this->keep; 
    q << this->cd; 
    q << this->hpAdd; 
    q << this->hpAddScaleRemanent; 
    q << this->hpAddScaleLost; 
    q << this->propID; 
    q << this->dstTeleport; 
    q << this->selfTeleport; 
    q << this->dstMoveTime; 
    q << this->dstMoveSpeed; 
    q << this->selfMoveTime; 
    q << this->selfMoveSpeed; 
    q << this->appendBuffsText; 
    q << this->harmBuffsText; 
    q << this->nextSkillID; 
    q << this->desc; 
    return q.pickSQL(); 
} 
bool DictSkill::fetchFromDBResult(zsummer::mysql::DBResult &result) 
{ 
    if (result.getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("error fetch DictSkill from table `tb_DictSkill` . ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    try 
    { 
        if (result.haveRow()) 
        { 
            result >> this->id; 
            result >> this->stamp; 
            result >> this->searchID; 
            result >> this->aoeID; 
            result >> this->appBuffID; 
            result >> this->delay; 
            result >> this->keep; 
            result >> this->cd; 
            result >> this->hpAdd; 
            result >> this->hpAddScaleRemanent; 
            result >> this->hpAddScaleLost; 
            result >> this->propID; 
            result >> this->dstTeleport; 
            result >> this->selfTeleport; 
            result >> this->dstMoveTime; 
            result >> this->dstMoveSpeed; 
            result >> this->selfMoveTime; 
            result >> this->selfMoveSpeed; 
            result >> this->appendBuffsText; 
            result >> this->harmBuffsText; 
            result >> this->nextSkillID; 
            result >> this->desc; 
            return true;  
        } 
    } 
    catch(const std::exception & e) 
    { 
        LOGE("catch one except error when fetch DictSkill from table `tb_DictSkill` . what=" << e.what() << "  ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    return false; 
} 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const DictSkill & data) 
{ 
    ws << data.id;  
    ws << data.stamp;  
    ws << data.searchID;  
    ws << data.aoeID;  
    ws << data.appBuffID;  
    ws << data.delay;  
    ws << data.keep;  
    ws << data.cd;  
    ws << data.hpAdd;  
    ws << data.hpAddScaleRemanent;  
    ws << data.hpAddScaleLost;  
    ws << data.propID;  
    ws << data.dstTeleport;  
    ws << data.selfTeleport;  
    ws << data.dstMoveTime;  
    ws << data.dstMoveSpeed;  
    ws << data.selfMoveTime;  
    ws << data.selfMoveSpeed;  
    ws << data.appendBuffs;  
    ws << data.appendBuffsText;  
    ws << data.harmBuffs;  
    ws << data.harmBuffsText;  
    ws << data.nextSkillID;  
    ws << data.desc;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DictSkill & data) 
{ 
    rs >> data.id;  
    rs >> data.stamp;  
    rs >> data.searchID;  
    rs >> data.aoeID;  
    rs >> data.appBuffID;  
    rs >> data.delay;  
    rs >> data.keep;  
    rs >> data.cd;  
    rs >> data.hpAdd;  
    rs >> data.hpAddScaleRemanent;  
    rs >> data.hpAddScaleLost;  
    rs >> data.propID;  
    rs >> data.dstTeleport;  
    rs >> data.selfTeleport;  
    rs >> data.dstMoveTime;  
    rs >> data.dstMoveSpeed;  
    rs >> data.selfMoveTime;  
    rs >> data.selfMoveSpeed;  
    rs >> data.appendBuffs;  
    rs >> data.appendBuffsText;  
    rs >> data.harmBuffs;  
    rs >> data.harmBuffsText;  
    rs >> data.nextSkillID;  
    rs >> data.desc;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DictSkill & info) 
{ 
    stm << "["; 
    stm << "id=" << info.id << ","; 
    stm << "stamp=" << info.stamp << ","; 
    stm << "searchID=" << info.searchID << ","; 
    stm << "aoeID=" << info.aoeID << ","; 
    stm << "appBuffID=" << info.appBuffID << ","; 
    stm << "delay=" << info.delay << ","; 
    stm << "keep=" << info.keep << ","; 
    stm << "cd=" << info.cd << ","; 
    stm << "hpAdd=" << info.hpAdd << ","; 
    stm << "hpAddScaleRemanent=" << info.hpAddScaleRemanent << ","; 
    stm << "hpAddScaleLost=" << info.hpAddScaleLost << ","; 
    stm << "propID=" << info.propID << ","; 
    stm << "dstTeleport=" << info.dstTeleport << ","; 
    stm << "selfTeleport=" << info.selfTeleport << ","; 
    stm << "dstMoveTime=" << info.dstMoveTime << ","; 
    stm << "dstMoveSpeed=" << info.dstMoveSpeed << ","; 
    stm << "selfMoveTime=" << info.selfMoveTime << ","; 
    stm << "selfMoveSpeed=" << info.selfMoveSpeed << ","; 
    stm << "appendBuffs=" << info.appendBuffs << ","; 
    stm << "appendBuffsText=" << info.appendBuffsText << ","; 
    stm << "harmBuffs=" << info.harmBuffs << ","; 
    stm << "harmBuffsText=" << info.harmBuffsText << ","; 
    stm << "nextSkillID=" << info.nextSkillID << ","; 
    stm << "desc=" << info.desc << ","; 
    stm << "]"; 
    return stm; 
} 
 
#endif 

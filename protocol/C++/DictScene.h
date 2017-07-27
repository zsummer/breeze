 
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
    double attackQuick; //攻击加速  
    std::string desc;  
    DictProp() 
    { 
        id = 0; 
        hp = 0.0; 
        attack = 0.0; 
        moveSpeed = 0.0; 
        attackQuick = 0.0; 
    } 
    DictProp(const unsigned long long & id, const double & hp, const double & attack, const double & moveSpeed, const double & attackQuick, const std::string & desc) 
    { 
        this->id = id; 
        this->hp = hp; 
        this->attack = attack; 
        this->moveSpeed = moveSpeed; 
        this->attackQuick = attackQuick; 
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
    ret.push_back("alter table `tb_DictProp` add `attackQuick`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictProp` change `attackQuick`  `attackQuick`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictProp` add `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictProp` change `desc`  `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    return ret; 
} 
std::string  DictProp::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `id`,`hp`,`attack`,`moveSpeed`,`attackQuick`,`desc` from `tb_DictProp` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictProp::getDBSelectPure() 
{ 
    return "select `id`,`hp`,`attack`,`moveSpeed`,`attackQuick`,`desc` from `tb_DictProp` "; 
} 
std::string  DictProp::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictProp`(`id`,`hp`,`attack`,`moveSpeed`,`attackQuick`,`desc`) values(?,?,?,?,?,?)"); 
    q << this->id; 
    q << this->hp; 
    q << this->attack; 
    q << this->moveSpeed; 
    q << this->attackQuick; 
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
    q.init("insert into `tb_DictProp`(id) values(? ) on duplicate key update `hp` = ?,`attack` = ?,`moveSpeed` = ?,`attackQuick` = ?,`desc` = ? "); 
    q << this->id; 
    q << this->hp; 
    q << this->attack; 
    q << this->moveSpeed; 
    q << this->attackQuick; 
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
            result >> this->attackQuick; 
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
    ws << data.attackQuick;  
    ws << data.desc;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DictProp & data) 
{ 
    rs >> data.id;  
    rs >> data.hp;  
    rs >> data.attack;  
    rs >> data.moveSpeed;  
    rs >> data.attackQuick;  
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
    stm << "attackQuick=" << info.attackQuick << ","; 
    stm << "desc=" << info.desc << ","; 
    stm << "]"; 
    return stm; 
} 
 
 
typedef std::vector<DictProp> DictPropArray;  
 
 
typedef std::map<unsigned long long, DictProp> DictPropMap;  
 
enum FILTER_STAMP : unsigned long long 
{ 
    FILTER_NONE = 1, //全部  
    FILTER_SELF = 2, //自己  
    FILTER_OTHER_FRIEND = 3, //友方阵营  
    FILTER_ENEMY_CAMP = 4, //敌方阵营  
    FILTER_NEUTRAL_CAMP = 5, //中立阵营  
}; 
 
struct AOESearch 
{ 
    static const unsigned short getProtoID() { return 11001;} 
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
    unsigned long long filter;  
    std::string filterText;  
    unsigned short isRect; //0扇形, 其他矩形  
    double value1; //伤害距离  
    double value2; //弧度或者远端宽度  
    double value3; //忽略或者近端宽度  
    double compensate; //距离补偿, 一般填负数 规避视觉上的灯下黑问题  
    double clip; //可以裁剪扇形的尖角, 圆环等 矩形忽略该参数  
    unsigned long long limitEntitys; //最大目标数, 距离优先  
    AOESearch() 
    { 
        id = 0; 
        etype = 0; 
        filter = 0; 
        isRect = 0; 
        value1 = 0.0; 
        value2 = 0.0; 
        value3 = 0.0; 
        compensate = 0.0; 
        clip = 0.0; 
        limitEntitys = 0; 
    } 
    AOESearch(const unsigned long long & id, const unsigned short & etype, const unsigned long long & filter, const std::string & filterText, const unsigned short & isRect, const double & value1, const double & value2, const double & value3, const double & compensate, const double & clip, const unsigned long long & limitEntitys) 
    { 
        this->id = id; 
        this->etype = etype; 
        this->filter = filter; 
        this->filterText = filterText; 
        this->isRect = isRect; 
        this->value1 = value1; 
        this->value2 = value2; 
        this->value3 = value3; 
        this->compensate = compensate; 
        this->clip = clip; 
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
    ret.push_back("alter table `tb_AOESearch` add `filterText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_AOESearch` change `filterText`  `filterText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_AOESearch` add `isRect`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AOESearch` change `isRect`  `isRect`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AOESearch` add `value1`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AOESearch` change `value1`  `value1`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AOESearch` add `value2`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AOESearch` change `value2`  `value2`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AOESearch` add `value3`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AOESearch` change `value3`  `value3`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AOESearch` add `compensate`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AOESearch` change `compensate`  `compensate`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AOESearch` add `clip`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AOESearch` change `clip`  `clip`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AOESearch` add `limitEntitys`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_AOESearch` change `limitEntitys`  `limitEntitys`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    return ret; 
} 
std::string  AOESearch::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `id`,`etype`,`filterText`,`isRect`,`value1`,`value2`,`value3`,`compensate`,`clip`,`limitEntitys` from `tb_AOESearch` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  AOESearch::getDBSelectPure() 
{ 
    return "select `id`,`etype`,`filterText`,`isRect`,`value1`,`value2`,`value3`,`compensate`,`clip`,`limitEntitys` from `tb_AOESearch` "; 
} 
std::string  AOESearch::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_AOESearch`(`id`,`etype`,`filterText`,`isRect`,`value1`,`value2`,`value3`,`compensate`,`clip`,`limitEntitys`) values(?,?,?,?,?,?,?,?,?,?)"); 
    q << this->id; 
    q << this->etype; 
    q << this->filterText; 
    q << this->isRect; 
    q << this->value1; 
    q << this->value2; 
    q << this->value3; 
    q << this->compensate; 
    q << this->clip; 
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
    q.init("insert into `tb_AOESearch`(id) values(? ) on duplicate key update `etype` = ?,`filterText` = ?,`isRect` = ?,`value1` = ?,`value2` = ?,`value3` = ?,`compensate` = ?,`clip` = ?,`limitEntitys` = ? "); 
    q << this->id; 
    q << this->etype; 
    q << this->filterText; 
    q << this->isRect; 
    q << this->value1; 
    q << this->value2; 
    q << this->value3; 
    q << this->compensate; 
    q << this->clip; 
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
            result >> this->filterText; 
            result >> this->isRect; 
            result >> this->value1; 
            result >> this->value2; 
            result >> this->value3; 
            result >> this->compensate; 
            result >> this->clip; 
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
    ws << data.filter;  
    ws << data.filterText;  
    ws << data.isRect;  
    ws << data.value1;  
    ws << data.value2;  
    ws << data.value3;  
    ws << data.compensate;  
    ws << data.clip;  
    ws << data.limitEntitys;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, AOESearch & data) 
{ 
    rs >> data.id;  
    rs >> data.etype;  
    rs >> data.filter;  
    rs >> data.filterText;  
    rs >> data.isRect;  
    rs >> data.value1;  
    rs >> data.value2;  
    rs >> data.value3;  
    rs >> data.compensate;  
    rs >> data.clip;  
    rs >> data.limitEntitys;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const AOESearch & info) 
{ 
    stm << "["; 
    stm << "id=" << info.id << ","; 
    stm << "etype=" << info.etype << ","; 
    stm << "filter=" << info.filter << ","; 
    stm << "filterText=" << info.filterText << ","; 
    stm << "isRect=" << info.isRect << ","; 
    stm << "value1=" << info.value1 << ","; 
    stm << "value2=" << info.value2 << ","; 
    stm << "value3=" << info.value3 << ","; 
    stm << "compensate=" << info.compensate << ","; 
    stm << "clip=" << info.clip << ","; 
    stm << "limitEntitys=" << info.limitEntitys << ","; 
    stm << "]"; 
    return stm; 
} 
 
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
 
struct DictBuff 
{ 
    static const unsigned short getProtoID() { return 11002;} 
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
    unsigned long long propID; //提升的属性效果, 求积方式的参数是基础属性 不算其他装备  
    DictArrayKey skills; //触发技能  
    std::string skillsText; //触发技能 格式id,id,id   
    DictArrayKey buffs; //触发buff  
    std::string buffsText; //触发buff 格式id,id,id  
    double triggerAoeSearchID; //search结果不为空触发  
    double triggerDelay; //延迟触发, 当间隔触发不为0时生效  
    double triggerInterval; //间隔触发  
    double triggerCountLimit; //触发次数限制  
    double triggerAutoRemove; //触发后移除buff  
    double keepTime;  
    double limitStackTime; //相同buff叠加时间并且刷新触发次数  
    std::string desc;  
    DictBuff() 
    { 
        id = 0; 
        stamp = 0; 
        propID = 0; 
        triggerAoeSearchID = 0.0; 
        triggerDelay = 0.0; 
        triggerInterval = 0.0; 
        triggerCountLimit = 0.0; 
        triggerAutoRemove = 0.0; 
        keepTime = 0.0; 
        limitStackTime = 0.0; 
    } 
    DictBuff(const unsigned long long & id, const unsigned long long & stamp, const std::string & stampText, const unsigned long long & propID, const DictArrayKey & skills, const std::string & skillsText, const DictArrayKey & buffs, const std::string & buffsText, const double & triggerAoeSearchID, const double & triggerDelay, const double & triggerInterval, const double & triggerCountLimit, const double & triggerAutoRemove, const double & keepTime, const double & limitStackTime, const std::string & desc) 
    { 
        this->id = id; 
        this->stamp = stamp; 
        this->stampText = stampText; 
        this->propID = propID; 
        this->skills = skills; 
        this->skillsText = skillsText; 
        this->buffs = buffs; 
        this->buffsText = buffsText; 
        this->triggerAoeSearchID = triggerAoeSearchID; 
        this->triggerDelay = triggerDelay; 
        this->triggerInterval = triggerInterval; 
        this->triggerCountLimit = triggerCountLimit; 
        this->triggerAutoRemove = triggerAutoRemove; 
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
    ret.push_back("alter table `tb_DictBuff` add `propID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuff` change `propID`  `propID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuff` add `skillsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictBuff` change `skillsText`  `skillsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictBuff` add `buffsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictBuff` change `buffsText`  `buffsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictBuff` add `triggerAoeSearchID`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuff` change `triggerAoeSearchID`  `triggerAoeSearchID`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuff` add `triggerDelay`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuff` change `triggerDelay`  `triggerDelay`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuff` add `triggerInterval`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuff` change `triggerInterval`  `triggerInterval`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuff` add `triggerCountLimit`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuff` change `triggerCountLimit`  `triggerCountLimit`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuff` add `triggerAutoRemove`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuff` change `triggerAutoRemove`  `triggerAutoRemove`  double NOT NULL DEFAULT '0' "); 
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
    q.init("select `id`,`stampText`,`propID`,`skillsText`,`buffsText`,`triggerAoeSearchID`,`triggerDelay`,`triggerInterval`,`triggerCountLimit`,`triggerAutoRemove`,`keepTime`,`limitStackTime`,`desc` from `tb_DictBuff` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictBuff::getDBSelectPure() 
{ 
    return "select `id`,`stampText`,`propID`,`skillsText`,`buffsText`,`triggerAoeSearchID`,`triggerDelay`,`triggerInterval`,`triggerCountLimit`,`triggerAutoRemove`,`keepTime`,`limitStackTime`,`desc` from `tb_DictBuff` "; 
} 
std::string  DictBuff::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictBuff`(`id`,`stampText`,`propID`,`skillsText`,`buffsText`,`triggerAoeSearchID`,`triggerDelay`,`triggerInterval`,`triggerCountLimit`,`triggerAutoRemove`,`keepTime`,`limitStackTime`,`desc`) values(?,?,?,?,?,?,?,?,?,?,?,?,?)"); 
    q << this->id; 
    q << this->stampText; 
    q << this->propID; 
    q << this->skillsText; 
    q << this->buffsText; 
    q << this->triggerAoeSearchID; 
    q << this->triggerDelay; 
    q << this->triggerInterval; 
    q << this->triggerCountLimit; 
    q << this->triggerAutoRemove; 
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
    q.init("insert into `tb_DictBuff`(id) values(? ) on duplicate key update `stampText` = ?,`propID` = ?,`skillsText` = ?,`buffsText` = ?,`triggerAoeSearchID` = ?,`triggerDelay` = ?,`triggerInterval` = ?,`triggerCountLimit` = ?,`triggerAutoRemove` = ?,`keepTime` = ?,`limitStackTime` = ?,`desc` = ? "); 
    q << this->id; 
    q << this->stampText; 
    q << this->propID; 
    q << this->skillsText; 
    q << this->buffsText; 
    q << this->triggerAoeSearchID; 
    q << this->triggerDelay; 
    q << this->triggerInterval; 
    q << this->triggerCountLimit; 
    q << this->triggerAutoRemove; 
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
            result >> this->propID; 
            result >> this->skillsText; 
            result >> this->buffsText; 
            result >> this->triggerAoeSearchID; 
            result >> this->triggerDelay; 
            result >> this->triggerInterval; 
            result >> this->triggerCountLimit; 
            result >> this->triggerAutoRemove; 
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
    ws << data.propID;  
    ws << data.skills;  
    ws << data.skillsText;  
    ws << data.buffs;  
    ws << data.buffsText;  
    ws << data.triggerAoeSearchID;  
    ws << data.triggerDelay;  
    ws << data.triggerInterval;  
    ws << data.triggerCountLimit;  
    ws << data.triggerAutoRemove;  
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
    rs >> data.propID;  
    rs >> data.skills;  
    rs >> data.skillsText;  
    rs >> data.buffs;  
    rs >> data.buffsText;  
    rs >> data.triggerAoeSearchID;  
    rs >> data.triggerDelay;  
    rs >> data.triggerInterval;  
    rs >> data.triggerCountLimit;  
    rs >> data.triggerAutoRemove;  
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
    stm << "propID=" << info.propID << ","; 
    stm << "skills=" << info.skills << ","; 
    stm << "skillsText=" << info.skillsText << ","; 
    stm << "buffs=" << info.buffs << ","; 
    stm << "buffsText=" << info.buffsText << ","; 
    stm << "triggerAoeSearchID=" << info.triggerAoeSearchID << ","; 
    stm << "triggerDelay=" << info.triggerDelay << ","; 
    stm << "triggerInterval=" << info.triggerInterval << ","; 
    stm << "triggerCountLimit=" << info.triggerCountLimit << ","; 
    stm << "triggerAutoRemove=" << info.triggerAutoRemove << ","; 
    stm << "keepTime=" << info.keepTime << ","; 
    stm << "limitStackTime=" << info.limitStackTime << ","; 
    stm << "desc=" << info.desc << ","; 
    stm << "]"; 
    return stm; 
} 
 
enum SKILL_STAMP : unsigned long long 
{ 
    SKILL_NONE = 0,  
    SKILL_NORMAL = 1, //普攻攻击技能  
    SKILL_PASSIVE = 2, //被动技能  
    SKILL_PHYSICAL = 3, //物理伤害  
    SKILL_MAGIC = 4, //魔法伤害  
    SKILL_HARM = 5, //血量减损  
    SKILL_REGEN = 6, //血量再生  
    SKILL_ON_HIT_BREAK = 7, //可被中断  
    SKILL_ON_MOVE_BREAK = 8, //可被中断  
    SKILL_CAN_MOVE = 9, //可移动  
    SKILL_REMOVE_DEBUFF = 10, //驱散减益BUFF  
    SKILL_REMOVE_BUFF = 11, //驱散增益BUFF  
}; 
 
enum SKILL_AOS : unsigned long long 
{ 
    SKILL_LOCKED_POS = 0, //锁坐标  
    SKILL_LOCKED_VECTOR = 1, //锁方向  
    SKILL_LOCKED_ENTITY = 2, //永久锁目标  
    SKILL_LOCKED_FREE = 3, //自由锁定  
}; 
 
struct DictSkill 
{ 
    static const unsigned short getProtoID() { return 11003;} 
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
    unsigned long long aosID; //锁敌范围  
    AOESearch aosDict; //锁敌  
    unsigned short aosType; //0一次性锁坐标, 1一次性锁方向, 2永久锁目标, 3锁目标 超出范围外锁坐标  
    unsigned long long aoeID; //AOE范围  
    AOESearch aoeDict;  
    double delay;  
    double interval; //自动释放间隔,针对自动施法,被动技能有效  
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
    unsigned long long appendBuffsAreaID; //上buff的searchid  
    AOESearch appendBuffsAreaDict;  
    DictArrayKey harmBuffs;  
    std::string harmBuffsText; //触发buff 格式 k,k,k,   
    DictArrayKey combSkills;  
    std::string combSkillsText; //组合技能  
    DictArrayKey followSkills;  
    std::string followSkillsText; //跟随技能  
    std::string desc;  
    DictSkill() 
    { 
        id = 0; 
        stamp = 0; 
        aosID = 0; 
        aosType = 0; 
        aoeID = 0; 
        delay = 0.0; 
        interval = 0.0; 
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
        appendBuffsAreaID = 0; 
    } 
    DictSkill(const unsigned long long & id, const unsigned long long & stamp, const unsigned long long & aosID, const AOESearch & aosDict, const unsigned short & aosType, const unsigned long long & aoeID, const AOESearch & aoeDict, const double & delay, const double & interval, const double & keep, const double & cd, const double & hpAdd, const double & hpAddScaleRemanent, const double & hpAddScaleLost, const unsigned long long & propID, const double & dstTeleport, const double & selfTeleport, const double & dstMoveTime, const double & dstMoveSpeed, const double & selfMoveTime, const double & selfMoveSpeed, const DictArrayKey & appendBuffs, const std::string & appendBuffsText, const unsigned long long & appendBuffsAreaID, const AOESearch & appendBuffsAreaDict, const DictArrayKey & harmBuffs, const std::string & harmBuffsText, const DictArrayKey & combSkills, const std::string & combSkillsText, const DictArrayKey & followSkills, const std::string & followSkillsText, const std::string & desc) 
    { 
        this->id = id; 
        this->stamp = stamp; 
        this->aosID = aosID; 
        this->aosDict = aosDict; 
        this->aosType = aosType; 
        this->aoeID = aoeID; 
        this->aoeDict = aoeDict; 
        this->delay = delay; 
        this->interval = interval; 
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
        this->appendBuffsAreaID = appendBuffsAreaID; 
        this->appendBuffsAreaDict = appendBuffsAreaDict; 
        this->harmBuffs = harmBuffs; 
        this->harmBuffsText = harmBuffsText; 
        this->combSkills = combSkills; 
        this->combSkillsText = combSkillsText; 
        this->followSkills = followSkills; 
        this->followSkillsText = followSkillsText; 
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
    ret.push_back("alter table `tb_DictSkill` add `aosID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` change `aosID`  `aosID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` add `aosType`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` change `aosType`  `aosType`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` add `aoeID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` change `aoeID`  `aoeID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` add `delay`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` change `delay`  `delay`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` add `interval`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` change `interval`  `interval`  double NOT NULL DEFAULT '0' "); 
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
    ret.push_back("alter table `tb_DictSkill` add `appendBuffsAreaID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` change `appendBuffsAreaID`  `appendBuffsAreaID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` add `harmBuffsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictSkill` change `harmBuffsText`  `harmBuffsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictSkill` add `combSkillsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictSkill` change `combSkillsText`  `combSkillsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictSkill` add `followSkillsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictSkill` change `followSkillsText`  `followSkillsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictSkill` add `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictSkill` change `desc`  `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    return ret; 
} 
std::string  DictSkill::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `id`,`stamp`,`aosID`,`aosType`,`aoeID`,`delay`,`interval`,`keep`,`cd`,`hpAdd`,`hpAddScaleRemanent`,`hpAddScaleLost`,`propID`,`dstTeleport`,`selfTeleport`,`dstMoveTime`,`dstMoveSpeed`,`selfMoveTime`,`selfMoveSpeed`,`appendBuffsText`,`appendBuffsAreaID`,`harmBuffsText`,`combSkillsText`,`followSkillsText`,`desc` from `tb_DictSkill` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictSkill::getDBSelectPure() 
{ 
    return "select `id`,`stamp`,`aosID`,`aosType`,`aoeID`,`delay`,`interval`,`keep`,`cd`,`hpAdd`,`hpAddScaleRemanent`,`hpAddScaleLost`,`propID`,`dstTeleport`,`selfTeleport`,`dstMoveTime`,`dstMoveSpeed`,`selfMoveTime`,`selfMoveSpeed`,`appendBuffsText`,`appendBuffsAreaID`,`harmBuffsText`,`combSkillsText`,`followSkillsText`,`desc` from `tb_DictSkill` "; 
} 
std::string  DictSkill::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictSkill`(`id`,`stamp`,`aosID`,`aosType`,`aoeID`,`delay`,`interval`,`keep`,`cd`,`hpAdd`,`hpAddScaleRemanent`,`hpAddScaleLost`,`propID`,`dstTeleport`,`selfTeleport`,`dstMoveTime`,`dstMoveSpeed`,`selfMoveTime`,`selfMoveSpeed`,`appendBuffsText`,`appendBuffsAreaID`,`harmBuffsText`,`combSkillsText`,`followSkillsText`,`desc`) values(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)"); 
    q << this->id; 
    q << this->stamp; 
    q << this->aosID; 
    q << this->aosType; 
    q << this->aoeID; 
    q << this->delay; 
    q << this->interval; 
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
    q << this->appendBuffsAreaID; 
    q << this->harmBuffsText; 
    q << this->combSkillsText; 
    q << this->followSkillsText; 
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
    q.init("insert into `tb_DictSkill`(id) values(? ) on duplicate key update `stamp` = ?,`aosID` = ?,`aosType` = ?,`aoeID` = ?,`delay` = ?,`interval` = ?,`keep` = ?,`cd` = ?,`hpAdd` = ?,`hpAddScaleRemanent` = ?,`hpAddScaleLost` = ?,`propID` = ?,`dstTeleport` = ?,`selfTeleport` = ?,`dstMoveTime` = ?,`dstMoveSpeed` = ?,`selfMoveTime` = ?,`selfMoveSpeed` = ?,`appendBuffsText` = ?,`appendBuffsAreaID` = ?,`harmBuffsText` = ?,`combSkillsText` = ?,`followSkillsText` = ?,`desc` = ? "); 
    q << this->id; 
    q << this->stamp; 
    q << this->aosID; 
    q << this->aosType; 
    q << this->aoeID; 
    q << this->delay; 
    q << this->interval; 
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
    q << this->appendBuffsAreaID; 
    q << this->harmBuffsText; 
    q << this->combSkillsText; 
    q << this->followSkillsText; 
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
            result >> this->aosID; 
            result >> this->aosType; 
            result >> this->aoeID; 
            result >> this->delay; 
            result >> this->interval; 
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
            result >> this->appendBuffsAreaID; 
            result >> this->harmBuffsText; 
            result >> this->combSkillsText; 
            result >> this->followSkillsText; 
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
    ws << data.aosID;  
    ws << data.aosDict;  
    ws << data.aosType;  
    ws << data.aoeID;  
    ws << data.aoeDict;  
    ws << data.delay;  
    ws << data.interval;  
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
    ws << data.appendBuffsAreaID;  
    ws << data.appendBuffsAreaDict;  
    ws << data.harmBuffs;  
    ws << data.harmBuffsText;  
    ws << data.combSkills;  
    ws << data.combSkillsText;  
    ws << data.followSkills;  
    ws << data.followSkillsText;  
    ws << data.desc;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DictSkill & data) 
{ 
    rs >> data.id;  
    rs >> data.stamp;  
    rs >> data.aosID;  
    rs >> data.aosDict;  
    rs >> data.aosType;  
    rs >> data.aoeID;  
    rs >> data.aoeDict;  
    rs >> data.delay;  
    rs >> data.interval;  
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
    rs >> data.appendBuffsAreaID;  
    rs >> data.appendBuffsAreaDict;  
    rs >> data.harmBuffs;  
    rs >> data.harmBuffsText;  
    rs >> data.combSkills;  
    rs >> data.combSkillsText;  
    rs >> data.followSkills;  
    rs >> data.followSkillsText;  
    rs >> data.desc;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DictSkill & info) 
{ 
    stm << "["; 
    stm << "id=" << info.id << ","; 
    stm << "stamp=" << info.stamp << ","; 
    stm << "aosID=" << info.aosID << ","; 
    stm << "aosDict=" << info.aosDict << ","; 
    stm << "aosType=" << info.aosType << ","; 
    stm << "aoeID=" << info.aoeID << ","; 
    stm << "aoeDict=" << info.aoeDict << ","; 
    stm << "delay=" << info.delay << ","; 
    stm << "interval=" << info.interval << ","; 
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
    stm << "appendBuffsAreaID=" << info.appendBuffsAreaID << ","; 
    stm << "appendBuffsAreaDict=" << info.appendBuffsAreaDict << ","; 
    stm << "harmBuffs=" << info.harmBuffs << ","; 
    stm << "harmBuffsText=" << info.harmBuffsText << ","; 
    stm << "combSkills=" << info.combSkills << ","; 
    stm << "combSkillsText=" << info.combSkillsText << ","; 
    stm << "followSkills=" << info.followSkills << ","; 
    stm << "followSkillsText=" << info.followSkillsText << ","; 
    stm << "desc=" << info.desc << ","; 
    stm << "]"; 
    return stm; 
} 
 
#endif 

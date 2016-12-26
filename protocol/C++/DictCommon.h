 
#ifndef _DICTCOMMON_H_ 
#define _DICTCOMMON_H_ 
 
 
struct DictGlobal //全局配置  
{ 
    static const unsigned short getProtoID() { return 10000;} 
    static const std::string getProtoName() { return "DictGlobal";} 
    inline std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned long long id;  
    unsigned long long val; //整数  
    double valFloat; //浮点数  
    std::string combo; //字符串  
    std::string desc;  
    DictGlobal() 
    { 
        id = 0; 
        val = 0; 
        valFloat = 0.0; 
    } 
    DictGlobal(const unsigned long long & id, const unsigned long long & val, const double & valFloat, const std::string & combo, const std::string & desc) 
    { 
        this->id = id; 
        this->val = val; 
        this->valFloat = valFloat; 
        this->combo = combo; 
        this->desc = desc; 
    } 
}; 
 
std::vector<std::string>  DictGlobal::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_DictGlobal` (        `id` bigint(20) unsigned NOT NULL DEFAULT '0' ,        PRIMARY KEY(`id`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_DictGlobal` add `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictGlobal` change `id`  `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictGlobal` add `val`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictGlobal` change `val`  `val`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictGlobal` add `valFloat`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictGlobal` change `valFloat`  `valFloat`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictGlobal` add `combo`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictGlobal` change `combo`  `combo`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictGlobal` add `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictGlobal` change `desc`  `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    return ret; 
} 
std::string  DictGlobal::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `id`,`val`,`valFloat`,`combo`,`desc` from `tb_DictGlobal` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictGlobal::getDBSelectPure() 
{ 
    return "select `id`,`val`,`valFloat`,`combo`,`desc` from `tb_DictGlobal` "; 
} 
std::string  DictGlobal::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictGlobal`(`id`,`val`,`valFloat`,`combo`,`desc`) values(?,?,?,?,?)"); 
    q << this->id; 
    q << this->val; 
    q << this->valFloat; 
    q << this->combo; 
    q << this->desc; 
    return q.pickSQL(); 
} 
std::string  DictGlobal::getDBDelete() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("delete from `tb_DictGlobal` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictGlobal::getDBUpdate() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictGlobal`(id) values(? ) on duplicate key update `val` = ?,`valFloat` = ?,`combo` = ?,`desc` = ? "); 
    q << this->id; 
    q << this->val; 
    q << this->valFloat; 
    q << this->combo; 
    q << this->desc; 
    return q.pickSQL(); 
} 
bool DictGlobal::fetchFromDBResult(zsummer::mysql::DBResult &result) 
{ 
    if (result.getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("error fetch DictGlobal from table `tb_DictGlobal` . ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    try 
    { 
        if (result.haveRow()) 
        { 
            result >> this->id; 
            result >> this->val; 
            result >> this->valFloat; 
            result >> this->combo; 
            result >> this->desc; 
            return true;  
        } 
    } 
    catch(const std::exception & e) 
    { 
        LOGE("catch one except error when fetch DictGlobal from table `tb_DictGlobal` . what=" << e.what() << "  ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    return false; 
} 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const DictGlobal & data) 
{ 
    ws << data.id;  
    ws << data.val;  
    ws << data.valFloat;  
    ws << data.combo;  
    ws << data.desc;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DictGlobal & data) 
{ 
    rs >> data.id;  
    rs >> data.val;  
    rs >> data.valFloat;  
    rs >> data.combo;  
    rs >> data.desc;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DictGlobal & info) 
{ 
    stm << "["; 
    stm << "id=" << info.id << ","; 
    stm << "val=" << info.val << ","; 
    stm << "valFloat=" << info.valFloat << ","; 
    stm << "combo=" << info.combo << ","; 
    stm << "desc=" << info.desc << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct DictReward //奖品  
{ 
    static const unsigned short getProtoID() { return 10007;} 
    static const std::string getProtoName() { return "DictReward";} 
    unsigned long long id; //奖品ID  
    unsigned long long count; //数量  
    double probability; //概率[0~1], 0为永远无法随机到 1是100%随机到  
    DictReward() 
    { 
        id = 0; 
        count = 0; 
        probability = 0.0; 
    } 
    DictReward(const unsigned long long & id, const unsigned long long & count, const double & probability) 
    { 
        this->id = id; 
        this->count = count; 
        this->probability = probability; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const DictReward & data) 
{ 
    ws << data.id;  
    ws << data.count;  
    ws << data.probability;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DictReward & data) 
{ 
    rs >> data.id;  
    rs >> data.count;  
    rs >> data.probability;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DictReward & info) 
{ 
    stm << "["; 
    stm << "id=" << info.id << ","; 
    stm << "count=" << info.count << ","; 
    stm << "probability=" << info.probability << ","; 
    stm << "]"; 
    return stm; 
} 
 
 
typedef std::vector<DictReward> DictRewardArray;  
 
struct DictDrop //道具抽奖,道具掉落  
{ 
    static const unsigned short getProtoID() { return 10008;} 
    static const std::string getProtoName() { return "DictDrop";} 
    inline std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned long long id;  
    unsigned long long dropType; //0 独立随机, 所有奖品根据自身概率随机,  1 从奖池中抽取一个奖品, 如果所有奖品概率总和小于1则可能什么都抽取不到  
    DictRewardArray rewards; //奖池  
    std::string rewardsString; //奖池,为填写方便,暂时用id|weight|prob, 格式的字符串填写, 服务器load后手动解析成RaffleAwardArray格式  
    DictDrop() 
    { 
        id = 0; 
        dropType = 0; 
    } 
    DictDrop(const unsigned long long & id, const unsigned long long & dropType, const DictRewardArray & rewards, const std::string & rewardsString) 
    { 
        this->id = id; 
        this->dropType = dropType; 
        this->rewards = rewards; 
        this->rewardsString = rewardsString; 
    } 
}; 
 
std::vector<std::string>  DictDrop::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_DictDrop` (        `id` bigint(20) unsigned NOT NULL DEFAULT '0' ,        PRIMARY KEY(`id`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_DictDrop` add `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictDrop` change `id`  `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictDrop` add `dropType`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictDrop` change `dropType`  `dropType`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictDrop` add `rewardsString`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictDrop` change `rewardsString`  `rewardsString`  varchar(255) NOT NULL DEFAULT '' "); 
    return ret; 
} 
std::string  DictDrop::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `id`,`dropType`,`rewardsString` from `tb_DictDrop` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictDrop::getDBSelectPure() 
{ 
    return "select `id`,`dropType`,`rewardsString` from `tb_DictDrop` "; 
} 
std::string  DictDrop::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictDrop`(`id`,`dropType`,`rewardsString`) values(?,?,?)"); 
    q << this->id; 
    q << this->dropType; 
    q << this->rewardsString; 
    return q.pickSQL(); 
} 
std::string  DictDrop::getDBDelete() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("delete from `tb_DictDrop` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictDrop::getDBUpdate() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictDrop`(id) values(? ) on duplicate key update `dropType` = ?,`rewardsString` = ? "); 
    q << this->id; 
    q << this->dropType; 
    q << this->rewardsString; 
    return q.pickSQL(); 
} 
bool DictDrop::fetchFromDBResult(zsummer::mysql::DBResult &result) 
{ 
    if (result.getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("error fetch DictDrop from table `tb_DictDrop` . ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    try 
    { 
        if (result.haveRow()) 
        { 
            result >> this->id; 
            result >> this->dropType; 
            result >> this->rewardsString; 
            return true;  
        } 
    } 
    catch(const std::exception & e) 
    { 
        LOGE("catch one except error when fetch DictDrop from table `tb_DictDrop` . what=" << e.what() << "  ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    return false; 
} 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const DictDrop & data) 
{ 
    ws << data.id;  
    ws << data.dropType;  
    ws << data.rewards;  
    ws << data.rewardsString;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DictDrop & data) 
{ 
    rs >> data.id;  
    rs >> data.dropType;  
    rs >> data.rewards;  
    rs >> data.rewardsString;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DictDrop & info) 
{ 
    stm << "["; 
    stm << "id=" << info.id << ","; 
    stm << "dropType=" << info.dropType << ","; 
    stm << "rewards=" << info.rewards << ","; 
    stm << "rewardsString=" << info.rewardsString << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct DictItem //道具字典  
{ 
    static const unsigned short getProtoID() { return 10003;} 
    static const std::string getProtoName() { return "DictItem";} 
    inline std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned long long id;  
    unsigned short visible; //是否可见  
    unsigned short icon;  
    unsigned short stacks; //可堆叠个数,0和1都是1次  
    unsigned short autoUse; //0 不可使用, 1 可使用, 2 获得后自动使用  
    unsigned long long dropID;  
    unsigned long long propID;  
    unsigned short vocationLimit; //限制职业类型, 装备类型  
    double levelLimit; //限制职业最小等级, 装备类型  
    std::string desc;  
    DictItem() 
    { 
        id = 0; 
        visible = 0; 
        icon = 0; 
        stacks = 0; 
        autoUse = 0; 
        dropID = 0; 
        propID = 0; 
        vocationLimit = 0; 
        levelLimit = 0.0; 
    } 
    DictItem(const unsigned long long & id, const unsigned short & visible, const unsigned short & icon, const unsigned short & stacks, const unsigned short & autoUse, const unsigned long long & dropID, const unsigned long long & propID, const unsigned short & vocationLimit, const double & levelLimit, const std::string & desc) 
    { 
        this->id = id; 
        this->visible = visible; 
        this->icon = icon; 
        this->stacks = stacks; 
        this->autoUse = autoUse; 
        this->dropID = dropID; 
        this->propID = propID; 
        this->vocationLimit = vocationLimit; 
        this->levelLimit = levelLimit; 
        this->desc = desc; 
    } 
}; 
 
std::vector<std::string>  DictItem::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_DictItem` (        `id` bigint(20) unsigned NOT NULL DEFAULT '0' ,        PRIMARY KEY(`id`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_DictItem` add `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` change `id`  `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` add `visible`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` change `visible`  `visible`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` add `icon`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` change `icon`  `icon`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` add `stacks`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` change `stacks`  `stacks`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` add `autoUse`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` change `autoUse`  `autoUse`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` add `dropID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` change `dropID`  `dropID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` add `propID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` change `propID`  `propID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` add `vocationLimit`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` change `vocationLimit`  `vocationLimit`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` add `levelLimit`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` change `levelLimit`  `levelLimit`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` add `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictItem` change `desc`  `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    return ret; 
} 
std::string  DictItem::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `id`,`visible`,`icon`,`stacks`,`autoUse`,`dropID`,`propID`,`vocationLimit`,`levelLimit`,`desc` from `tb_DictItem` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictItem::getDBSelectPure() 
{ 
    return "select `id`,`visible`,`icon`,`stacks`,`autoUse`,`dropID`,`propID`,`vocationLimit`,`levelLimit`,`desc` from `tb_DictItem` "; 
} 
std::string  DictItem::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictItem`(`id`,`visible`,`icon`,`stacks`,`autoUse`,`dropID`,`propID`,`vocationLimit`,`levelLimit`,`desc`) values(?,?,?,?,?,?,?,?,?,?)"); 
    q << this->id; 
    q << this->visible; 
    q << this->icon; 
    q << this->stacks; 
    q << this->autoUse; 
    q << this->dropID; 
    q << this->propID; 
    q << this->vocationLimit; 
    q << this->levelLimit; 
    q << this->desc; 
    return q.pickSQL(); 
} 
std::string  DictItem::getDBDelete() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("delete from `tb_DictItem` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictItem::getDBUpdate() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictItem`(id) values(? ) on duplicate key update `visible` = ?,`icon` = ?,`stacks` = ?,`autoUse` = ?,`dropID` = ?,`propID` = ?,`vocationLimit` = ?,`levelLimit` = ?,`desc` = ? "); 
    q << this->id; 
    q << this->visible; 
    q << this->icon; 
    q << this->stacks; 
    q << this->autoUse; 
    q << this->dropID; 
    q << this->propID; 
    q << this->vocationLimit; 
    q << this->levelLimit; 
    q << this->desc; 
    return q.pickSQL(); 
} 
bool DictItem::fetchFromDBResult(zsummer::mysql::DBResult &result) 
{ 
    if (result.getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("error fetch DictItem from table `tb_DictItem` . ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    try 
    { 
        if (result.haveRow()) 
        { 
            result >> this->id; 
            result >> this->visible; 
            result >> this->icon; 
            result >> this->stacks; 
            result >> this->autoUse; 
            result >> this->dropID; 
            result >> this->propID; 
            result >> this->vocationLimit; 
            result >> this->levelLimit; 
            result >> this->desc; 
            return true;  
        } 
    } 
    catch(const std::exception & e) 
    { 
        LOGE("catch one except error when fetch DictItem from table `tb_DictItem` . what=" << e.what() << "  ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    return false; 
} 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const DictItem & data) 
{ 
    ws << data.id;  
    ws << data.visible;  
    ws << data.icon;  
    ws << data.stacks;  
    ws << data.autoUse;  
    ws << data.dropID;  
    ws << data.propID;  
    ws << data.vocationLimit;  
    ws << data.levelLimit;  
    ws << data.desc;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DictItem & data) 
{ 
    rs >> data.id;  
    rs >> data.visible;  
    rs >> data.icon;  
    rs >> data.stacks;  
    rs >> data.autoUse;  
    rs >> data.dropID;  
    rs >> data.propID;  
    rs >> data.vocationLimit;  
    rs >> data.levelLimit;  
    rs >> data.desc;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DictItem & info) 
{ 
    stm << "["; 
    stm << "id=" << info.id << ","; 
    stm << "visible=" << info.visible << ","; 
    stm << "icon=" << info.icon << ","; 
    stm << "stacks=" << info.stacks << ","; 
    stm << "autoUse=" << info.autoUse << ","; 
    stm << "dropID=" << info.dropID << ","; 
    stm << "propID=" << info.propID << ","; 
    stm << "vocationLimit=" << info.vocationLimit << ","; 
    stm << "levelLimit=" << info.levelLimit << ","; 
    stm << "desc=" << info.desc << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct DictProp 
{ 
    static const unsigned short getProtoID() { return 10004;} 
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
    double hpRegen; //每秒血量值恢复  
    double attack; //伤害  
    double defense; //防御  
    double crit; //暴击  
    double toughness; //韧性  
    double moveSpeed; //移动速度  
    double attackSpeed; //攻击速度  
    double vampirk; //吸血  
    DictProp() 
    { 
        id = 0; 
        hp = 0.0; 
        hpRegen = 0.0; 
        attack = 0.0; 
        defense = 0.0; 
        crit = 0.0; 
        toughness = 0.0; 
        moveSpeed = 0.0; 
        attackSpeed = 0.0; 
        vampirk = 0.0; 
    } 
    DictProp(const unsigned long long & id, const double & hp, const double & hpRegen, const double & attack, const double & defense, const double & crit, const double & toughness, const double & moveSpeed, const double & attackSpeed, const double & vampirk) 
    { 
        this->id = id; 
        this->hp = hp; 
        this->hpRegen = hpRegen; 
        this->attack = attack; 
        this->defense = defense; 
        this->crit = crit; 
        this->toughness = toughness; 
        this->moveSpeed = moveSpeed; 
        this->attackSpeed = attackSpeed; 
        this->vampirk = vampirk; 
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
    ret.push_back("alter table `tb_DictProp` add `hpRegen`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictProp` change `hpRegen`  `hpRegen`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictProp` add `attack`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictProp` change `attack`  `attack`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictProp` add `defense`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictProp` change `defense`  `defense`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictProp` add `crit`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictProp` change `crit`  `crit`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictProp` add `toughness`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictProp` change `toughness`  `toughness`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictProp` add `moveSpeed`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictProp` change `moveSpeed`  `moveSpeed`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictProp` add `attackSpeed`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictProp` change `attackSpeed`  `attackSpeed`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictProp` add `vampirk`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictProp` change `vampirk`  `vampirk`  double NOT NULL DEFAULT '0' "); 
    return ret; 
} 
std::string  DictProp::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `id`,`hp`,`hpRegen`,`attack`,`defense`,`crit`,`toughness`,`moveSpeed`,`attackSpeed`,`vampirk` from `tb_DictProp` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictProp::getDBSelectPure() 
{ 
    return "select `id`,`hp`,`hpRegen`,`attack`,`defense`,`crit`,`toughness`,`moveSpeed`,`attackSpeed`,`vampirk` from `tb_DictProp` "; 
} 
std::string  DictProp::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictProp`(`id`,`hp`,`hpRegen`,`attack`,`defense`,`crit`,`toughness`,`moveSpeed`,`attackSpeed`,`vampirk`) values(?,?,?,?,?,?,?,?,?,?)"); 
    q << this->id; 
    q << this->hp; 
    q << this->hpRegen; 
    q << this->attack; 
    q << this->defense; 
    q << this->crit; 
    q << this->toughness; 
    q << this->moveSpeed; 
    q << this->attackSpeed; 
    q << this->vampirk; 
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
    q.init("insert into `tb_DictProp`(id) values(? ) on duplicate key update `hp` = ?,`hpRegen` = ?,`attack` = ?,`defense` = ?,`crit` = ?,`toughness` = ?,`moveSpeed` = ?,`attackSpeed` = ?,`vampirk` = ? "); 
    q << this->id; 
    q << this->hp; 
    q << this->hpRegen; 
    q << this->attack; 
    q << this->defense; 
    q << this->crit; 
    q << this->toughness; 
    q << this->moveSpeed; 
    q << this->attackSpeed; 
    q << this->vampirk; 
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
            result >> this->hpRegen; 
            result >> this->attack; 
            result >> this->defense; 
            result >> this->crit; 
            result >> this->toughness; 
            result >> this->moveSpeed; 
            result >> this->attackSpeed; 
            result >> this->vampirk; 
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
    ws << data.hpRegen;  
    ws << data.attack;  
    ws << data.defense;  
    ws << data.crit;  
    ws << data.toughness;  
    ws << data.moveSpeed;  
    ws << data.attackSpeed;  
    ws << data.vampirk;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DictProp & data) 
{ 
    rs >> data.id;  
    rs >> data.hp;  
    rs >> data.hpRegen;  
    rs >> data.attack;  
    rs >> data.defense;  
    rs >> data.crit;  
    rs >> data.toughness;  
    rs >> data.moveSpeed;  
    rs >> data.attackSpeed;  
    rs >> data.vampirk;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DictProp & info) 
{ 
    stm << "["; 
    stm << "id=" << info.id << ","; 
    stm << "hp=" << info.hp << ","; 
    stm << "hpRegen=" << info.hpRegen << ","; 
    stm << "attack=" << info.attack << ","; 
    stm << "defense=" << info.defense << ","; 
    stm << "crit=" << info.crit << ","; 
    stm << "toughness=" << info.toughness << ","; 
    stm << "moveSpeed=" << info.moveSpeed << ","; 
    stm << "attackSpeed=" << info.attackSpeed << ","; 
    stm << "vampirk=" << info.vampirk << ","; 
    stm << "]"; 
    return stm; 
} 
 
 
typedef std::vector<DictProp> DictPropArray;  
 
 
typedef std::map<unsigned long long, DictProp> DictPropMap;  
 
struct DictSceneUpLevel 
{ 
    static const unsigned short getProtoID() { return 10005;} 
    static const std::string getProtoName() { return "DictSceneUpLevel";} 
    inline std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned long long id;  
    unsigned long long nextID; //下一等级的ID  
    unsigned long long propID; //对应的prop数值  
    double upExp; //升级所需经验  
    DictSceneUpLevel() 
    { 
        id = 0; 
        nextID = 0; 
        propID = 0; 
        upExp = 0.0; 
    } 
    DictSceneUpLevel(const unsigned long long & id, const unsigned long long & nextID, const unsigned long long & propID, const double & upExp) 
    { 
        this->id = id; 
        this->nextID = nextID; 
        this->propID = propID; 
        this->upExp = upExp; 
    } 
}; 
 
std::vector<std::string>  DictSceneUpLevel::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_DictSceneUpLevel` (        `id` bigint(20) unsigned NOT NULL DEFAULT '0' ,        PRIMARY KEY(`id`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_DictSceneUpLevel` add `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSceneUpLevel` change `id`  `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSceneUpLevel` add `nextID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSceneUpLevel` change `nextID`  `nextID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSceneUpLevel` add `propID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSceneUpLevel` change `propID`  `propID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSceneUpLevel` add `upExp`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSceneUpLevel` change `upExp`  `upExp`  double NOT NULL DEFAULT '0' "); 
    return ret; 
} 
std::string  DictSceneUpLevel::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `id`,`nextID`,`propID`,`upExp` from `tb_DictSceneUpLevel` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictSceneUpLevel::getDBSelectPure() 
{ 
    return "select `id`,`nextID`,`propID`,`upExp` from `tb_DictSceneUpLevel` "; 
} 
std::string  DictSceneUpLevel::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictSceneUpLevel`(`id`,`nextID`,`propID`,`upExp`) values(?,?,?,?)"); 
    q << this->id; 
    q << this->nextID; 
    q << this->propID; 
    q << this->upExp; 
    return q.pickSQL(); 
} 
std::string  DictSceneUpLevel::getDBDelete() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("delete from `tb_DictSceneUpLevel` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictSceneUpLevel::getDBUpdate() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictSceneUpLevel`(id) values(? ) on duplicate key update `nextID` = ?,`propID` = ?,`upExp` = ? "); 
    q << this->id; 
    q << this->nextID; 
    q << this->propID; 
    q << this->upExp; 
    return q.pickSQL(); 
} 
bool DictSceneUpLevel::fetchFromDBResult(zsummer::mysql::DBResult &result) 
{ 
    if (result.getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("error fetch DictSceneUpLevel from table `tb_DictSceneUpLevel` . ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    try 
    { 
        if (result.haveRow()) 
        { 
            result >> this->id; 
            result >> this->nextID; 
            result >> this->propID; 
            result >> this->upExp; 
            return true;  
        } 
    } 
    catch(const std::exception & e) 
    { 
        LOGE("catch one except error when fetch DictSceneUpLevel from table `tb_DictSceneUpLevel` . what=" << e.what() << "  ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    return false; 
} 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const DictSceneUpLevel & data) 
{ 
    ws << data.id;  
    ws << data.nextID;  
    ws << data.propID;  
    ws << data.upExp;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DictSceneUpLevel & data) 
{ 
    rs >> data.id;  
    rs >> data.nextID;  
    rs >> data.propID;  
    rs >> data.upExp;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DictSceneUpLevel & info) 
{ 
    stm << "["; 
    stm << "id=" << info.id << ","; 
    stm << "nextID=" << info.nextID << ","; 
    stm << "propID=" << info.propID << ","; 
    stm << "upExp=" << info.upExp << ","; 
    stm << "]"; 
    return stm; 
} 
 
 
typedef std::vector<DictSceneUpLevel> DictSceneUpLevelArray;  
 
 
typedef std::map<unsigned long long, DictSceneUpLevel> DictSceneUpLevelMap;  
 
struct DictModel 
{ 
    static const unsigned short getProtoID() { return 10006;} 
    static const std::string getProtoName() { return "DictModel";} 
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
    DictModel() 
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
    DictModel(const unsigned long long & eid, const unsigned long long & modelID, const std::string & modelName, const unsigned long long & avatarID, const std::string & avatarName, const unsigned long long & iconID, const double & level, const double & exp, const double & gold, const unsigned short & camp, const unsigned short & etype, const unsigned short & state) 
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
 
std::vector<std::string>  DictModel::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_DictModel` (        `modelID` bigint(20) unsigned NOT NULL DEFAULT '0' ,        PRIMARY KEY(`modelID`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_DictModel` add `eid`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModel` change `eid`  `eid`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModel` add `modelID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModel` change `modelID`  `modelID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModel` add `modelName`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictModel` change `modelName`  `modelName`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictModel` add `avatarID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModel` change `avatarID`  `avatarID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModel` add `avatarName`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictModel` change `avatarName`  `avatarName`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictModel` add `iconID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModel` change `iconID`  `iconID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModel` add `level`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModel` change `level`  `level`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModel` add `exp`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModel` change `exp`  `exp`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModel` add `gold`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModel` change `gold`  `gold`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModel` add `camp`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModel` change `camp`  `camp`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModel` add `etype`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModel` change `etype`  `etype`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModel` add `state`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModel` change `state`  `state`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    return ret; 
} 
std::string  DictModel::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `eid`,`modelID`,`modelName`,`avatarID`,`avatarName`,`iconID`,`level`,`exp`,`gold`,`camp`,`etype`,`state` from `tb_DictModel` where `modelID` = ? "); 
    q << this->modelID; 
    return q.pickSQL(); 
} 
std::string  DictModel::getDBSelectPure() 
{ 
    return "select `eid`,`modelID`,`modelName`,`avatarID`,`avatarName`,`iconID`,`level`,`exp`,`gold`,`camp`,`etype`,`state` from `tb_DictModel` "; 
} 
std::string  DictModel::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictModel`(`eid`,`modelID`,`modelName`,`avatarID`,`avatarName`,`iconID`,`level`,`exp`,`gold`,`camp`,`etype`,`state`) values(?,?,?,?,?,?,?,?,?,?,?,?)"); 
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
std::string  DictModel::getDBDelete() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("delete from `tb_DictModel` where `modelID` = ? "); 
    q << this->modelID; 
    return q.pickSQL(); 
} 
std::string  DictModel::getDBUpdate() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictModel`(modelID) values(? ) on duplicate key update `eid` = ?,`modelName` = ?,`avatarID` = ?,`avatarName` = ?,`iconID` = ?,`level` = ?,`exp` = ?,`gold` = ?,`camp` = ?,`etype` = ?,`state` = ? "); 
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
bool DictModel::fetchFromDBResult(zsummer::mysql::DBResult &result) 
{ 
    if (result.getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("error fetch DictModel from table `tb_DictModel` . ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
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
        LOGE("catch one except error when fetch DictModel from table `tb_DictModel` . what=" << e.what() << "  ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    return false; 
} 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const DictModel & data) 
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
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DictModel & data) 
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
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DictModel & info) 
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
 
 
typedef std::vector<DictModel> DictModelArray;  
 
 
typedef std::map<unsigned long long, DictModel> DictModelMap;  
 
#endif 

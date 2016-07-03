 
#ifndef _PROTODICT_H_ 
#define _PROTODICT_H_ 
 
 
struct DictGlobal //全局配置  
{ 
    static const unsigned short getProtoID() { return 10000;} 
    static const std::string getProtoName() { return "DictGlobal";} 
    inline const std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned int id;  
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
    DictGlobal(const unsigned int & id, const unsigned long long & val, const double & valFloat, const std::string & combo, const std::string & desc) 
    { 
        this->id = id; 
        this->val = val; 
        this->valFloat = valFloat; 
        this->combo = combo; 
        this->desc = desc; 
    } 
}; 
 
const std::vector<std::string>  DictGlobal::getDBBuild() 
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
    return std::move(ret); 
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
    stm << "[\n"; 
    stm << "id=" << info.id << "\n"; 
    stm << "val=" << info.val << "\n"; 
    stm << "valFloat=" << info.valFloat << "\n"; 
    stm << "combo=" << info.combo << "\n"; 
    stm << "desc=" << info.desc << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct RaffleAward //奖池中的奖品  
{ 
    static const unsigned short getProtoID() { return 10004;} 
    static const std::string getProtoName() { return "RaffleAward";} 
    inline const std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned int id; //奖品ID  
    unsigned int weight; //本奖品在奖池中的权重, 总权重在[10000~30000]之间的随机效果最好  
    double probability; //[0~1]独立随机的概率,0为永远无法随机到 1是100%随机到  
    RaffleAward() 
    { 
        id = 0; 
        weight = 0; 
        probability = 0.0; 
    } 
    RaffleAward(const unsigned int & id, const unsigned int & weight, const double & probability) 
    { 
        this->id = id; 
        this->weight = weight; 
        this->probability = probability; 
    } 
}; 
 
const std::vector<std::string>  RaffleAward::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_RaffleAward` (        `id` bigint(20) unsigned NOT NULL DEFAULT '0' ,        PRIMARY KEY(`id`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_RaffleAward` add `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_RaffleAward` change `id`  `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_RaffleAward` add `weight`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_RaffleAward` change `weight`  `weight`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_RaffleAward` add `probability`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_RaffleAward` change `probability`  `probability`  double NOT NULL DEFAULT '0' "); 
    return std::move(ret); 
} 
std::string  RaffleAward::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `id`,`weight`,`probability` from `tb_RaffleAward` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  RaffleAward::getDBSelectPure() 
{ 
    return "select `id`,`weight`,`probability` from `tb_RaffleAward` "; 
} 
std::string  RaffleAward::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_RaffleAward`(`id`,`weight`,`probability`) values(?,?,?)"); 
    q << this->id; 
    q << this->weight; 
    q << this->probability; 
    return q.pickSQL(); 
} 
std::string  RaffleAward::getDBDelete() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("delete from `tb_RaffleAward` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  RaffleAward::getDBUpdate() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_RaffleAward`(id) values(? ) on duplicate key update `weight` = ?,`probability` = ? "); 
    q << this->id; 
    q << this->weight; 
    q << this->probability; 
    return q.pickSQL(); 
} 
bool RaffleAward::fetchFromDBResult(zsummer::mysql::DBResult &result) 
{ 
    if (result.getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("error fetch RaffleAward from table `tb_RaffleAward` . ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    try 
    { 
        if (result.haveRow()) 
        { 
            result >> this->id; 
            result >> this->weight; 
            result >> this->probability; 
            return true;  
        } 
    } 
    catch(const std::exception & e) 
    { 
        LOGE("catch one except error when fetch RaffleAward from table `tb_RaffleAward` . what=" << e.what() << "  ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    return false; 
} 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const RaffleAward & data) 
{ 
    ws << data.id;  
    ws << data.weight;  
    ws << data.probability;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, RaffleAward & data) 
{ 
    rs >> data.id;  
    rs >> data.weight;  
    rs >> data.probability;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const RaffleAward & info) 
{ 
    stm << "[\n"; 
    stm << "id=" << info.id << "\n"; 
    stm << "weight=" << info.weight << "\n"; 
    stm << "probability=" << info.probability << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
 
typedef std::vector<RaffleAward> RaffleAwardArray;  
 
struct DictRafflePool //道具抽奖,道具掉落  
{ 
    static const unsigned short getProtoID() { return 10001;} 
    static const std::string getProtoName() { return "DictRafflePool";} 
    inline const std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned int id;  
    int raffleCount; //批量抽取次数  
    RaffleAwardArray pool; //奖池  
    std::string poolString; //奖池,为填写方便,暂时用id|weight|prob, 格式的字符串填写, 服务器load后手动解析成RaffleAwardArray格式  
    DictRafflePool() 
    { 
        id = 0; 
        raffleCount = 0; 
    } 
    DictRafflePool(const unsigned int & id, const int & raffleCount, const RaffleAwardArray & pool, const std::string & poolString) 
    { 
        this->id = id; 
        this->raffleCount = raffleCount; 
        this->pool = pool; 
        this->poolString = poolString; 
    } 
}; 
 
const std::vector<std::string>  DictRafflePool::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_DictRafflePool` (        `id` bigint(20) unsigned NOT NULL DEFAULT '0' ,        PRIMARY KEY(`id`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_DictRafflePool` add `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictRafflePool` change `id`  `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictRafflePool` add `raffleCount`  bigint(20) NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictRafflePool` change `raffleCount`  `raffleCount`  bigint(20) NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictRafflePool` add `pool`  longblob NOT NULL "); 
    ret.push_back("alter table `tb_DictRafflePool` change `pool`  `pool`  longblob NOT NULL "); 
    ret.push_back("alter table `tb_DictRafflePool` add `poolString`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictRafflePool` change `poolString`  `poolString`  varchar(255) NOT NULL DEFAULT '' "); 
    return std::move(ret); 
} 
std::string  DictRafflePool::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `id`,`raffleCount`,`pool`,`poolString` from `tb_DictRafflePool` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictRafflePool::getDBSelectPure() 
{ 
    return "select `id`,`raffleCount`,`pool`,`poolString` from `tb_DictRafflePool` "; 
} 
std::string  DictRafflePool::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictRafflePool`(`id`,`raffleCount`,`pool`,`poolString`) values(?,?,?,?)"); 
    q << this->id; 
    q << this->raffleCount; 
    try 
    { 
        zsummer::proto4z::WriteStream ws(0); 
        ws <<  this->pool; 
        q.add(ws.getStreamBody(), ws.getStreamBodyLen()); 
    } 
    catch(const std::exception & e) 
    { 
        LOGW("catch one except error when insert DictRafflePool.pool error=" << e.what()); 
    } 
    q << this->poolString; 
    return q.pickSQL(); 
} 
std::string  DictRafflePool::getDBDelete() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("delete from `tb_DictRafflePool` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictRafflePool::getDBUpdate() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictRafflePool`(id) values(? ) on duplicate key update `raffleCount` = ?,`pool` = ?,`poolString` = ? "); 
    q << this->id; 
    q << this->raffleCount; 
    try 
    { 
        zsummer::proto4z::WriteStream ws(0); 
        ws <<  this->pool; 
        q.add(ws.getStreamBody(), ws.getStreamBodyLen()); 
    } 
    catch(const std::exception & e) 
    { 
        LOGW("catch one except error when update DictRafflePool.pool error=" << e.what()); 
    } 
    q << this->poolString; 
    return q.pickSQL(); 
} 
bool DictRafflePool::fetchFromDBResult(zsummer::mysql::DBResult &result) 
{ 
    if (result.getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("error fetch DictRafflePool from table `tb_DictRafflePool` . ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    try 
    { 
        if (result.haveRow()) 
        { 
            result >> this->id; 
            result >> this->raffleCount; 
            try 
            { 
                std::string blob; 
                result >> blob; 
                if(!blob.empty()) 
                { 
                    zsummer::proto4z::ReadStream rs(blob.c_str(), (zsummer::proto4z::Integer)blob.length(), false); 
                    rs >> this->pool; 
                } 
            } 
            catch(const std::exception & e) 
            { 
                LOGW("catch one except error when fetch DictRafflePool.pool  from table `tb_DictRafflePool` . what=" << e.what() << "  ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
            } 
            result >> this->poolString; 
            return true;  
        } 
    } 
    catch(const std::exception & e) 
    { 
        LOGE("catch one except error when fetch DictRafflePool from table `tb_DictRafflePool` . what=" << e.what() << "  ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    return false; 
} 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const DictRafflePool & data) 
{ 
    ws << data.id;  
    ws << data.raffleCount;  
    ws << data.pool;  
    ws << data.poolString;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DictRafflePool & data) 
{ 
    rs >> data.id;  
    rs >> data.raffleCount;  
    rs >> data.pool;  
    rs >> data.poolString;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DictRafflePool & info) 
{ 
    stm << "[\n"; 
    stm << "id=" << info.id << "\n"; 
    stm << "raffleCount=" << info.raffleCount << "\n"; 
    stm << "pool=" << info.pool << "\n"; 
    stm << "poolString=" << info.poolString << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct FightEffect //战斗属性效果,用于装备,属性类增减益buff  
{ 
    static const unsigned short getProtoID() { return 10005;} 
    static const std::string getProtoName() { return "FightEffect";} 
    inline const std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned int id;  
    double hp; //血量值  
    double hpRegen; //每秒血量值恢复  
    double attack; //伤害  
    double defense; //防御  
    double crit; //暴击  
    double toughness; //韧性  
    double moveSpeed; //移动速度  
    double attackSpeed; //攻击速度  
    double vampirk; //吸血  
    FightEffect() 
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
    FightEffect(const unsigned int & id, const double & hp, const double & hpRegen, const double & attack, const double & defense, const double & crit, const double & toughness, const double & moveSpeed, const double & attackSpeed, const double & vampirk) 
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
 
const std::vector<std::string>  FightEffect::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_FightEffect` (        `id` bigint(20) unsigned NOT NULL DEFAULT '0' ,        PRIMARY KEY(`id`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_FightEffect` add `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_FightEffect` change `id`  `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_FightEffect` add `hp`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_FightEffect` change `hp`  `hp`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_FightEffect` add `hpRegen`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_FightEffect` change `hpRegen`  `hpRegen`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_FightEffect` add `attack`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_FightEffect` change `attack`  `attack`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_FightEffect` add `defense`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_FightEffect` change `defense`  `defense`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_FightEffect` add `crit`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_FightEffect` change `crit`  `crit`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_FightEffect` add `toughness`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_FightEffect` change `toughness`  `toughness`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_FightEffect` add `moveSpeed`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_FightEffect` change `moveSpeed`  `moveSpeed`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_FightEffect` add `attackSpeed`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_FightEffect` change `attackSpeed`  `attackSpeed`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_FightEffect` add `vampirk`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_FightEffect` change `vampirk`  `vampirk`  double NOT NULL DEFAULT '0' "); 
    return std::move(ret); 
} 
std::string  FightEffect::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `id`,`hp`,`hpRegen`,`attack`,`defense`,`crit`,`toughness`,`moveSpeed`,`attackSpeed`,`vampirk` from `tb_FightEffect` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  FightEffect::getDBSelectPure() 
{ 
    return "select `id`,`hp`,`hpRegen`,`attack`,`defense`,`crit`,`toughness`,`moveSpeed`,`attackSpeed`,`vampirk` from `tb_FightEffect` "; 
} 
std::string  FightEffect::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_FightEffect`(`id`,`hp`,`hpRegen`,`attack`,`defense`,`crit`,`toughness`,`moveSpeed`,`attackSpeed`,`vampirk`) values(?,?,?,?,?,?,?,?,?,?)"); 
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
std::string  FightEffect::getDBDelete() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("delete from `tb_FightEffect` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  FightEffect::getDBUpdate() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_FightEffect`(id) values(? ) on duplicate key update `hp` = ?,`hpRegen` = ?,`attack` = ?,`defense` = ?,`crit` = ?,`toughness` = ?,`moveSpeed` = ?,`attackSpeed` = ?,`vampirk` = ? "); 
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
bool FightEffect::fetchFromDBResult(zsummer::mysql::DBResult &result) 
{ 
    if (result.getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("error fetch FightEffect from table `tb_FightEffect` . ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
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
        LOGE("catch one except error when fetch FightEffect from table `tb_FightEffect` . what=" << e.what() << "  ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    return false; 
} 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const FightEffect & data) 
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
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, FightEffect & data) 
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
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const FightEffect & info) 
{ 
    stm << "[\n"; 
    stm << "id=" << info.id << "\n"; 
    stm << "hp=" << info.hp << "\n"; 
    stm << "hpRegen=" << info.hpRegen << "\n"; 
    stm << "attack=" << info.attack << "\n"; 
    stm << "defense=" << info.defense << "\n"; 
    stm << "crit=" << info.crit << "\n"; 
    stm << "toughness=" << info.toughness << "\n"; 
    stm << "moveSpeed=" << info.moveSpeed << "\n"; 
    stm << "attackSpeed=" << info.attackSpeed << "\n"; 
    stm << "vampirk=" << info.vampirk << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct DictItem //道具字典  
{ 
    static const unsigned short getProtoID() { return 10003;} 
    static const std::string getProtoName() { return "DictItem";} 
    inline const std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned int id;  
    unsigned short primitiveType; //主类型  
    unsigned short subType; //子类型  
    unsigned short visible; //是否可见  
    unsigned short stacks; //可堆叠个数,0和1都是1次  
    unsigned int fightEffectID; //战斗属性效果,装备后生效  
    unsigned short autoUse; //0 不可使用, 1 可使用, 2 获得后自动使用  
    unsigned int dropID; //DictRafflePool中的id, 使用后销毁本道具并根据配置进行道具抽取  
    unsigned short vocationLimit; //限制职业类型, 装备类型  
    int levelLimit; //限制职业最小等级, 装备类型  
    std::string desc;  
    DictItem() 
    { 
        id = 0; 
        primitiveType = 0; 
        subType = 0; 
        visible = 0; 
        stacks = 0; 
        fightEffectID = 0; 
        autoUse = 0; 
        dropID = 0; 
        vocationLimit = 0; 
        levelLimit = 0; 
    } 
    DictItem(const unsigned int & id, const unsigned short & primitiveType, const unsigned short & subType, const unsigned short & visible, const unsigned short & stacks, const unsigned int & fightEffectID, const unsigned short & autoUse, const unsigned int & dropID, const unsigned short & vocationLimit, const int & levelLimit, const std::string & desc) 
    { 
        this->id = id; 
        this->primitiveType = primitiveType; 
        this->subType = subType; 
        this->visible = visible; 
        this->stacks = stacks; 
        this->fightEffectID = fightEffectID; 
        this->autoUse = autoUse; 
        this->dropID = dropID; 
        this->vocationLimit = vocationLimit; 
        this->levelLimit = levelLimit; 
        this->desc = desc; 
    } 
}; 
 
const std::vector<std::string>  DictItem::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_DictItem` (        `id` bigint(20) unsigned NOT NULL DEFAULT '0' ,        `primitiveType` bigint(20) unsigned NOT NULL DEFAULT '0' ,        `subType` bigint(20) unsigned NOT NULL DEFAULT '0' ,        PRIMARY KEY(`id`),        KEY `primitiveType` (`primitiveType`),        KEY `subType` (`subType`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_DictItem` add `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` change `id`  `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` add `primitiveType`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` change `primitiveType`  `primitiveType`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` add `subType`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` change `subType`  `subType`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` add `visible`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` change `visible`  `visible`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` add `stacks`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` change `stacks`  `stacks`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` add `fightEffectID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` change `fightEffectID`  `fightEffectID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` add `autoUse`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` change `autoUse`  `autoUse`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` add `dropID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` change `dropID`  `dropID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` add `vocationLimit`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` change `vocationLimit`  `vocationLimit`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` add `levelLimit`  bigint(20) NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` change `levelLimit`  `levelLimit`  bigint(20) NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` add `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictItem` change `desc`  `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    return std::move(ret); 
} 
std::string  DictItem::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `id`,`primitiveType`,`subType`,`visible`,`stacks`,`fightEffectID`,`autoUse`,`dropID`,`vocationLimit`,`levelLimit`,`desc` from `tb_DictItem` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictItem::getDBSelectPure() 
{ 
    return "select `id`,`primitiveType`,`subType`,`visible`,`stacks`,`fightEffectID`,`autoUse`,`dropID`,`vocationLimit`,`levelLimit`,`desc` from `tb_DictItem` "; 
} 
std::string  DictItem::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictItem`(`id`,`primitiveType`,`subType`,`visible`,`stacks`,`fightEffectID`,`autoUse`,`dropID`,`vocationLimit`,`levelLimit`,`desc`) values(?,?,?,?,?,?,?,?,?,?,?)"); 
    q << this->id; 
    q << this->primitiveType; 
    q << this->subType; 
    q << this->visible; 
    q << this->stacks; 
    q << this->fightEffectID; 
    q << this->autoUse; 
    q << this->dropID; 
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
    q.init("insert into `tb_DictItem`(id) values(? ) on duplicate key update `primitiveType` = ?,`subType` = ?,`visible` = ?,`stacks` = ?,`fightEffectID` = ?,`autoUse` = ?,`dropID` = ?,`vocationLimit` = ?,`levelLimit` = ?,`desc` = ? "); 
    q << this->id; 
    q << this->primitiveType; 
    q << this->subType; 
    q << this->visible; 
    q << this->stacks; 
    q << this->fightEffectID; 
    q << this->autoUse; 
    q << this->dropID; 
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
            result >> this->primitiveType; 
            result >> this->subType; 
            result >> this->visible; 
            result >> this->stacks; 
            result >> this->fightEffectID; 
            result >> this->autoUse; 
            result >> this->dropID; 
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
    ws << data.primitiveType;  
    ws << data.subType;  
    ws << data.visible;  
    ws << data.stacks;  
    ws << data.fightEffectID;  
    ws << data.autoUse;  
    ws << data.dropID;  
    ws << data.vocationLimit;  
    ws << data.levelLimit;  
    ws << data.desc;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DictItem & data) 
{ 
    rs >> data.id;  
    rs >> data.primitiveType;  
    rs >> data.subType;  
    rs >> data.visible;  
    rs >> data.stacks;  
    rs >> data.fightEffectID;  
    rs >> data.autoUse;  
    rs >> data.dropID;  
    rs >> data.vocationLimit;  
    rs >> data.levelLimit;  
    rs >> data.desc;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DictItem & info) 
{ 
    stm << "[\n"; 
    stm << "id=" << info.id << "\n"; 
    stm << "primitiveType=" << info.primitiveType << "\n"; 
    stm << "subType=" << info.subType << "\n"; 
    stm << "visible=" << info.visible << "\n"; 
    stm << "stacks=" << info.stacks << "\n"; 
    stm << "fightEffectID=" << info.fightEffectID << "\n"; 
    stm << "autoUse=" << info.autoUse << "\n"; 
    stm << "dropID=" << info.dropID << "\n"; 
    stm << "vocationLimit=" << info.vocationLimit << "\n"; 
    stm << "levelLimit=" << info.levelLimit << "\n"; 
    stm << "desc=" << info.desc << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
#endif 

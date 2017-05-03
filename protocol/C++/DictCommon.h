 
#ifndef _DICTCOMMON_H_ 
#define _DICTCOMMON_H_ 
 
 
 
typedef std::vector<double> DictArrayValue; //通用Value数组  
 
 
typedef std::vector<unsigned long long> DictArrayKey; //通用KEY数组  
 
 
typedef std::map<unsigned long long, double> DictMapKeyValue; //通用Key value  
 
struct DictPairValue 
{ 
    static const unsigned short getProtoID() { return 10000;} 
    static const std::string getProtoName() { return "DictPairValue";} 
    double val1;  
    double val2;  
    DictPairValue() 
    { 
        val1 = 0.0; 
        val2 = 0.0; 
    } 
    DictPairValue(const double & val1, const double & val2) 
    { 
        this->val1 = val1; 
        this->val2 = val2; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const DictPairValue & data) 
{ 
    ws << data.val1;  
    ws << data.val2;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DictPairValue & data) 
{ 
    rs >> data.val1;  
    rs >> data.val2;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DictPairValue & info) 
{ 
    stm << "["; 
    stm << "val1=" << info.val1 << ","; 
    stm << "val2=" << info.val2 << ","; 
    stm << "]"; 
    return stm; 
} 
 
 
typedef std::map<unsigned long long, DictPairValue> DictMapPairValue;  
 
 
typedef std::vector<DictPairValue> DictArrayPairValue;  
 
struct DictGlobal //全局配置  
{ 
    static const unsigned short getProtoID() { return 10001;} 
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
 
 
typedef std::vector<DictGlobal> DictGlobalArray;  
 
 
typedef std::map<unsigned long long, DictGlobal> DictGlobalMap;  
 
struct DictDrop //道具抽奖,道具掉落  
{ 
    static const unsigned short getProtoID() { return 10002;} 
    static const std::string getProtoName() { return "DictDrop";} 
    inline std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned long long id;  
    unsigned short dropType; //0 独立随机, 所有奖品根据自身概率随机,  1 从奖池中抽取一个奖品, 如果所有奖品概率总和小于1则可能什么都抽取不到  
    DictMapPairValue rewards; //奖池  
    std::string rewardsText; //奖池 格式为 id|count|prob,id|count|prob   
    std::string desc;  
    DictDrop() 
    { 
        id = 0; 
        dropType = 0; 
    } 
    DictDrop(const unsigned long long & id, const unsigned short & dropType, const DictMapPairValue & rewards, const std::string & rewardsText, const std::string & desc) 
    { 
        this->id = id; 
        this->dropType = dropType; 
        this->rewards = rewards; 
        this->rewardsText = rewardsText; 
        this->desc = desc; 
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
    ret.push_back("alter table `tb_DictDrop` add `rewardsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictDrop` change `rewardsText`  `rewardsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictDrop` add `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictDrop` change `desc`  `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    return ret; 
} 
std::string  DictDrop::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `id`,`dropType`,`rewardsText`,`desc` from `tb_DictDrop` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictDrop::getDBSelectPure() 
{ 
    return "select `id`,`dropType`,`rewardsText`,`desc` from `tb_DictDrop` "; 
} 
std::string  DictDrop::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictDrop`(`id`,`dropType`,`rewardsText`,`desc`) values(?,?,?,?)"); 
    q << this->id; 
    q << this->dropType; 
    q << this->rewardsText; 
    q << this->desc; 
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
    q.init("insert into `tb_DictDrop`(id) values(? ) on duplicate key update `dropType` = ?,`rewardsText` = ?,`desc` = ? "); 
    q << this->id; 
    q << this->dropType; 
    q << this->rewardsText; 
    q << this->desc; 
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
            result >> this->rewardsText; 
            result >> this->desc; 
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
    ws << data.rewardsText;  
    ws << data.desc;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DictDrop & data) 
{ 
    rs >> data.id;  
    rs >> data.dropType;  
    rs >> data.rewards;  
    rs >> data.rewardsText;  
    rs >> data.desc;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DictDrop & info) 
{ 
    stm << "["; 
    stm << "id=" << info.id << ","; 
    stm << "dropType=" << info.dropType << ","; 
    stm << "rewards=" << info.rewards << ","; 
    stm << "rewardsText=" << info.rewardsText << ","; 
    stm << "desc=" << info.desc << ","; 
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
    unsigned short icon;  
    unsigned short autoUse; //0 手动, 其他 自动使用  
    double stacks; //可堆叠个数,0和1都是1次  
    DictMapKeyValue costItems; //使用该道具需要消耗的其他道具  
    DictMapKeyValue costItemsText; //使用该道具需要消耗的其他道具  
    unsigned long long dropID; //使用该道具后会产生掉落效果 0为无效  
    unsigned long long propID; //装备该道具带来的属性加成  
    DictArrayKey skills; //装备该道具带来的可用技能  
    std::string skillsText; //装备该道具带来的可用技能 格式id,id,id   
    DictArrayKey buffs; //装备该道具带来的可用buff  
    std::string buffsText; //装备该道具带来的可用buff 格式id,id,id  
    unsigned short visible; //是否可见  
    std::string desc;  
    DictItem() 
    { 
        id = 0; 
        icon = 0; 
        autoUse = 0; 
        stacks = 0.0; 
        dropID = 0; 
        propID = 0; 
        visible = 0; 
    } 
    DictItem(const unsigned long long & id, const unsigned short & icon, const unsigned short & autoUse, const double & stacks, const DictMapKeyValue & costItems, const DictMapKeyValue & costItemsText, const unsigned long long & dropID, const unsigned long long & propID, const DictArrayKey & skills, const std::string & skillsText, const DictArrayKey & buffs, const std::string & buffsText, const unsigned short & visible, const std::string & desc) 
    { 
        this->id = id; 
        this->icon = icon; 
        this->autoUse = autoUse; 
        this->stacks = stacks; 
        this->costItems = costItems; 
        this->costItemsText = costItemsText; 
        this->dropID = dropID; 
        this->propID = propID; 
        this->skills = skills; 
        this->skillsText = skillsText; 
        this->buffs = buffs; 
        this->buffsText = buffsText; 
        this->visible = visible; 
        this->desc = desc; 
    } 
}; 
 
std::vector<std::string>  DictItem::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_DictItem` (        `id` bigint(20) unsigned NOT NULL DEFAULT '0' ,        PRIMARY KEY(`id`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_DictItem` add `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` change `id`  `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` add `icon`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` change `icon`  `icon`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` add `autoUse`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` change `autoUse`  `autoUse`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` add `stacks`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` change `stacks`  `stacks`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` add `costItemsText`  longblob NOT NULL "); 
    ret.push_back("alter table `tb_DictItem` change `costItemsText`  `costItemsText`  longblob NOT NULL "); 
    ret.push_back("alter table `tb_DictItem` add `dropID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` change `dropID`  `dropID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` add `propID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` change `propID`  `propID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` add `skillsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictItem` change `skillsText`  `skillsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictItem` add `buffsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictItem` change `buffsText`  `buffsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictItem` add `visible`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` change `visible`  `visible`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictItem` add `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictItem` change `desc`  `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    return ret; 
} 
std::string  DictItem::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `id`,`icon`,`autoUse`,`stacks`,`costItemsText`,`dropID`,`propID`,`skillsText`,`buffsText`,`visible`,`desc` from `tb_DictItem` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictItem::getDBSelectPure() 
{ 
    return "select `id`,`icon`,`autoUse`,`stacks`,`costItemsText`,`dropID`,`propID`,`skillsText`,`buffsText`,`visible`,`desc` from `tb_DictItem` "; 
} 
std::string  DictItem::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictItem`(`id`,`icon`,`autoUse`,`stacks`,`costItemsText`,`dropID`,`propID`,`skillsText`,`buffsText`,`visible`,`desc`) values(?,?,?,?,?,?,?,?,?,?,?)"); 
    q << this->id; 
    q << this->icon; 
    q << this->autoUse; 
    q << this->stacks; 
    try 
    { 
        zsummer::proto4z::WriteStream ws(0); 
        ws <<  this->costItemsText; 
        q.add(ws.getStreamBody(), ws.getStreamBodyLen()); 
    } 
    catch(const std::exception & e) 
    { 
        LOGW("catch one except error when insert DictItem.costItemsText error=" << e.what()); 
    } 
    q << this->dropID; 
    q << this->propID; 
    q << this->skillsText; 
    q << this->buffsText; 
    q << this->visible; 
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
    q.init("insert into `tb_DictItem`(id) values(? ) on duplicate key update `icon` = ?,`autoUse` = ?,`stacks` = ?,`costItemsText` = ?,`dropID` = ?,`propID` = ?,`skillsText` = ?,`buffsText` = ?,`visible` = ?,`desc` = ? "); 
    q << this->id; 
    q << this->icon; 
    q << this->autoUse; 
    q << this->stacks; 
    try 
    { 
        zsummer::proto4z::WriteStream ws(0); 
        ws <<  this->costItemsText; 
        q.add(ws.getStreamBody(), ws.getStreamBodyLen()); 
    } 
    catch(const std::exception & e) 
    { 
        LOGW("catch one except error when update DictItem.costItemsText error=" << e.what()); 
    } 
    q << this->dropID; 
    q << this->propID; 
    q << this->skillsText; 
    q << this->buffsText; 
    q << this->visible; 
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
            result >> this->icon; 
            result >> this->autoUse; 
            result >> this->stacks; 
            try 
            { 
                std::string blob; 
                result >> blob; 
                if(!blob.empty()) 
                { 
                    zsummer::proto4z::ReadStream rs(blob.c_str(), (zsummer::proto4z::Integer)blob.length(), false); 
                    rs >> this->costItemsText; 
                } 
            } 
            catch(const std::exception & e) 
            { 
                LOGW("catch one except error when fetch DictItem.costItemsText  from table `tb_DictItem` . what=" << e.what() << "  ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
            } 
            result >> this->dropID; 
            result >> this->propID; 
            result >> this->skillsText; 
            result >> this->buffsText; 
            result >> this->visible; 
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
    ws << data.icon;  
    ws << data.autoUse;  
    ws << data.stacks;  
    ws << data.costItems;  
    ws << data.costItemsText;  
    ws << data.dropID;  
    ws << data.propID;  
    ws << data.skills;  
    ws << data.skillsText;  
    ws << data.buffs;  
    ws << data.buffsText;  
    ws << data.visible;  
    ws << data.desc;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DictItem & data) 
{ 
    rs >> data.id;  
    rs >> data.icon;  
    rs >> data.autoUse;  
    rs >> data.stacks;  
    rs >> data.costItems;  
    rs >> data.costItemsText;  
    rs >> data.dropID;  
    rs >> data.propID;  
    rs >> data.skills;  
    rs >> data.skillsText;  
    rs >> data.buffs;  
    rs >> data.buffsText;  
    rs >> data.visible;  
    rs >> data.desc;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DictItem & info) 
{ 
    stm << "["; 
    stm << "id=" << info.id << ","; 
    stm << "icon=" << info.icon << ","; 
    stm << "autoUse=" << info.autoUse << ","; 
    stm << "stacks=" << info.stacks << ","; 
    stm << "costItems=" << info.costItems << ","; 
    stm << "costItemsText=" << info.costItemsText << ","; 
    stm << "dropID=" << info.dropID << ","; 
    stm << "propID=" << info.propID << ","; 
    stm << "skills=" << info.skills << ","; 
    stm << "skillsText=" << info.skillsText << ","; 
    stm << "buffs=" << info.buffs << ","; 
    stm << "buffsText=" << info.buffsText << ","; 
    stm << "visible=" << info.visible << ","; 
    stm << "desc=" << info.desc << ","; 
    stm << "]"; 
    return stm; 
} 
 
 
typedef std::vector<DictItem> DictItemArray;  
 
 
typedef std::map<unsigned long long, DictItem> DictItemMap;  
 
#endif 

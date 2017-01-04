 
#ifndef _DICTCOMMON_H_ 
#define _DICTCOMMON_H_ 
 
 
 
typedef std::vector<double> DictArrayValue; //通用Value数组  
 
 
typedef std::vector<unsigned long long> DictArrayKey; //通用KEY数组  
 
 
typedef std::map<unsigned long long, double> DictMapKeyValue; //通用Key value  
 
struct DictPairValue 
{ 
    static const unsigned short getProtoID() { return 10009;} 
    static const std::string getProtoName() { return "DictPairValue";} 
    unsigned long long val1;  
    unsigned long long val2;  
    DictPairValue() 
    { 
        val1 = 0; 
        val2 = 0; 
    } 
    DictPairValue(const unsigned long long & val1, const unsigned long long & val2) 
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
 
 
typedef std::map<unsigned long long, DictPairValue> DictMapKeyPairValue;  
 
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
 
 
typedef std::vector<DictGlobal> DictGlobalArray;  
 
 
typedef std::map<unsigned long long, DictGlobal> DictGlobalMap;  
 
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
    unsigned short dropType; //0 独立随机, 所有奖品根据自身概率随机,  1 从奖池中抽取一个奖品, 如果所有奖品概率总和小于1则可能什么都抽取不到  
    DictMapKeyPairValue rewards; //奖池  
    std::string rewardsText; //奖池 格式为 id|count|prob,id|count|prob   
    std::string desc;  
    DictDrop() 
    { 
        id = 0; 
        dropType = 0; 
    } 
    DictDrop(const unsigned long long & id, const unsigned short & dropType, const DictMapKeyPairValue & rewards, const std::string & rewardsText, const std::string & desc) 
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
 
struct DictProp //战斗属性  
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
    std::string desc;  
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
    DictProp(const unsigned long long & id, const double & hp, const double & hpRegen, const double & attack, const double & defense, const double & crit, const double & toughness, const double & moveSpeed, const double & attackSpeed, const double & vampirk, const std::string & desc) 
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
    ret.push_back("alter table `tb_DictProp` add `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictProp` change `desc`  `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    return ret; 
} 
std::string  DictProp::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `id`,`hp`,`hpRegen`,`attack`,`defense`,`crit`,`toughness`,`moveSpeed`,`attackSpeed`,`vampirk`,`desc` from `tb_DictProp` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictProp::getDBSelectPure() 
{ 
    return "select `id`,`hp`,`hpRegen`,`attack`,`defense`,`crit`,`toughness`,`moveSpeed`,`attackSpeed`,`vampirk`,`desc` from `tb_DictProp` "; 
} 
std::string  DictProp::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictProp`(`id`,`hp`,`hpRegen`,`attack`,`defense`,`crit`,`toughness`,`moveSpeed`,`attackSpeed`,`vampirk`,`desc`) values(?,?,?,?,?,?,?,?,?,?,?)"); 
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
    q.init("insert into `tb_DictProp`(id) values(? ) on duplicate key update `hp` = ?,`hpRegen` = ?,`attack` = ?,`defense` = ?,`crit` = ?,`toughness` = ?,`moveSpeed` = ?,`attackSpeed` = ?,`vampirk` = ?,`desc` = ? "); 
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
            result >> this->hpRegen; 
            result >> this->attack; 
            result >> this->defense; 
            result >> this->crit; 
            result >> this->toughness; 
            result >> this->moveSpeed; 
            result >> this->attackSpeed; 
            result >> this->vampirk; 
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
    ws << data.hpRegen;  
    ws << data.attack;  
    ws << data.defense;  
    ws << data.crit;  
    ws << data.toughness;  
    ws << data.moveSpeed;  
    ws << data.attackSpeed;  
    ws << data.vampirk;  
    ws << data.desc;  
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
    rs >> data.desc;  
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
    stm << "desc=" << info.desc << ","; 
    stm << "]"; 
    return stm; 
} 
 
 
typedef std::vector<DictProp> DictPropArray;  
 
 
typedef std::map<unsigned long long, DictProp> DictPropMap;  
 
struct DictModelLevel 
{ 
    static const unsigned short getProtoID() { return 10010;} 
    static const std::string getProtoName() { return "DictModelLevel";} 
    inline std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned long long modelID;  
    unsigned long long levelID;  
    double needExp; //升级所需经验  
    unsigned long long propID; //战斗属性  
    DictArrayKey skills; //该等级带来的可用技能  
    std::string skillsText; //该等级带来的可用技能 格式id,id,id   
    DictArrayKey buffs; //该等级带来的可用buff  
    std::string buffsText; //该等级带来的可用buff 格式id,id,id  
    DictModelLevel() 
    { 
        modelID = 0; 
        levelID = 0; 
        needExp = 0.0; 
        propID = 0; 
    } 
    DictModelLevel(const unsigned long long & modelID, const unsigned long long & levelID, const double & needExp, const unsigned long long & propID, const DictArrayKey & skills, const std::string & skillsText, const DictArrayKey & buffs, const std::string & buffsText) 
    { 
        this->modelID = modelID; 
        this->levelID = levelID; 
        this->needExp = needExp; 
        this->propID = propID; 
        this->skills = skills; 
        this->skillsText = skillsText; 
        this->buffs = buffs; 
        this->buffsText = buffsText; 
    } 
}; 
 
std::vector<std::string>  DictModelLevel::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_DictModelLevel` (        `modelID` bigint(20) unsigned NOT NULL DEFAULT '0' ,        `levelID` bigint(20) unsigned NOT NULL DEFAULT '0' ,        PRIMARY KEY(`modelID`,`levelID`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_DictModelLevel` add `modelID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModelLevel` change `modelID`  `modelID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModelLevel` add `levelID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModelLevel` change `levelID`  `levelID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModelLevel` add `needExp`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModelLevel` change `needExp`  `needExp`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModelLevel` add `propID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModelLevel` change `propID`  `propID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModelLevel` add `skillsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictModelLevel` change `skillsText`  `skillsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictModelLevel` add `buffsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictModelLevel` change `buffsText`  `buffsText`  varchar(255) NOT NULL DEFAULT '' "); 
    return ret; 
} 
std::string  DictModelLevel::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `modelID`,`levelID`,`needExp`,`propID`,`skillsText`,`buffsText` from `tb_DictModelLevel` where `modelID` = ? and `levelID` = ? "); 
    q << this->modelID; 
    q << this->levelID; 
    return q.pickSQL(); 
} 
std::string  DictModelLevel::getDBSelectPure() 
{ 
    return "select `modelID`,`levelID`,`needExp`,`propID`,`skillsText`,`buffsText` from `tb_DictModelLevel` "; 
} 
std::string  DictModelLevel::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictModelLevel`(`modelID`,`levelID`,`needExp`,`propID`,`skillsText`,`buffsText`) values(?,?,?,?,?,?)"); 
    q << this->modelID; 
    q << this->levelID; 
    q << this->needExp; 
    q << this->propID; 
    q << this->skillsText; 
    q << this->buffsText; 
    return q.pickSQL(); 
} 
std::string  DictModelLevel::getDBDelete() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("delete from `tb_DictModelLevel` where `modelID` = ?,`levelID` = ? "); 
    q << this->modelID; 
    q << this->levelID; 
    return q.pickSQL(); 
} 
std::string  DictModelLevel::getDBUpdate() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictModelLevel`(modelID,levelID) values(?,? ) on duplicate key update `needExp` = ?,`propID` = ?,`skillsText` = ?,`buffsText` = ? "); 
    q << this->modelID; 
    q << this->levelID; 
    q << this->needExp; 
    q << this->propID; 
    q << this->skillsText; 
    q << this->buffsText; 
    return q.pickSQL(); 
} 
bool DictModelLevel::fetchFromDBResult(zsummer::mysql::DBResult &result) 
{ 
    if (result.getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("error fetch DictModelLevel from table `tb_DictModelLevel` . ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    try 
    { 
        if (result.haveRow()) 
        { 
            result >> this->modelID; 
            result >> this->levelID; 
            result >> this->needExp; 
            result >> this->propID; 
            result >> this->skillsText; 
            result >> this->buffsText; 
            return true;  
        } 
    } 
    catch(const std::exception & e) 
    { 
        LOGE("catch one except error when fetch DictModelLevel from table `tb_DictModelLevel` . what=" << e.what() << "  ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    return false; 
} 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const DictModelLevel & data) 
{ 
    ws << data.modelID;  
    ws << data.levelID;  
    ws << data.needExp;  
    ws << data.propID;  
    ws << data.skills;  
    ws << data.skillsText;  
    ws << data.buffs;  
    ws << data.buffsText;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DictModelLevel & data) 
{ 
    rs >> data.modelID;  
    rs >> data.levelID;  
    rs >> data.needExp;  
    rs >> data.propID;  
    rs >> data.skills;  
    rs >> data.skillsText;  
    rs >> data.buffs;  
    rs >> data.buffsText;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DictModelLevel & info) 
{ 
    stm << "["; 
    stm << "modelID=" << info.modelID << ","; 
    stm << "levelID=" << info.levelID << ","; 
    stm << "needExp=" << info.needExp << ","; 
    stm << "propID=" << info.propID << ","; 
    stm << "skills=" << info.skills << ","; 
    stm << "skillsText=" << info.skillsText << ","; 
    stm << "buffs=" << info.buffs << ","; 
    stm << "buffsText=" << info.buffsText << ","; 
    stm << "]"; 
    return stm; 
} 
 
 
typedef std::vector<DictModelLevel> DictModelLevelArray;  
 
 
typedef std::map<unsigned long long, DictModelLevel> DictModelLevelMap;  
 
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
    unsigned long long modelID;  
    std::string modelName;  
    double modelRedius; //碰撞半径  
    unsigned long long iconID; //头像  
    double initLevel; //等级  
    unsigned short initCamp;  
    DictMapKeyPairValue initItems;  
    std::string initItemsText;  
    unsigned short initState; //初始化状态  
    std::string actionScriptPath; //行为树脚本路径  
    std::string clientModelPath; //客户端模型路径  
    std::string desc;  
    DictModel() 
    { 
        modelID = 0; 
        modelRedius = 0.0; 
        iconID = 0; 
        initLevel = 0.0; 
        initCamp = 0; 
        initState = 0; 
    } 
    DictModel(const unsigned long long & modelID, const std::string & modelName, const double & modelRedius, const unsigned long long & iconID, const double & initLevel, const unsigned short & initCamp, const DictMapKeyPairValue & initItems, const std::string & initItemsText, const unsigned short & initState, const std::string & actionScriptPath, const std::string & clientModelPath, const std::string & desc) 
    { 
        this->modelID = modelID; 
        this->modelName = modelName; 
        this->modelRedius = modelRedius; 
        this->iconID = iconID; 
        this->initLevel = initLevel; 
        this->initCamp = initCamp; 
        this->initItems = initItems; 
        this->initItemsText = initItemsText; 
        this->initState = initState; 
        this->actionScriptPath = actionScriptPath; 
        this->clientModelPath = clientModelPath; 
        this->desc = desc; 
    } 
}; 
 
std::vector<std::string>  DictModel::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_DictModel` (        `modelID` bigint(20) unsigned NOT NULL DEFAULT '0' ,        PRIMARY KEY(`modelID`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_DictModel` add `modelID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModel` change `modelID`  `modelID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModel` add `modelName`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictModel` change `modelName`  `modelName`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictModel` add `modelRedius`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModel` change `modelRedius`  `modelRedius`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModel` add `iconID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModel` change `iconID`  `iconID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModel` add `initLevel`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModel` change `initLevel`  `initLevel`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModel` add `initCamp`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModel` change `initCamp`  `initCamp`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModel` add `initItemsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictModel` change `initItemsText`  `initItemsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictModel` add `initState`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModel` change `initState`  `initState`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictModel` add `actionScriptPath`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictModel` change `actionScriptPath`  `actionScriptPath`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictModel` add `clientModelPath`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictModel` change `clientModelPath`  `clientModelPath`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictModel` add `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictModel` change `desc`  `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    return ret; 
} 
std::string  DictModel::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `modelID`,`modelName`,`modelRedius`,`iconID`,`initLevel`,`initCamp`,`initItemsText`,`initState`,`actionScriptPath`,`clientModelPath`,`desc` from `tb_DictModel` where `modelID` = ? "); 
    q << this->modelID; 
    return q.pickSQL(); 
} 
std::string  DictModel::getDBSelectPure() 
{ 
    return "select `modelID`,`modelName`,`modelRedius`,`iconID`,`initLevel`,`initCamp`,`initItemsText`,`initState`,`actionScriptPath`,`clientModelPath`,`desc` from `tb_DictModel` "; 
} 
std::string  DictModel::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictModel`(`modelID`,`modelName`,`modelRedius`,`iconID`,`initLevel`,`initCamp`,`initItemsText`,`initState`,`actionScriptPath`,`clientModelPath`,`desc`) values(?,?,?,?,?,?,?,?,?,?,?)"); 
    q << this->modelID; 
    q << this->modelName; 
    q << this->modelRedius; 
    q << this->iconID; 
    q << this->initLevel; 
    q << this->initCamp; 
    q << this->initItemsText; 
    q << this->initState; 
    q << this->actionScriptPath; 
    q << this->clientModelPath; 
    q << this->desc; 
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
    q.init("insert into `tb_DictModel`(modelID) values(? ) on duplicate key update `modelName` = ?,`modelRedius` = ?,`iconID` = ?,`initLevel` = ?,`initCamp` = ?,`initItemsText` = ?,`initState` = ?,`actionScriptPath` = ?,`clientModelPath` = ?,`desc` = ? "); 
    q << this->modelID; 
    q << this->modelName; 
    q << this->modelRedius; 
    q << this->iconID; 
    q << this->initLevel; 
    q << this->initCamp; 
    q << this->initItemsText; 
    q << this->initState; 
    q << this->actionScriptPath; 
    q << this->clientModelPath; 
    q << this->desc; 
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
            result >> this->modelID; 
            result >> this->modelName; 
            result >> this->modelRedius; 
            result >> this->iconID; 
            result >> this->initLevel; 
            result >> this->initCamp; 
            result >> this->initItemsText; 
            result >> this->initState; 
            result >> this->actionScriptPath; 
            result >> this->clientModelPath; 
            result >> this->desc; 
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
    ws << data.modelID;  
    ws << data.modelName;  
    ws << data.modelRedius;  
    ws << data.iconID;  
    ws << data.initLevel;  
    ws << data.initCamp;  
    ws << data.initItems;  
    ws << data.initItemsText;  
    ws << data.initState;  
    ws << data.actionScriptPath;  
    ws << data.clientModelPath;  
    ws << data.desc;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DictModel & data) 
{ 
    rs >> data.modelID;  
    rs >> data.modelName;  
    rs >> data.modelRedius;  
    rs >> data.iconID;  
    rs >> data.initLevel;  
    rs >> data.initCamp;  
    rs >> data.initItems;  
    rs >> data.initItemsText;  
    rs >> data.initState;  
    rs >> data.actionScriptPath;  
    rs >> data.clientModelPath;  
    rs >> data.desc;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DictModel & info) 
{ 
    stm << "["; 
    stm << "modelID=" << info.modelID << ","; 
    stm << "modelName=" << info.modelName << ","; 
    stm << "modelRedius=" << info.modelRedius << ","; 
    stm << "iconID=" << info.iconID << ","; 
    stm << "initLevel=" << info.initLevel << ","; 
    stm << "initCamp=" << info.initCamp << ","; 
    stm << "initItems=" << info.initItems << ","; 
    stm << "initItemsText=" << info.initItemsText << ","; 
    stm << "initState=" << info.initState << ","; 
    stm << "actionScriptPath=" << info.actionScriptPath << ","; 
    stm << "clientModelPath=" << info.clientModelPath << ","; 
    stm << "desc=" << info.desc << ","; 
    stm << "]"; 
    return stm; 
} 
 
 
typedef std::vector<DictModel> DictModelArray;  
 
 
typedef std::map<unsigned long long, DictModel> DictModelMap;  
 
enum TARGET_CAMP : unsigned long long 
{ 
    SEARCH_CAMP_NONE = 0, //自身  
    SEARCH_CAMP_SELF = 1, //自身  
    SEARCH_CAMP_SAME_WITHOUT_SELF = 2, //同阵营非自己  
    SEARCH_CAMP_ALIEN = 3, //非己方阵营  
}; 
 
struct AOESearch 
{ 
    static const unsigned short getProtoID() { return 10011;} 
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
    unsigned long long camp; //0忽略改选项, 1位标识自己, 2位标识同阵营非自己, 3其他阵营,   逗号分割 多选 SearchCampType  
    std::string campText;  
    unsigned short isRect; //0扇形, 其他矩形  
    double distance; //伤害距离  
    double radian; //弧度或者宽度  
    double offsetX; //坐标偏移量, 以caster为原点, 朝向为y轴  
    double offsetY; //坐标偏移量, 以caster为原点, 朝向为y轴  
    unsigned long long limitEntitys; //最大目标数  
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
 
enum BUFF_EFFECT_STAMP : unsigned long long 
{ 
    BUFF_EFFECT_TRIGGER_WHEN_LOAD = 1, //加载buff立刻触发  
    BUFF_EFFECT_TRIGGER_WHEN_UNLOAD = 2, //卸载buff立刻触发  
    BUFF_EFFECT_PROP_MULTIPLICATION = 3, //属性求积, 没有该标记为求和  
    BUFF_EFFECT_TRIGGER_PRE_DEATH = 10, //死亡前触发  
    BUFF_EFFECT_TRIGGER_AFT_DEATH = 11, //死亡后触发  
    BUFF_EFFECT_TRIGGER_WHEN_GENERAL = 15, //攻击触发  
    BUFF_EFFECT_TRIGGER_WHEN_PHYSICAL = 16, //攻击触发  
    BUFF_EFFECT_TRIGGER_WHEN_MAGIC = 17, //攻击触发  
    BUFF_EFFECT_TRIGGER_ON_GENERAL = 20, //被攻击触发  
    BUFF_EFFECT_TRIGGER_ON_PHYSICAL = 21, //被攻击触发  
    BUFF_EFFECT_TRIGGER_ON_MAGIC = 22, //被攻击触发  
    BUFF_EFFECT_TRIGGER_WHEN_ATTACH_GENERAL = 30, //攻击触发  
    BUFF_EFFECT_TRIGGER_WHEN_ON_ATTACH = 31, //被攻击触发  
}; 
 
struct DictBuffEffect 
{ 
    static const unsigned short getProtoID() { return 10012;} 
    static const std::string getProtoName() { return "DictBuffEffect";} 
    inline std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned long long id;  
    unsigned long long stamp; //BUFF_EFFECT_STAMP  
    std::string stampText;  
    unsigned long long propID; //提升的属性效果, 求积方式的参数是基础属性 不算其他装备  
    DictArrayKey skills; //触发技能  
    std::string skillsText; //触发技能 格式id,id,id   
    DictArrayKey buffs; //触发buff  
    std::string buffsText; //触发buff 格式id,id,id  
    double delayTrigger; //延迟触发, 0为无效  
    double areaTrigger; //距离触发, 0为无效  
    double intervalLimit; //最小触发间隔时间, 0为无效  
    double countLimit; //触发次数限制  
    std::string desc;  
    DictBuffEffect() 
    { 
        id = 0; 
        stamp = 0; 
        propID = 0; 
        delayTrigger = 0.0; 
        areaTrigger = 0.0; 
        intervalLimit = 0.0; 
        countLimit = 0.0; 
    } 
    DictBuffEffect(const unsigned long long & id, const unsigned long long & stamp, const std::string & stampText, const unsigned long long & propID, const DictArrayKey & skills, const std::string & skillsText, const DictArrayKey & buffs, const std::string & buffsText, const double & delayTrigger, const double & areaTrigger, const double & intervalLimit, const double & countLimit, const std::string & desc) 
    { 
        this->id = id; 
        this->stamp = stamp; 
        this->stampText = stampText; 
        this->propID = propID; 
        this->skills = skills; 
        this->skillsText = skillsText; 
        this->buffs = buffs; 
        this->buffsText = buffsText; 
        this->delayTrigger = delayTrigger; 
        this->areaTrigger = areaTrigger; 
        this->intervalLimit = intervalLimit; 
        this->countLimit = countLimit; 
        this->desc = desc; 
    } 
}; 
 
std::vector<std::string>  DictBuffEffect::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_DictBuffEffect` (        `id` bigint(20) unsigned NOT NULL DEFAULT '0' ,        PRIMARY KEY(`id`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_DictBuffEffect` add `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuffEffect` change `id`  `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuffEffect` add `stampText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictBuffEffect` change `stampText`  `stampText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictBuffEffect` add `propID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuffEffect` change `propID`  `propID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuffEffect` add `skillsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictBuffEffect` change `skillsText`  `skillsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictBuffEffect` add `buffsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictBuffEffect` change `buffsText`  `buffsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictBuffEffect` add `delayTrigger`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuffEffect` change `delayTrigger`  `delayTrigger`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuffEffect` add `areaTrigger`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuffEffect` change `areaTrigger`  `areaTrigger`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuffEffect` add `intervalLimit`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuffEffect` change `intervalLimit`  `intervalLimit`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuffEffect` add `countLimit`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuffEffect` change `countLimit`  `countLimit`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuffEffect` add `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictBuffEffect` change `desc`  `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    return ret; 
} 
std::string  DictBuffEffect::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `id`,`stampText`,`propID`,`skillsText`,`buffsText`,`delayTrigger`,`areaTrigger`,`intervalLimit`,`countLimit`,`desc` from `tb_DictBuffEffect` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictBuffEffect::getDBSelectPure() 
{ 
    return "select `id`,`stampText`,`propID`,`skillsText`,`buffsText`,`delayTrigger`,`areaTrigger`,`intervalLimit`,`countLimit`,`desc` from `tb_DictBuffEffect` "; 
} 
std::string  DictBuffEffect::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictBuffEffect`(`id`,`stampText`,`propID`,`skillsText`,`buffsText`,`delayTrigger`,`areaTrigger`,`intervalLimit`,`countLimit`,`desc`) values(?,?,?,?,?,?,?,?,?,?)"); 
    q << this->id; 
    q << this->stampText; 
    q << this->propID; 
    q << this->skillsText; 
    q << this->buffsText; 
    q << this->delayTrigger; 
    q << this->areaTrigger; 
    q << this->intervalLimit; 
    q << this->countLimit; 
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
    q.init("insert into `tb_DictBuffEffect`(id) values(? ) on duplicate key update `stampText` = ?,`propID` = ?,`skillsText` = ?,`buffsText` = ?,`delayTrigger` = ?,`areaTrigger` = ?,`intervalLimit` = ?,`countLimit` = ?,`desc` = ? "); 
    q << this->id; 
    q << this->stampText; 
    q << this->propID; 
    q << this->skillsText; 
    q << this->buffsText; 
    q << this->delayTrigger; 
    q << this->areaTrigger; 
    q << this->intervalLimit; 
    q << this->countLimit; 
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
            result >> this->stampText; 
            result >> this->propID; 
            result >> this->skillsText; 
            result >> this->buffsText; 
            result >> this->delayTrigger; 
            result >> this->areaTrigger; 
            result >> this->intervalLimit; 
            result >> this->countLimit; 
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
    ws << data.stamp;  
    ws << data.stampText;  
    ws << data.propID;  
    ws << data.skills;  
    ws << data.skillsText;  
    ws << data.buffs;  
    ws << data.buffsText;  
    ws << data.delayTrigger;  
    ws << data.areaTrigger;  
    ws << data.intervalLimit;  
    ws << data.countLimit;  
    ws << data.desc;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DictBuffEffect & data) 
{ 
    rs >> data.id;  
    rs >> data.stamp;  
    rs >> data.stampText;  
    rs >> data.propID;  
    rs >> data.skills;  
    rs >> data.skillsText;  
    rs >> data.buffs;  
    rs >> data.buffsText;  
    rs >> data.delayTrigger;  
    rs >> data.areaTrigger;  
    rs >> data.intervalLimit;  
    rs >> data.countLimit;  
    rs >> data.desc;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DictBuffEffect & info) 
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
    stm << "delayTrigger=" << info.delayTrigger << ","; 
    stm << "areaTrigger=" << info.areaTrigger << ","; 
    stm << "intervalLimit=" << info.intervalLimit << ","; 
    stm << "countLimit=" << info.countLimit << ","; 
    stm << "desc=" << info.desc << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct DictBuff 
{ 
    static const unsigned short getProtoID() { return 10013;} 
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
    unsigned short mutexType; //0无互斥, 1 同ID时间叠加, 2 同ID时间最长的覆盖, 3 同ID最强的覆盖  
    unsigned long long mutexID; //0  
    double mutexStrength;  
    double limitTime;  
    std::string desc;  
    DictBuff() 
    { 
        id = 0; 
        stamp = 0; 
        keepTime = 0.0; 
        mutexType = 0; 
        mutexID = 0; 
        mutexStrength = 0.0; 
        limitTime = 0.0; 
    } 
    DictBuff(const unsigned long long & id, const unsigned long long & stamp, const std::string & stampText, const DictArrayKey & effects, const std::string & effectsText, const double & keepTime, const unsigned short & mutexType, const unsigned long long & mutexID, const double & mutexStrength, const double & limitTime, const std::string & desc) 
    { 
        this->id = id; 
        this->stamp = stamp; 
        this->stampText = stampText; 
        this->effects = effects; 
        this->effectsText = effectsText; 
        this->keepTime = keepTime; 
        this->mutexType = mutexType; 
        this->mutexID = mutexID; 
        this->mutexStrength = mutexStrength; 
        this->limitTime = limitTime; 
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
    ret.push_back("alter table `tb_DictBuff` add `mutexType`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuff` change `mutexType`  `mutexType`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuff` add `mutexID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuff` change `mutexID`  `mutexID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuff` add `mutexStrength`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuff` change `mutexStrength`  `mutexStrength`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuff` add `limitTime`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuff` change `limitTime`  `limitTime`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictBuff` add `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictBuff` change `desc`  `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    return ret; 
} 
std::string  DictBuff::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `id`,`stampText`,`effectsText`,`keepTime`,`mutexType`,`mutexID`,`mutexStrength`,`limitTime`,`desc` from `tb_DictBuff` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictBuff::getDBSelectPure() 
{ 
    return "select `id`,`stampText`,`effectsText`,`keepTime`,`mutexType`,`mutexID`,`mutexStrength`,`limitTime`,`desc` from `tb_DictBuff` "; 
} 
std::string  DictBuff::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictBuff`(`id`,`stampText`,`effectsText`,`keepTime`,`mutexType`,`mutexID`,`mutexStrength`,`limitTime`,`desc`) values(?,?,?,?,?,?,?,?,?)"); 
    q << this->id; 
    q << this->stampText; 
    q << this->effectsText; 
    q << this->keepTime; 
    q << this->mutexType; 
    q << this->mutexID; 
    q << this->mutexStrength; 
    q << this->limitTime; 
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
    q.init("insert into `tb_DictBuff`(id) values(? ) on duplicate key update `stampText` = ?,`effectsText` = ?,`keepTime` = ?,`mutexType` = ?,`mutexID` = ?,`mutexStrength` = ?,`limitTime` = ?,`desc` = ? "); 
    q << this->id; 
    q << this->stampText; 
    q << this->effectsText; 
    q << this->keepTime; 
    q << this->mutexType; 
    q << this->mutexID; 
    q << this->mutexStrength; 
    q << this->limitTime; 
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
            result >> this->mutexType; 
            result >> this->mutexID; 
            result >> this->mutexStrength; 
            result >> this->limitTime; 
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
    ws << data.mutexType;  
    ws << data.mutexID;  
    ws << data.mutexStrength;  
    ws << data.limitTime;  
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
    rs >> data.mutexType;  
    rs >> data.mutexID;  
    rs >> data.mutexStrength;  
    rs >> data.limitTime;  
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
    stm << "mutexType=" << info.mutexType << ","; 
    stm << "mutexID=" << info.mutexID << ","; 
    stm << "mutexStrength=" << info.mutexStrength << ","; 
    stm << "limitTime=" << info.limitTime << ","; 
    stm << "desc=" << info.desc << ","; 
    stm << "]"; 
    return stm; 
} 
 
enum SKILL_STAMP : unsigned long long 
{ 
    SKILL_NONE = 0,  
    SKILL_AUTO_LOCK = 1, //自动锁敌  
    SKILL_AUTO_USE = 2, //自动施法  
    SKILL_PASSIVE = 3, //被动技能  
    SKILL_ON_HIT_BREAK = 4, //可被中断  
    SKILL_ON_MOVE_BREAK = 5, //可被中断  
    SKILL_CAN_MOVE = 6, //可移动  
    SKILL_PHYSICAL = 7, //物理类型  
    SKILL_MAGIC = 8, //魔法类型  
}; 
 
enum SKILL_BEHAVIOUR_STAMP : unsigned long long 
{ 
    SKILL_BEHAVIOUR_NONE = 0,  
    SKILL_BEHAVIOUR_HIT = 1, //攻击  
    SKILL_BEHAVIOUR_HILL = 2, //治疗  
    SKILL_BEHAVIOUR_TELEPORT_TARGET = 3, //瞬移到目标  
    SKILL_BEHAVIOUR_REMOVE_DEBUFF = 4, //驱散减益BUFF  
    SKILL_BEHAVIOUR_REMOVE_BUFF = 5, //驱散增益BUFF  
    SKILL_BEHAVIOUR_TRIGGER_BUFF = 6, //触发buff  
    SKILL_BEHAVIOUR_TRIGGER_SKILL = 7, //触发技能  
}; 
 
struct DictSkillEffect 
{ 
    static const unsigned short getProtoID() { return 10014;} 
    static const std::string getProtoName() { return "DictSkillEffect";} 
    inline std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned long long id;  
    unsigned long long stamp;  
    unsigned short hpMode; //血量变化类型:0 相加, 1与总血量相乘后再相加, 2与剩余血量相乘后再相加, 3与已损失血量相乘后叠加  
    double hpLeft; //血量变化参数  
    double hitKeepTime; //击退,浮空,牵引,的持续时间  
    double hitKeepSpeed; //击退,浮空,牵引,的持速度  
    DictArrayKey skills; //触发技能  
    std::string skillsText; //触发技能 格式id,id,id   
    DictArrayKey buffs; //触发buff  
    std::string buffsText; //触发buff 格式id,id,id  
    std::string desc;  
    DictSkillEffect() 
    { 
        id = 0; 
        stamp = 0; 
        hpMode = 0; 
        hpLeft = 0.0; 
        hitKeepTime = 0.0; 
        hitKeepSpeed = 0.0; 
    } 
    DictSkillEffect(const unsigned long long & id, const unsigned long long & stamp, const unsigned short & hpMode, const double & hpLeft, const double & hitKeepTime, const double & hitKeepSpeed, const DictArrayKey & skills, const std::string & skillsText, const DictArrayKey & buffs, const std::string & buffsText, const std::string & desc) 
    { 
        this->id = id; 
        this->stamp = stamp; 
        this->hpMode = hpMode; 
        this->hpLeft = hpLeft; 
        this->hitKeepTime = hitKeepTime; 
        this->hitKeepSpeed = hitKeepSpeed; 
        this->skills = skills; 
        this->skillsText = skillsText; 
        this->buffs = buffs; 
        this->buffsText = buffsText; 
        this->desc = desc; 
    } 
}; 
 
std::vector<std::string>  DictSkillEffect::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_DictSkillEffect` (        `id` bigint(20) unsigned NOT NULL DEFAULT '0' ,        PRIMARY KEY(`id`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_DictSkillEffect` add `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkillEffect` change `id`  `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkillEffect` add `stamp`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkillEffect` change `stamp`  `stamp`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkillEffect` add `hpMode`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkillEffect` change `hpMode`  `hpMode`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkillEffect` add `hpLeft`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkillEffect` change `hpLeft`  `hpLeft`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkillEffect` add `hitKeepTime`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkillEffect` change `hitKeepTime`  `hitKeepTime`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkillEffect` add `hitKeepSpeed`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkillEffect` change `hitKeepSpeed`  `hitKeepSpeed`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkillEffect` add `skillsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictSkillEffect` change `skillsText`  `skillsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictSkillEffect` add `buffsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictSkillEffect` change `buffsText`  `buffsText`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictSkillEffect` add `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictSkillEffect` change `desc`  `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    return ret; 
} 
std::string  DictSkillEffect::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `id`,`stamp`,`hpMode`,`hpLeft`,`hitKeepTime`,`hitKeepSpeed`,`skillsText`,`buffsText`,`desc` from `tb_DictSkillEffect` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictSkillEffect::getDBSelectPure() 
{ 
    return "select `id`,`stamp`,`hpMode`,`hpLeft`,`hitKeepTime`,`hitKeepSpeed`,`skillsText`,`buffsText`,`desc` from `tb_DictSkillEffect` "; 
} 
std::string  DictSkillEffect::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictSkillEffect`(`id`,`stamp`,`hpMode`,`hpLeft`,`hitKeepTime`,`hitKeepSpeed`,`skillsText`,`buffsText`,`desc`) values(?,?,?,?,?,?,?,?,?)"); 
    q << this->id; 
    q << this->stamp; 
    q << this->hpMode; 
    q << this->hpLeft; 
    q << this->hitKeepTime; 
    q << this->hitKeepSpeed; 
    q << this->skillsText; 
    q << this->buffsText; 
    q << this->desc; 
    return q.pickSQL(); 
} 
std::string  DictSkillEffect::getDBDelete() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("delete from `tb_DictSkillEffect` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictSkillEffect::getDBUpdate() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictSkillEffect`(id) values(? ) on duplicate key update `stamp` = ?,`hpMode` = ?,`hpLeft` = ?,`hitKeepTime` = ?,`hitKeepSpeed` = ?,`skillsText` = ?,`buffsText` = ?,`desc` = ? "); 
    q << this->id; 
    q << this->stamp; 
    q << this->hpMode; 
    q << this->hpLeft; 
    q << this->hitKeepTime; 
    q << this->hitKeepSpeed; 
    q << this->skillsText; 
    q << this->buffsText; 
    q << this->desc; 
    return q.pickSQL(); 
} 
bool DictSkillEffect::fetchFromDBResult(zsummer::mysql::DBResult &result) 
{ 
    if (result.getErrorCode() != zsummer::mysql::QEC_SUCCESS) 
    { 
        LOGE("error fetch DictSkillEffect from table `tb_DictSkillEffect` . ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    try 
    { 
        if (result.haveRow()) 
        { 
            result >> this->id; 
            result >> this->stamp; 
            result >> this->hpMode; 
            result >> this->hpLeft; 
            result >> this->hitKeepTime; 
            result >> this->hitKeepSpeed; 
            result >> this->skillsText; 
            result >> this->buffsText; 
            result >> this->desc; 
            return true;  
        } 
    } 
    catch(const std::exception & e) 
    { 
        LOGE("catch one except error when fetch DictSkillEffect from table `tb_DictSkillEffect` . what=" << e.what() << "  ErrorCode="  <<  result.getErrorCode() << ", Error=" << result.getErrorMsg() << ", sql=" << result.peekSQL()); 
        return false; 
    } 
    return false; 
} 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const DictSkillEffect & data) 
{ 
    ws << data.id;  
    ws << data.stamp;  
    ws << data.hpMode;  
    ws << data.hpLeft;  
    ws << data.hitKeepTime;  
    ws << data.hitKeepSpeed;  
    ws << data.skills;  
    ws << data.skillsText;  
    ws << data.buffs;  
    ws << data.buffsText;  
    ws << data.desc;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DictSkillEffect & data) 
{ 
    rs >> data.id;  
    rs >> data.stamp;  
    rs >> data.hpMode;  
    rs >> data.hpLeft;  
    rs >> data.hitKeepTime;  
    rs >> data.hitKeepSpeed;  
    rs >> data.skills;  
    rs >> data.skillsText;  
    rs >> data.buffs;  
    rs >> data.buffsText;  
    rs >> data.desc;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DictSkillEffect & info) 
{ 
    stm << "["; 
    stm << "id=" << info.id << ","; 
    stm << "stamp=" << info.stamp << ","; 
    stm << "hpMode=" << info.hpMode << ","; 
    stm << "hpLeft=" << info.hpLeft << ","; 
    stm << "hitKeepTime=" << info.hitKeepTime << ","; 
    stm << "hitKeepSpeed=" << info.hitKeepSpeed << ","; 
    stm << "skills=" << info.skills << ","; 
    stm << "skillsText=" << info.skillsText << ","; 
    stm << "buffs=" << info.buffs << ","; 
    stm << "buffsText=" << info.buffsText << ","; 
    stm << "desc=" << info.desc << ","; 
    stm << "]"; 
    return stm; 
} 
 
struct DictSkill 
{ 
    static const unsigned short getProtoID() { return 10015;} 
    static const std::string getProtoName() { return "DictSkill";} 
    inline std::vector<std::string>  getDBBuild(); 
    inline std::string  getDBInsert(); 
    inline std::string  getDBDelete(); 
    inline std::string  getDBUpdate(); 
    inline std::string  getDBSelect(); 
    inline std::string  getDBSelectPure(); 
    inline bool fetchFromDBResult(zsummer::mysql::DBResult &result); 
    unsigned long long id;  
    unsigned long long effectID;  
    unsigned short hpMode; //0 相加, 1与总血量相乘后再相加, 2与剩余血量相乘后再相加, 3与已损失血量相乘后叠加  
    double hpLeft; //当前血量提升, 如果是求积 则是  
    std::string desc;  
    DictSkill() 
    { 
        id = 0; 
        effectID = 0; 
        hpMode = 0; 
        hpLeft = 0.0; 
    } 
    DictSkill(const unsigned long long & id, const unsigned long long & effectID, const unsigned short & hpMode, const double & hpLeft, const std::string & desc) 
    { 
        this->id = id; 
        this->effectID = effectID; 
        this->hpMode = hpMode; 
        this->hpLeft = hpLeft; 
        this->desc = desc; 
    } 
}; 
 
std::vector<std::string>  DictSkill::getDBBuild() 
{ 
    std::vector<std::string> ret; 
    ret.push_back("CREATE TABLE IF NOT EXISTS `tb_DictSkill` (        `id` bigint(20) unsigned NOT NULL DEFAULT '0' ,        PRIMARY KEY(`id`) ) ENGINE = MyISAM DEFAULT CHARSET = utf8"); 
    ret.push_back("alter table `tb_DictSkill` add `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` change `id`  `id`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` add `effectID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` change `effectID`  `effectID`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` add `hpMode`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` change `hpMode`  `hpMode`  bigint(20) unsigned NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` add `hpLeft`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` change `hpLeft`  `hpLeft`  double NOT NULL DEFAULT '0' "); 
    ret.push_back("alter table `tb_DictSkill` add `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    ret.push_back("alter table `tb_DictSkill` change `desc`  `desc`  varchar(255) NOT NULL DEFAULT '' "); 
    return ret; 
} 
std::string  DictSkill::getDBSelect() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("select `id`,`effectID`,`hpMode`,`hpLeft`,`desc` from `tb_DictSkill` where `id` = ? "); 
    q << this->id; 
    return q.pickSQL(); 
} 
std::string  DictSkill::getDBSelectPure() 
{ 
    return "select `id`,`effectID`,`hpMode`,`hpLeft`,`desc` from `tb_DictSkill` "; 
} 
std::string  DictSkill::getDBInsert() 
{ 
    zsummer::mysql::DBQuery q; 
    q.init("insert into `tb_DictSkill`(`id`,`effectID`,`hpMode`,`hpLeft`,`desc`) values(?,?,?,?,?)"); 
    q << this->id; 
    q << this->effectID; 
    q << this->hpMode; 
    q << this->hpLeft; 
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
    q.init("insert into `tb_DictSkill`(id) values(? ) on duplicate key update `effectID` = ?,`hpMode` = ?,`hpLeft` = ?,`desc` = ? "); 
    q << this->id; 
    q << this->effectID; 
    q << this->hpMode; 
    q << this->hpLeft; 
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
            result >> this->effectID; 
            result >> this->hpMode; 
            result >> this->hpLeft; 
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
    ws << data.effectID;  
    ws << data.hpMode;  
    ws << data.hpLeft;  
    ws << data.desc;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DictSkill & data) 
{ 
    rs >> data.id;  
    rs >> data.effectID;  
    rs >> data.hpMode;  
    rs >> data.hpLeft;  
    rs >> data.desc;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DictSkill & info) 
{ 
    stm << "["; 
    stm << "id=" << info.id << ","; 
    stm << "effectID=" << info.effectID << ","; 
    stm << "hpMode=" << info.hpMode << ","; 
    stm << "hpLeft=" << info.hpLeft << ","; 
    stm << "desc=" << info.desc << ","; 
    stm << "]"; 
    return stm; 
} 
 
#endif 

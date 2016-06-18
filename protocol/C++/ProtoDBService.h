 
#ifndef _PROTODBSERVICE_H_ 
#define _PROTODBSERVICE_H_ 
 
 
 
typedef std::vector<std::string> DBStringArray;  
 
struct DBDataResult 
{ 
    static const unsigned short getProtoID() { return 3000;} 
    static const std::string getProtoName() { return "DBDataResult";} 
    unsigned short qc;  
    std::string errMsg;  
    std::string sql;  
    unsigned long long affected;  
    DBStringArray fields;  
    DBDataResult() 
    { 
        qc = 0; 
        affected = 0; 
    } 
    DBDataResult(const unsigned short & qc, const std::string & errMsg, const std::string & sql, const unsigned long long & affected, const DBStringArray & fields) 
    { 
        this->qc = qc; 
        this->errMsg = errMsg; 
        this->sql = sql; 
        this->affected = affected; 
        this->fields = fields; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const DBDataResult & data) 
{ 
    ws << data.qc;  
    ws << data.errMsg;  
    ws << data.sql;  
    ws << data.affected;  
    ws << data.fields;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DBDataResult & data) 
{ 
    rs >> data.qc;  
    rs >> data.errMsg;  
    rs >> data.sql;  
    rs >> data.affected;  
    rs >> data.fields;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DBDataResult & info) 
{ 
    stm << "[\n"; 
    stm << "qc=" << info.qc << "\n"; 
    stm << "errMsg=" << info.errMsg << "\n"; 
    stm << "sql=" << info.sql << "\n"; 
    stm << "affected=" << info.affected << "\n"; 
    stm << "fields=" << info.fields << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
 
typedef std::vector<DBDataResult> DBDataResultArray;  
 
struct DBQueryReq //通用SQL语句执行协议  
{ 
    static const unsigned short getProtoID() { return 3001;} 
    static const std::string getProtoName() { return "DBQueryReq";} 
    std::string sql;  
    DBQueryReq() 
    { 
    } 
    DBQueryReq(const std::string & sql) 
    { 
        this->sql = sql; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const DBQueryReq & data) 
{ 
    ws << data.sql;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DBQueryReq & data) 
{ 
    rs >> data.sql;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DBQueryReq & info) 
{ 
    stm << "[\n"; 
    stm << "sql=" << info.sql << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct DBQueryResp //通用SQL语句执行协议返回,DBDataResult可以借助dbHepler进行构建DBResult  
{ 
    static const unsigned short getProtoID() { return 3002;} 
    static const std::string getProtoName() { return "DBQueryResp";} 
    unsigned short retCode;  
    DBDataResult result;  
    DBQueryResp() 
    { 
        retCode = 0; 
    } 
    DBQueryResp(const unsigned short & retCode, const DBDataResult & result) 
    { 
        this->retCode = retCode; 
        this->result = result; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const DBQueryResp & data) 
{ 
    ws << data.retCode;  
    ws << data.result;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DBQueryResp & data) 
{ 
    rs >> data.retCode;  
    rs >> data.result;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DBQueryResp & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "result=" << info.result << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct DBQueryArrayReq //通用批量SQL语句执行协议  
{ 
    static const unsigned short getProtoID() { return 3003;} 
    static const std::string getProtoName() { return "DBQueryArrayReq";} 
    DBStringArray sqls;  
    DBQueryArrayReq() 
    { 
    } 
    DBQueryArrayReq(const DBStringArray & sqls) 
    { 
        this->sqls = sqls; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const DBQueryArrayReq & data) 
{ 
    ws << data.sqls;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DBQueryArrayReq & data) 
{ 
    rs >> data.sqls;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DBQueryArrayReq & info) 
{ 
    stm << "[\n"; 
    stm << "sqls=" << info.sqls << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
struct DBQueryArrayResp //通用批量SQL语句执行协议  
{ 
    static const unsigned short getProtoID() { return 3004;} 
    static const std::string getProtoName() { return "DBQueryArrayResp";} 
    unsigned short retCode;  
    DBDataResultArray results; //批量返回,注意不要超出协议包最大长度  
    DBQueryArrayResp() 
    { 
        retCode = 0; 
    } 
    DBQueryArrayResp(const unsigned short & retCode, const DBDataResultArray & results) 
    { 
        this->retCode = retCode; 
        this->results = results; 
    } 
}; 
inline zsummer::proto4z::WriteStream & operator << (zsummer::proto4z::WriteStream & ws, const DBQueryArrayResp & data) 
{ 
    ws << data.retCode;  
    ws << data.results;  
    return ws; 
} 
inline zsummer::proto4z::ReadStream & operator >> (zsummer::proto4z::ReadStream & rs, DBQueryArrayResp & data) 
{ 
    rs >> data.retCode;  
    rs >> data.results;  
    return rs; 
} 
inline zsummer::log4z::Log4zStream & operator << (zsummer::log4z::Log4zStream & stm, const DBQueryArrayResp & info) 
{ 
    stm << "[\n"; 
    stm << "retCode=" << info.retCode << "\n"; 
    stm << "results=" << info.results << "\n"; 
    stm << "]\n"; 
    return stm; 
} 
 
#endif 

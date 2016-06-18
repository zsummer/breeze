 
namespace Proto4z  
{ 
 
 
    public class DBStringArray : System.Collections.Generic.List<string>, Proto4z.IProtoObject  
    { 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var ret = new System.Collections.Generic.List<byte>(); 
            int len = (int)this.Count; 
            ret.AddRange(Proto4z.BaseProtoObject.encodeI32(len)); 
            for (int i = 0; i < this.Count; i++ ) 
            { 
                ret.AddRange(Proto4z.BaseProtoObject.encodeString(this[i]));  
            } 
            return ret; 
        } 
 
        public int __decode(byte[] binData, ref int pos) 
        { 
            int len = Proto4z.BaseProtoObject.decodeI32(binData, ref pos); 
            if(len > 0) 
            { 
                for (int i=0; i<len; i++) 
                { 
                    this.Add(Proto4z.BaseProtoObject.decodeString(binData, ref pos)); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public class DBDataResult: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 3005;  
        static public ushort getProtoID() { return 3005; } 
        static public string getProtoName() { return "DBDataResult"; } 
        //members   
        public ushort qc;  
        public string errMsg;  
        public string sql;  
        public ulong affected;  
        public DBStringArray fields;  
        public DBDataResult()  
        { 
            qc = 0;  
            errMsg = "";  
            sql = "";  
            affected = 0;  
            fields = new DBStringArray();  
        } 
        public DBDataResult(ushort qc, string errMsg, string sql, ulong affected, DBStringArray fields) 
        { 
            this.qc = qc; 
            this.errMsg = errMsg; 
            this.sql = sql; 
            this.affected = affected; 
            this.fields = fields; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.qc)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.errMsg)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.sql)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.affected)); 
            if (this.fields == null) this.fields = new DBStringArray(); 
            data.AddRange(this.fields.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.qc = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.errMsg = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.sql = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.affected = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.fields = new DBStringArray(); 
            this.fields.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class DBDataResultArray : System.Collections.Generic.List<DBDataResult>, Proto4z.IProtoObject  
    { 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var ret = new System.Collections.Generic.List<byte>(); 
            int len = (int)this.Count; 
            ret.AddRange(Proto4z.BaseProtoObject.encodeI32(len)); 
            for (int i = 0; i < this.Count; i++ ) 
            { 
                ret.AddRange(this[i].__encode()); 
            } 
            return ret; 
        } 
 
        public int __decode(byte[] binData, ref int pos) 
        { 
            int len = Proto4z.BaseProtoObject.decodeI32(binData, ref pos); 
            if(len > 0) 
            { 
                for (int i=0; i<len; i++) 
                { 
                    var data = new DBDataResult(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public class DBQueryReq: Proto4z.IProtoObject //通用SQL语句执行协议  
    {     
        //proto id   
        public const ushort protoID = 3006;  
        static public ushort getProtoID() { return 3006; } 
        static public string getProtoName() { return "DBQueryReq"; } 
        //members   
        public string sql;  
        public DBQueryReq()  
        { 
            sql = "";  
        } 
        public DBQueryReq(string sql) 
        { 
            this.sql = sql; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.sql)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.sql = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class DBQueryResp: Proto4z.IProtoObject //通用SQL语句执行协议返回,DBDataResult可以借助dbHepler进行构建DBResult  
    {     
        //proto id   
        public const ushort protoID = 3007;  
        static public ushort getProtoID() { return 3007; } 
        static public string getProtoName() { return "DBQueryResp"; } 
        //members   
        public ushort retCode;  
        public DBDataResult result;  
        public DBQueryResp()  
        { 
            retCode = 0;  
            result = new DBDataResult();  
        } 
        public DBQueryResp(ushort retCode, DBDataResult result) 
        { 
            this.retCode = retCode; 
            this.result = result; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            if (this.result == null) this.result = new DBDataResult(); 
            data.AddRange(this.result.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.result = new DBDataResult(); 
            this.result.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class DBQueryArrayReq: Proto4z.IProtoObject //通用批量SQL语句执行协议  
    {     
        //proto id   
        public const ushort protoID = 3008;  
        static public ushort getProtoID() { return 3008; } 
        static public string getProtoName() { return "DBQueryArrayReq"; } 
        //members   
        public DBStringArray sqls;  
        public DBQueryArrayReq()  
        { 
            sqls = new DBStringArray();  
        } 
        public DBQueryArrayReq(DBStringArray sqls) 
        { 
            this.sqls = sqls; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.sqls == null) this.sqls = new DBStringArray(); 
            data.AddRange(this.sqls.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.sqls = new DBStringArray(); 
            this.sqls.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class DBQueryArrayResp: Proto4z.IProtoObject //通用批量SQL语句执行协议  
    {     
        //proto id   
        public const ushort protoID = 3009;  
        static public ushort getProtoID() { return 3009; } 
        static public string getProtoName() { return "DBQueryArrayResp"; } 
        //members   
        public ushort retCode;  
        public DBDataResultArray results; //批量返回,注意不要超出协议包最大长度  
        public DBQueryArrayResp()  
        { 
            retCode = 0;  
            results = new DBDataResultArray();  
        } 
        public DBQueryArrayResp(ushort retCode, DBDataResultArray results) 
        { 
            this.retCode = retCode; 
            this.results = results; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            if (this.results == null) this.results = new DBDataResultArray(); 
            data.AddRange(this.results.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.results = new DBDataResultArray(); 
            this.results.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
} 
 
 

 
namespace Proto4z  
{ 
 
 
    public class SQLFieldArray : System.Collections.Generic.List<string>, Proto4z.IProtoObject  
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
 
    public class SQLResult: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 41002;  
        static public ushort getProtoID() { return 41002; } 
        static public string getProtoName() { return "SQLResult"; } 
        //members   
        public ushort qc;  
        public string errMsg;  
        public string sql;  
        public ulong affected;  
        public SQLFieldArray fields;  
        public SQLResult()  
        { 
            qc = 0;  
            errMsg = "";  
            sql = "";  
            affected = 0;  
            fields = new SQLFieldArray();  
        } 
        public SQLResult(ushort qc, string errMsg, string sql, ulong affected, SQLFieldArray fields) 
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
            if (this.fields == null) this.fields = new SQLFieldArray(); 
            data.AddRange(this.fields.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.qc = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.errMsg = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.sql = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.affected = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.fields = new SQLFieldArray(); 
            this.fields.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SQLQueryReq: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 41000;  
        static public ushort getProtoID() { return 41000; } 
        static public string getProtoName() { return "SQLQueryReq"; } 
        //members   
        public string sql;  
        public SQLQueryReq()  
        { 
            sql = "";  
        } 
        public SQLQueryReq(string sql) 
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
 
    public class SQLQueryResp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 41001;  
        static public ushort getProtoID() { return 41001; } 
        static public string getProtoName() { return "SQLQueryResp"; } 
        //members   
        public ushort retCode;  
        public SQLResult result;  
        public SQLQueryResp()  
        { 
            retCode = 0;  
            result = new SQLResult();  
        } 
        public SQLQueryResp(ushort retCode, SQLResult result) 
        { 
            this.retCode = retCode; 
            this.result = result; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            if (this.result == null) this.result = new SQLResult(); 
            data.AddRange(this.result.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.result = new SQLResult(); 
            this.result.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
} 
 
 

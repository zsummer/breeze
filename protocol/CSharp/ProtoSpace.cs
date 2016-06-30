 
namespace Proto4z  
{ 
 
    public class SceneInfoReq: Proto4z.IProtoObject //获取场景信息  
    {     
        //proto id   
        public const ushort protoID = 10001;  
        static public ushort getProtoID() { return 10001; } 
        static public string getProtoName() { return "SceneInfoReq"; } 
        //members   
        public SceneInfoReq()  
        { 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            return pos; 
        } 
    } 
 
    public class SceneInfoAck: Proto4z.IProtoObject //获取场景信息  
    {     
        //proto id   
        public const ushort protoID = 10002;  
        static public ushort getProtoID() { return 10002; } 
        static public string getProtoName() { return "SceneInfoAck"; } 
        //members   
        public ushort retCode; //错误码  
        public SceneInfoArray scenes;  
        public SceneInfoAck()  
        { 
            retCode = 0;  
            scenes = new SceneInfoArray();  
        } 
        public SceneInfoAck(ushort retCode, SceneInfoArray scenes) 
        { 
            this.retCode = retCode; 
            this.scenes = scenes; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            if (this.scenes == null) this.scenes = new SceneInfoArray(); 
            data.AddRange(this.scenes.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.scenes = new SceneInfoArray(); 
            this.scenes.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class TryEnterSceneReq: Proto4z.IProtoObject //进入场景  
    {     
        //proto id   
        public const ushort protoID = 10003;  
        static public ushort getProtoID() { return 10003; } 
        static public string getProtoName() { return "TryEnterSceneReq"; } 
        //members   
        public ushort type; //类型, 如果是不同类型,该请求会触发场景切换动作  
        public TryEnterSceneReq()  
        { 
            type = 0;  
        } 
        public TryEnterSceneReq(ushort type) 
        { 
            this.type = type; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.type)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.type = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class TryEnterSceneAck: Proto4z.IProtoObject //进入场景  
    {     
        //proto id   
        public const ushort protoID = 10004;  
        static public ushort getProtoID() { return 10004; } 
        static public string getProtoName() { return "TryEnterSceneAck"; } 
        //members   
        public ushort retCode; //错误码  
        public SceneInfoArray scenes; //要检查状态, 如果是主城则状态会置换为INSTACING, 如果是需要匹配的 状态为匹配中  
        public TryEnterSceneAck()  
        { 
            retCode = 0;  
            scenes = new SceneInfoArray();  
        } 
        public TryEnterSceneAck(ushort retCode, SceneInfoArray scenes) 
        { 
            this.retCode = retCode; 
            this.scenes = scenes; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            if (this.scenes == null) this.scenes = new SceneInfoArray(); 
            data.AddRange(this.scenes.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.scenes = new SceneInfoArray(); 
            this.scenes.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SceneInfoNotice: Proto4z.IProtoObject //场景信息刷新,如果是匹配模式, 需要扩展当前匹配信息到该协议中  
    {     
        //proto id   
        public const ushort protoID = 10005;  
        static public ushort getProtoID() { return 10005; } 
        static public string getProtoName() { return "SceneInfoNotice"; } 
        //members   
        public ushort retCode; //错误码  
        public SceneInfoArray scenes; //要检查状态, 如果是主城则状态会置换为INSTACING, 如果是需要匹配的 状态为匹配中  
        public SceneInfoNotice()  
        { 
            retCode = 0;  
            scenes = new SceneInfoArray();  
        } 
        public SceneInfoNotice(ushort retCode, SceneInfoArray scenes) 
        { 
            this.retCode = retCode; 
            this.scenes = scenes; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            if (this.scenes == null) this.scenes = new SceneInfoArray(); 
            data.AddRange(this.scenes.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.scenes = new SceneInfoArray(); 
            this.scenes.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class LeaveSceneReq: Proto4z.IProtoObject //离开场景  
    {     
        //proto id   
        public const ushort protoID = 10006;  
        static public ushort getProtoID() { return 10006; } 
        static public string getProtoName() { return "LeaveSceneReq"; } 
        //members   
        public ushort type; //类型  
        public LeaveSceneReq()  
        { 
            type = 0;  
        } 
        public LeaveSceneReq(ushort type) 
        { 
            this.type = type; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.type)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.type = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class LeaveSceneAck: Proto4z.IProtoObject //离开场景  
    {     
        //proto id   
        public const ushort protoID = 10007;  
        static public ushort getProtoID() { return 10007; } 
        static public string getProtoName() { return "LeaveSceneAck"; } 
        //members   
        public ushort retCode; //错误码  
        public SceneInfoArray scenes; //要检查状态, 如果是主城则状态会置换为INSTACING, 如果是需要匹配的 状态为匹配中  
        public LeaveSceneAck()  
        { 
            retCode = 0;  
            scenes = new SceneInfoArray();  
        } 
        public LeaveSceneAck(ushort retCode, SceneInfoArray scenes) 
        { 
            this.retCode = retCode; 
            this.scenes = scenes; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            if (this.scenes == null) this.scenes = new SceneInfoArray(); 
            data.AddRange(this.scenes.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.scenes = new SceneInfoArray(); 
            this.scenes.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class QuitSceneReq: Proto4z.IProtoObject //退出场景  
    {     
        //proto id   
        public const ushort protoID = 10008;  
        static public ushort getProtoID() { return 10008; } 
        static public string getProtoName() { return "QuitSceneReq"; } 
        //members   
        public ushort type; //类型  
        public QuitSceneReq()  
        { 
            type = 0;  
        } 
        public QuitSceneReq(ushort type) 
        { 
            this.type = type; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.type)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.type = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class QuitSceneAck: Proto4z.IProtoObject //退出场景  
    {     
        //proto id   
        public const ushort protoID = 10009;  
        static public ushort getProtoID() { return 10009; } 
        static public string getProtoName() { return "QuitSceneAck"; } 
        //members   
        public ushort retCode; //错误码  
        public SceneInfoArray scenes; //要检查状态, 如果是主城则状态会置换为INSTACING, 如果是需要匹配的 状态为匹配中  
        public QuitSceneAck()  
        { 
            retCode = 0;  
            scenes = new SceneInfoArray();  
        } 
        public QuitSceneAck(ushort retCode, SceneInfoArray scenes) 
        { 
            this.retCode = retCode; 
            this.scenes = scenes; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            if (this.scenes == null) this.scenes = new SceneInfoArray(); 
            data.AddRange(this.scenes.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.scenes = new SceneInfoArray(); 
            this.scenes.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
} 
 
 

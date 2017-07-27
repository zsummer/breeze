 
namespace Proto4z  
{ 
 
    public class ClientPulse: Proto4z.IProtoObject //客户端脉冲请求  
    {     
        //proto id   
        public const ushort protoID = 55000;  
        static public ushort getProtoID() { return 55000; } 
        static public string getProtoName() { return "ClientPulse"; } 
        //members   
        public ClientPulse()  
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
 
    public class ClientAuthReq: Proto4z.IProtoObject //认证请求  
    {     
        //proto id   
        public const ushort protoID = 55001;  
        static public ushort getProtoID() { return 55001; } 
        static public string getProtoName() { return "ClientAuthReq"; } 
        //members   
        public string account;  
        public string token;  
        public ClientAuthReq()  
        { 
            account = "";  
            token = "";  
        } 
        public ClientAuthReq(string account, string token) 
        { 
            this.account = account; 
            this.token = token; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.account)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.token)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.account = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.token = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class ClientAuthResp: Proto4z.IProtoObject //认证返回  
    {     
        //proto id   
        public const ushort protoID = 55002;  
        static public ushort getProtoID() { return 55002; } 
        static public string getProtoName() { return "ClientAuthResp"; } 
        //members   
        public ushort retCode;  
        public string account;  
        public string token;  
        public AvatarPreviewArray previews;  
        public ClientAuthResp()  
        { 
            retCode = 0;  
            account = "";  
            token = "";  
            previews = new AvatarPreviewArray();  
        } 
        public ClientAuthResp(ushort retCode, string account, string token, AvatarPreviewArray previews) 
        { 
            this.retCode = retCode; 
            this.account = account; 
            this.token = token; 
            this.previews = previews; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.account)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.token)); 
            if (this.previews == null) this.previews = new AvatarPreviewArray(); 
            data.AddRange(this.previews.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.account = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.token = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.previews = new AvatarPreviewArray(); 
            this.previews.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class CreateAvatarReq: Proto4z.IProtoObject //创角色请求  
    {     
        //proto id   
        public const ushort protoID = 55003;  
        static public ushort getProtoID() { return 55003; } 
        static public string getProtoName() { return "CreateAvatarReq"; } 
        //members   
        public string accountName; //这个字段会被服务器填充.客户端可以不填写  
        public string avatarName;  
        public CreateAvatarReq()  
        { 
            accountName = "";  
            avatarName = "";  
        } 
        public CreateAvatarReq(string accountName, string avatarName) 
        { 
            this.accountName = accountName; 
            this.avatarName = avatarName; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.accountName)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.avatarName)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.accountName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.avatarName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class CreateAvatarResp: Proto4z.IProtoObject //创角色请求返回  
    {     
        //proto id   
        public const ushort protoID = 55004;  
        static public ushort getProtoID() { return 55004; } 
        static public string getProtoName() { return "CreateAvatarResp"; } 
        //members   
        public ushort retCode;  
        public ulong avatarID;  
        public AvatarPreviewArray previews;  
        public CreateAvatarResp()  
        { 
            retCode = 0;  
            avatarID = 0;  
            previews = new AvatarPreviewArray();  
        } 
        public CreateAvatarResp(ushort retCode, ulong avatarID, AvatarPreviewArray previews) 
        { 
            this.retCode = retCode; 
            this.avatarID = avatarID; 
            this.previews = previews; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.avatarID)); 
            if (this.previews == null) this.previews = new AvatarPreviewArray(); 
            data.AddRange(this.previews.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.avatarID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.previews = new AvatarPreviewArray(); 
            this.previews.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class DeviceInfo : System.Collections.Generic.Dictionary<string, string>, Proto4z.IProtoObject  
    { 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var ret = new System.Collections.Generic.List<byte>(); 
            int len = (int)this.Count; 
            ret.AddRange(Proto4z.BaseProtoObject.encodeI32(len)); 
            foreach(var kv in this) 
            { 
                ret.AddRange(Proto4z.BaseProtoObject.encodeString(kv.Key)); 
                ret.AddRange(Proto4z.BaseProtoObject.encodeString(kv.Value)); 
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
                    var key = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
                    var val = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
                    this.Add(key, val); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public class AttachAvatarReq: Proto4z.IProtoObject //选角色请求  
    {     
        //proto id   
        public const ushort protoID = 55005;  
        static public ushort getProtoID() { return 55005; } 
        static public string getProtoName() { return "AttachAvatarReq"; } 
        //members   
        public string accountName; //这个字段会被服务器填充.客户端可以不填写  
        public ulong avatarID;  
        public DeviceInfo di;  
        public AttachAvatarReq()  
        { 
            accountName = "";  
            avatarID = 0;  
            di = new DeviceInfo();  
        } 
        public AttachAvatarReq(string accountName, ulong avatarID, DeviceInfo di) 
        { 
            this.accountName = accountName; 
            this.avatarID = avatarID; 
            this.di = di; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.accountName)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.avatarID)); 
            if (this.di == null) this.di = new DeviceInfo(); 
            data.AddRange(this.di.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.accountName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.avatarID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.di = new DeviceInfo(); 
            this.di.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class AttachAvatarResp: Proto4z.IProtoObject //选角色请求返回  
    {     
        //proto id   
        public const ushort protoID = 55006;  
        static public ushort getProtoID() { return 55006; } 
        static public string getProtoName() { return "AttachAvatarResp"; } 
        //members   
        public ushort retCode;  
        public AvatarBaseInfo baseInfo;  
        public AttachAvatarResp()  
        { 
            retCode = 0;  
            baseInfo = new AvatarBaseInfo();  
        } 
        public AttachAvatarResp(ushort retCode, AvatarBaseInfo baseInfo) 
        { 
            this.retCode = retCode; 
            this.baseInfo = baseInfo; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            if (this.baseInfo == null) this.baseInfo = new AvatarBaseInfo(); 
            data.AddRange(this.baseInfo.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.baseInfo = new AvatarBaseInfo(); 
            this.baseInfo.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class AvatarBaseInfoNotice: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 55007;  
        static public ushort getProtoID() { return 55007; } 
        static public string getProtoName() { return "AvatarBaseInfoNotice"; } 
        //members   
        public AvatarBaseInfo baseInfo;  
        public AvatarBaseInfoNotice()  
        { 
            baseInfo = new AvatarBaseInfo();  
        } 
        public AvatarBaseInfoNotice(AvatarBaseInfo baseInfo) 
        { 
            this.baseInfo = baseInfo; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.baseInfo == null) this.baseInfo = new AvatarBaseInfo(); 
            data.AddRange(this.baseInfo.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.baseInfo = new AvatarBaseInfo(); 
            this.baseInfo.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class AvatarPropMapNotice: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 55008;  
        static public ushort getProtoID() { return 55008; } 
        static public string getProtoName() { return "AvatarPropMapNotice"; } 
        //members   
        public ulong avatarID;  
        public AvatarPropMapNotice()  
        { 
            avatarID = 0;  
        } 
        public AvatarPropMapNotice(ulong avatarID) 
        { 
            this.avatarID = avatarID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.avatarID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.avatarID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SceneGroupInfoNotice: Proto4z.IProtoObject //编队数据通知  
    {     
        //proto id   
        public const ushort protoID = 55009;  
        static public ushort getProtoID() { return 55009; } 
        static public string getProtoName() { return "SceneGroupInfoNotice"; } 
        //members   
        public SceneGroupInfo groupInfo;  
        public SceneGroupInfoNotice()  
        { 
            groupInfo = new SceneGroupInfo();  
        } 
        public SceneGroupInfoNotice(SceneGroupInfo groupInfo) 
        { 
            this.groupInfo = groupInfo; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.groupInfo == null) this.groupInfo = new SceneGroupInfo(); 
            data.AddRange(this.groupInfo.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.groupInfo = new SceneGroupInfo(); 
            this.groupInfo.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SceneGroupGetReq: Proto4z.IProtoObject //获取当前角色的场景状态数据  
    {     
        //proto id   
        public const ushort protoID = 55010;  
        static public ushort getProtoID() { return 55010; } 
        static public string getProtoName() { return "SceneGroupGetReq"; } 
        //members   
        public SceneGroupGetReq()  
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
 
    public class SceneGroupGetResp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 55011;  
        static public ushort getProtoID() { return 55011; } 
        static public string getProtoName() { return "SceneGroupGetResp"; } 
        //members   
        public ushort retCode;  
        public SceneGroupGetResp()  
        { 
            retCode = 0;  
        } 
        public SceneGroupGetResp(ushort retCode) 
        { 
            this.retCode = retCode; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SceneGroupEnterReq: Proto4z.IProtoObject //申请进入场景  
    {     
        //proto id   
        public const ushort protoID = 55012;  
        static public ushort getProtoID() { return 55012; } 
        static public string getProtoName() { return "SceneGroupEnterReq"; } 
        //members   
        public ushort sceneType;  
        public ulong mapID;  
        public SceneGroupEnterReq()  
        { 
            sceneType = 0;  
            mapID = 0;  
        } 
        public SceneGroupEnterReq(ushort sceneType, ulong mapID) 
        { 
            this.sceneType = sceneType; 
            this.mapID = mapID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.sceneType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.mapID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.sceneType = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.mapID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SceneGroupEnterResp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 55013;  
        static public ushort getProtoID() { return 55013; } 
        static public string getProtoName() { return "SceneGroupEnterResp"; } 
        //members   
        public ushort retCode;  
        public SceneGroupEnterResp()  
        { 
            retCode = 0;  
        } 
        public SceneGroupEnterResp(ushort retCode) 
        { 
            this.retCode = retCode; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SceneGroupCancelReq: Proto4z.IProtoObject //取消申请(根据状态不同会有取消匹配,重置状态,结束战斗(可中途结束的场景类型)  
    {     
        //proto id   
        public const ushort protoID = 55014;  
        static public ushort getProtoID() { return 55014; } 
        static public string getProtoName() { return "SceneGroupCancelReq"; } 
        //members   
        public SceneGroupCancelReq()  
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
 
    public class SceneGroupCancelResp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 55015;  
        static public ushort getProtoID() { return 55015; } 
        static public string getProtoName() { return "SceneGroupCancelResp"; } 
        //members   
        public ushort retCode;  
        public SceneGroupCancelResp()  
        { 
            retCode = 0;  
        } 
        public SceneGroupCancelResp(ushort retCode) 
        { 
            this.retCode = retCode; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SceneGroupCreateReq: Proto4z.IProtoObject //发起组队请求  
    {     
        //proto id   
        public const ushort protoID = 55016;  
        static public ushort getProtoID() { return 55016; } 
        static public string getProtoName() { return "SceneGroupCreateReq"; } 
        //members   
        public SceneGroupCreateReq()  
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
 
    public class SceneGroupCreateResp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 55017;  
        static public ushort getProtoID() { return 55017; } 
        static public string getProtoName() { return "SceneGroupCreateResp"; } 
        //members   
        public ushort retCode;  
        public SceneGroupCreateResp()  
        { 
            retCode = 0;  
        } 
        public SceneGroupCreateResp(ushort retCode) 
        { 
            this.retCode = retCode; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SceneGroupJoinReq: Proto4z.IProtoObject //加入组队  
    {     
        //proto id   
        public const ushort protoID = 55018;  
        static public ushort getProtoID() { return 55018; } 
        static public string getProtoName() { return "SceneGroupJoinReq"; } 
        //members   
        public ulong groupID;  
        public SceneGroupJoinReq()  
        { 
            groupID = 0;  
        } 
        public SceneGroupJoinReq(ulong groupID) 
        { 
            this.groupID = groupID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.groupID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.groupID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SceneGroupJoinResp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 55019;  
        static public ushort getProtoID() { return 55019; } 
        static public string getProtoName() { return "SceneGroupJoinResp"; } 
        //members   
        public ushort retCode;  
        public SceneGroupJoinResp()  
        { 
            retCode = 0;  
        } 
        public SceneGroupJoinResp(ushort retCode) 
        { 
            this.retCode = retCode; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SceneGroupInviteReq: Proto4z.IProtoObject //邀请对方加入自己的编队  
    {     
        //proto id   
        public const ushort protoID = 55020;  
        static public ushort getProtoID() { return 55020; } 
        static public string getProtoName() { return "SceneGroupInviteReq"; } 
        //members   
        public ulong avatarID;  
        public SceneGroupInviteReq()  
        { 
            avatarID = 0;  
        } 
        public SceneGroupInviteReq(ulong avatarID) 
        { 
            this.avatarID = avatarID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.avatarID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.avatarID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SceneGroupInviteResp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 55021;  
        static public ushort getProtoID() { return 55021; } 
        static public string getProtoName() { return "SceneGroupInviteResp"; } 
        //members   
        public ushort retCode;  
        public SceneGroupInviteResp()  
        { 
            retCode = 0;  
        } 
        public SceneGroupInviteResp(ushort retCode) 
        { 
            this.retCode = retCode; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SceneGroupInviteNotice: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 55022;  
        static public ushort getProtoID() { return 55022; } 
        static public string getProtoName() { return "SceneGroupInviteNotice"; } 
        //members   
        public ulong avatarID;  
        public string avatarName;  
        public ulong groupID;  
        public SceneGroupInviteNotice()  
        { 
            avatarID = 0;  
            avatarName = "";  
            groupID = 0;  
        } 
        public SceneGroupInviteNotice(ulong avatarID, string avatarName, ulong groupID) 
        { 
            this.avatarID = avatarID; 
            this.avatarName = avatarName; 
            this.groupID = groupID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.avatarID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.avatarName)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.groupID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.avatarID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.avatarName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.groupID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SceneGroupRejectReq: Proto4z.IProtoObject //拒绝对方邀请  
    {     
        //proto id   
        public const ushort protoID = 55023;  
        static public ushort getProtoID() { return 55023; } 
        static public string getProtoName() { return "SceneGroupRejectReq"; } 
        //members   
        public ulong groupID;  
        public SceneGroupRejectReq()  
        { 
            groupID = 0;  
        } 
        public SceneGroupRejectReq(ulong groupID) 
        { 
            this.groupID = groupID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.groupID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.groupID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SceneGroupRejectResp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 55024;  
        static public ushort getProtoID() { return 55024; } 
        static public string getProtoName() { return "SceneGroupRejectResp"; } 
        //members   
        public ushort retCode;  
        public SceneGroupRejectResp()  
        { 
            retCode = 0;  
        } 
        public SceneGroupRejectResp(ushort retCode) 
        { 
            this.retCode = retCode; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SceneGroupLeaveReq: Proto4z.IProtoObject //离开编队  
    {     
        //proto id   
        public const ushort protoID = 55025;  
        static public ushort getProtoID() { return 55025; } 
        static public string getProtoName() { return "SceneGroupLeaveReq"; } 
        //members   
        public SceneGroupLeaveReq()  
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
 
    public class SceneGroupLeaveResp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 55026;  
        static public ushort getProtoID() { return 55026; } 
        static public string getProtoName() { return "SceneGroupLeaveResp"; } 
        //members   
        public ushort retCode;  
        public SceneGroupLeaveResp()  
        { 
            retCode = 0;  
        } 
        public SceneGroupLeaveResp(ushort retCode) 
        { 
            this.retCode = retCode; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class ChatReq: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 55027;  
        static public ushort getProtoID() { return 55027; } 
        static public string getProtoName() { return "ChatReq"; } 
        //members   
        public ushort channelID;  
        public ulong targetID;  
        public string msg;  
        public ChatReq()  
        { 
            channelID = 0;  
            targetID = 0;  
            msg = "";  
        } 
        public ChatReq(ushort channelID, ulong targetID, string msg) 
        { 
            this.channelID = channelID; 
            this.targetID = targetID; 
            this.msg = msg; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.channelID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.targetID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.msg)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.channelID = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.targetID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.msg = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class ChatResp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 55028;  
        static public ushort getProtoID() { return 55028; } 
        static public string getProtoName() { return "ChatResp"; } 
        //members   
        public ushort channelID;  
        public ulong sourceID;  
        public string sourceName;  
        public ulong targetID;  
        public string targetName;  
        public string msg;  
        public ulong chatTime;  
        public ChatResp()  
        { 
            channelID = 0;  
            sourceID = 0;  
            sourceName = "";  
            targetID = 0;  
            targetName = "";  
            msg = "";  
            chatTime = 0;  
        } 
        public ChatResp(ushort channelID, ulong sourceID, string sourceName, ulong targetID, string targetName, string msg, ulong chatTime) 
        { 
            this.channelID = channelID; 
            this.sourceID = sourceID; 
            this.sourceName = sourceName; 
            this.targetID = targetID; 
            this.targetName = targetName; 
            this.msg = msg; 
            this.chatTime = chatTime; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.channelID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.sourceID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.sourceName)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.targetID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.targetName)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.msg)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.chatTime)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.channelID = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.sourceID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.sourceName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.targetID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.targetName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.msg = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.chatTime = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class PingPongReq: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 55029;  
        static public ushort getProtoID() { return 55029; } 
        static public string getProtoName() { return "PingPongReq"; } 
        //members   
        public string msg;  
        public PingPongReq()  
        { 
            msg = "";  
        } 
        public PingPongReq(string msg) 
        { 
            this.msg = msg; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.msg)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.msg = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class PingPongResp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 55030;  
        static public ushort getProtoID() { return 55030; } 
        static public string getProtoName() { return "PingPongResp"; } 
        //members   
        public string msg;  
        public PingPongResp()  
        { 
            msg = "";  
        } 
        public PingPongResp(string msg) 
        { 
            this.msg = msg; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.msg)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.msg = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class ChangeIconIDReq: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 55031;  
        static public ushort getProtoID() { return 55031; } 
        static public string getProtoName() { return "ChangeIconIDReq"; } 
        //members   
        public ulong iconID;  
        public ChangeIconIDReq()  
        { 
            iconID = 0;  
        } 
        public ChangeIconIDReq(ulong iconID) 
        { 
            this.iconID = iconID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.iconID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.iconID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class ChangeIconIDResp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 55032;  
        static public ushort getProtoID() { return 55032; } 
        static public string getProtoName() { return "ChangeIconIDResp"; } 
        //members   
        public ushort retCode;  
        public ulong iconID;  
        public ChangeIconIDResp()  
        { 
            retCode = 0;  
            iconID = 0;  
        } 
        public ChangeIconIDResp(ushort retCode, ulong iconID) 
        { 
            this.retCode = retCode; 
            this.iconID = iconID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.iconID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.iconID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class ChangeModeIDReq: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 55033;  
        static public ushort getProtoID() { return 55033; } 
        static public string getProtoName() { return "ChangeModeIDReq"; } 
        //members   
        public ulong modeID;  
        public ChangeModeIDReq()  
        { 
            modeID = 0;  
        } 
        public ChangeModeIDReq(ulong modeID) 
        { 
            this.modeID = modeID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.modeID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.modeID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class ChangeModeIDResp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 55034;  
        static public ushort getProtoID() { return 55034; } 
        static public string getProtoName() { return "ChangeModeIDResp"; } 
        //members   
        public ushort retCode;  
        public ulong modeID;  
        public ChangeModeIDResp()  
        { 
            retCode = 0;  
            modeID = 0;  
        } 
        public ChangeModeIDResp(ushort retCode, ulong modeID) 
        { 
            this.retCode = retCode; 
            this.modeID = modeID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.modeID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.modeID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
} 
 
 

 
namespace Proto4z  
{ 
 
    public class ClientPulse: Proto4z.IProtoObject //客户端脉冲请求  
    {     
        //proto id   
        public const ushort protoID = 40034;  
        static public ushort getProtoID() { return 40034; } 
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
        public const ushort protoID = 40035;  
        static public ushort getProtoID() { return 40035; } 
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
        public const ushort protoID = 40036;  
        static public ushort getProtoID() { return 40036; } 
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
        public const ushort protoID = 40037;  
        static public ushort getProtoID() { return 40037; } 
        static public string getProtoName() { return "CreateAvatarReq"; } 
        //members   
        public string accountName; //这个字段会被服务器填充.客户端可以不填写  
        public string userName;  
        public CreateAvatarReq()  
        { 
            accountName = "";  
            userName = "";  
        } 
        public CreateAvatarReq(string accountName, string userName) 
        { 
            this.accountName = accountName; 
            this.userName = userName; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.accountName)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.userName)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.accountName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.userName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class CreateAvatarResp: Proto4z.IProtoObject //创角色请求返回  
    {     
        //proto id   
        public const ushort protoID = 40038;  
        static public ushort getProtoID() { return 40038; } 
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
 
    public class AttachAvatarReq: Proto4z.IProtoObject //选角色请求  
    {     
        //proto id   
        public const ushort protoID = 40039;  
        static public ushort getProtoID() { return 40039; } 
        static public string getProtoName() { return "AttachAvatarReq"; } 
        //members   
        public string accountName; //这个字段会被服务器填充.客户端可以不填写  
        public ulong avatarID;  
        public AttachAvatarReq()  
        { 
            accountName = "";  
            avatarID = 0;  
        } 
        public AttachAvatarReq(string accountName, ulong avatarID) 
        { 
            this.accountName = accountName; 
            this.avatarID = avatarID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.accountName)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.avatarID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.accountName = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.avatarID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class AttachAvatarResp: Proto4z.IProtoObject //选角色请求返回  
    {     
        //proto id   
        public const ushort protoID = 40040;  
        static public ushort getProtoID() { return 40040; } 
        static public string getProtoName() { return "AttachAvatarResp"; } 
        //members   
        public ushort retCode;  
        public AvatarBaseInfo baseInfo;  
        public AvatarPropMap props;  
        public AttachAvatarResp()  
        { 
            retCode = 0;  
            baseInfo = new AvatarBaseInfo();  
            props = new AvatarPropMap();  
        } 
        public AttachAvatarResp(ushort retCode, AvatarBaseInfo baseInfo, AvatarPropMap props) 
        { 
            this.retCode = retCode; 
            this.baseInfo = baseInfo; 
            this.props = props; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            if (this.baseInfo == null) this.baseInfo = new AvatarBaseInfo(); 
            data.AddRange(this.baseInfo.__encode()); 
            if (this.props == null) this.props = new AvatarPropMap(); 
            data.AddRange(this.props.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.baseInfo = new AvatarBaseInfo(); 
            this.baseInfo.__decode(binData, ref pos); 
            this.props = new AvatarPropMap(); 
            this.props.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class AvatarBaseInfoNotice: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 40041;  
        static public ushort getProtoID() { return 40041; } 
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
        public const ushort protoID = 40042;  
        static public ushort getProtoID() { return 40042; } 
        static public string getProtoName() { return "AvatarPropMapNotice"; } 
        //members   
        public ulong avatarID;  
        public AvatarPropMap props;  
        public AvatarPropMapNotice()  
        { 
            avatarID = 0;  
            props = new AvatarPropMap();  
        } 
        public AvatarPropMapNotice(ulong avatarID, AvatarPropMap props) 
        { 
            this.avatarID = avatarID; 
            this.props = props; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.avatarID)); 
            if (this.props == null) this.props = new AvatarPropMap(); 
            data.AddRange(this.props.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.avatarID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.props = new AvatarPropMap(); 
            this.props.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SceneGroupGetStatusReq: Proto4z.IProtoObject //获取当前角色的场景状态数据  
    {     
        //proto id   
        public const ushort protoID = 40043;  
        static public ushort getProtoID() { return 40043; } 
        static public string getProtoName() { return "SceneGroupGetStatusReq"; } 
        //members   
        public SceneGroupGetStatusReq()  
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
 
    public class SceneGroupGetStatusResp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 40044;  
        static public ushort getProtoID() { return 40044; } 
        static public string getProtoName() { return "SceneGroupGetStatusResp"; } 
        //members   
        public ushort retCode;  
        public SceneGroupGetStatusResp()  
        { 
            retCode = 0;  
        } 
        public SceneGroupGetStatusResp(ushort retCode) 
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
 
    public class SceneGroupAvatarInfo: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 40045;  
        static public ushort getProtoID() { return 40045; } 
        static public string getProtoName() { return "SceneGroupAvatarInfo"; } 
        //members   
        public AvatarBaseInfo baseInfo;  
        public ushort powerType; //0普通,1leader,2master  
        public SceneGroupAvatarInfo()  
        { 
            baseInfo = new AvatarBaseInfo();  
            powerType = 0;  
        } 
        public SceneGroupAvatarInfo(AvatarBaseInfo baseInfo, ushort powerType) 
        { 
            this.baseInfo = baseInfo; 
            this.powerType = powerType; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.baseInfo == null) this.baseInfo = new AvatarBaseInfo(); 
            data.AddRange(this.baseInfo.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.powerType)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.baseInfo = new AvatarBaseInfo(); 
            this.baseInfo.__decode(binData, ref pos); 
            this.powerType = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
 
    public class SceneGroupAvatarInfoArray : System.Collections.Generic.List<SceneGroupAvatarInfo>, Proto4z.IProtoObject  
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
                    var data = new SceneGroupAvatarInfo(); 
                    data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
    public class SceneGroupInfoNotice: Proto4z.IProtoObject //编队数据通知  
    {     
        //proto id   
        public const ushort protoID = 40046;  
        static public ushort getProtoID() { return 40046; } 
        static public string getProtoName() { return "SceneGroupInfoNotice"; } 
        //members   
        public ushort sceneType; //场景类型  
        public ulong mapID;  
        public ulong groupID;  
        public ushort sceneStatus; //状态  
        public ulong lineID; //分线ID  
        public ulong sceneID; //场景实例ID  
        public string host; //服务器host  
        public ushort port; //服务器port  
        public string token; //自己的令牌  
        public SceneGroupAvatarInfoArray members; //队友数据  
        public SceneGroupInfoNotice()  
        { 
            sceneType = 0;  
            mapID = 0;  
            groupID = 0;  
            sceneStatus = 0;  
            lineID = 0;  
            sceneID = 0;  
            host = "";  
            port = 0;  
            token = "";  
            members = new SceneGroupAvatarInfoArray();  
        } 
        public SceneGroupInfoNotice(ushort sceneType, ulong mapID, ulong groupID, ushort sceneStatus, ulong lineID, ulong sceneID, string host, ushort port, string token, SceneGroupAvatarInfoArray members) 
        { 
            this.sceneType = sceneType; 
            this.mapID = mapID; 
            this.groupID = groupID; 
            this.sceneStatus = sceneStatus; 
            this.lineID = lineID; 
            this.sceneID = sceneID; 
            this.host = host; 
            this.port = port; 
            this.token = token; 
            this.members = members; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.sceneType)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.mapID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.groupID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.sceneStatus)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.lineID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.sceneID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.host)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.port)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.token)); 
            if (this.members == null) this.members = new SceneGroupAvatarInfoArray(); 
            data.AddRange(this.members.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.sceneType = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.mapID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.groupID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.sceneStatus = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.lineID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.sceneID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.host = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.port = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.token = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            this.members = new SceneGroupAvatarInfoArray(); 
            this.members.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SceneGroupCreateReq: Proto4z.IProtoObject //发起组队请求  
    {     
        //proto id   
        public const ushort protoID = 40047;  
        static public ushort getProtoID() { return 40047; } 
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
        public const ushort protoID = 40048;  
        static public ushort getProtoID() { return 40048; } 
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
        public const ushort protoID = 40049;  
        static public ushort getProtoID() { return 40049; } 
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
        public const ushort protoID = 40050;  
        static public ushort getProtoID() { return 40050; } 
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
        public const ushort protoID = 40051;  
        static public ushort getProtoID() { return 40051; } 
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
        public const ushort protoID = 40052;  
        static public ushort getProtoID() { return 40052; } 
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
 
    public class SceneGroupRejectReq: Proto4z.IProtoObject //拒绝对方邀请  
    {     
        //proto id   
        public const ushort protoID = 40053;  
        static public ushort getProtoID() { return 40053; } 
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
        public const ushort protoID = 40054;  
        static public ushort getProtoID() { return 40054; } 
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
        public const ushort protoID = 40055;  
        static public ushort getProtoID() { return 40055; } 
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
        public const ushort protoID = 40056;  
        static public ushort getProtoID() { return 40056; } 
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
 
    public class SceneGroupEnterSceneReq: Proto4z.IProtoObject //申请进入场景  
    {     
        //proto id   
        public const ushort protoID = 40057;  
        static public ushort getProtoID() { return 40057; } 
        static public string getProtoName() { return "SceneGroupEnterSceneReq"; } 
        //members   
        public ushort sceneType;  
        public ulong mapID;  
        public SceneGroupEnterSceneReq()  
        { 
            sceneType = 0;  
            mapID = 0;  
        } 
        public SceneGroupEnterSceneReq(ushort sceneType, ulong mapID) 
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
 
    public class SceneGroupEnterSceneResp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 40058;  
        static public ushort getProtoID() { return 40058; } 
        static public string getProtoName() { return "SceneGroupEnterSceneResp"; } 
        //members   
        public ushort retCode;  
        public SceneGroupEnterSceneResp()  
        { 
            retCode = 0;  
        } 
        public SceneGroupEnterSceneResp(ushort retCode) 
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
 
    public class SceneGroupCancelEnterReq: Proto4z.IProtoObject //取消申请(根据状态不同会有取消匹配,重置状态,结束战斗(可中途结束的场景类型)  
    {     
        //proto id   
        public const ushort protoID = 40059;  
        static public ushort getProtoID() { return 40059; } 
        static public string getProtoName() { return "SceneGroupCancelEnterReq"; } 
        //members   
        public SceneGroupCancelEnterReq()  
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
 
    public class SceneGroupCancelEnterResp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 40060;  
        static public ushort getProtoID() { return 40060; } 
        static public string getProtoName() { return "SceneGroupCancelEnterResp"; } 
        //members   
        public ushort retCode;  
        public SceneGroupCancelEnterResp()  
        { 
            retCode = 0;  
        } 
        public SceneGroupCancelEnterResp(ushort retCode) 
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
        public const ushort protoID = 40061;  
        static public ushort getProtoID() { return 40061; } 
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
        public const ushort protoID = 40062;  
        static public ushort getProtoID() { return 40062; } 
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
        public const ushort protoID = 40063;  
        static public ushort getProtoID() { return 40063; } 
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
        public const ushort protoID = 40064;  
        static public ushort getProtoID() { return 40064; } 
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
        public const ushort protoID = 40065;  
        static public ushort getProtoID() { return 40065; } 
        static public string getProtoName() { return "ChangeIconIDReq"; } 
        //members   
        public int iconID;  
        public ChangeIconIDReq()  
        { 
            iconID = 0;  
        } 
        public ChangeIconIDReq(int iconID) 
        { 
            this.iconID = iconID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeI32(this.iconID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.iconID = Proto4z.BaseProtoObject.decodeI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class ChangeIconIDResp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 40066;  
        static public ushort getProtoID() { return 40066; } 
        static public string getProtoName() { return "ChangeIconIDResp"; } 
        //members   
        public ushort retCode;  
        public int iconID;  
        public ChangeIconIDResp()  
        { 
            retCode = 0;  
            iconID = 0;  
        } 
        public ChangeIconIDResp(ushort retCode, int iconID) 
        { 
            this.retCode = retCode; 
            this.iconID = iconID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeI32(this.iconID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.iconID = Proto4z.BaseProtoObject.decodeI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class ChangeModeIDReq: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 40067;  
        static public ushort getProtoID() { return 40067; } 
        static public string getProtoName() { return "ChangeModeIDReq"; } 
        //members   
        public int modeID;  
        public ChangeModeIDReq()  
        { 
            modeID = 0;  
        } 
        public ChangeModeIDReq(int modeID) 
        { 
            this.modeID = modeID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeI32(this.modeID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.modeID = Proto4z.BaseProtoObject.decodeI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class ChangeModeIDResp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 40068;  
        static public ushort getProtoID() { return 40068; } 
        static public string getProtoName() { return "ChangeModeIDResp"; } 
        //members   
        public ushort retCode;  
        public int modeID;  
        public ChangeModeIDResp()  
        { 
            retCode = 0;  
            modeID = 0;  
        } 
        public ChangeModeIDResp(ushort retCode, int modeID) 
        { 
            this.retCode = retCode; 
            this.modeID = modeID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeI32(this.modeID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.modeID = Proto4z.BaseProtoObject.decodeI32(binData, ref pos); 
            return pos; 
        } 
    } 
 
} 
 
 

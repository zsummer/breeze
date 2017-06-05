 
namespace Proto4z  
{ 
 
    public class SceneClientPulse: Proto4z.IProtoObject //客户端脉冲请求  
    {     
        //proto id   
        public const ushort protoID = 50000;  
        static public ushort getProtoID() { return 50000; } 
        static public string getProtoName() { return "SceneClientPulse"; } 
        //members   
        public SceneClientPulse()  
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
 
    public class AttachSceneReq: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 50001;  
        static public ushort getProtoID() { return 50001; } 
        static public string getProtoName() { return "AttachSceneReq"; } 
        //members   
        public ulong avatarID;  
        public ulong sceneID;  
        public string token; //令牌  
        public AttachSceneReq()  
        { 
            avatarID = 0;  
            sceneID = 0;  
            token = "";  
        } 
        public AttachSceneReq(ulong avatarID, ulong sceneID, string token) 
        { 
            this.avatarID = avatarID; 
            this.sceneID = sceneID; 
            this.token = token; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.avatarID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.sceneID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.token)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.avatarID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.sceneID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.token = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class AttachSceneResp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 50002;  
        static public ushort getProtoID() { return 50002; } 
        static public string getProtoName() { return "AttachSceneResp"; } 
        //members   
        public ushort retCode; //错误码  
        public ulong avatarID;  
        public ulong sceneID;  
        public AttachSceneResp()  
        { 
            retCode = 0;  
            avatarID = 0;  
            sceneID = 0;  
        } 
        public AttachSceneResp(ushort retCode, ulong avatarID, ulong sceneID) 
        { 
            this.retCode = retCode; 
            this.avatarID = avatarID; 
            this.sceneID = sceneID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.avatarID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.sceneID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.avatarID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.sceneID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SceneSectionNotice: Proto4z.IProtoObject //填充场景数据  
    {     
        //proto id   
        public const ushort protoID = 50003;  
        static public ushort getProtoID() { return 50003; } 
        static public string getProtoName() { return "SceneSectionNotice"; } 
        //members   
        public SceneSection section;  
        public SceneSectionNotice()  
        { 
            section = new SceneSection();  
        } 
        public SceneSectionNotice(SceneSection section) 
        { 
            this.section = section; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.section == null) this.section = new SceneSection(); 
            data.AddRange(this.section.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.section = new SceneSection(); 
            this.section.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SceneRefreshNotice: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 50004;  
        static public ushort getProtoID() { return 50004; } 
        static public string getProtoName() { return "SceneRefreshNotice"; } 
        //members   
        public DictPropArray entityProps;  
        public EntityStateArray entityStates;  
        public EntityMoveArray entityMoves;  
        public SceneRefreshNotice()  
        { 
            entityProps = new DictPropArray();  
            entityStates = new EntityStateArray();  
            entityMoves = new EntityMoveArray();  
        } 
        public SceneRefreshNotice(DictPropArray entityProps, EntityStateArray entityStates, EntityMoveArray entityMoves) 
        { 
            this.entityProps = entityProps; 
            this.entityStates = entityStates; 
            this.entityMoves = entityMoves; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.entityProps == null) this.entityProps = new DictPropArray(); 
            data.AddRange(this.entityProps.__encode()); 
            if (this.entityStates == null) this.entityStates = new EntityStateArray(); 
            data.AddRange(this.entityStates.__encode()); 
            if (this.entityMoves == null) this.entityMoves = new EntityMoveArray(); 
            data.AddRange(this.entityMoves.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.entityProps = new DictPropArray(); 
            this.entityProps.__decode(binData, ref pos); 
            this.entityStates = new EntityStateArray(); 
            this.entityStates.__decode(binData, ref pos); 
            this.entityMoves = new EntityMoveArray(); 
            this.entityMoves.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SceneReportsNotice: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 50005;  
        static public ushort getProtoID() { return 50005; } 
        static public string getProtoName() { return "SceneReportsNotice"; } 
        //members   
        public EntityReportArray reports;  
        public SceneReportsNotice()  
        { 
            reports = new EntityReportArray();  
        } 
        public SceneReportsNotice(EntityReportArray reports) 
        { 
            this.reports = reports; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.reports == null) this.reports = new EntityReportArray(); 
            data.AddRange(this.reports.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.reports = new EntityReportArray(); 
            this.reports.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class AddEntityNotice: Proto4z.IProtoObject //一批实体加入场景时, 把这些实体的数据广播给其他玩家  
    {     
        //proto id   
        public const ushort protoID = 50006;  
        static public ushort getProtoID() { return 50006; } 
        static public string getProtoName() { return "AddEntityNotice"; } 
        //members   
        public EntityClientSyncArray syncs;  
        public AddEntityNotice()  
        { 
            syncs = new EntityClientSyncArray();  
        } 
        public AddEntityNotice(EntityClientSyncArray syncs) 
        { 
            this.syncs = syncs; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.syncs == null) this.syncs = new EntityClientSyncArray(); 
            data.AddRange(this.syncs.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.syncs = new EntityClientSyncArray(); 
            this.syncs.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class RemoveEntityNotice: Proto4z.IProtoObject //实体离开场景时, 把该实体的数据广播给其他玩家  
    {     
        //proto id   
        public const ushort protoID = 50007;  
        static public ushort getProtoID() { return 50007; } 
        static public string getProtoName() { return "RemoveEntityNotice"; } 
        //members   
        public EntityIDArray eids;  
        public RemoveEntityNotice()  
        { 
            eids = new EntityIDArray();  
        } 
        public RemoveEntityNotice(EntityIDArray eids) 
        { 
            this.eids = eids; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.eids == null) this.eids = new EntityIDArray(); 
            data.AddRange(this.eids.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.eids = new EntityIDArray(); 
            this.eids.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class MoveReq: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 50008;  
        static public ushort getProtoID() { return 50008; } 
        static public string getProtoName() { return "MoveReq"; } 
        //members   
        public ulong eid;  
        public ushort action;  
        public EPosition clientPos;  
        public EPositionArray waypoints;  
        public ulong follow;  
        public MoveReq()  
        { 
            eid = 0;  
            action = 0;  
            clientPos = new EPosition();  
            waypoints = new EPositionArray();  
            follow = 0;  
        } 
        public MoveReq(ulong eid, ushort action, EPosition clientPos, EPositionArray waypoints, ulong follow) 
        { 
            this.eid = eid; 
            this.action = action; 
            this.clientPos = clientPos; 
            this.waypoints = waypoints; 
            this.follow = follow; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.eid)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.action)); 
            if (this.clientPos == null) this.clientPos = new EPosition(); 
            data.AddRange(this.clientPos.__encode()); 
            if (this.waypoints == null) this.waypoints = new EPositionArray(); 
            data.AddRange(this.waypoints.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.follow)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.eid = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.action = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.clientPos = new EPosition(); 
            this.clientPos.__decode(binData, ref pos); 
            this.waypoints = new EPositionArray(); 
            this.waypoints.__decode(binData, ref pos); 
            this.follow = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class MoveResp: Proto4z.IProtoObject //只有失败时才会使用该协议  
    {     
        //proto id   
        public const ushort protoID = 50009;  
        static public ushort getProtoID() { return 50009; } 
        static public string getProtoName() { return "MoveResp"; } 
        //members   
        public ushort retCode;  
        public ulong eid;  
        public ushort action;  
        public MoveResp()  
        { 
            retCode = 0;  
            eid = 0;  
            action = 0;  
        } 
        public MoveResp(ushort retCode, ulong eid, ushort action) 
        { 
            this.retCode = retCode; 
            this.eid = eid; 
            this.action = action; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.eid)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.action)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.eid = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.action = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class MoveNotice: Proto4z.IProtoObject //移动开始/结束通知  
    {     
        //proto id   
        public const ushort protoID = 50010;  
        static public ushort getProtoID() { return 50010; } 
        static public string getProtoName() { return "MoveNotice"; } 
        //members   
        public EntityMove moveInfo;  
        public MoveNotice()  
        { 
            moveInfo = new EntityMove();  
        } 
        public MoveNotice(EntityMove moveInfo) 
        { 
            this.moveInfo = moveInfo; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.moveInfo == null) this.moveInfo = new EntityMove(); 
            data.AddRange(this.moveInfo.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.moveInfo = new EntityMove(); 
            this.moveInfo.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class AddBuffNotice: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 50011;  
        static public ushort getProtoID() { return 50011; } 
        static public string getProtoName() { return "AddBuffNotice"; } 
        //members   
        public ulong eid;  
        public AddBuffNotice()  
        { 
            eid = 0;  
        } 
        public AddBuffNotice(ulong eid) 
        { 
            this.eid = eid; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.eid)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.eid = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class RemoveBuffNotice: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 50012;  
        static public ushort getProtoID() { return 50012; } 
        static public string getProtoName() { return "RemoveBuffNotice"; } 
        //members   
        public ulong eid;  
        public RemoveBuffNotice()  
        { 
            eid = 0;  
        } 
        public RemoveBuffNotice(ulong eid) 
        { 
            this.eid = eid; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.eid)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.eid = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class UseSkillReq: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 50013;  
        static public ushort getProtoID() { return 50013; } 
        static public string getProtoName() { return "UseSkillReq"; } 
        //members   
        public ulong eid;  
        public ulong skillID;  
        public EPosition dst;  
        public ushort foeFirst;  
        public UseSkillReq()  
        { 
            eid = 0;  
            skillID = 0;  
            dst = new EPosition();  
            foeFirst = 0;  
        } 
        public UseSkillReq(ulong eid, ulong skillID, EPosition dst, ushort foeFirst) 
        { 
            this.eid = eid; 
            this.skillID = skillID; 
            this.dst = dst; 
            this.foeFirst = foeFirst; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.eid)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.skillID)); 
            if (this.dst == null) this.dst = new EPosition(); 
            data.AddRange(this.dst.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.foeFirst)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.eid = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.skillID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.dst = new EPosition(); 
            this.dst.__decode(binData, ref pos); 
            this.foeFirst = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class UseSkillResp: Proto4z.IProtoObject //只有失败时才会使用该协议  
    {     
        //proto id   
        public const ushort protoID = 50014;  
        static public ushort getProtoID() { return 50014; } 
        static public string getProtoName() { return "UseSkillResp"; } 
        //members   
        public ushort retCode;  
        public ulong eid;  
        public ulong skillID;  
        public EPosition dst;  
        public ushort foeFirst;  
        public UseSkillResp()  
        { 
            retCode = 0;  
            eid = 0;  
            skillID = 0;  
            dst = new EPosition();  
            foeFirst = 0;  
        } 
        public UseSkillResp(ushort retCode, ulong eid, ulong skillID, EPosition dst, ushort foeFirst) 
        { 
            this.retCode = retCode; 
            this.eid = eid; 
            this.skillID = skillID; 
            this.dst = dst; 
            this.foeFirst = foeFirst; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.eid)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.skillID)); 
            if (this.dst == null) this.dst = new EPosition(); 
            data.AddRange(this.dst.__encode()); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.foeFirst)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.eid = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.skillID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.dst = new EPosition(); 
            this.dst.__decode(binData, ref pos); 
            this.foeFirst = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class UseSkillNotice: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 50015;  
        static public ushort getProtoID() { return 50015; } 
        static public string getProtoName() { return "UseSkillNotice"; } 
        //members   
        public ulong eid;  
        public EntitySkillInfo skill;  
        public UseSkillNotice()  
        { 
            eid = 0;  
            skill = new EntitySkillInfo();  
        } 
        public UseSkillNotice(ulong eid, EntitySkillInfo skill) 
        { 
            this.eid = eid; 
            this.skill = skill; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.eid)); 
            if (this.skill == null) this.skill = new EntitySkillInfo(); 
            data.AddRange(this.skill.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.eid = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.skill = new EntitySkillInfo(); 
            this.skill.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class SceneEventNotice: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 50016;  
        static public ushort getProtoID() { return 50016; } 
        static public string getProtoName() { return "SceneEventNotice"; } 
        //members   
        public SceneEventInfoArray info;  
        public SceneEventNotice()  
        { 
            info = new SceneEventInfoArray();  
        } 
        public SceneEventNotice(SceneEventInfoArray info) 
        { 
            this.info = info; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            if (this.info == null) this.info = new SceneEventInfoArray(); 
            data.AddRange(this.info.__encode()); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.info = new SceneEventInfoArray(); 
            this.info.__decode(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class ClientCustomReq: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 50017;  
        static public ushort getProtoID() { return 50017; } 
        static public string getProtoName() { return "ClientCustomReq"; } 
        //members   
        public ulong eid;  
        public ulong customID;  
        public double fValue;  
        public ulong uValue;  
        public string sValue;  
        public ClientCustomReq()  
        { 
            eid = 0;  
            customID = 0;  
            fValue = 0.0;  
            uValue = 0;  
            sValue = "";  
        } 
        public ClientCustomReq(ulong eid, ulong customID, double fValue, ulong uValue, string sValue) 
        { 
            this.eid = eid; 
            this.customID = customID; 
            this.fValue = fValue; 
            this.uValue = uValue; 
            this.sValue = sValue; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.eid)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.customID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.fValue)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.uValue)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.sValue)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.eid = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.customID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.fValue = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.uValue = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.sValue = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class ClientCustomResp: Proto4z.IProtoObject //只有失败时才会使用该协议  
    {     
        //proto id   
        public const ushort protoID = 50018;  
        static public ushort getProtoID() { return 50018; } 
        static public string getProtoName() { return "ClientCustomResp"; } 
        //members   
        public ushort retCode;  
        public ulong eid;  
        public ulong customID;  
        public ClientCustomResp()  
        { 
            retCode = 0;  
            eid = 0;  
            customID = 0;  
        } 
        public ClientCustomResp(ushort retCode, ulong eid, ulong customID) 
        { 
            this.retCode = retCode; 
            this.eid = eid; 
            this.customID = customID; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.eid)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.customID)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.eid = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.customID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class ClientCustomNotice: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 50019;  
        static public ushort getProtoID() { return 50019; } 
        static public string getProtoName() { return "ClientCustomNotice"; } 
        //members   
        public ulong eid;  
        public ulong customID;  
        public double fValue;  
        public ulong uValue;  
        public string sValue;  
        public ClientCustomNotice()  
        { 
            eid = 0;  
            customID = 0;  
            fValue = 0.0;  
            uValue = 0;  
            sValue = "";  
        } 
        public ClientCustomNotice(ulong eid, ulong customID, double fValue, ulong uValue, string sValue) 
        { 
            this.eid = eid; 
            this.customID = customID; 
            this.fValue = fValue; 
            this.uValue = uValue; 
            this.sValue = sValue; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.eid)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.customID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.fValue)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.uValue)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeString(this.sValue)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.eid = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.customID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.fValue = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            this.uValue = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.sValue = Proto4z.BaseProtoObject.decodeString(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class ClientPingTestReq: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 50020;  
        static public ushort getProtoID() { return 50020; } 
        static public string getProtoName() { return "ClientPingTestReq"; } 
        //members   
        public ulong seqID;  
        public double clientTime;  
        public ClientPingTestReq()  
        { 
            seqID = 0;  
            clientTime = 0.0;  
        } 
        public ClientPingTestReq(ulong seqID, double clientTime) 
        { 
            this.seqID = seqID; 
            this.clientTime = clientTime; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.seqID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.clientTime)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.seqID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.clientTime = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            return pos; 
        } 
    } 
 
    public class ClientPingTestResp: Proto4z.IProtoObject 
    {     
        //proto id   
        public const ushort protoID = 50021;  
        static public ushort getProtoID() { return 50021; } 
        static public string getProtoName() { return "ClientPingTestResp"; } 
        //members   
        public ushort retCode;  
        public ulong seqID;  
        public double clientTime;  
        public ClientPingTestResp()  
        { 
            retCode = 0;  
            seqID = 0;  
            clientTime = 0.0;  
        } 
        public ClientPingTestResp(ushort retCode, ulong seqID, double clientTime) 
        { 
            this.retCode = retCode; 
            this.seqID = seqID; 
            this.clientTime = clientTime; 
        } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI16(this.retCode)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeUI64(this.seqID)); 
            data.AddRange(Proto4z.BaseProtoObject.encodeDouble(this.clientTime)); 
            return data; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            this.retCode = Proto4z.BaseProtoObject.decodeUI16(binData, ref pos); 
            this.seqID = Proto4z.BaseProtoObject.decodeUI64(binData, ref pos); 
            this.clientTime = Proto4z.BaseProtoObject.decodeDouble(binData, ref pos); 
            return pos; 
        } 
    } 
 
} 
 
 

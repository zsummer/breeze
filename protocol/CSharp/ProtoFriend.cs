 
namespace Proto4z  
{ 
    class STATIC_FRIEND_DELETED //已删除好友关系 
    { 
        public static Proto4z.ui8 value = 0;  
    } 
    class STATIC_FRIEND_WAITING //等待好友确认 
    { 
        public static Proto4z.ui8 value = 1;  
    } 
    class STATIC_FRIEND_REQUESTING //需要确认 
    { 
        public static Proto4z.ui8 value = 2;  
    } 
    class STATIC_FRIEND_BLACKLIST //黑名单 
    { 
        public static Proto4z.ui8 value = 3;  
    } 
    class STATIC_FRIEND_ESTABLISHED //好友 
    { 
        public static Proto4z.ui8 value = 4;  
    } 
    class STATIC_FRIEND_ADD_FRIEND //添加好友 
    { 
        public static Proto4z.ui8 value = 0;  
    } 
    class STATIC_FRIEND_REMOVE_FRIEND //移除好友 
    { 
        public static Proto4z.ui8 value = 1;  
    } 
    class STATIC_FRIEND_ADD_BLACKLIST //添加黑名单 
    { 
        public static Proto4z.ui8 value = 2;  
    } 
    class STATIC_FRIEND_REMOVE_BLACKLIST //移除黑名单 
    { 
        public static Proto4z.ui8 value = 3;  
    } 
    class STATIC_FRIEND_ALLOW //同意 
    { 
        public static Proto4z.ui8 value = 4;  
    } 
    class STATIC_FRIEND_REJECT //拒绝 
    { 
        public static Proto4z.ui8 value = 5;  
    } 
    class STATIC_FRIEND_IGNORE //忽略 
    { 
        public static Proto4z.ui8 value = 6;  
    } 
 
    class FriendInfo: Proto4z.IProtoObject //好友信息 
    {     
        public Proto4z.ui64 ownID;  
        public Proto4z.ui64 fID;  
        public Proto4z.ui8 flag; //状态标志 
        public Proto4z.ui8 online; //好友是否在线,不需要存数据库 
        public Proto4z.ui32 makeTime; //建立时间 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            Proto4z.ui32 sttLen = 0; 
            Proto4z.ui64 tag = 31; 
             
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(ownID.__encode()); 
            data.AddRange(fID.__encode()); 
            data.AddRange(flag.__encode()); 
            data.AddRange(online.__encode()); 
            data.AddRange(makeTime.__encode()); 
            sttLen = (System.UInt32)data.Count + 8; 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(sttLen.__encode()); 
            ret.AddRange(tag.__encode()); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            Proto4z.ui32 offset = 0; 
            Proto4z.ui64 tag = 0; 
            offset.__decode(binData, ref pos); 
            offset.val += (System.UInt32)pos; 
            tag.__decode(binData, ref pos); 
            ownID = new Proto4z.ui64(); 
            if ((tag.val & ((System.UInt64)1 << 0)) != 0) 
            { 
                ownID.__decode(binData, ref pos); 
            } 
            fID = new Proto4z.ui64(); 
            if ((tag.val & ((System.UInt64)1 << 1)) != 0) 
            { 
                fID.__decode(binData, ref pos); 
            } 
            flag = new Proto4z.ui8(); 
            if ((tag.val & ((System.UInt64)1 << 2)) != 0) 
            { 
                flag.__decode(binData, ref pos); 
            } 
            online = new Proto4z.ui8(); 
            if ((tag.val & ((System.UInt64)1 << 3)) != 0) 
            { 
                online.__decode(binData, ref pos); 
            } 
            makeTime = new Proto4z.ui32(); 
            if ((tag.val & ((System.UInt64)1 << 4)) != 0) 
            { 
                makeTime.__decode(binData, ref pos); 
            } 
            return (int)offset.val; 
        } 
    } 
 
    class FriendInfoArray : System.Collections.Generic.List<FriendInfo>, Proto4z.IProtoObject  
    { 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            var ret = new System.Collections.Generic.List<byte>(); 
             var len = new Proto4z.ui32((System.UInt32)this.Count); 
            ret.AddRange(len.__encode()); 
            for (int i = 0; i < this.Count; i++ ) 
            { 
                ret.AddRange(this[i].__encode()); 
            } 
            return ret; 
        } 
 
        public int __decode(byte[] binData, ref int pos) 
        { 
            var len = new Proto4z.ui32(0); 
            len.__decode(binData, ref pos); 
            if(len.val > 0) 
            { 
                for (int i=0; i<len.val; i++) 
                { 
                    var data = new FriendInfo(); 
                     data.__decode(binData, ref pos); 
                    this.Add(data); 
                } 
            } 
            return pos; 
        } 
    } 
 
    class GetFriendsReq: Proto4z.IProtoObject //获取好友列表 
    {     
        static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(1005); } 
        static public string getProtoName() { return "GetFriendsReq"; } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            Proto4z.ui32 sttLen = 0; 
            Proto4z.ui64 tag = 0; 
             
            var data = new System.Collections.Generic.List<byte>(); 
            sttLen = (System.UInt32)data.Count + 8; 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(sttLen.__encode()); 
            ret.AddRange(tag.__encode()); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            Proto4z.ui32 offset = 0; 
            Proto4z.ui64 tag = 0; 
            offset.__decode(binData, ref pos); 
            offset.val += (System.UInt32)pos; 
            tag.__decode(binData, ref pos); 
            return (int)offset.val; 
        } 
    } 
 
    class UpdateFriendsNotice: Proto4z.IProtoObject //好友列表推送通知 
    {     
        static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(1006); } 
        static public string getProtoName() { return "UpdateFriendsNotice"; } 
        public FriendInfoArray friends;  
        public System.Collections.Generic.List<byte> __encode() 
        { 
            Proto4z.ui32 sttLen = 0; 
            Proto4z.ui64 tag = 1; 
             
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(friends.__encode()); 
            sttLen = (System.UInt32)data.Count + 8; 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(sttLen.__encode()); 
            ret.AddRange(tag.__encode()); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            Proto4z.ui32 offset = 0; 
            Proto4z.ui64 tag = 0; 
            offset.__decode(binData, ref pos); 
            offset.val += (System.UInt32)pos; 
            tag.__decode(binData, ref pos); 
            friends = new FriendInfoArray(); 
            if ((tag.val & ((System.UInt64)1 << 0)) != 0) 
            { 
                friends.__decode(binData, ref pos); 
            } 
            return (int)offset.val; 
        } 
    } 
 
    class FriendOperationReq: Proto4z.IProtoObject //好友操作请求 
    {     
        static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(1002); } 
        static public string getProtoName() { return "FriendOperationReq"; } 
        public Proto4z.ui64 dst; //目标ID 
        public Proto4z.ui8 instruct; //操作指令 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            Proto4z.ui32 sttLen = 0; 
            Proto4z.ui64 tag = 3; 
             
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(dst.__encode()); 
            data.AddRange(instruct.__encode()); 
            sttLen = (System.UInt32)data.Count + 8; 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(sttLen.__encode()); 
            ret.AddRange(tag.__encode()); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            Proto4z.ui32 offset = 0; 
            Proto4z.ui64 tag = 0; 
            offset.__decode(binData, ref pos); 
            offset.val += (System.UInt32)pos; 
            tag.__decode(binData, ref pos); 
            dst = new Proto4z.ui64(); 
            if ((tag.val & ((System.UInt64)1 << 0)) != 0) 
            { 
                dst.__decode(binData, ref pos); 
            } 
            instruct = new Proto4z.ui8(); 
            if ((tag.val & ((System.UInt64)1 << 1)) != 0) 
            { 
                instruct.__decode(binData, ref pos); 
            } 
            return (int)offset.val; 
        } 
    } 
 
    class FriendOperationNotice: Proto4z.IProtoObject //好友操作推送通知 
    {     
        static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(1004); } 
        static public string getProtoName() { return "FriendOperationNotice"; } 
        public Proto4z.ui16 retCode;  
        public Proto4z.ui64 src; //发起操作的用户 
        public Proto4z.ui8 instruct; //发起的操作指令 
        public Proto4z.ui64 dst; //操作目标用户 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            Proto4z.ui32 sttLen = 0; 
            Proto4z.ui64 tag = 15; 
             
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(retCode.__encode()); 
            data.AddRange(src.__encode()); 
            data.AddRange(instruct.__encode()); 
            data.AddRange(dst.__encode()); 
            sttLen = (System.UInt32)data.Count + 8; 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(sttLen.__encode()); 
            ret.AddRange(tag.__encode()); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            Proto4z.ui32 offset = 0; 
            Proto4z.ui64 tag = 0; 
            offset.__decode(binData, ref pos); 
            offset.val += (System.UInt32)pos; 
            tag.__decode(binData, ref pos); 
            retCode = new Proto4z.ui16(); 
            if ((tag.val & ((System.UInt64)1 << 0)) != 0) 
            { 
                retCode.__decode(binData, ref pos); 
            } 
            src = new Proto4z.ui64(); 
            if ((tag.val & ((System.UInt64)1 << 1)) != 0) 
            { 
                src.__decode(binData, ref pos); 
            } 
            instruct = new Proto4z.ui8(); 
            if ((tag.val & ((System.UInt64)1 << 2)) != 0) 
            { 
                instruct.__decode(binData, ref pos); 
            } 
            dst = new Proto4z.ui64(); 
            if ((tag.val & ((System.UInt64)1 << 3)) != 0) 
            { 
                dst.__decode(binData, ref pos); 
            } 
            return (int)offset.val; 
        } 
    } 
 
    class GetSomeStrangersReq: Proto4z.IProtoObject //获取一些陌生人 
    {     
        static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(1000); } 
        static public string getProtoName() { return "GetSomeStrangersReq"; } 
        public System.Collections.Generic.List<byte> __encode() 
        { 
            Proto4z.ui32 sttLen = 0; 
            Proto4z.ui64 tag = 0; 
             
            var data = new System.Collections.Generic.List<byte>(); 
            sttLen = (System.UInt32)data.Count + 8; 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(sttLen.__encode()); 
            ret.AddRange(tag.__encode()); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            Proto4z.ui32 offset = 0; 
            Proto4z.ui64 tag = 0; 
            offset.__decode(binData, ref pos); 
            offset.val += (System.UInt32)pos; 
            tag.__decode(binData, ref pos); 
            return (int)offset.val; 
        } 
    } 
 
    class GetSomeStrangersAck: Proto4z.IProtoObject //获取一些陌生人 
    {     
        static public Proto4z.ui16 getProtoID() { return new Proto4z.ui16(1001); } 
        static public string getProtoName() { return "GetSomeStrangersAck"; } 
        public Proto4z.ui16 retCode;  
        public UserIDArray uIDs;  
        public System.Collections.Generic.List<byte> __encode() 
        { 
            Proto4z.ui32 sttLen = 0; 
            Proto4z.ui64 tag = 3; 
             
            var data = new System.Collections.Generic.List<byte>(); 
            data.AddRange(retCode.__encode()); 
            data.AddRange(uIDs.__encode()); 
            sttLen = (System.UInt32)data.Count + 8; 
            var ret = new System.Collections.Generic.List<byte>(); 
            ret.AddRange(sttLen.__encode()); 
            ret.AddRange(tag.__encode()); 
            ret.AddRange(data); 
            return ret; 
        } 
        public int __decode(byte[] binData, ref int pos) 
        { 
            Proto4z.ui32 offset = 0; 
            Proto4z.ui64 tag = 0; 
            offset.__decode(binData, ref pos); 
            offset.val += (System.UInt32)pos; 
            tag.__decode(binData, ref pos); 
            retCode = new Proto4z.ui16(); 
            if ((tag.val & ((System.UInt64)1 << 0)) != 0) 
            { 
                retCode.__decode(binData, ref pos); 
            } 
            uIDs = new UserIDArray(); 
            if ((tag.val & ((System.UInt64)1 << 1)) != 0) 
            { 
                uIDs.__decode(binData, ref pos); 
            } 
            return (int)offset.val; 
        } 
    } 
 
} 
 
 

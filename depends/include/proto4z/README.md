Welcome to the proto4z wiki!  
## Introduction:    
[![Build Status](https://travis-ci.org/zsummer/proto4z.svg?branch=master)](https://travis-ci.org/zsummer/proto4z)  
proto4z  is an efficient serialization library for C++, lua, C#, It's like Google protocol buffers.  
proto4z是一个序列化工具库, 可以通过一次编写xml格式的数据结构, 使用genProto工具一键生成对应的C++,lua,C#的原生数据结构和对应的序列化/反序列化代码, 并且通过开关可以额外生成C++使用的MYSQL增删改查的接口代码(和dbHelper.h配合使用).  


##example  
**这里提供一套简单的模板配置和对应的测试代码. 完整版的测试见项目test/genCode目录下的测试例子.**
  
###xml idl  
```  
<?xml version="1.0" encoding="utf-8"?>
<ProtoTraits>
    <MinNo>30000</MinNo>
    <MaxNo>32000</MaxNo>
</ProtoTraits>
<Proto>
    <packet    name="MoneyTree" desc= "摇钱树功能模块">
        <member name="lastTime" type="ui32"  desc="最后一次执行时间"/>
        <member name="freeCount" type="ui32"  desc="今日剩余免费次数"/>
        <member name="payCount" type="ui32"  desc="今日已购买次数"/>
        <member name="statSum" type="ui32" desc="历史总和"/>
        <member name="statCount" type="ui32" desc="历史总次数"/>
    </packet>
    <packet    name="SimplePack" desc= "简单示例">
        <member name="id" type="ui32" tag="auto,key"     desc="id, 对应数据库的结构为自增ID,key"/>
        <member name="name" type="string" tag="uni"     desc="昵称, 唯一索引"/>
        <member name="createTime" type="ui32" tag="idx"     desc="创建时间, 普通索引"/>
        <member name="moneyTree" type="MoneyTree"     desc=""/>
    </packet>
</Proto>
```   
###lua code  

**test serializable/deserialize code**  
```  
--require
require("proto4z")
require("TestProto")
local pack = {id=10, name="name", createTime=100, moneyTree={lastTime=1,freeCount=5,payCount=5,statSum=0,statCount=0}}
local binMemory = Proto4z.encode(pack, "SimplePack") --序列化  
local recvPack = Proto4z.decode(binMemory, Proto4z.getName(Proto4z.SimplePack.__protoID)) --反序列化  
Proto4z.dump(recvPack)
```

###c++ test code  

**test serializable/deserialize code**  
```  
    try
    {
        
        SimplePack pack;
        pack.id = 10;
        pack.name = "aaa";
        pack.createTime = time(NULL);
        pack.moneyTree.freeCount = 0;
        pack.moneyTree.lastTime = pack.createTime;
        pack.moneyTree.statSum = 0;
        pack.moneyTree.statCount = 0;
        pack.moneyTree.payCount = 0;

        //序列化
        WriteStream ws(SimplePack::getProtoID());
        ws << pack;
        //反序列化
        ReadStream rs(ws.getStream(), ws.getStreamLen());
        rs >> pack;
        cout << "success" << endl;
    }
    catch (const std::exception & e)
    {
        cout << "error:" << e.what() << endl;
    }
```  

###c# code  

**test serializable/deserialize code**  
```  
        try
        {
            SimplePack pk = new SimplePack(10, "name", 100, null);
            pk.moneyTree = new MoneyTree(10001, 5, 5, 0, 0);
            var binMemory = pk.__encode().ToArray();  //序列化  

            SimplePack recvPK = new SimplePack();
            int curPos = 0;
            recvPK.__decode(binMemory, ref curPos);
            System.Console.Write("success");
        }
        catch(Exception e)
        {
            System.Console.Write("error");
        }
```  

###sql code  
**test sql build, load, select, insert, del code**  
```  
        SimplePack pack;
        pack.id = 10;
        pack.name = "aaa";
        pack.createTime = time(NULL);
        pack.moneyTree.freeCount = 0;
        pack.moneyTree.lastTime = pack.createTime;
        pack.moneyTree.statSum = 0;
        pack.moneyTree.statCount = 0;
        pack.moneyTree.payCount = 0;

        DBHelperPtr dbHelper = std::make_shared<DBHelper>();
        dbHelper->init(dbConfig._ip, dbConfig._port, dbConfig._db, dbConfig._user, dbConfig._pwd, true); //最后一个true可以自动创建库如果库不存在 
        if (!dbHelper->connect())
        {
            return false;
        }
        dbhelper->query(pack.getDBBuild()); //创建对应的表,并自动alter普通字段 . 
        if (dbhelper->query(pack.getDBInsert())->getErrorCode() != QEC_SUCCESS)
        {
            return false;
        }
        if (dbhelper->query(pack.getDBUpdate())->getErrorCode() != QEC_SUCCESS)
        {
            return false;
        }
        auto ret = dbhelper->query(pack.getDBSelect());
        if (ret->getErrorCode() == QEC_SUCCESS)
        {
            if (!pack.fetchFromDBResult(*ret))
            {
                return false;
            }
        }
```  
  
###http code  
**test http serializable/deserialize code. (和模板配置无关)**
```  
    TestHTTP th;
    WriteHTTP whGet;
    whGet.addHead("Content-Type", "application/x-www-form-urlencoded");
    whGet.addHead("Host", "www.google.com");
    whGet.get("/");
    th.Test(whGet);

    WriteHTTP whPost;
    whPost.addHead("Content-Type", "application/x-www-form-urlencoded");
    whPost.addHead("Host", "www.google.com");
    whPost.post("/", "index.php?aaa=333");
    th.Test(whPost);

    WriteHTTP whResult;
    whResult.addHead("test", "test");
    whResult.addHead("Content-Type", "application/x-www-form-urlencoded");
    whResult.addHead("Host", "www.google.com");
    whResult.response("200", "");
    th.Test(whResult);
```  




#About The Author  
Auther: YaweiZhang  
Mail: yawei.zhang@foxmail.com  
GitHub: https://github.com/zsummer  

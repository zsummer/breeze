Welcome to the proto4z wiki!  
## Introduction:    
[![Build Status](https://travis-ci.org/zsummer/proto4z.svg?branch=master)](https://travis-ci.org/zsummer/proto4z)  
proto4z  is an efficient serialization library for C++, lua, C#, It's like Google protocol buffers.  
proto4z是一个序列化工具库, 可以通过一次编写xml格式的数据结构, 使用genProto工具一键生成对应的C++,lua,C#的原生数据结构和对应的序列化/反序列化代码, 并且会额外生成C++使用的MYSQL增删改查的接口代码.  
proto4z提供C++的HTTP协议处理接口.  

##example  
**这里提供一套简单的模板配置和对应的测试代码. 完整版的测试见项目test/genCode目录下的测试例子.**
  
###xml configure  
```
<?xml version="1.0" encoding="utf-8"?>
<ProtoTraits>
    <MinNo>30000</MinNo>
    <MaxNo>32000</MaxNo>
</ProtoTraits>
<Proto>
    <!-- 整形-->
    <struct name="TestIntegerData" store="true" desc="测试">
        <member name="_uint"    type="ui32" tag="key"    desc=""/>
        <member name="_i64"    type="i64" tag="key"     desc=""/>
        <member name="_ui64"    type="ui64"    tag="ignore" desc=""/>
    </struct>
    <!-- 数组类型-->
    <array name="TestIntegerDataArray" type="TestIntegerData" desc=""/>
    <!-- 协议类型-->
    <proto  name="EchoPack" desc= "">
        <member name="_iarray" type="TestIntegerDataArray"     desc=""/>
        <member name="_f" type="float"     desc=""/>
        <member name="_s" type="string"     desc=""/>
    </proto>
</Proto>
```
###lua code  

**test serializable/deserialize code**  
```
--require
require("proto4z")
local dump = Proto4z.dump
local proto = Proto4z
local echo = {  _iarray = {{_uint=6,_i64=12345678.2,_ui64=12345678},{_uint=6,_i64="123456789000000.2",_ui64="1123122345678.0"}},
				_f =2.235,
				_s = "abcdefg"
				}

local data = proto.encode(echo, "EchoPack")
local dr = proto.decode(data, proto.getName(proto.EchoPack.__getID))
dump(dr)
```

###c++ test code  

**test serializable/deserialize code**
```
    try
    {
        WriteStream ws(100);
        EchoPack echo({ { 1, 2, 3 }, { 2, 8, 0 } }, 1.0f, "a");
        ws << echo;
        ReadStream rs(ws.getStream(), ws.getStreamLen());
        EchoPack result;
        rs >> result;
        cout << "success" << endl;
    }
    catch (std::runtime_error & e)
    {
        cout << "error:" << e.what() << endl;
    }
```
**test sql build, load, select, insert, del code**
```
    zsummer::mysql::DBHelper helper;
    helper.init("127.0.0.1", 3306, "info", "root", "123");
    if (!helper.connect())
    {
        return -1;
    }
    auto buidsqls = TestIntegerData_BUILD();
    auto result = helper.query(buidsqls.at(0));
    if (result->getErrorCode() != zsummer::mysql::QEC_SUCCESS) //need create table  
    {
        if (helper.query(buidsqls.at(1))->getErrorCode() != zsummer::mysql::QEC_SUCCESS)
        {
            return -2; //create tables failed 
        }
    }
    auto insertSql = TestIntegerData_INSERT(TestIntegerData(12, 23, 1));
    if (helper.query(insertSql)->getErrorCode() != zsummer::mysql::QEC_SUCCESS)
    {
        return -3;
    }
    auto selectSql = TestIntegerData_SELECT(12, 23);//double key 
    result = helper.query(insertSql);
    if (result->getErrorCode() != zsummer::mysql::QEC_SUCCESS)
    {
        return -4;
    }
    while (result->haveRow())
    {
        TestIntegerData td;
        *result >> td._uint;
        *result >> td._i64;
        *result >> td._ui64;
    }
```
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
###c# code

**test serializable/deserialize code**
```
    EchoPack pack = new EchoPack(null, 1.0f, "aaa");
    pack._iarray = new TestIntegerDataArray();
    pack._iarray.Add(new TestIntegerData(1, 2, 3));
    pack._iarray.Add(new TestIntegerData(2, 3, 4));
    var binData = pack.__encode().ToArray();
    var result = new EchoPack();
    int pos = 0;
    result.__decode(binData, ref pos);
```



#About The Author  
Auther: YaweiZhang  
Mail: yawei.zhang@foxmail.com  
GitHub: https://github.com/zsummer  

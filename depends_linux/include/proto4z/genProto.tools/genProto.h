/*
 * ZSUMMER License
 * -----------
 * 
 * ZSUMMER is licensed under the terms of the MIT license reproduced below.
 * This means that ZSUMMER is free software and can be used for both academic
 * and commercial purposes at absolutely no cost.
 * 
 * 
 * ===============================================================================
 * 
 * Copyright (C) 2012 YaweiZhang <yawei_zhang@foxmail.com>.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 * ===============================================================================
 * 
 * (end of COPYRIGHT)
 */



#pragma once
#ifndef _GEN_PROTO_H_
#define _GEN_PROTO_H_

#include <map>
#include <vector>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include "utility.h"
#include "log4z.h"
#include "tinyxml2.h"
#include "md5.h"
#ifndef WIN32
#include <sys/stat.h>
#else
#include <direct.h>
#endif
#include "genProto.h"
using namespace tinyxml2;

//support data type
static  std::map<std::string, std::string> xmlTypeToCppType = {
		{ "i8", "char" },
		{ "ui8", "unsigned char" },
		{ "i16", "short" },
		{ "ui16", "unsigned short" },
		{ "i32", "unsigned int" },
		{ "ui32", "unsigned int" },
		{ "i64", "long long" },
		{ "ui64", "unsigned long long" },
		{ "float", "float" },
		{ "double", "double" },
		{ "string", "std::string" },
};

//data default init value
static  std::map<std::string, std::string> xmlTypeToCppDefaultValue = {
		{ "i8", "'\0'" },
		{ "ui8", "0" },
		{ "i16", "0" },
		{ "ui16", "0" },
		{ "i32", "0" },
		{ "ui32", "0" },
		{ "i64", "0" },
		{ "ui64", "0" },
		{ "float", "0.0" },
		{ "double", "0.0" },
};

//include file name, without suffix
struct DataInclude
{
	std::string _filename;
	std::string _desc;
};

//array type
struct DataArray
{
	std::string _type;
	std::string _arrayName;
	std::string _desc;
};

//dict type
struct DataMap
{
	std::string _typeKey;
	std::string _typeValue;
	std::string _mapName;
	std::string _desc;
};

//const type
struct DataConstValue
{
	std::string _type;
	std::string _name;
	std::string _value;
	std::string _desc;
};

//struct type
struct DataStruct
{
	std::string _name;
	std::string _desc;
	struct DataMember
	{
		std::string _type;
		std::string _name;
		std::string _desc;
	};
	std::vector<DataMember> _members;
};

//proto type
struct DataProto
{
	DataConstValue _const;
	DataStruct _struct;
};


//proto id type
const std::string ProtoIDType = "ui16";

//lfcr
const std::string LFCR = " \r\n ";


//store type enum
enum StoreType
{
	GT_DataInclude,
	GT_DataArray,
	GT_DataMap,
	GT_DataConstValue,
	GT_DataStruct,
	GT_DataProto,
};

//general store type
struct StoreInfo
{
	StoreType _type;
	DataInclude _include;
	DataArray _array;
	DataMap _map;
	DataConstValue _const;
	DataProto _proto;
};


//gen code file
bool genCppFile(std::string path, std::string filename, std::string attr, std::vector<StoreInfo> & stores);
bool genLuaFile(std::string path, std::string filename, std::string attr, std::vector<StoreInfo> & stores);
bool genCSharpFile(std::string path, std::string filename, std::string attr, std::vector<StoreInfo> & stores);
bool genJsFile(std::string path, std::string filename, std::string attr, std::vector<StoreInfo> & stores);




//parse
enum ParseCode
{
	PC_SUCCESS,
	PC_NEEDSKIP,
	PC_ERROR,
};


//manager
class genProto
{
	//init
	std::string _fileName;
	std::string _fileConfigAttr = ".xml";
	std::string _fileCacheAttr = ".xml.cache";

	//cache data
	unsigned short _curNo = 0;
	std::string _md5;
	struct DataCache
	{
		std::string protoName;
		unsigned int protoValue;
	};
	std::map<std::string, DataCache> _mapCacheNo;

	//xml data
	unsigned short _minNo = 0;
	unsigned short _maxNo = 0;
	std::vector<StoreInfo> _vctStoreInfo;

public:
	//filename without suffix
	genProto(std::string filename){	_fileName = filename;}

	//parse cache
	ParseCode parseCache();
	//parse config
	ParseCode parseConfig();
	//gen code
	ParseCode genCode();
	//write cache
	ParseCode writeCache();
};


#endif

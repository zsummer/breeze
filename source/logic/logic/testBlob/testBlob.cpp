
#include "testBlob.h"
#include "../dbManager.h"
using namespace zsummer::mysql;


TestBlob::TestBlob()
{

}

TestBlob::~TestBlob()
{
}

bool TestBlob::init()
{
	//一段测试blob存储的测试代码.
	auto checkTable = DBManager::getRef().infoQuery("desc tb_testBlob");
	if (checkTable->getErrorCode() != QEC_SUCCESS)
	{
		LOGI("create talbe tb_testBlob ");
		DBQuery q("CREATE TABLE `tb_testBlob` ( "
			"`uID` bigint(20) unsigned NOT NULL, "
			"PRIMARY KEY(`uID`) "
			") ENGINE = MyISAM DEFAULT CHARSET = utf8");
		checkTable = DBManager::getRef().infoQuery(q.popSQL());
		if (checkTable->getErrorCode() != QEC_SUCCESS)
		{
			LOGE("create talbe tb_testBlob error=" << checkTable->getLastError());
			return false;
		}
	}
	//版本升级自动alter add 新字段. 
	DBManager::getRef().infoQuery("alter table `tb_testBlob` add `bag` blob");


	//blob test
	DBQuery q;
	q.init("insert into tb_testBlob(uID, bag)values(?,?) on duplicate key update bag=?");
	std::string apendBin;
	for (int i = 0; i < 256; i++)
	{
		apendBin.append(1, (char)i);
	}
	WriteStream wsdb(0);
	wsdb << (UserID)1;
	wsdb << apendBin;
	std::string blob(wsdb.getStreamBody(), wsdb.getStreamBodyLen());
	q.add(1);
	q.add(blob);
	q.add(blob);

	auto result = DBManager::getRef().infoQuery(q.popSQL());
	if (result->getErrorCode() != QEC_SUCCESS )
	{
		LOGE("update blob error. msg=" << result->getLastError());
		return false;
	}
	
	q.init("select bag from tb_testBlob where uID=?");
	q.add(1);
	result = DBManager::getRef().infoQuery(q.popSQL());
	if (result->getErrorCode() != QEC_SUCCESS)
	{
		LOGE("select blob error. errorMsg=" << result->getLastError());
		return false;
	}
	
	try
	{
		if (result->haveRow())
		{

			std::string blob;
			*result >> blob;

			ReadStream rs(blob.c_str(), (zsummer::proto4z::Integer)blob.length(), false);

			UserID uID = 0;
			std::string resBlob;
			rs >> uID;
			rs >> resBlob;
			if (resBlob != apendBin)
			{
				LOGE("write to blob binary is not equal to res bin");
				return false;
			}
		}
	}
	catch (const std::runtime_error & e)
	{
		LOGE("test blog read error. catch:" << e.what());
		return false;
	}
	catch (...)
	{
		LOGE("test blog read error. catch:other.");
		return false;
	}

	return true;
}


// test
// this is one test .
// wait a moment,  the sql query code will needless write more that I will use proto tools make it.
//
#include <ProtoCommon.h>
inline std::string LOAD_UserInfo(unsigned long long uID)
{
	DBQuery q("select * from tb_UserInfo where uID>?");
	q << uID;
	return q.popSQL();
}

inline std::string SELECT_UserInfo(unsigned long long uID)
{
	DBQuery q("select * from tb_UserInfo where uID=?");
	q << uID;
	return q.popSQL();
}

inline std::map<unsigned long long, UserInfo> UserInfo_FROMDB(DBResultPtr ptr)
{
	std::map <unsigned long long, UserInfo> ret;
	if (ptr->getErrorCode() == QEC_SUCCESS)
	{
		while (ptr->haveRow())
		{
			UserInfo info;
			*ptr >> info.uID;
			*ptr >> info.nickName;
			//...
			ret[info.uID] = info;
		}
	}
}

inline std::string UPDATE_UserInfo(const UserInfo & info)
{
	DBQuery q("insert into tb_UserInfo(uID)values(?) on duplicate key set .........");
	q << info.uID;
	///
	return q.popSQL();
}




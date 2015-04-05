
#include "createTestAuthInfo.h"
#include "../dbManager.h"
using namespace zsummer::mysql;


CreateTestAuthInfo::CreateTestAuthInfo()
{

}

CreateTestAuthInfo::~CreateTestAuthInfo()
{
}

bool CreateTestAuthInfo::init()
{
	//一段测试blob存储的测试代码.
	auto checkTable = DBManager::getRef().authQuery("desc tb_auth");
	if (checkTable->getErrorCode() != QEC_SUCCESS)
	{
		LOGI("create talbe tb_auth ");
		DBQuery q("CREATE TABLE `tb_auth` ( "
			"`user` varchar(20) NOT NULL DEFAULT '',"
			"`passwd` varchar(20) NOT NULL DEFAULT '',"
			"`uid` bigint(20) unsigned NOT NULL AUTO_INCREMENT,"
			"PRIMARY KEY(`user`), "
			"UNIQUE KEY `accID` (`uid`) "
			") ENGINE=MyISAM AUTO_INCREMENT=1 DEFAULT CHARSET=utf8");
		checkTable = DBManager::getRef().authQuery(q.genSQL());
		if (checkTable->getErrorCode() != QEC_SUCCESS)
		{
			LOGE("create talbe tb_auth error=" << checkTable->getLastError());
			return false;
		}
		for (int i = 0; i < 1000; i++)
		{
			DBQuery q("insert ignore into tb_auth(`user`, passwd)values(?, ?)");
			char buf[100];
			sprintf(buf, "zhangyawei%04d", i);
			std::string str(buf);
			q.add(buf);
			q.add("123");
			DBResultPtr result = DBManager::getRef().authQuery(q.genSQL());
			if (result->getErrorCode() != QueryErrorCode::QEC_SUCCESS)
			{
				LOGE("mysql querry error. the error=" << result->getLastError() << ", sql=" << q.genSQL());
				return false;
			}
			if (result->getAffectedRows() == 0)
			{
				LOGW("mysql insert auth user not affect any rows. the user=" << buf);
				continue;
			}
		}
	}



	return true;
}





/*
* breeze License
* Copyright (C) 2014-2016 YaweiZhang <yawei.zhang@foxmail.com>.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "dbDict.h"

#include "utls.h"





bool DBDict::initHelper()
{
    auto dbconfigs = ServerConfig::getRef().getDBConfig();
    auto founder = std::find_if(dbconfigs.begin(), dbconfigs.end(), [](const DBConfig & config) {return config._name == "STDictDBMgr"; });
    if (founder == dbconfigs.end())
    {
        LOGE("STDictDBMgr not found");
        return false;
    }
    _dictHelper = std::make_shared<DBHelper>();
    _dictHelper->init(founder->_ip, founder->_port, founder->_db, founder->_user, founder->_pwd, true);
    if (!_dictHelper->connect())
    {
        LOGE("can't connect mysql STDictDBMgr. config=" << *founder);
        return false;
    }
    return true;
}


















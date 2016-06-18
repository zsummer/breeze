

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



#ifndef _DB_DICT_H_
#define _DB_DICT_H_


#include "defined.h"
#include "single.h"
#include "dbAsync.h"
#include "utls.h"

template<class Packet>
bool fetchDict(DBHelperPtr helper, std::function<void(const Packet &)>);



class DBDict : public Singleton<DBDict>
{
public:

public:


};

template<class Packet>
bool fetchDict(DBHelperPtr helper, std::function<void(const Packet &)> cb)
{
    auto sql = Packet().getDBSelectPure();
    int cursor = 0;
    DBResultPtr result;
    do
    {
        result = helper->query(sql + " limit " + toString(cursor) + ", 100");
        if(!result)
        {
            LOGE("fetchDict error. dict name=" << Packet::getProtoName());
            return false;
        }
        if (result->getErrorCode() != QEC_SUCCESS)
        {
            LOGE("fetchDict error. dict name=" << Packet::getProtoName() << ", error=" << result->getErrorMsg());
            return false;
        }
        if (!result->haveRow())
        {
            break;
        }
        Packet pkt;
        while(result->haveRow())
        {
            auto ret = pkt.fetchFromDBResult(result);
            if (!ret)
            {
                LOGE("fetchDict errror when fetchFromDBResult to packet. dict name=" << Packet::getProtoName());
                return false;
            }
            cb(pkt);
        }
    }while(true);
    return true;
}




























#endif
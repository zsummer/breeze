

/*
* mini-breeze License
* Copyright (C) 2014 YaweiZhang <yawei_zhang@foxmail.com>.
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

/*
*
*/

#ifndef _GEN_OBJECT_ID_H_
#define _GEN_OBJECT_ID_H_
#include <InnerTypeDefine.h>
class GenObjectID
{
public:
	GenObjectID(){}
	inline void initConfig(PlatID pID, AreaID aID)
	{
		_platID = pID;
		_areaID = aID;
		_minObjID = (((ui64)_platID << 48) | (ui64)_areaID) << 32;
		_maxObjID = _minObjID | (ui64)((ui32)-1);
		_seqObjID = _minObjID;
	}
	inline void setCurObjID(ui64 seq){ _seqObjID = seq; }

	inline ui64 getMinObjID(){ return _minObjID; }
	inline ui64 getMaxObjID(){ return _maxObjID; }
	inline ui64 getCurObjID(){ return _seqObjID; }

	inline ui64 genNewObjID(){ return ++_seqObjID; }
	
protected:
private:
	PlatID _platID = 0;
	AreaID _areaID = 0;
	ui64 _minObjID = 0;
	ui64 _maxObjID = 0;
	ui64 _seqObjID = 0;
};
#endif

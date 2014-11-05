

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
	inline void InitConfig(PlatID pID, AreaID aID)
	{
		m_platID = pID;
		m_areaID = aID;
		m_minObjID = (((ui64)m_platID << 48) | (ui64)m_areaID) << 32;
		m_maxObjID = m_minObjID | (ui64)((ui32)-1);
		m_seqObjID = m_minObjID;
	}
	inline void SetCurObjID(ui64 seq){ m_seqObjID = seq; }

	inline ui64 GetMinObjID(){ return m_minObjID; }
	inline ui64 GetMaxObjID(){ return m_maxObjID; }
	inline ui64 GetCurObjID(){ return m_seqObjID; }

	inline ui64 GenNewObjID(){ return ++m_seqObjID; }
	
protected:
private:
	PlatID m_platID = 0;
	AreaID m_areaID = 0;
	ui64 m_minObjID = 0;
	ui64 m_maxObjID = 0;
	ui64 m_seqObjID = 0;
};
#endif


/*
* breeze License
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
 *  file desc
 *  BaseHandler provide a unified way to manager message handler.
 */


#ifndef _SINGLETON_H_
#define _SINGLETON_H_
#include <innerDefined.h>


template<class T>
class Singleton
{
public:
	virtual ~Singleton(){}
	static T * instantiate(){if (_pInstance)return _pInstance;else return _pInstance = new T();}
	//warning.  a single instance must new by user. 
	static T & getRef(){ return *instantiate(); }
	static T * getPtr(){ return instantiate(); }
public:
	Singleton() = default;
private:
	static T * _pInstance;
	Singleton(const Singleton<T> &) = delete;
};

template<class T>
T *  Singleton<T>::_pInstance = nullptr;


































#endif

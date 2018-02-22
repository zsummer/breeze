/*
* breeze License
* Copyright (C) 2014-2018 YaweiZhang <yawei.zhang@foxmail.com>.
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

#include <map>
#include <tuple>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

//test code 
template<class ... Args>
class NestedMap;

template<class Key>
class NestedMap<Key>
{
public:
	NestedMap() {}
	~NestedMap() 
	{
		for (auto pr : m_)
		{
			if (pr.second != nullptr)
			{
				delete pr.second;
			}
		}
		m_.clear();
	}
	void * find(Key t)
	{
		auto iter = m_.find(t);
		if (iter == m_.end() || iter->second == nullptr)
		{
			return nullptr;
		}
		return iter->second;
	}
	bool insert(void * val, Key key)
	{
		m_[key] = val;
		return true;
	}
private:
	std::map<Key, void*> m_;
};


template<class Key, class ... Args>
class NestedMap<Key, Args...>
{
public:
	NestedMap() {}
	~NestedMap() 
	{
		for (auto pr : m_)
		{
			if (pr.second != nullptr)
			{
				delete pr.second;
			}
		}
		m_.clear();
	}
	void * find(Key key, Args ... args)
	{
		auto iter = m_.find(key);
		if (iter == m_.end() || iter->second == nullptr)
		{
			return nullptr;
		}
		return iter->second->find(args ...);
	}
	bool insert(void * val, Key key, Args ... args)
	{
		auto iter = m_.find(key);
		if (iter == m_.end())
		{
			iter = m_.insert(std::make_pair(key, new NestedMap<Args ...>())).first;
		}
		return iter->second->insert(val, args ...);
	}
private:
	std::map<Key, NestedMap<Args ...> *> m_;
};



class Message
{
public:
	Message() {}
	~Message() {}
	int getInt(int) { return 0; }
	std::string getString(int) { return "string"; }
private:

};

template<class T>
typename std::enable_if<std::is_same<int, T>::value, T>::type get_message(int)
{
	return Message().getInt(2);
}
template<class T>
typename std::enable_if<std::is_same<std::string, T>::value, T>::type get_message(int)
{
	return Message().getString(2);
}

template<class ... Keys >
class MessageMgr
{
public:
	MessageMgr()
	{

	}
	~MessageMgr()
	{

	}
	template<int ... IDS>
	bool load()
	{
		Message m;
		std::tuple<Keys ...> t = {};
		
		m_.insert(new int(21), get_message<Keys>(IDS) ...);
		return true;
	}
	void * find(Keys ... keys)
	{
		return m_.find(keys ...);
	}
private:
	NestedMap<Keys ... > m_;
};



int main()
{

	NestedMap<int> a;
	a.insert(new int(1), 1);
	std::cout << a.find(1) << std::endl;

	NestedMap<int, std::string> b;
	b.insert(new double(2.2), 1, "3");
	std::cout << b.find(1, "3") << std::endl;

	MessageMgr<int, std::string> m;
	m.load<2,3>();
	std::cout << m.find(0, "string") << std::endl;


    return 0;
}

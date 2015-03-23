

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

#include "tinyxml2.h"
#include "config.h"

static ServerNode toServerNode(std::string strNode)
{
	if (strNode == "logic")
	{
		return LogicNode;
	}
	else if (strNode == "stress")
	{
		return StressNode;
	}
	return InvalidServerNode;
}

static DBConfigID toDBConfigID(std::string db)
{
	if (db == "auth")
	{
		return AuthDB;
	}
	else if (db == "dict")
	{
		return DictDB;
	}
	else if (db == "info")
	{
		return InfoDB;
	}
	else if (db == "log")
	{
		return LogDB;
	}
	return InvalidDB;
}


const ::ListenConfig & ServerConfig::getConfigListen(ServerNode node, NodeIndex index)
{
	if (index == InvalidNodeIndex)
	{
		index = _ownNodeIndex;
	}
	auto founder = std::find_if(_configListen.begin(), _configListen.end(),
		[node, index](const ::ListenConfig & lc){return lc._node == node && lc._index == index; });
	if (founder == _configListen.end())
	{
		static ::ListenConfig lc;
		return lc;
	}
	return *founder;
}


std::vector<ConnectorConfig > ServerConfig::getConfigConnect(ServerNode node)
{
	std::vector<ConnectorConfig > ret;
	for (const auto & cc : _configConnect)
	{
		if (cc._srcNode != node)
		{
			continue;
		}
		ret.push_back(cc);
	}
	
	return ret;
}


const DBConfig & ServerConfig::getDBConfig(DBConfigID id)
{
	auto founder = std::find_if(_configDB.begin(), _configDB.end(),
		[id](const DBConfig & db){return db._id == id; });
	if (founder == _configDB.end())
	{
		static DBConfig db;
		return db;
	}
	return *founder;
}





bool ServerConfig::parse(std::string filename, ServerNode ownNode, NodeIndex ownIndex)
{
	_ownServerNode = ownNode;
	_ownNodeIndex = ownIndex;
	tinyxml2::XMLDocument doc;
	if (doc.LoadFile(filename.c_str()) != tinyxml2::XML_SUCCESS)
	{
		LOGE(filename << " parse ServerConfig Error. ");
		doc.PrintError();
		return false;
	}

	//////////////////////////////////////////////////////////////////////////
	auto elmTraits = doc.FirstChildElement("traits");
	if (!elmTraits || ! elmTraits->Attribute("platid") || ! elmTraits->Attribute("areaid"))
	{
		LOGE(filename << " parse ServerConfig Error. not have traits");
		return false;
	}
	_platid = elmTraits->IntAttribute("platid");
	_areaid = elmTraits->IntAttribute("areaid");

	//////////////////////////////////////////////////////////////////////////
	{
		auto elmListen = doc.FirstChildElement("listen");
		if (!elmListen || !elmListen->FirstChildElement())
		{
			LOGE(filename << " parse ServerConfig Error. not have listen");
			return false;
		}
		auto elmListenChild = elmListen->FirstChildElement();
		do
		{
			std::string strNode = elmListenChild->Name();
			if (!elmListenChild->Attribute("ip") || !elmListenChild->Attribute("port") || !elmListenChild->Attribute("index"))
			{
				LOGE(filename << " parse ServerConfig Error. listen have invalide config.");
				return false;
			}

			::ListenConfig lconfig;
			lconfig._ip = elmListenChild->Attribute("ip");
			lconfig._port = elmListenChild->IntAttribute("port");
			lconfig._index = elmListenChild->IntAttribute("index");
			lconfig._node = toServerNode(strNode);
			if (lconfig._node != InvalidServerNode)
			{
				_configListen.push_back(lconfig);
				LOGI("ListenConfig=" << lconfig );
			}
			else
			{
				LOGE("UNKNOWN ListenConfig=" << lconfig);
			}

			elmListenChild = elmListenChild->NextSiblingElement();
		} while (elmListenChild);
	}


	//////////////////////////////////////////////////////////////////////////
	{
		auto elmConnect = doc.FirstChildElement("connect");
		if (!elmConnect || !elmConnect->FirstChildElement())
		{
			LOGE(filename << " parse ServerConfig Error. not have connect");
			return false;
		}
		auto elmConnectChild = elmConnect->FirstChildElement();
		do
		{
			std::string srcStrNode = elmConnectChild->Name();
			if (!elmConnectChild->Attribute("ip")
				|| !elmConnectChild->Attribute("port")
				|| !elmConnectChild->Attribute("dstNode"))
			{
				LOGE(filename << " parse ServerConfig Error. connect have invalide config.");
				return false;
			}


			ConnectorConfig lconfig;
			std::string dstStrNode = elmConnectChild->Attribute("dstNode");
			lconfig._remoteIP = elmConnectChild->Attribute("ip");
			lconfig._remotePort = elmConnectChild->IntAttribute("port");
			lconfig._srcNode = toServerNode(srcStrNode);
			lconfig._dstNode = toServerNode(dstStrNode);
			if (lconfig._srcNode != InvalidServerNode && lconfig._dstNode != InvalidServerNode)
			{
				_configConnect.push_back(lconfig);
				LOGD("ConnectorConfig=" << lconfig);
			}
			else
			{
				LOGE("UNKNOWN ConnectorConfig=" << lconfig);
			}
			elmConnectChild = elmConnectChild->NextSiblingElement();
		} while (elmConnectChild);
	}

	//////////////////////////////////////////////////////////////////////////
	{
		auto elmDB = doc.FirstChildElement("db");
		if (!elmDB || !elmDB->FirstChildElement())
		{
			LOGE(filename << " parse ServerConfig Error. not have mongo");
			return false;
		}
		auto elmDBChild = elmDB->FirstChildElement();
		do
		{
			std::string strNode = elmDBChild->Name();
			if (!elmDBChild->Attribute("ip")
				|| !elmDBChild->Attribute("port")
				|| !elmDBChild->Attribute("db")
				|| !elmDBChild->Attribute("user")
				|| !elmDBChild->Attribute("pwd"))
			{
				LOGE(filename << " parse ServerConfig Error. mongo have invalide config.");
				return false;
			}

			DBConfig lconfig;
			lconfig._ip = elmDBChild->Attribute("ip");
			lconfig._port = elmDBChild->IntAttribute("port");
			lconfig._db = elmDBChild->Attribute("db");
			lconfig._user = elmDBChild->Attribute("user");
			lconfig._pwd = elmDBChild->Attribute("pwd");
			lconfig._id = toDBConfigID(strNode);
			if (lconfig._id != InvalidDB)
			{
				_configDB.push_back(lconfig);
				LOGI("DBConfig=" << lconfig);
			}
			else
			{
				LOGE("unknown DBConfig=" << lconfig);
			}
			elmDBChild = elmDBChild->NextSiblingElement();
		} while (elmDBChild);
	}
	return true;
}



























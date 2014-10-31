#pragma once
#ifndef _TEST_STREAM_H_
#define _TEST_STREAM_H_
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <deque>
#include <queue>
#include <typeinfo>
#include "../proto4z.h"
using namespace  std;
using namespace zsummer::proto4z;

struct tagTestData
{
	bool bl;
	char ch;
	unsigned char uch;
	short sh;
	unsigned short ush;
	int n;
	unsigned int u;
	long l;
	unsigned long ul;
	long long ll;
	unsigned long long ull;
	float f;
	double lf;
	std::string str;
	std::vector<int> vct;
	std::map<int, int> kv;
	std::set<int> st;
	std::multimap<int, int> mkv;
	std::multiset<int> mst;
	std::list<int> lt;
	std::deque<int> dq;
	std::queue<int> qu;
};



inline bool operator==(const tagTestData & tag1, const tagTestData &tag2)
{
	return tag1.bl == tag2.bl
		&& tag1.ch == tag2.ch
		&& tag1.uch == tag2.uch
		&& tag1.ush == tag2.ush
		&& tag1.n == tag2.n
		&& tag1.u == tag2.u
		&& tag1.l == tag2.l
		&& tag1.ul == tag2.ul
		&& tag1.ll == tag2.ll
		&& tag1.ull == tag2.ull
		&& tag1.f == tag2.f
		&& tag1.lf == tag2.lf
		&& tag1.str == tag2.str
		&& tag1.vct.size() == tag2.vct.size()
		&& tag1.kv.size() == tag2.kv.size()
		&& tag1.st.size() == tag2.st.size()
		&& tag1.mkv.size() == tag2.mkv.size()
		&& tag1.mst.size() == tag2.mst.size()
		&& tag1.lt.size() == tag2.lt.size()
		&& tag1.dq.size() == tag2.dq.size();
}
inline bool operator!=(const tagTestData & tag1, const tagTestData &tag2)
{
	return !(tag1 == tag2);
}
template<class StreamHeadTrait>
inline ReadStream<StreamHeadTrait> & operator >>(ReadStream<StreamHeadTrait> & rs, tagTestData & data)
{
	rs >> data.bl;
	rs >> data.ch;
	rs >> data.uch;
	rs >> data.sh;
	rs >> data.ush;
	rs >> data.n;
	rs >> data.u;
	rs >> data.l;
	rs >> data.ul;
	rs >> data.ll;
	rs >> data.ull;
	rs >> data.f;
	rs >> data.lf;
	rs >> data.str;
	rs >> data.vct;
	rs >> data.kv;
	rs >> data.st;
	rs >> data.mkv;
	rs >> data.mst;
	rs >> data.lt;
	rs >> data.dq;
	return rs;
}
template<class StreamHeadTrait>
inline WriteStream<StreamHeadTrait> & operator <<(WriteStream<StreamHeadTrait> & ws, const tagTestData & data)
{
	ws << data.bl;
	ws << data.ch;
	ws << data.uch;
	ws << data.sh;
	ws << data.ush;
	ws << data.n;
	ws << data.u;
	ws << data.l;
	ws << data.ul;
	ws << data.ll;
	ws << data.ull;
	ws << data.f;
	ws << data.lf;
	ws << data.str;
	ws << data.vct;
	ws << data.kv;
	ws << data.st;
	ws << data.mkv;
	ws << data.mst;
	ws << data.lt;
	ws << data.dq;
	return ws;
}





#pragma pack(push)
#pragma pack(1)
struct tagStreamHead
{
	unsigned int _protocolID;
	unsigned int _packLen;
	unsigned int _sessionID;
	unsigned int _agentID;
};
#pragma pack(pop)

struct UDStreamHeadTraits
{
	typedef unsigned int Integer;
	const static Integer PreOffset = sizeof(unsigned int);
	const static Integer PostOffset = sizeof(unsigned int)*2;
	const static Integer MaxPackLen = 1024*1024*10;//10M
	const static bool PackLenIsContainHead = true;
	const static ZSummer_EndianType EndianType = LittleEndian;
	const static Integer IntegerTypeSize = sizeof(Integer); // Don't Touch. PackLenSize and sizeof(Integer) must be equal. 
	const static Integer HeadLen = PreOffset + IntegerTypeSize + PostOffset; //Don't Touch.
};


template <class StreamHeadTrait>
class TestBase
{
public:
	TestBase()
	{
		m_testData.bl = true;
		m_testData.ch = 'a';
		m_testData.uch = 200;
		m_testData.ush = -1;
		m_testData.n = 65000;
		m_testData.u = -2;
		m_testData.l = 333;
		m_testData.ul = -3;
		m_testData.ll = 111;
		m_testData.ull = -4;
		m_testData.f = (float)123.2;
		m_testData.lf = 123.4;
		m_testData.str = "1234567";
		m_testData.vct.push_back(1);
		m_testData.vct.push_back(2);
		m_testData.kv[1] = 1;
		m_testData.kv[100] = 100;
		m_testData.st.insert(10);
		m_testData.mkv.insert(std::make_pair(10, 10));
		m_testData.mkv.insert(std::make_pair(10, 100));
		m_testData.mst.insert(100);
		m_testData.mst.insert(100);
		m_testData.lt.push_back(10);
		m_testData.dq.push_back(100);
		m_packLen = 0;
		m_bodyLen = 0;
	}

	~TestBase()
	{

	}

	inline bool CheckLenght()
	{
		const char * className = typeid(StreamHeadTrait).name();
		WriteStream<StreamHeadTrait> testWS(NULL, StreamHeadTrait::MaxPackLen, true);
		try
		{
			testWS << m_testData;
			m_packLen = testWS.GetStreamLen();
			m_bodyLen = testWS.GetBodyStreamLen();
		}
		catch (std::runtime_error e)
		{
			cout << "CheckLenght -> " << className << " write Fail. error msg=" << e.what() << endl;
			return false;
		}
		cout << "CheckLenght -> " << className << " m_packLen=" << m_packLen << ", m_bodyLen=" << m_bodyLen << endl;
		return true;
	}

	inline bool CheckProtocol(WriteStream<StreamHeadTrait> &ws, const char * desc);

	inline bool CheckAttachProtocol()
	{
		char * writeBuff = new char[m_packLen];
		memset(writeBuff, 0, m_packLen);
		WriteStream<StreamHeadTrait> ws(writeBuff, m_packLen);
		std::string str = "Check Attach Write. protocolTrits=";
		str += typeid(StreamHeadTrait).name();
		str += ":  ";
		return CheckProtocol(ws, str.c_str());
	}

	inline bool CheckNoAttachProtocol()
	{
		WriteStream<StreamHeadTrait> ws(UBT_AUTO, m_packLen);
		std::string str = "Check NoAttach Write. protocolTrits=";
		str += typeid(StreamHeadTrait).name();
		str += ":  ";
		return CheckProtocol(ws, str.c_str());
	}

	inline bool CheckRouteProtocol()
	{
		const char * className = "TestBigStreamHeadTrait";

		try
		{
			//analog recv message buff.
			WriteStream<UDStreamHeadTraits> ws;
			unsigned int _roomID = 1;
			tagStreamHead _head;
			_head._agentID = 67;
			_head._protocolID = 65530;
			_head._sessionID = 343;
			ws.SetStreamHead((const char*)&_head);
			ws << _roomID << m_testData;
			


			//analog recv msg
			std::pair<INTEGRITY_RET_TYPE, UDStreamHeadTraits::Integer> ret = CheckBuffIntegrity<UDStreamHeadTraits>(ws.GetStream(), ws.GetStreamLen(), UDStreamHeadTraits::MaxPackLen);
			if (ret.first == IRT_CORRUPTION || ret.first == IRT_SHORTAGE)
			{
				cout << "CheckRouteProtocol -> " << className << "  CheckBuffIntegrity error" << endl;
				return false;
			}

			//check
			ReadStream<UDStreamHeadTraits> rs(ws.GetStream(), ws.GetStreamLen());
			//check user-defined head
			tagStreamHead rsHead;
			rs.GetStreamHead((char*)&rsHead);
			if (rsHead._agentID != _head._agentID
				|| rsHead._protocolID != _head._protocolID
				|| rsHead._sessionID != _head._sessionID)
			{
				cout << "CheckRouteProtocol -> " << className << "  check head  error" << endl;
				return false;
			}
			//check user data
			unsigned int roomID2 = 0;
			rs >> roomID2;
			if (roomID2 != _roomID)
			{
				cout << "CheckRouteProtocol -> " << className << "  check room ID error" << endl;
				return false;
			}
			//check route
			WriteStream<UDStreamHeadTraits> ws2;
			ws2.SetStreamHead((const char*)&rsHead);
			ws2.AppendOriginalData(rs.GetStreamUnread(), rs.GetStreamUnreadLen());
			ReadStream<UDStreamHeadTraits> rs2(ws2.GetStream(), ws2.GetStreamLen());
			tagTestData testData;
			rs2 >> testData;
			if (testData != m_testData)
			{
				cout << "CheckRouteProtocol -> " << className << "  check route error" << endl;
				return false;
			}
			cout << "CheckRouteProtocol -> " << className << "  check route OK" << endl;
			return true;
		}
		catch (std::runtime_error e)
		{
			cout << "CheckRouteProtocol -> " << className << "  check route Failed. msg=" << e.what() << endl;
			return false;
		}
		return true;
			
	}


	typename StreamHeadTrait::Integer m_packLen;
	typename StreamHeadTrait::Integer m_bodyLen;
	tagTestData m_testData;
};







template < class StreamHeadTrait>
bool TestBase<StreamHeadTrait>::CheckProtocol(WriteStream<StreamHeadTrait> &ws, const char * desc)
{
	try
	{
		ws << m_testData;
		cout << desc << " write all data OK." << endl;
		if (ws.GetStreamLen() == m_packLen)
		{
			cout << desc << " WriteStreamLen OK." << endl;
		}
		else
		{
			cout << desc << " WriteStreamLen Failed. GetStreamLen()="
				<< ws.GetStreamLen() << ", m_packLen=" << m_packLen << endl;
			return false;
		}
		if (ws.GetBodyStreamLen() == m_bodyLen)
		{
			cout << desc << " WriteBodyStreamLen OK." << endl;
		}
		else
		{
			cout << desc << " WriteBodyStreamLen Failed. GetBodyStreamLen()="
				<< ws.GetBodyStreamLen() << ", m_bodyLen=" << m_bodyLen << endl;
			return false;
		}
	}
	catch (std::runtime_error e)
	{
		cout << desc << " write data Fail. error msg=" << e.what() << endl;
		return false;
	}
	try
	{
		ws << 'c';
		cout << desc << " check Write bound Failed. GetBodyStreamLen()="
			<< ws.GetBodyStreamLen() << ", m_bodyLen=" << m_bodyLen << endl;
		return false;
	}
	catch (std::runtime_error e)
	{
		cout << desc << " check Write bound OK" << endl;
	}


	std::pair<INTEGRITY_RET_TYPE, typename StreamHeadTrait::Integer> ret = CheckBuffIntegrity<StreamHeadTrait>(ws.GetStream(), 1, m_packLen);
	if (ret.first == IRT_SHORTAGE && ret.second == StreamHeadTrait::HeadLen - 1)
	{
		cout << desc << " CheckBuffIntegrity check write header len OK" << endl;
	}
	else
	{
		cout << desc << " CheckBuffIntegrity check write header len failed" << endl;
		return false;
	}
	ret = CheckBuffIntegrity<StreamHeadTrait>(ws.GetStream(), ws.GetStreamLen(), ws.GetStreamLen());
	if (ret.first == IRT_SUCCESS && ret.second == m_packLen)
	{
		cout << desc << " CheckBuffIntegrity check write  OK" << endl;
	}
	else
	{
		cout << desc << " CheckBuffIntegrity check write  failed" << endl;
		return false;
	}


	tagTestData readTestData;
	ReadStream<StreamHeadTrait> rs(ws.GetStream(), ws.GetStreamLen());

	try
	{
		rs >> readTestData;
		cout << desc << " check Read all data  OK" << endl;
	}
	catch (std::runtime_error e)
	{
		cout << desc << " check Read all data  failed" << e.what() << endl;
		return false;
	}

	if (readTestData == m_testData)
	{
		cout << desc << "consistency check OK" << endl;
	}
	else
	{
		cout << desc << "consistency check failed" << endl;
		return false;
	}

	try
	{
		char ch = 'a';
		rs >> ch;
		cout << desc << "read bounds check  ReadStream failed" << endl;
		return false;
	}
	catch (std::runtime_error e)
	{
		cout << desc << "read bounds check  ReadStream OK." << endl;
	}
	cout << desc << "check OK." << endl;
	return true;
}



#endif



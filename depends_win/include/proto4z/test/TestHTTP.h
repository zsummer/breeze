#pragma once
#ifndef _TEST_HTTP_H_
#define _TEST_HTTP_H_
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

const int MAX_HTTP_LEN = 1000;
class TestHTTP
{
public:
	bool Test(WriteHTTP &wh)
	{
		bool isChunked = false;
		PairString commandLine;
		HTTPHeadMap head;
		std::string body;
		unsigned int usedLen = 0;
		if (CheckHTTPBuffIntegrity(wh.GetStream(), wh.GetStreamLen(), 1024, false, isChunked, commandLine, head, body, usedLen) == IRT_SUCCESS)
		{
			if (head.find("Host") != head.end()
				&& (commandLine.first == "GET" || commandLine.first == "POST" || commandLine.second == "200"))
			{
				cout << "Check CheckHTTPBuffIntegrity Success" << endl;
			}
			else
			{
				cout << "Check CheckHTTPBuffIntegrity Data error" << endl;
				return false;
			}
		}
		else
		{
			cout << "Check CheckHTTPBuffIntegrity unpack error. ret =" << (IRT_SHORTAGE ? "IRT_SHORTAGE":"IRT_CORRUPTION") << endl;
			return false;
		}
		if (CheckHTTPBuffIntegrity(wh.GetStream(), wh.GetStreamLen() - 1, 1024, false, isChunked, commandLine, head, body, usedLen) != IRT_SHORTAGE)
		{
			cout << "Check CheckHTTPBuffIntegrity IRT_SHORTAGE error" << endl;
			return false;
		}
		if (CheckHTTPBuffIntegrity(wh.GetStream(), wh.GetStreamLen(), wh.GetStreamLen() - 1, false, isChunked, commandLine, head, body, usedLen) != IRT_CORRUPTION)
		{
			cout << "Check CheckHTTPBuffIntegrity IRT_CORRUPTION error" << endl;
			return false;
		}	
		return true;
	}
protected:
private:
};




#endif



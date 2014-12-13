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
		if (checkHTTPBuffIntegrity(wh.getStream(), wh.getStreamLen(), 1024, false, isChunked, commandLine, head, body, usedLen) == IRT_SUCCESS)
		{
			if (head.find("Host") != head.end()
				&& (commandLine.first == "GET" || commandLine.first == "POST" || commandLine.second == "200"))
			{
				cout << "Check checkHTTPBuffIntegrity Success" << endl;
			}
			else
			{
				cout << "Check checkHTTPBuffIntegrity Data error" << endl;
				return false;
			}
		}
		else
		{
			cout << "Check checkHTTPBuffIntegrity unpack error. ret =" << (IRT_SHORTAGE ? "IRT_SHORTAGE":"IRT_CORRUPTION") << endl;
			return false;
		}
		if (checkHTTPBuffIntegrity(wh.getStream(), wh.getStreamLen() - 1, 1024, false, isChunked, commandLine, head, body, usedLen) != IRT_SHORTAGE)
		{
			cout << "Check checkHTTPBuffIntegrity IRT_SHORTAGE error" << endl;
			return false;
		}
		if (checkHTTPBuffIntegrity(wh.getStream(), wh.getStreamLen(), wh.getStreamLen() - 1, false, isChunked, commandLine, head, body, usedLen) != IRT_CORRUPTION)
		{
			cout << "Check checkHTTPBuffIntegrity IRT_CORRUPTION error" << endl;
			return false;
		}	
		return true;
	}
protected:
private:
};




#endif



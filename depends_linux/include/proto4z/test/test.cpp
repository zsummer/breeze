//! yawei_zhang@foxmail.com

#include "../proto4z.h"
#include <iostream>
#include <stdio.h>
using namespace std;
using namespace zsummer::proto4z;

#include "TestStream.h"
#include "TestHTTP.h"

int main()
{
	bool bAllCheckOK = false;
	do 
	{
		TestBase<DefaultStreamHeadTraits> test1;
		if (!test1.CheckLenght()) break;
		cout << endl;
		if (!test1.CheckAttachProtocol()) break;
		cout << endl;
		if (!test1.CheckNoAttachProtocol()) break;
		cout << endl;
		if (!test1.CheckRouteProtocol()) break;
		cout << endl << endl;
		TestBase<TestBigStreamHeadTraits> test2;
		if (!test2.CheckLenght()) break;
		cout << endl;
		if (!test2.CheckAttachProtocol()) break;
		cout << endl;
		if (!test2.CheckNoAttachProtocol()) break;
		cout << endl;
		if (!test2.CheckRouteProtocol()) break;
		bAllCheckOK = true;

	} while (0);
	cout << endl;
	if (bAllCheckOK) cout << "all check OK . " << endl;
	else cout << "check failed . " << endl;

	cout << "check http proto ..." << endl;
	TestHTTP th;
	WriteHTTP whGet;
	whGet.addHead("Content-Type", "application/x-www-form-urlencoded");
	whGet.addHead("Host", "www.google.com");
	whGet.get("/");
	th.Test(whGet);

	WriteHTTP whPost;
	whPost.addHead("Content-Type", "application/x-www-form-urlencoded");
	whPost.addHead("Host", "www.google.com");
	whPost.post("/", "index.php?aaa=333");
	th.Test(whPost);

	WriteHTTP whResult;
	whResult.addHead("test", "test");
	whResult.addHead("Content-Type", "application/x-www-form-urlencoded");
	whResult.addHead("Host", "www.google.com");
	whResult.response("200", "");
	th.Test(whResult);

	cout << "press any key to continue." << endl;
	getchar();
	return 0;
}
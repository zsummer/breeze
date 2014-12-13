
#include "../log4z.h"
#include <iostream>
#include <stdio.h>
#include <stdarg.h>
using namespace zsummer::log4z;

#ifdef WIN32
#include <windows.h>
#endif
int main(int argc, char *argv[])
{

	//start log4z
	ILog4zManager::getRef().start();
	ILog4zManager::getRef().setLoggerLevel(LOG4Z_MAIN_LOGGER_ID,LOG_LEVEL_TRACE);

	//LOGD: LOG WITH level LOG_DEBUG
	//LOGI: LOG WITH level LOG_INFO
#ifdef WIN32
	//begin test wstring(utf-16) log  string input....
	WCHAR checkWCHAR[100] = L"check unicode WCHAR log";
	std::wstring check_wstring = L"check wstring log";
	LOGF(L"PATH=" << checkWCHAR << ":" << check_wstring);
#endif

	//begin test stream log input....
	LOGT("stream input *** " << "LOGT LOGT LOGT LOGT" << " *** ");
	LOGD("stream input *** " << "LOGD LOGD LOGD LOGD" << " *** ");
	LOGI("stream input *** " << "LOGI LOGI LOGI LOGI" << " *** ");
	LOGW("stream input *** " << "LOGW LOGW LOGW LOGW" << " *** ");
	LOGE("stream input *** " << "LOGE LOGE LOGE LOGE" << " *** ");
	LOGA("stream input *** " << "LOGA LOGA LOGA LOGA" << " *** ");
	LOGF("stream input *** " << "LOGF LOGF LOGF LOGF" << " *** ");


	//begin test stream log all types input....
	LOGD("char:" <<'c'
		<< ", unsigned char:" << (unsigned char) 'c'
		<< ", short:" << (short) -1
		<< ", unsigned short:" << (unsigned short) -1
		<< ", int:" << (int) -1
		<< ", unsigned int:" << (unsigned int) -1
		<< ", long:" << (long) -1
		<< ", unsigned long:" << (unsigned long) -1
		<< ", long long:" << (long long) -1
		<< ", unsigned long long:" << (unsigned long long) -1
		<< ", float:" << (float) -1.234567
		<< ", double:" << (double) -2.34566
		<< ", std::string:" << std::string("fffff")
		<< ", int *:" << ( int *) argv
		<< ", const int *:" << (const int *) argv
		<< ", constant:" << 1000 
		<< ", constant:" << 100.12345678
		<< ", bool:" << true
		<< ", show hex data:" << Log4zBinary("1234567890abcdefghigklmnopqrstuvwxyz_zyw_zsummer_log4z", 50));

	
	std::string str;
	str.resize(3000, 's');

	// cannot support VC6 or VS2003
	
	//begin test format log input....
	LOGFMTT("format input *** %s *** %d ***", "LOGFMTT", 123456);
	LOGFMTD("format input *** %s *** %d ***", "LOGFMTD", 123456);
	LOGFMTI("format input *** %s *** %d ***", "LOGFMTI", 123456);
	LOGFMTW("format input *** %s *** %d ***", "LOGFMTW", 123456);
	LOGFMTE("format input *** %s *** %d ***", "LOGFMTE", 123456);
	LOGFMTA("format input *** %s *** %d ***", "LOGFMTA", 123456);
	LOGFMTF("format input *** %s *** %d ***", "LOGFMTF", 123456);

	//begin test format log big string more than buff size input....
	LOGFMT_DEBUG(LOG4Z_MAIN_LOGGER_ID, "%s", str.c_str());

	//begin test stream log big string more than buff size input....
	LOGD(str);
	LOGA("main quit ...");
	return 0;
}


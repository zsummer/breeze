
#include "../log4z.h"
#include <iostream>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <fstream>
#if WIN32
#include <Windows.h>
#include <process.h>
#else
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#endif
using namespace zsummer::log4z;




LoggerId logid_fromfile;
LoggerId logid_dynamic;

bool g_quit;
void signalFunc(int id)
{
    g_quit = false;
#ifdef WIN32
    signal(id, &signalFunc);
#endif
}
int main(int argc, char *argv[])
{
    g_quit = true;
    signal(SIGINT, &signalFunc);

    ILog4zManager::getRef().config("config.cfg");
    logid_dynamic = ILog4zManager::getRef().createLogger("dynamic");
    logid_fromfile = ILog4zManager::getRef().findLogger("fromfile");
    //start log4z
    ILog4zManager::getRef().start();

    //configure the output behaviour
    ILog4zManager::getRef().setLoggerDisplay(LOG4Z_MAIN_LOGGER_ID, true);
    ILog4zManager::getRef().setLoggerDisplay(logid_dynamic, true);
    ILog4zManager::getRef().setLoggerLevel(LOG4Z_MAIN_LOGGER_ID, LOG_LEVEL_DEBUG);
    ILog4zManager::getRef().setLoggerLevel(logid_dynamic, LOG_LEVEL_DEBUG);
    ILog4zManager::getRef().setLoggerMonthdir(logid_dynamic, true);
    ILog4zManager::getRef().setLoggerFileLine(LOG4Z_MAIN_LOGGER_ID, false);
    ILog4zManager::getRef().setLoggerName(LOG4Z_MAIN_LOGGER_ID, "main");
    ILog4zManager::getRef().setLoggerPath(LOG4Z_MAIN_LOGGER_ID, "./");
    ILog4zManager::getRef().setLoggerLimitsize(logid_dynamic, 1);
    ILog4zManager::getRef().setLoggerOutFile(LOG4Z_MAIN_LOGGER_ID, true);


    ILog4zManager::getRef().setLoggerLevel(LOG4Z_MAIN_LOGGER_ID, LOG_LEVEL_TRACE);
    LOGT("set LOG_LEVEL_TRACE ----------------------------");
    ILog4zManager::getRef().setLoggerLevel(LOG4Z_MAIN_LOGGER_ID, LOG_LEVEL_DEBUG);
    LOGT("set LOG_LEVEL_TRACE ============================");
    
    //hot update configure
    ILog4zManager::getRef().setAutoUpdate(10);
    time_t now = time(NULL);
    while(g_quit &&  time(NULL) - now < 10)
    {
        LOG_TRACE(logid_fromfile, "fromfile LOG_TRACE");
        LOG_DEBUG(logid_fromfile, "fromfile LOG_DEBUG");
        LOG_INFO(logid_fromfile, "fromfile LOG_INFO");
        LOG_WARN(logid_fromfile, "fromfile LOG_WARN");
        LOG_ERROR(logid_fromfile, "fromfile LOG_ERROR");
        LOG_ALARM(logid_fromfile, "fromfile LOG_ALARM");
        LOG_FATAL(logid_fromfile, "fromfile LOG_FATAL");

        LOG_TRACE(logid_dynamic, "dynamic LOG_TRACE");
        LOG_DEBUG(logid_dynamic, "dynamic LOG_DEBUG");
        LOG_INFO(logid_dynamic, "dynamic LOG_INFO");
        LOG_WARN(logid_dynamic, "dynamic LOG_WARN");
        LOG_ERROR(logid_dynamic, "dynamic LOG_ERROR");
        LOG_ALARM(logid_dynamic, "dynamic LOG_ALARM");
        LOG_FATAL(logid_dynamic, "dynamic LOG_FATAL");

        LOGT("main LOGT");
        LOGD("main LOGD");
        LOGI("main LOGI");
        LOGW("main LOGW");
        LOGE("main LOGE");
        LOGA("main LOGA");
        LOGF("main LOGF");
        LOGF(" = = = = = = = = = = = = = = =  = = = = = ");
#ifdef WIN32
        ::Sleep(rand()%3000);
#else
        usleep((rand()%3000)*1000);
#endif
    }

#ifdef WIN32
    // test ANSI->OEM codepage converting, only interesting in Windows environment
    // source file contains characters in ANSI CP1251
    // log file should contain same coding as source ANSI CP1251
    // console output should be OEM 866
    // sorry guys, this test is in russian
#ifdef LOG4Z_OEM_CONSOLE
	LOGI("(LOG4Z_OEM_CONSOLE enabled)");
    LOGI("Following string should be in CP1251 if compiled without LOG4Z_OEM_CONSOLE and in OEM coding if compiled with LOG4Z_OEM_CONSOLE (for RU locale oem=866)");
    std::fstream fs;
    fs.open("./oem_test_CP1251.txt", std::ios::binary | std::ios::in);
    if (fs.is_open())
    {
        char buf[201] = { 0 };
        fs.read(buf, 200);
        LOGI(buf);
        fs.close();
    }
#else
	LOGI("(LOG4Z_OEM_CONSOLE disabled)");
#endif

#endif

    LOGA("main quit .. hit 'enter' to exit.");
    getchar();
    return 0;
}




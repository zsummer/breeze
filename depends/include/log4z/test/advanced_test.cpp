
#include "../log4z.h"
#include <iostream>
#include <stdio.h>
#include <signal.h>
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


    //hot update configure
    ILog4zManager::getRef().setAutoUpdate(10);

    while(g_quit)
    {
        LOG_DEBUG(logid_fromfile, "fromfile LOG_DEBUG");
        LOG_INFO(logid_fromfile, "fromfile LOG_INFO");
        LOG_WARN(logid_fromfile, "fromfile LOG_WARN");
        LOG_ERROR(logid_fromfile, "fromfile LOG_ERROR");
        LOG_ALARM(logid_fromfile, "fromfile LOG_ALARM");
        LOG_FATAL(logid_fromfile, "fromfile LOG_FATAL");

        LOG_DEBUG(logid_dynamic, "dynamic LOG_DEBUG");
        LOG_INFO(logid_dynamic, "dynamic LOG_INFO");
        LOG_WARN(logid_dynamic, "dynamic LOG_WARN");
        LOG_ERROR(logid_dynamic, "dynamic LOG_ERROR");
        LOG_ALARM(logid_dynamic, "dynamic LOG_ALARM");
        LOG_FATAL(logid_dynamic, "dynamic LOG_FATAL");

        LOGD("main LOGD");
        LOGI("main LOGI");
        LOGW("main LOGW");
        LOGE("main LOGE");
        LOGA("main LOGA");
        LOGF("main LOGF");
        LOGF(" = = = = = = = = = = = = = = =  = = = = = ");
#ifdef WIN32
        ::Sleep(rand()%10000);
#else
        usleep((rand()%10000)*1000);
#endif

    }

    LOGA("main quit ..");
    return 0;
}




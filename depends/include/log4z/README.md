Welcome to the log4z wiki!  
## Introduction:  
[![Build Status](https://travis-ci.org/zsummer/log4z.svg?branch=master)](https://travis-ci.org/zsummer/log4z)
[![Build Status](https://webapi.biicode.com/v1/badges/fenix/fenix/log4z/master)](https://www.biicode.com/fenix/log4z)   
```
Log4z is an open source C++ lightweight & cross platform log library.   
It provides in a C++ application log and trace debug function for 7*24h service program.  
Support 64/32 of windows/linux/mac/android/iOS.   
Log4z是一款开源的轻量级的跨平台日志库 主要针对7*24小时服务器程序的日志输出与跟踪调试,   
支持64/32位的windows/linux/mac/android/iOS等操作系统.  
```
## Feature:  
```
1. MIT open source license,very liberal.  
   MIT开源授权 授权的限制非常小.  
2. Cross Platform Linux & Windows & mac, Lightweight  only one cpp sourse file one header file.  
   跨平台支持linux & windows & mac, 轻量级 只有一个头文件和一个cpp文件.  
3. 不需要关心创建和销毁等问题 全部自动化.  
4. Multi-Logger Output, Rolling File, Priority Filter, Thread Safe.  
   支持多日志分流,滚动日志记录, 优先级过滤, 多线程安全.
5. Screen Display Log with Different Color.  
   屏显日志彩色输出.  
6. Support format-style and stream-style write log.  
   支持格式化形式和流形式输入日志.  
7. Support configure from file and hot update, or can direct fast work without any config.  
   可通过配置文件配置并进行配置热更新,也可以不做任何配置直接快速使用.  
```
### File Name Format:   
**LogName_YearMonthDayHourMinute_ProcessID_BlockNumber.log**  
**日志名_年月日时分_进程ID_文件滚动分块编号.log**  
  
```   
E:\GITHUB\LOG4Z\PROJECT\BIN  
│──advanced_test.exe  
│──config.cfg  
│──fast_test.exe  
│──stress_test.exe  
│  
├─log  
│──│──advanced_test_2013100921_003852_000.log  
│──│──advanced_test_2013101313_005920_000.log    
│──│──fast_test_2013100921_003855_000.log  
│──│  
│──└─2013_10  
│─────│────Dynamic_2013100921_003852_000.log  
│  
└─Stress  
───│────NetWork_2013101313_007196_000.log  
───│────NetWork_2013101313_007196_001.log  
───│────NetWork_2013101313_007196_002.log  
```  
### 日志内容[Log Content]  
![fast_output_linux.png](https://raw.github.com/zsummer/wiki-pic/master/log4z/fast_output_linux.png)  
![fast_output_windows.png](https://raw.github.com/zsummer/wiki-pic/master/log4z/fast_output_windows.png)  
```
2015-12-15 14:36:43.453 LOG_ALARM -----------------  log4z thread started!   ----------------------------
2015-12-15 14:36:43.453 LOG_ALARM logger id=0 key=Main name=a.out path=./log/ level=1 display=1
2015-12-15 14:36:43.503 LOG_DEBUG stream input *** LOGD LOGD LOGD LOGD ***  (main.cpp):10
2015-12-15 14:36:43.503 LOG_INFO  stream input *** LOGI LOGI LOGI LOGI ***  (main.cpp):11
2015-12-15 14:36:43.503 LOG_WARN  stream input *** LOGW LOGW LOGW LOGW ***  (main.cpp):12
2015-12-15 14:36:43.503 LOG_ERROR stream input *** LOGE LOGE LOGE LOGE ***  (main.cpp):13
2015-12-15 14:36:43.503 LOG_ALARM stream input *** LOGA LOGA LOGA LOGA ***  (main.cpp):14
2015-12-15 14:36:43.503 LOG_FATAL stream input *** LOGF LOGF LOGF LOGF ***  (main.cpp):15
2015-12-15 14:36:43.503 LOG_DEBUG format input *** LOGFMTD *** 123456 *** (main.cpp):20
2015-12-15 14:36:43.503 LOG_INFO  format input *** LOGFMTI *** 123456 *** (main.cpp):21
2015-12-15 14:36:43.503 LOG_WARN  format input *** LOGFMTW *** 123456 *** (main.cpp):22
2015-12-15 14:36:43.503 LOG_ERROR format input *** LOGFMTE *** 123456 *** (main.cpp):23
2015-12-15 14:36:43.503 LOG_ALARM format input *** LOGFMTA *** 123456 *** (main.cpp):24
2015-12-15 14:36:43.503 LOG_FATAL format input *** LOGFMTF *** 123456 *** (main.cpp):25
2015-12-15 14:36:43.503 LOG_ALARM main quit ... (main.cpp):27
```
## Example  
```  
  #include "log4z.h"  
  using namespace zsummer::log4z;  
  int main(int argc, char *argv[])  
  {  
      //start log4z  
      ILog4zManager::getRef().start();  
      
      //begin test stream log input....  
      LOGT("stream input *** " << "LOGT LOGT LOGT LOGT" << " *** ");  
      LOGD("stream input *** " << "LOGD LOGD LOGD LOGD" << " *** ");  
      LOGI("stream input *** " << "LOGI LOGI LOGI LOGI" << " *** ");  
      LOGW("stream input *** " << "LOGW LOGW LOGW LOGW" << " *** ");  
      LOGE("stream input *** " << "LOGE LOGE LOGE LOGE" << " *** ");  
      LOGA("stream input *** " << "LOGA LOGA LOGA LOGA" << " *** ");  
      LOGF("stream input *** " << "LOGF LOGF LOGF LOGF" << " *** ");  
  
      // cannot support VC6 or VS2003  
      //begin test format log input....  
      LOGFMTT("format input *** %s *** %d ***", "LOGFMTT", 123456);  
      LOGFMTD("format input *** %s *** %d ***", "LOGFMTD", 123456);  
      LOGFMTI("format input *** %s *** %d ***", "LOGFMTI", 123456);  
      LOGFMTW("format input *** %s *** %d ***", "LOGFMTW", 123456);  
      LOGFMTE("format input *** %s *** %d ***", "LOGFMTE", 123456);  
      LOGFMTA("format input *** %s *** %d ***", "LOGFMTA", 123456);  
      LOGFMTF("format input *** %s *** %d ***", "LOGFMTF", 123456);  
  
      LOGA("main quit ...");  
      return 0;  
  }  
```  

# How to compile  
### Directly Using The Way 直接使用:    
Add files log4z.cpp log4z.h and compile together in the existing projects  
把文件 log4z.cpp log4z.h添加到已有项目中并一起编译.  
### Make Library To Use   
**In Windows:**  
```
Open and compile log4z/vc2005/log4z.vcproj
```  
**In Linux :**   
```
cd log4z/g++   
cmake .   
make   
```  
#About The Author  
Author: YaweiZhang  
Mail: yawei.zhang@foxmail.com  
GitHub: https://github.com/zsummer/log4z  

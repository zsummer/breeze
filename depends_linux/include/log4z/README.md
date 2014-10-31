Welcome to the log4z wiki!  
# Introduction:    

Log4z is an open source C++ lightweight & cross platform log library.   
It provides in a C++ application log and trace debug function for 7*24h service program.  
Support 64/32 of windows/linux/mac/android/iOS.   

Log4z是一款开源的轻量级的跨平台日志库 主要针对7*24小时服务器程序的日志输出与跟踪调试,   
支持64/32位的windows/linux/mac/android/iOS等操作系统.  
  


# Feature:  
    
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


# The  Log File  
The output log file through a configuration file or when the program starts a flexible configuration   
日志文件的输出可以通过配置文件或者在程序启动时进行灵活的配置   
  
### File Name Format:   
LogName_YearMonthDayHourMinute_ProcessID_BlockNumber.log    
日志名_年月日时分_进程ID_文件滚动分块编号.log    
  
***   
E:\GITHUB\LOG4Z\PROJECT\BIN  
│──advanced_test.exe  
│──config.cfg  
│──fast_test.exe  
│──stress_test.exe  
│  
├─AdvacedLog  
│──│───FileConfig_2013100921_003852_000.log  
│──│───FileConfig_2013101313_005920_000.log  
│  
├─log  
│──│──advanced_test_2013100921_003852_000.log  
│──│──advanced_test_2013101313_005920_000.log    
│──│──fast_test_2013100921_003855_000.log  
│──│──fast_test_2013101313_006160_000.log  
│──│──stress_test_2013101313_007196_000.log  
│──│  
│──└─2013_10  
│─────│────Dynamic_2013100921_003852_000.log  
│─────│────Dynamic_2013101313_005920_000.log  
│  
└─Stress  
───│────NetWork_2013101313_007196_000.log  
───│────NetWork_2013101313_007196_001.log  
───│────NetWork_2013101313_007196_002.log  
───│────NetWork_2013101313_007196_003.log  
───│────NetWork_2013101313_007196_004.log  
***  
### 日志内容[Log Content]  
![fast_output_linux.png](https://raw.github.com/zsummer/wiki-pic/master/log4z/fast_output_linux.png)  
![fast_output_windows.png](https://raw.github.com/zsummer/wiki-pic/master/log4z/fast_output_windows.png)  

# How To Use Log4z  
![hellow_world.png](https://raw.github.com/zsummer/wiki-pic/master/log4z/hellow_world.png)  

# How to compile  
### Directly Using The Way 直接使用:    
Add files log4z.cpp log4z.h and compile together in the existing projects  
把文件 log4z.cpp log4z.h添加到已有项目中并一起编译.  
### Make Library To Use   
**In Windows:**  
`Open and compile log4z/vc2005/log4z.vcproj`  
**In Linux :**   
`cd log4z/g++`   
`cmake .`   
`make`   

#About The Author  
Auther: YaweiZhang  
Web Site: www.zsummer.net  
Mail: yawei_zhang@foxmail.com  
GitHub: https://github.com/zsummer  

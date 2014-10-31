#ifndef _APPLICATION_H_
#define _APPLICATION_H_
#include <string>
//文件说明
//应用程序类
//封装程序启动-初始化-运行-结束的功能
class Appliction
{
public:
	Appliction();
	~Appliction();
	static Appliction & getRef();
	static Appliction * getPtr(){ return &getRef(); }

	bool Init(std::string filename, unsigned int index);
	void RunPump();
	void Stop();
protected:
	void _Stop();
};




































#endif

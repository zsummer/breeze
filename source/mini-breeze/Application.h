#ifndef _APPLICATION_H_
#define _APPLICATION_H_
#include <string>


class Appliction
{
public:
	Appliction();
	~Appliction();
	static Appliction & getRef();
	static Appliction * getPtr(){ return &getRef(); }

	bool Init(std::string filename, unsigned int index);
	void Run();
	void Stop();
protected:
	void _Stop();
};




































#endif

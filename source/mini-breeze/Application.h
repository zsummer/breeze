#ifndef _APPLICATION_H_
#define _APPLICATION_H_
#include <string>
#include <Common.h>

class Appliction : public Singleton<Appliction>
{
public:
	Appliction();
	~Appliction();
	bool Init(std::string filename, unsigned int index);
	void Run();
	void Stop();
protected:
	void _Stop();
};




































#endif

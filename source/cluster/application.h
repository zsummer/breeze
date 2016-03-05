#ifndef _APPLICATION_H_
#define _APPLICATION_H_
#include <common.h>

class Appliction : public Singleton<Appliction>
{
public:
    Appliction();
    ~Appliction();
    bool init(std::string filename, unsigned int index);
    void run();
    void stop();
protected:
    void _onSigalStop();
    void _onNetClosed();
    void _onDBClosed();
};




































#endif

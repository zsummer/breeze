#include "../traceback.h"

void func(int a)
{
    std::cout << zsummer::traceback();
}
int main(int argc, char *argv[])
{
    func(1);

    return 0;
}

/*
g++ stack.cpp -g -O0
gdb info line * 0x40000000
google coredumper
*/
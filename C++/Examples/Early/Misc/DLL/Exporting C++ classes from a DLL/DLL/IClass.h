#pragma once

class IClass { //Exporting C++ classes from a DLL @ http://eli.thegreenplace.net/2011/09/16/exporting-c-classes-from-a-dll/
public:
    virtual void destroy() = 0;
    virtual int do_stuff(int param) = 0;
    virtual void do_something_else(double f) = 0;
};

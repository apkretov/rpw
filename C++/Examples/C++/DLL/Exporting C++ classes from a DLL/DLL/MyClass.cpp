#include "stdafx.h"
#include "IClass.h" //Exporting C++ classes from a DLL @ http://eli.thegreenplace.net/2011/09/16/exporting-c-classes-from-a-dll/
#include <iostream>
#include <windows.h>
using namespace std;

class MyClass : public IClass {
	int m_data;
public:
	MyClass() : m_data(0) { cerr << "MyClass constructor\n"; }
	~MyClass() { cerr << "MyClass destructor\n";	}
	void destroy()	{ delete this; }

	int do_stuff(int param) {
		m_data += param;
		return m_data;
	}

	void do_something_else(double f)	{
		int intpart = static_cast<int>(f);
		m_data += intpart;
}	};

extern "C" __declspec(dllexport) IClass* __cdecl create_class() { return new MyClass; }

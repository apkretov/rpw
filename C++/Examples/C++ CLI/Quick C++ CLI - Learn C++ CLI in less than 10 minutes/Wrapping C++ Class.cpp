#include "stdafx.h" //Quick C++/CLI - Learn C++/CLI in less than 10 minutes @ https://www.codeproject.com/Articles/19354/Quick-C-CLI-Learn-C-CLI-in-less-than-minutes
#include <cstring>
using namespace System;

class Student { // native class
private:
	char *_fullname;
	double _gpa;
public:
	Student(char* name, double gpa) {
		_fullname = new char[strlen(name + 1)];
		strcpy(_fullname, name);
		_gpa = gpa;
	}
	~Student() { delete[] _fullname; }
	double getGpa() { return _gpa; }
	char* getName() { return _fullname; }
};

ref class StudentWrapper { // Managed class
private:
	Student* _stu;
public:
	StudentWrapper(String^ fullname, double gpa) { _stu = new Student((char*)Runtime::InteropServices::Marshal::StringToHGlobalAnsi(fullname).ToPointer(), gpa); }
	~StudentWrapper() {
		delete _stu;
		_stu = 0;
	}
	property String^ Name {
		String^ get() { return gcnew String(_stu->getName()); }
	}
	property double Gpa {
		double get() { return _stu->getGpa(); }
}	};

int main(array<String ^> ^args) {

	return 0;
}

#include "stdafx.h" //Quick C++/CLI - Learn C++/CLI in less than 10 minutes @ https://www.codeproject.com/Articles/19354/Quick-C-CLI-Learn-C-CLI-in-less-than-minutes
#using <mscorlib.dll>
using namespace System;

public ref class MyNamesSplitterClass {
	String^ _FName, ^_LName;
public:
	MyNamesSplitterClass(String ^FullName) {
		int pos = FullName->IndexOf(" ");
		if (pos < 0) throw gcnew Exception("Invalid full name!");
		_FName = FullName->Substring(0, pos);
		_LName = FullName->Substring(pos + 1, FullName->Length - pos - 1);
	}
	void Print() { Console::WriteLine("First name: {0}\nLastName: {1}", _FName, _LName); }
};

void avg(String ^msg, ... array<int>^ values) {
	int tot = 0;
	for each (int v in values) tot += v;
	Console::WriteLine("{0} {1}", msg, tot / values->Length);
}

int main(array<String^>^ args) {
	MyNamesSplitterClass s("John Doe"); // local copy
	s.Print();
	MyNamesSplitterClass^ ms = gcnew MyNamesSplitterClass("Managed C++"); // managed heap
	ms->Print();
	cli::array<int> ^a = gcnew cli::array<int> {1, 2, 3};
	
	for each (auto% i in a) Console::WriteLine(i);

	array<String^>^ strs = gcnew array<String^>(5);
	int cnt = 0;
	for each (String^% s in strs)	s = gcnew String((cnt++).ToString()); // We use the tracking reference to access the references inside the array since normally strings are passed by value
	
	avg("The avg is:", 1,2,3,4,5);

	return 0;
}

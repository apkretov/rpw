#include "stdafx.h" //C++/CLI Tutorial @ http://asawicki.info/Download/Productions/Publications/CPP_CLI_tutorial.pdf
#include <iostream>
//using namespace std;
using std::cout;
using std::endl;
using namespace System;

ref class ManagedMonster {
	int* m_DynamicHP;
public:
	ManagedMonster(int HP) : m_DynamicHP(new int(HP)) { cout << "ManagedMonster Constructor" << endl; }
	~ManagedMonster() {
		cout << "ManagedMonster Destructor" << endl;
		this->!ManagedMonster();
	}
	!ManagedMonster() {
		cout << "ManagedMonster Finalizer" << endl;
		delete m_DynamicHP;
	}
	void TellHitPoints() { cout << "ManagedMonster has " << *m_DynamicHP << " HP" << endl;	}
};

ref struct Globals {	static ManagedMonster^ g_GlobalManagedMonster = gcnew ManagedMonster(200); };

int main(array<System::String ^> ^args) {
	Console::WriteLine(L"Hello World");
	Globals::g_GlobalManagedMonster->TellHitPoints();
	return 0;
}

#include "stdafx.h" //C++/CLI Tutorial @ http://asawicki.info/Download/Productions/Publications/CPP_CLI_tutorial.pdf
using namespace System;
#include <iostream>
using std::cout;
using std::endl;

class NativeMonster {
	int m_HP;
public:
	NativeMonster(int HP) : m_HP(HP) { cout << "NativeMonster Constructor" << endl; }
	~NativeMonster() { cout << "NativeMonster Destructor" << endl;	}
	void TellHitPoints() { cout << "NativeMonster has " << m_HP << " HP" << endl;	}
};

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
	void TellHitPoints() { cout << "ManagedMonster has " << *m_DynamicHP << " HP" << endl; }
};

ref class ManagedDungeonRoom {
	NativeMonster* m_Goblin; // OK
	ManagedMonster^ m_Boss; // OK
};

class NativeDungeonRoom {
	NativeMonster *m_Goblin; // OK
	// ERROR ManagedMonster ^m_Boss; 
};

int main(array<System::String ^> ^args) {
	Console::WriteLine(L"Hello World");
	return 0;
}

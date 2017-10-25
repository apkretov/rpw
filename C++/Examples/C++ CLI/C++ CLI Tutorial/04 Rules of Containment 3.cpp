#include "stdafx.h" //C++/CLI Tutorial @ http://asawicki.info/Download/Productions/Publications/CPP_CLI_tutorial.pdf
using namespace System;
#include <iostream>
using std::cout;
using std::endl;
#include <msclr\gcroot.h>

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

class NativeDungeonRoom {
	NativeMonster *m_Goblin; // OK
	msclr::gcroot<ManagedMonster^> m_Boss; // Also OK
public:
	NativeDungeonRoom() : m_Goblin(new NativeMonster(10))	, m_Boss(gcnew ManagedMonster(1000)) {}
	~NativeDungeonRoom() { delete m_Goblin; }
	void AskMonsters() {
		m_Goblin->TellHitPoints();
		m_Boss->TellHitPoints();
}	};

int main(array<System::String ^> ^args) {
	Console::WriteLine(L"Hello World");
	return 0;
}

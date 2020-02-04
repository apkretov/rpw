#include "stdafx.h" //C++/CLI Tutorial @ http://asawicki.info/Download/Productions/Publications/CPP_CLI_tutorial.pdf
using namespace System;
#include <iostream>
using std::cout;
using std::endl;

ref class ManagedMonster {
	int *m_DynamicHP;
public:
	ManagedMonster(int HP) : m_DynamicHP(new int(HP)) { cout << "ManagedMonster Constructor" << endl; }
	ManagedMonster::~ManagedMonster() {
		cout << "ManagedMonster Destructor" << endl;
		this->!ManagedMonster();
	}
	!ManagedMonster() {
		cout << "ManagedMonster Finalizer" << endl;
		delete m_DynamicHP;
	}
	void ManagedMonster::TellHitPoints() { cout << "ManagedMonster has " << *m_DynamicHP << " HP" << endl; }
};

int main(array<System::String ^> ^args) {
	ManagedMonster ^monster_ref = gcnew ManagedMonster(120);
	monster_ref->TellHitPoints();
}

#include "stdafx.h" //Top 10 dumb mistakes to avoid with C++ 11 smart pointers @ http://www.acodersjourney.com/2016/05/top-10-dumb-mistakes-avoid-c-11-smart-pointers/
#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Aircraft {
	string m_model;
public:
	int m_flyCount;
	weak_ptr<Aircraft> myWingMan;

	void Fly() { cout << "Aircraft type" << m_model << "is flying !" << endl; }

	Aircraft(string model) {
		m_model = model;
		cout << __COUNTER__ << " Constructor: Aircraft type " << model << " is created" << endl;
	}

	Aircraft() {
		m_model = "Generic Model";
		cout << __COUNTER__ << " Constructor: Generic Model Aircraft created." << endl;
	}

	~Aircraft()	{ cout << __COUNTER__ << " ~Destructor: Aircraft type  " << m_model << " is destroyed" << endl; }
};

void Mistake5() { //Mistake # 5 : Not assigning an object(raw pointer) to a shared_ptr as soon as it is created !
	Aircraft* myAircraft = new Aircraft("F-16");

	shared_ptr<Aircraft> pAircraft (myAircraft);
	cout << "pAircraft.use_count() = " << pAircraft.use_count() << endl; // ref-count is 1

	shared_ptr<Aircraft> pAircraft2(myAircraft); //The problem is that when the first shared_ptr goes out of scope, the myAircraft object is destroyed. When the second shared_ptr goes out of scope , it tries to destroy the previously destroyed object again ! @ http://www.acodersjourney.com/2016/05/top-10-dumb-mistakes-avoid-c-11-smart-pointers/
	cout << "pAircraft2.use_count() = " << pAircraft2.use_count() << endl; // ref-count is 1
}

void Mistake6() { //Mistake # 6 : Deleting the raw pointer used by the shared_ptr !
	shared_ptr<Aircraft> pAircraft(new Aircraft("F-16"));
	Aircraft* myAircraft = pAircraft.get(); // returns the raw pointer
	delete myAircraft;  // myAircraft is gone
}

void Mistake7_1() { //Mistake # 7 : Not using a custom deleter when using an array of pointers with a shared_ptr !
	shared_ptr<Aircraft> pAircraft(new Aircraft[3]); //The shared pointer will just point to Aircraft[0] — Aircraft[1] and Aircraft[2] have memory leaks will not be cleaned up when the smart pointer goes out of scope.
}

void Mistake7_2() { //Recommendation: Always pass a custom delete with array objects managed by shared_ptr. The following code fixes the issue:
	shared_ptr<Aircraft> pAircraft(new Aircraft[3], [](Aircraft* ptrAircraft) { delete[] ptrAircraft; } );
}

void Mistake8() { //Mistake # 8 : Not avoiding cyclic references when using shared pointers !
	shared_ptr<Aircraft> pMaverick = make_shared<Aircraft>("Maverick: F-14");
	shared_ptr<Aircraft> pIceman = make_shared<Aircraft>("Iceman: F-14");
	pMaverick->myWingMan = pIceman; // So far so good - no cycles yet
	pIceman->myWingMan = pMaverick; // now we got a cycle - neither maverick nor goose will ever be destroyed
}

void Mistake10_1() { //Mistake # 10 : Not using a expiry check when calling weak_ptr.lock() !
	auto pMaverick = make_shared<Aircraft>("F-22");
	auto pIceman = make_shared<Aircraft>("F-14");
	pMaverick->myWingMan = pIceman;
	pIceman->m_flyCount = 17;
	pIceman.reset(); // destroy the object managed by pIceman
	cout << pMaverick->myWingMan.lock()->m_flyCount << endl; // ACCESS VIOLATION
}

void Mistake10_2() { //It can be fixed easily by incorporating the following if check before using the myWingMan weak_ptr.
	auto pMaverick = make_shared<Aircraft>("F-22");
	auto pIceman = make_shared<Aircraft>("F-14");
	pMaverick->myWingMan = pIceman;
	pIceman->m_flyCount = 17;
	pIceman.reset(); // destroy the object managed by pIceman
	if (!pMaverick->myWingMan.expired()) cout << pMaverick->myWingMan.lock()->m_flyCount << endl;
}

int main() {
	//Mistake5();
	//Mistake6();
	//Mistake7_1();
	//Mistake7_2();
	//Mistake8();
	//Mistake10_1();
	Mistake10_2();
   return 0;
}

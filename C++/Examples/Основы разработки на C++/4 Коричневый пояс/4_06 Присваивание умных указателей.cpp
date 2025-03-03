#if 0

#include <iostream>
#include <memory>
#include <string>
//OFF #include "vld.h"
using namespace std;

#ifdef MINE
class A {
	string name_;
public:
	explicit A(const string &name) : name_(name) { cout << name << " created\n"; }
	~A() { cout << name_ << " destroyed\n"; }
};

int main() {
	auto up1 = make_unique<A>("Alice");
	auto up2 = make_unique<A>("Boris");
	cout << "Before up1 = std::move(up2);\n";
	up1 = std::move(up2);
	cout << "After up1 = std::move(up2);\n";
}
#endif //MINE

class Actor {
	string name_;
public:
	explicit Actor(string name) : name_(std::move(name)) { cout << name_ << " was born! :)" << endl; }
	~Actor() { cout << name_ << " died! :(" << endl; }

	void DoWork() {	cout << name_ << " did some job! :(" << endl; }
};

void run(Actor *ptr) {
	if (ptr)
		ptr->DoWork();
	else
		cout << "An actor was expected :-/" << endl;
}

int main() {
	auto ptr1 = make_unique<Actor>("Alice");
	auto ptr2 = make_unique<Actor>("Boris");
	cout << "----" << endl;
	ptr1 = std::move(ptr2);
	run(ptr1.get()); //TEST!
	run(ptr2.get());
	cout << "----" << endl;
	return 0;
}
#endif //1

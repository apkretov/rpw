#pragma once

#pragma region Perplexity

#include <iostream> // Propagation Example
#include <stdexcept>
using namespace std;

struct Base {
	Base() { cout << "Base constructed\n"; }
	~Base() { cout << "Base destroyed\n"; }
};

struct Member {
	Member() { 
		cout << "Member constructed\n"; 
		throw runtime_error("Member failure"); 
	}

	~Member() { cout << "Member destroyed\n"; }
};

struct Derived : Base {
	Member m;
	Derived() { cout << "Derived body\n"; }
	~Derived() { cout << "Derived destroyed\n"; }
};

int main_02() {
	try {
		Derived d;
	}
	catch (const exception& e) {
		cout << "Caught: " << e.what() << "\n";
	}
	return 0;
}
#pragma endregion

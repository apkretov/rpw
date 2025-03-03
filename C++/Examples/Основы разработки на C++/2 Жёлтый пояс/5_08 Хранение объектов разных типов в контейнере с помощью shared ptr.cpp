#ifdef MINE

#include <iostream>
#include <vector>
#include "../../stdafx.h"
using namespace std;

class base {
public:
	virtual ~base() = default;

	virtual void echo() const {
		cout << "Base\t";
		cout << "count = " << count << '\n';
	}

	void increment() {
		++count;
	}
protected:
	int count{};
};

class derived : public base {
public:
	void echo() const final {
		cout << "Derived\t";
		cout << "count = " << count << '\n';
	}
};

void call_const_fnc(const shared_ptr<const base> &b) { //TEST!
	b->echo();
}

void call_nonconst_fnc(const shared_ptr<base> &b) {
	b->increment();
	call_const_fnc(b);
}

int main() {
	PRINT_FILE_LINE();

	auto b = make_shared<base>();
	auto d = make_shared<derived>();

	vector<shared_ptr<base>> vs;
	vs.push_back(b);
	vs.push_back(d);

	for (const auto &i : vs) {
		call_const_fnc(i);
		call_nonconst_fnc(i);
	}
	cout << '\n';
}
#endif //MINE

#ifdef PERPLEXITY // A memory leak example.
#include <vector>
#include "vld.h"
#include <iostream>
using namespace std;

class Base {
public:
	Base() {
		cout << "Base constructor" << endl;
	}

	~Base() { //TEST //																																	Destructor not declared as virtual
		cout << "Base destructor" << endl;
	}
};

class Derived : public Base {
public:
	Derived() {
		cout << "Derived constructor" << endl;
		resource = new int[10]; // Allocating memory
	}

	~Derived() {
		cout << "Derived destructor" << endl;
		delete[] resource; // Deallocating memory
	}

private:
	int *resource;
};

int main() {
	Base *obj = new Derived();
	delete obj;  // Memory leak occurs here
}

#endif //PERPLEXITY

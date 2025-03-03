#ifdef ON

#include <format>
#include <iostream>
#include "../../stdafx.h"
using namespace std;

#pragma region MINE
struct Base {
	virtual void print() const {
		cout << "Base\n";
	}

	virtual ~Base() = default;
};

struct Derived : Base {
	void print() const final {
		cout << "Derived\n";
	}
};

void polymorphic_ref_1() {
	Base b;
	Base &rb = b;
	Derived d;
	const Derived &rd = d;

	rb = rd;
	rb.print();
}

void polymorphic_ref_2() {
	Base b;
	Derived d;
	const Base &base_rd = d;
	const Derived &der_rd = d;
	//ERR Derived &der_rb = b;

	base_rd.print();
	der_rd.print();
}

enum class errCodes {
	severeErr = 1,
	badErr = 2
};

struct my_error : exception {
	errCodes status{};
};

struct other_error : exception {
	errCodes status{};
};
#pragma endregion

[[noreturn]] void Rethrow_1() {
	try { //MINE
		throw my_error();
	}
	catch (my_error &eObj) { // specifier is a reference type
		eObj.status = errCodes::severeErr; // modifies the exception object
		throw; // the status member of the exception object is severeErr
	}
}

[[noreturn]] void Rethrow_2() {
	try { //MINE
		throw other_error();
	}
	catch (other_error eObj) { // specifier is a nonreference type
		eObj.status = errCodes::badErr; // modifies the local copy only
		throw; // the status member of the exception object is unchanged
	}
}

#pragma region The Catch - All Handler
void manip() {
	try {
		// actions that cause an exception to be thrown
	}
	catch (...) {
		// work to partially handle the exception
		throw;
	}
}
#pragma endregion

int main() {
	print_file_line();

	//polymorphic_ref_1();
	//polymorphic_ref_2();

	try {
		Rethrow_1();
		//Rethrow_2();
	}
	catch (const my_error &e) {
		auto msg = format("Error: {}\ne.status = {}", e.what(), static_cast<int>(e.status));
		cerr << log_str(msg) << '\n';
	}
	catch (const other_error &e) {
		auto msg = format("Error: {}\ne.status = {}", e.what(), static_cast<int>(e.status));
		cerr << log_str(msg) << '\n';
	}
	catch (...) {
		cerr << log_str("Unknown exception") << '\n';
	}

	return 0;
}
#endif

#ifdef EX_18_04

#include <iostream>
#include "../../stdafx.h"
using namespace std;

int main() {
	print_file_line();

#ifdef ORIG
	try {
		// use of the C++ standard library
	}
	catch (exception) {
		// ...
	}
	catch (const runtime_error &re) {
		// ...
	}
	catch (overflow_error eobj) { /* ... */ }
#endif

	try {
		// use of the C++ standard library
	}
	//ORIG catch (overflow_error eobj) { 
	catch (overflow_error &eobj) {
		/* ... */
	}
	catch (const runtime_error &re) {
		// ...
	}
	//ORIG catch (exception) {
	catch (const exception &e) {
		// ...
	}

	return 0;
}
#endif

#ifdef EX_18_05

#include <iostream>
#include "../../stdafx.h"
using namespace std;

int main() {
	print_file_line();

	try {
		// use of the C++ standard library
#ifndef EXCEPTION
		throw exception("Error thrown from main");
#else //BAD_CAST
		throw bad_cast();
#endif
	}
	catch (const bad_cast &e) {
		cerr << log_str(e.what()) << '\n';
	}
	catch (const bad_alloc &e) {
		cerr << log_str(e.what()) << '\n';
	}
#pragma region runtime_error
	catch (const range_error &e) {
		cerr << log_str(e.what()) << '\n';
	}
	catch (const underflow_error &e) {
		cerr << log_str(e.what()) << '\n';
	}
	catch (const overflow_error &e) {
		cerr << log_str(e.what()) << '\n';
	}
	catch (const runtime_error &e) {
		cerr << log_str(e.what()) << '\n';
	}
#pragma endregion
#pragma region logic_error
	catch (const length_error &e) {
		cerr << log_str(e.what()) << '\n';
	}
	catch (const out_of_range &e) {
		cerr << log_str(e.what()) << '\n';
	}
	catch (const invalid_argument &e) {
		cerr << log_str(e.what()) << '\n';
	}
	catch (const domain_error &e) {
		cerr << log_str(e.what()) << '\n';
	}
	catch (const logic_error &e) {
		cerr << log_str(e.what()) << '\n';
	}
#pragma endregion
	catch (const exception &e) {
		cerr << log_str(e.what()) << '\n';
	}
	catch (...) {
		cerr << log_str("Unknown error...") << '\n';
	}

	return 0;
}
#endif

#ifdef EX_18_06

#include <iostream>
#include "../../stdafx.h"
using namespace std;

typedef int EXCPTYPE; // (c) 
class exceptionType { // (a) 
public:
	explicit operator EXCPTYPE() const {
		return 111;
	}
};

int main() {
	print_file_line();

	try {
		auto et = exceptionType();
		auto j = static_cast<EXCPTYPE>(et);
		cout << "j = " << j << '\n';
		
#ifndef EXCEPTIONTYPE
		throw new exceptionType();
#else // EXCEPTIONTYPE
		throw EXCPTYPE();

#endif // !_1
	}
	catch (exceptionType *pet) {
		cerr << log_str("exceptionType *pet") << '\n';
	}
	catch (EXCPTYPE) { // (c) 
		cerr << log_str("EXCPTYPE") << '\n';
	}
	catch (...) { // (b) 
		cerr << log_str("Unknown error...") << '\n';
	}

	return 0;
}
#endif

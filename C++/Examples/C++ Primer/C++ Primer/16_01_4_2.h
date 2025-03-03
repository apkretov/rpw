#pragma once

#include <iostream>
using std::ostream;
using std::cout;
using std::cerr;
using std::endl;

//OFF #define DEBUG_DebugDelete

#ifndef Member_Templates_of_Ordianary_Nontemplate_Classes //ORIG Member Templates of Ordianary (Nontemplate) Classes
class DebugDelete { // function-object class that calls delete on a given pointer
public:
	explicit DebugDelete(ostream &s = cerr) : os(s) { //ORIG DebugDelete(ostream &s = cerr) : os(s) {
#ifdef DEBUG_DebugDelete //MINE
		os << this << ": DebugDelete constructor" << '\n';
#endif
	}
#ifdef DEBUG_DebugDelete //MINE
	DebugDelete(const DebugDelete &);
	~DebugDelete();
#endif
	template <typename T> // as with any function template, the type of T is deduced by the compiler
	void operator()(T *p) const {
#ifdef DEBUG_DebugDelete
		os << this << ": "; //MINE
		os << "deleting unique_ptr" << endl;
#endif
		delete p;
	}
private:
	ostream &os;
};
#endif

#ifdef DEBUG_DebugDelete //MINE
DebugDelete::DebugDelete(const DebugDelete &d) : os(d.os) {
	os << this << ": DebugDelete copy constructor\n";
}

DebugDelete::~DebugDelete() {
	os << this << ": DebugDelete destructor\n";
}
#endif
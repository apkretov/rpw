#pragma once // This separate header is needed because the definition of the Query constructor cannot be placed in 15_09_3.cpp, which in turn does not let 12_03_1.cpp compile.

#ifndef The_WordQuery_Class

#include "15_09_3_3.h"

#ifndef EX_15_41
inline Query::Query(const string &s) : q(new WordQuery(s)), use(new size_t(1)) {
#ifdef DEBUG
	cout << "Query constructor:\t" << typeid(*q).name() << "\t\tq->rep() = " << q->rep() << "\t\t*use = " << *use << '\n';
#endif
}

Query::Query(const Query &qr) : q(qr.q), use(qr.use) {
	++*use;
#ifdef DEBUG
	cout << "Query copy constructor:\t" << typeid(*q).name() << "\t\tq->rep() = " << q->rep() << "\t\t*use = " << *use << '\n';
#endif
}

Query &Query::operator=(const Query &rhs) {
	++*rhs.use;
#ifdef DEBUG
	cout << "\nQuery copy-assignment operator:\t" << typeid(*rhs.q).name() << "\t\tq->rep() = " << rhs.q->rep() << "\t\t*use = " << *rhs.use << '\n';
#endif

	if (--*use == 0) { 
#ifdef DEBUG
		cout << "deleting q...\n";
#endif
		delete q;
#ifdef DEBUG
		cout << "deleting use...\n";
#endif
		delete use;

	}

	q = rhs.q;
	use = rhs.use;

	return *this;
}

Query::Query(Query &&qr) noexcept : q(exchange(qr.q, nullptr)), use(exchange(qr.use, nullptr)) {
#ifdef DEBUG
	cout << "Query move constructor:\t" << typeid(*q).name() << "\t\tq->rep() = " << q->rep() << "\t\t*use = " << *use << '\n';
#endif
}

Query &Query::operator=(Query &&rhs) noexcept {
	if (&rhs != this) {
#ifdef DEBUG
		cout << "\nQuery move-assignment operator:\t" << typeid(*rhs.q).name() << "\t\tq->rep() = " << rhs.q->rep() << "\t\t*use = " << *rhs.use << '\n';
		cout << "deleting q...\n";
#endif
		delete q;
#ifdef DEBUG
		cout << "deleting use...\n";
#endif
		delete use;
		q = exchange(rhs.q, nullptr);
		use = exchange(rhs.use, nullptr);
	}
	return *this;
}

Query::~Query() {
	if (q != nullptr) {
		--*use;
#ifdef DEBUG
		cout << "\nQuery destructor:\t" << typeid(*q).name() << "\t\tq->rep() = " << q->rep() << "\t\t*use = " << *use << '\n';
#endif
		if (*use == 0) {
#ifdef DEBUG
			cout << "deleting q...\n";
#endif
			delete q;
#ifdef DEBUG
			cout << "deleting use...\n";
#endif
			delete use;
		}
	}
#ifdef DEBUG
	else
		cout << "\nQuery destructor:\tq = nullptr\t\tuse = nullptr\n";
#endif
}
#endif
#endif
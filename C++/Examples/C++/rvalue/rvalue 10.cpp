#include "stdafx.h" //Understanding lvalues and rvalues in C and C++ @ http://eli.thegreenplace.net/2011/12/15/understanding-lvalues-and-rvalues-in-c-and-c
#include <iostream>
#include <algorithm>
using namespace std;

class Intvec {
	size_t m_size;
	int* m_data;
	void log(const char* msg) { cout << this << " " << msg << "\n"; }

public:
	explicit Intvec(size_t num = 0) : m_size(num), m_data(new int[m_size]) { log("constructor"); }

	Intvec(const Intvec& other) : m_size(other.m_size), m_data(new int[m_size]) {
		log("copy constructor");
		for (size_t i = 0; i < m_size; ++i) m_data[i] = other.m_data[i];
	}

	~Intvec() {
		log("destructor");
		if (m_data) {
			delete[] m_data;
			m_data = 0;
	}	}

	Intvec& operator=(const Intvec& other) {
		log("copy assignment operator");
		Intvec tmp(other);
		swap(m_size, tmp.m_size);
		swap(m_data, tmp.m_data);
		return *this;
}	};

int main() {
	Intvec v1(20);
	Intvec v2;

	cout << endl << "assigning lvalue..." << endl;
	v2 = v1;
	cout << "ended assigning lvalue..." << endl << endl;
	return 0;
}

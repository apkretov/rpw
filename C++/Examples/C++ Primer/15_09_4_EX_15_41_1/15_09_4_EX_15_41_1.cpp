#undef DEBUG

#include <iostream>
#include <fstream>
#include <stdexcept>
//OFF #include <vld.h>
#include "../../stdafx.h"
#include "15_09_4_2.h"
#include "15_09_3_2.h"
#include "15_09_4_1.h"
using namespace std;

void queryExpress(const string path) {
	ifstream infile(path);
	TextQuery tq(infile);

	Query q = Query("fiery") & Query("bird") | Query("wind");
	cout << '\n';
	print(cout, q.eval(tq));
	cout << q << '\n';
}

void copyAssign() {
	Query q1("test 1"), q2("test 2");
	q2 = q1;
}

void moveConstr() {
	Query q1("test 1");
	Query q2 = std::move(q1);
}

void moveAssign() {
	Query q1("test 1"), q2("test 2");
	q1 = std::move(q2);
}

void memoryLeak(const string &path) {
	ifstream infile(path);
	if (!infile.is_open()) {
		string errMsg = path + " File not open!...";
		throw runtime_error(errMsg);
	}
	string fileText((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());
#ifdef DEBUG
	cout << "fileText = \n" << fileText << "\n\n";
	infile.close(); //Reset the stream after streaming out.
	infile.open(path);
	cout << '\n' << 111 << '\n';
#endif
	TextQuery tq(infile);
#ifndef _1
	Query q = Query("fiery");
#else
	Query q = Query(fileText);
#endif
#ifdef DEBUG
	cout << q << '\n';
	print(cout, q.eval(tq));
	cout << 222 << '\n';
#endif
}

void loopMemoryLeak(const string &path) {
	for (size_t i = 0; i < 10/*0000000*/; i++) {
		cout << i << "\n";
		memoryLeak(path);
	}
}

int main(int argc, char *argv[]) {
	print_file_line();

	//queryExpress(argv[1]);
	//copyAssign();
	//moveConstr();
	//moveAssign();

	try {
		{
			timer t;
			memoryLeak(argv[1]);
		}
		{
			timer t;
			loopMemoryLeak(argv[1]);
		}
	}
	catch (const runtime_error &e) {
		cerr << "Error: " << e.what() << '\n';
	}

	return 0;
}

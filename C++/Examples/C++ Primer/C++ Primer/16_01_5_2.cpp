#ifdef	EX_16_26

#include <iostream>
#include <vector>
#include "../../stdafx.h"
using std::cout;
using std::vector;

struct NoDefault {
	explicit NoDefault([[maybe_unused]] int i_) : i(i_) {}
	int i;
};

int main(int argc, char *argv[]) {
	print_file_line();

	vector<NoDefault> v;
	v.push_back(NoDefault(1));
	v.push_back(NoDefault(2));
	v.push_back(NoDefault(3));
	cout << "v.back().i = " << v.back().i << '\n';

	return 0;
}
#endif

#ifdef	EX_16_27

#include <iostream>
#include "../../stdafx.h"
using std::cout;
using std::string;

template <typename T> 
class Stack {
public:
	T t;
};

void f1(Stack<char> s) { // (a)
	cout << "f1(Stack<char> s): " << s.t << '\n';
}

class Exercise {
	Stack<double> &rsd; // (b)
	Stack<int> si; // (c)
};

void mine1() {
	Stack<char> *sc; // (d)
	//TEST f1(*sc); // (e)
	int iObj = sizeof(Stack< string >); // (f)
}

void mine2() {
	Stack<char> sc{};
	sc.t = 'a';
	f1(sc);
}

int main(int argc, char *argv[]) {
	print_file_line();

	mine2();

	return 0;
}
#endif

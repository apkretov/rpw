#ifdef ON

#include <iostream>
	#include <utility>
using namespace std;

void Rvalue_References() {
	int i = 42;
	int &r = i; // ok: r refers to i
	//TEST! int &&rr = i; //																																										error: cannot bind an rvalue reference to an lvalue
	//TEST! int &r2 = i * 42; // 																																									error: i * 42 is an rvalue
	//TEST! const int &r3 = i * 42; // 																																								ok: we can bind a reference to const to an rvalue
	//TEST! int &&rr2 = i * 42; // 																																									ok: bind rr2 to the result of the multiplication
}

void Variables_Are_Lvalues() {
	int &&rr1 = 42; //TEST! //																																										ok: literals are rvalues
	//TEST! int &&rr2 = rr1; // 																																									error: the expression rr1 is an lvalue!
#ifndef The_Library_move_Function
	cout << rr1 << '\n'; //MINE
	int &&rr3 = std::move(rr1); //TEST! //																																							ok

	//MINE
	int i = rr1;
	rr1 = 1;
	cout << i << '\n' << rr1 << '\n';
#endif
}

void mine() {
	int i{111};
	//TEST! int &&rri = static_cast<int &&>(i);
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//Variables_Are_Lvalues();
	mine();

	return 0;
}
#endif

#ifdef EX_13_46

#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	int f();
	vector<int> vi(100);
	//TEST! int &&r1 = f();
	int &r2 = vi[0];
	//TEST! int &r3 = r1; 
	//TEST! int &&r4 = vi[0] * f();

	return 0;
}
#endif

#ifdef EX_13_48

#include <vector>
#include "13_05.h"
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	vector<String> v;
	String s("aaa");
	
	for (int i = 1; i <= 14; ++i) {
		cout << "\npush_back " << i << '\n';
		v.push_back(s);
		cout << "v.size(): " << v.size() << '\t' << "v.capacity(): " << v.capacity() << '\n';
	}

	return 0;
}
#endif
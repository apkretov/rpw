#ifdef ON

#include <iostream>
#include <string>
using namespace std;

#ifdef Declaring_static_Members
class Account {
public:
	void calculate() { amount += amount * interestRate; }
	
	static double rate() { 
		return interestRate; 
	}
	
	static void rate(double);
private:
	std::string owner;
	//ORIG double amount;
	double amount{}; //MINE
	static double interestRate;
	static double initRate();
};

#ifndef Defining_static_Members
double Account::interestRate = initRate(); //TEST!! // define and initialize a static class member

void Account::rate(double newRate) {
	interestRate = newRate;
}

double Account::initRate() { //MINE
	return 0;
}
#endif

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

#ifndef Using_a_Class_static_Member
	double r;
	r = Account::rate(); // access a static member using the scope operator

	Account ac1;
	Account *ac2 = &ac1;
	// equivalent ways to call the static member rate function
	//TEST!! r = ac1.rate(); //																																							through an Account object or reference
	//TEST!! r = ac2->rate(); //																																							through a pointer to an	Account object
#endif

	return 0;
}

#elif In_Class_Initialization_of_static_Data_Members
class Account {
public:
	static double rate() { return interestRate; }
	static void rate(double);
private:
	static constexpr int period = 30; //TEST!! //																																			period is a constant expression
	double daily_tbl[period];
	static double interestRate; //MINE
};

double Account::interestRate{1}; //MINE

// Even if a const static data member is initialized in the class body, that member ordinarily should be defined outside the class definition.
// definition of a static member with no initializer
constexpr int Account::period; //TEST!! // initializer provided in the class definition

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//MINE
	Account v;
	cout << v.rate() << '\n';

	return 0;
}

#elif! static_Members_Can_Be_Used_in_Ways_Ordinary_Members_Cant
class Bar {
public:
	// ...
private:
	//TEST! static Bar mem1; //																																								ok: static member can have incomplete type
	//TEST! Bar *mem2; //																																									ok: pointer member can have incomplete type
	//TEST! Bar mem3; //																																									error: data members must have complete type
	//TEST! Bar &mem4; //MINE
};

class Screen {
public:
	Screen &clear(char = bkground); // bkground refers to the static member	// declared later in the class definition
private:
	static const char bkground;
};

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	return 0;
}
#endif
#endif

#ifdef EX_07_58

#include <iostream>
using namespace std;
#include "07_06_example.h"

constexpr double Example::rate;
vector<double> vec(Example::vecSize);

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//MINE
	cout << Example::rate << '\n';
	cout << vec.at(0) << '\n';

	return 0;
}
#endif
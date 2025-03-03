#ifdef ON

#include <iostream>
#include <type_traits> //MINE
#include <vector>
#include "../../stdafx.h"
#include "15_07_2.h"
#include "15_06.h"
#include "15_07_4.h"
using namespace std;

void Containers_and_Inheritance() {
	vector<Quote> basket;
	basket.push_back(Quote("0-201-82470-1", 50));
	basket.push_back(Bulk_quote("0-201-54848-8", 50, 10, .25)); //																																	ok, but copies only the Quote part of the object into basket
	cout << basket.back().net_price(15) << endl; //TEST! //																																			calls version defined by Quote, prints 750, i.e., 15 * $50

	Bulk_quote b("ccc", 300, 30, 3);
	basket.push_back(b);
	cout << basket.back().isbn() << '\t' << basket.back().net_price(1) << '\n';
}

void Put_Smart_Pointers_Not_Objects_in_Containers() {
	vector<shared_ptr<Quote>> basket;
	
	basket.push_back(make_shared<Quote>("0-201-82470-1", 50));
	cout << "basket.back()->net_price(15) = " << basket.back()->net_price(15) << '\n'; //MINE
	basket.push_back(make_shared<Bulk_quote>("0-201-54848-8", 50, 10, .25));
	
	cout << "basket.back()->net_price(15) = "; //MINE
	cout << basket.back()->net_price(15) << endl; //TEST!																																			//ERR: // calls the version defined by Quote; prints 562.5, i.e., 15 * $50 less the discount
}

template <typename T> 
void checkConstructorsAndAssignments() { //MINE
	static_assert(is_default_constructible_v<T>, "Default constructor is not available.");
	static_assert(is_copy_constructible_v<T>, "Copy constructor is not available.");
	static_assert(is_move_constructible_v<T>, "Move constructor is not available.");
	static_assert(is_copy_assignable_v<T>, "Copy assignment operator is not available.");
	static_assert(is_move_assignable_v<T>, "Move assignment operator is not available.");
}

void mine() {
	checkConstructorsAndAssignments<Quote>();
	checkConstructorsAndAssignments<Bulk_quote>();
}

int main(int argc, char *argv[]) {
	print_file_line();

	//Containers_and_Inheritance();
	Put_Smart_Pointers_Not_Objects_in_Containers();
	//mine(); // This can omitted because static_assert is executed at compile time.

	return 0;
}
#endif

#ifdef EX_15_28

#include "../../stdafx.h"
#include <vector>
#include "15_07_3.h"
using namespace std;

int main(int argc, char *argv[]) {
	print_file_line();

	vector<Quote> v;

	cout << "v.push_back(Bulk_quote(\"aaa\", 100, 10, 1)):\n";
	v.push_back(Bulk_quote("aaa", 100, 10, 1)); //TEST!

	cout << "return 0:\n";
	return 0;
}
#endif

#ifdef EX_15_29

#include "../../stdafx.h"
#include <vector>
#include "15_07_3.h"
using namespace std;

int main(int argc, char *argv[]) {
	print_file_line();

	vector<shared_ptr<Quote>> v;

	cout << "v.push_back(make_shared<Quote>(\"aaa\", 100)):\n";
	v.push_back(make_shared<Quote>("aaa", 100));
	
	cout << "\nv.push_back(make_shared<Bulk_quote>(\"bbb\", 100, 10, 1)):\n";
	v.push_back(make_shared<Bulk_quote>("bbb", 200, 20, 2)); //TEST!

	cout << '\n';
	v.back()->net_price(1);

	cout << "\n\nreturn 0:\n\n";
	return 0;
}
#endif

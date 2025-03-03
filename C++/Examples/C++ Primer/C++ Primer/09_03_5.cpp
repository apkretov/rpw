#ifdef ON

#include <iostream>
#include <list>
using namespace std;

void Resizing_a_Container() {
	list<int> ilist(10, 42); // ten ints: each has value 42
	
	ostream_iterator<int> out(cout, " "); //MINE
	copy(ilist.cbegin(), ilist.cend(), out); cout << '\n'; //MINE

	ilist.resize(15); //																																									adds five elements of value 0 to the back of ilist
	copy(ilist.cbegin(), ilist.cend(), out); cout << '\n'; //MINE

	ilist.resize(25, -1); //TEST! //																																						adds ten elements of value -1 to the back of ilist
	copy(ilist.cbegin(), ilist.cend(), out); cout << '\n'; //MINE

	ilist.resize(5); //TEST! //																																								erases 20 elements from the back of ilist
	copy(ilist.cbegin(), ilist.cend(), out); cout << '\n'; //MINE
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	Resizing_a_Container();

	return 0;
}
#endif

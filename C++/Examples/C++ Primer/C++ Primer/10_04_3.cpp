#ifdef ON

#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
using namespace std;

void Reverse_Iterators() {
	vector<int> vec = {0,1,2,3,4,5,6,7,8,9};
	// reverse iterator of vector from back to front
	for (auto r_iter = vec.crbegin(); //TEST! //																																					binds r_iter to the last element
		r_iter != vec.crend(); // crend refers 1 before 1st element
		++r_iter) // decrements the iterator one element
		cout << *r_iter << endl; // prints 9, 8, 7,... 0
	cout << '\n'; //MINE

	sort(vec.begin(), vec.end()); // sorts vec in ‘‘normal’’ order
	copy(vec.cbegin(), vec.cend(), ostream_iterator<int>(cout, " ")); cout << '\n'; //MINE

	//TEST! sort(vec.rbegin(), vec.rend()); //																																						sorts in reverse: puts the smallest element at the end of vec
	copy(vec.cbegin(), vec.cend(), ostream_iterator<int>(cout, " ")); cout << '\n'; //MINE
}

void Relationship_between_Reverse_Iterators_and_Other_Iterators() {
	//string line{"Aaa,Bbb,Ccc,Ddd"}; //MINE
	const string line{"FIRST,MIDDLE,LAST"};

	auto comma = find(line.cbegin(), line.cend(), ','); // find the first element in a comma-separated list
	cout << string(line.cbegin(), comma) << endl; //TEST! 

	auto rcomma = find(line.crbegin(), line.crend(), ','); //TEST! //																																find the last element in a comma-separated list
	cout << string(line.crbegin(), rcomma) << endl; //TEST! //																																		WRONG: will generate the word in reverse order
	cout << string(rcomma.base(), line.cend()) << endl; //TEST! //																																	ok: get a forward iterator and read to the end of line

	//MINE
	string rlast = string(line.crbegin(), rcomma);
	cout << string(rlast.crbegin(), rlast.crend()) << '\n'; //TEST! 
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//Reverse_Iterators();
	Relationship_between_Reverse_Iterators_and_Other_Iterators();

	return 0;
}

#endif

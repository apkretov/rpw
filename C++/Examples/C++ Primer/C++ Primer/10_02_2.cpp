#ifdef ON

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

void Algorithms_That_Write_Container_Elements() {
	vector<int> vec = {0, 1, 2, 3, 4, 5}; //MINE
	ostream_iterator<int> out(cout, " ");

	copy(vec.cbegin(), vec.cend(), out); cout << '\n'; //MINE

	fill(vec.begin(), vec.end(), 0); //TEST //																																						reset each element to 0
	copy(vec.cbegin(), vec.cend(), out); cout << '\n'; //MINE

	fill(vec.begin(), vec.begin() + vec.size() / 2, 10); //TEST //																																	set a subsequence of the container to 10
	copy(vec.cbegin(), vec.cend(), out); cout << '\n'; //MINE
}

void Algorithms_Do_Not_Check_Write_Operations() {
	vector<int> vec; // empty vector
	ostream_iterator<int> out(cout, " "); //MINE
	
	// use vec giving it various values
	//MINE
	for (size_t i = 0; i < 5; ++i)
		vec.push_back(i);
	copy(vec.cbegin(), vec.cend(), out); cout << '\n';

	fill_n(vec.begin(), vec.size(), 0); //TEST //																																					reset all the elements of vec to 0
	copy(vec.cbegin(), vec.cend(), out); cout << '\n'; //MINE

	fill_n(vec.begin(), 10, 0); //TEST!! //																																							disaster: attempts to write to ten (nonexistent) elements in vec
	copy(vec.cbegin(), vec.cend(), out); cout << '\n'; //MINE
}

void Introducing_back_inserter() {
	vector<int> vec; // empty vector
	auto it = back_inserter(vec); //TEST!! //																																						assigning through it adds elements to vec
	ostream_iterator<int> out(cout, " "); //MINE
	
	*it = 42; //TEST!! //																																											vec now has one element with value 42
	it = 21; //MINE
	copy(vec.cbegin(), vec.cend(), out); cout << '\n'; //MINE

	//																																																ok: back_inserter creates an insert iterator that adds elements to vec
	fill_n(back_inserter(vec), 10, 0); //TEST!! //																																					appends ten elements to vec
	copy(vec.cbegin(), vec.cend(), out); cout << '\n'; //MINE
}

void Copy_Algorithms() {
	int a1[] = {0,1,2,3,4,5,6,7,8,9};
	int a2[sizeof(a1) / sizeof(*a1)]; //TEST! //																																					a2 has the same size as a1
	list<int> ilst(4); //MINE
	vector<int> ivec; //MINE
	auto out = ostream_iterator<int>(cout, " "); //MINE
	//																																																ret points just past the last element copied into a2
	auto ret = copy(begin(a1), end(a1), a2); //TEST! //																																				copy a1 into a2	
	copy(begin(a2), ret, out); cout << '\n'; //TEST! //MINE

	replace(ilst.begin(), ilst.end(), 0, 42); //TEST //																																				replace any element with the value 0 with 42
	copy(ilst.cbegin(), ilst.cend(), out); cout << '\n'; //MINE
	
	replace_copy(ilst.cbegin(), ilst.cend(), back_inserter(ivec), 0, 42); //TEST! //																												use back_inserter to grow destination as needed
	copy(ivec.cbegin(), ivec.cend(), out); cout << '\n'; //MINE
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//Algorithms_That_Write_Container_Elements();
	//Algorithms_Do_Not_Check_Write_Operations();
	//Introducing_back_inserter();
	Copy_Algorithms();

	return 0;
}
#endif

#ifdef EX_10_07

#include <iostream>
#include <vector>
#include <list>
#include <deque>
using namespace std;

void a() {
	list<int> lst;
	vector<int> vec;
	deque<int> deq;
	int i;
	auto out = ostream_iterator<int>(cout, " ");

	while (cin >> i)
		lst.push_back(i); //TEST!

	copy(lst.cbegin(), lst.cend(), out);
	cout << '\n';

	vec.resize(lst.size()); //TEST!!
	//TEST!! vec.reserve(lst.size());
	copy(lst.cbegin(), lst.cend(), vec.begin()); //TEST!!
	copy(vec.cbegin(), vec.cend(), out);
	cout << '\n';

	copy(lst.cbegin(), lst.cend(), back_inserter(vec)); //TEST!
	copy(vec.cbegin(), vec.cend(), out);
	cout << '\n';

	copy(lst.cbegin(), lst.cend(), front_inserter(deq)); //TEST!!
	copy(deq.cbegin(), deq.cend(), out);
	cout << '\n';

	copy(lst.cbegin(), lst.cend(), back_inserter(deq)); //TEST!
	copy(deq.cbegin(), deq.cend(), out);
	cout << '\n';
}

void b() {
	vector<int> vec;
	ostream_iterator<int> out(cout, " ");

	//TEST! vec.reserve(10);
	vec.resize(10); //TEST!
	copy(vec.cbegin(), vec.cend(), out);
	cout << '\n';

	fill_n(vec.begin(), 10, 1);
	cout << "After fill_n\n";
	copy(vec.cbegin(), vec.cend(), out);
	cout << '\n';
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";
	
	//a();
	b();

	return 0;
}
#endif
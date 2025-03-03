#ifdef ON

#include <iostream>
#include <string>
#include <vector>
using namespace std;

void Iterator_Operations() {
	string text("some string");

	if (text.begin() != text.end()) { // make sure s is not empty
		auto it1 = text.begin(); //	it denotes the first character in s
		*it1 = toupper(*it1); // make that character uppercase
	}
}

void Moving_Iterators_from_One_Element_to_Another() {
	string text{"some string"};

	for (auto it1 = text.begin(); it1 != text.end() && !isspace(*it1); ++it1) // process characters in s until we run out of characters or we hit a whitespace
		*it1 = toupper(*it1); // capitalize the current character

	cout << text << '\n';
}

void The_begin_and_end_Operations() {
	vector<int> v;
	const vector<int> cv;

	auto it1 = v.begin(); // it1 has type vector<int>::iterator
	auto it2 = cv.begin(); // it2 has type vector<int>::const_iterator
}

void Combining_Dereference_and_Member_Access1() {
	//ORIG
	//vector<string> v; 
	//decltype(v.begin()) it;

	//MINE
	vector<string> v(10, "hi");
	decltype(v.begin()) it{v.begin()};

	for (auto it{v.begin()}; it != v.end(); ++it)
		cout << *it << ' ';
	cout << '\n';

	//OIRG (*it).empty(); //																																									dereferences it andcalls the member empty on the resulting object
	//TEST! cout << boolalpha << (*it).empty() << '\n'; 
	//TEST! *it.empty(); //																																										error: attempts to fetch the member named empty from it but it is an iterator andhas no member named empty
}

void Combining_Dereference_and_Member_Access2() {
	vector<string> text{"word1", "word2", "word3", "word4", "", "word1", "word2", "word3"};

	for (auto it1 = text.cbegin(); it1 != text.cend() && !it1->empty(); ++it1) // print each line in text up to the first blank line
		cout << *it1 << endl;
	cout << '\n';
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//Iterator_Operations();
	//Moving_Iterators_from_One_Element_to_Another();
	//The_begin_and_end_Operations();
	Combining_Dereference_and_Member_Access1();
	//Combining_Dereference_and_Member_Access2();

	return 0;
}
#endif

#ifdef EX_03_21

#include <iostream>
using std::cout;
#include <vector>
using std::vector;
#include <string>
using std::string;

template <typename T> void printVector(const vector<T> &v) {
	cout << "Size: " << v.size() << '\n';

	if (v.size() > 0) {
		cout << "Contents:";
		for (auto it1 = v.cbegin(); it1 != v.cend(); ++it1)
			cout << ' ' << *it1;
		cout << '\n';
	}
	cout << '\n';
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	vector<int> v1; // (a)
	printVector(v1);

	vector<int> v2(10); // (b)
	printVector(v2);

	vector<int> v3(10, 42); // (c)
	printVector(v3);

	vector<int> v4{10}; // (d)
	printVector(v4);

	vector<int> v5{10, 42}; // (e)
	printVector(v5);

	vector<string> v7{10, "hi"}; // (g)
	printVector(v7);

	return 0;
}
#endif

#ifdef EX_03_22

#include <iostream>
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include <string>
using std::string;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	vector<string> text{"word1", "word2", "word3", "word4", "", "word1", "word2", "word3"};

	//TEST for (auto it1 = text.begin();  it1 != text.end()  && !it1->empty(); ++it1) // print each line in text up to the first blank line
	//TEST for (auto it1 = text.cbegin(); it1 != text.cend() && !it1->empty(); ++it1) // print each line in text up to the first blank line
		for (auto it2 = it1->begin(); it2 != it1->end(); ++it2) 
			*it2 = toupper(*it2);

	for (auto it = text.cbegin(); it != text.cend() && !it->empty(); ++it) // print each line in text up to the first blank line
		cout << *it << endl;
	cout << '\n';

	return 0;
}
#endif

#undef EX_03_23
#ifdef EX_03_23

#include <iostream>
using std::cout;
#include <vector>
using std::vector;

void printVector(vector<int> &v) {
	for (auto it = v.cbegin(); it != v.cend(); ++it)
		cout << *it << ' ';
	cout << '\n';
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	vector<int> v(10, 16);

	printVector(v);
	for (auto it = v.begin(); it != v.end(); ++it)
		*it <<= 1;
	printVector(v);

	return 0;
}
#endif

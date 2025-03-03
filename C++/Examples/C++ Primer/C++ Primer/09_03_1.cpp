#ifdef ON

#include <iostream>
#include <list>
#include <forward_list>
#include <vector>
#include <deque>
#include <iterator>
#include <algorithm>
using namespace std;
#include "07_05_4.h"

void mine() {
	forward_list<int> fl = {0, 1, 2, 3, 4};
	
	copy(fl.cbegin(), fl.cend(), ostream_iterator<int>(cout, " "));
	cout << '\n';
	fl.push_front(-1);
	copy(fl.cbegin(), fl.cend(), ostream_iterator<int>(cout, " "));
	cout << '\n';
	fl.emplace_front(-2);
	copy(fl.cbegin(), fl.cend(), ostream_iterator<int>(cout, " "));
	cout << '\n';

	vector<int> v;
	v.emplace_back(1);
}

namespace Using_push_back {
	void f() {
		vector<string> container; //MINE
		string word; // read from standard input, putting each word onto the end of container

		while (cin >> word)
			container.push_back(word);
	}

	void pluralize(size_t cnt, string &word) {
		if (cnt > 1)
			word.push_back('s'); // same as word += ’s’
	}
}

void Using_push_front() {
	list<int> ilist;
#ifdef OFF
	for (size_t ix = 0; ix != 4; ++ix) // add elements to the start of ilist
		//TEST! ilist.push_front(ix);
#endif
}

namespace Adding_Elements_at_a_Specified_Point_in_the_Container {
	vector<string> svec;
	list<string> slist;
	
	void f() {
		slist.insert(slist.begin(), "Hello!"); // equivalent to calling slist.push_front("Hello!");
		//TEST! svec.insert(svec.begin(), "Hello!"); // no push_front on vector but we can insert before begin() // warning: inserting anywhere but at the end of a vector might be slow
	}
}

void Inserting_a_Range_of_Elements() {
	using namespace Adding_Elements_at_a_Specified_Point_in_the_Container;

	svec.insert(svec.end(), 10, "Anna");

	vector<string> v = {"quasi", "simba", "frollo", "scar"};
	//TEST! slist.insert(slist.begin(), v.end() - 2, v.end()); // insert the last two elements of v at the beginning of slist
	//TEST! slist.insert(slist.end(), {"these", "words", "will", "go", "at", "the", "end"});
	copy(slist.cbegin(), slist.cend(), ostream_iterator<string>(cout, " ")); cout << '\n'; //MINE
	//TEST! slist.insert(slist.begin(), slist.begin(), slist.end()); // run-time error: iterators denoting the range to copy from must not refer to the same container as the one we are changing
	copy(slist.cbegin(), slist.cend(), ostream_iterator<string>(cout, " ")); cout << '\n'; //MINE
}

void Using_the_Return_from_insert() {
	list<string> lst;
	auto iter = lst.begin();
	string word; //MINE
	
	while (cin >> word)
		//TEST! iter = lst.insert(iter, word); // same as calling push_front

	copy(lst.cbegin(), lst.cend(), ostream_iterator<string>(cout, " "));
	cout << '\n';
}

void Using_the_Emplace_Operations() {
	deque<Sales_data> c; //MINE

	//TEST! c.emplace_back("978-0590353403", 25, 15.99); //																																			construct a Sales_data object at the end of c uses the three-argument Sales_data constructor
	//TEST! c.push_back("978-0590353403", 25, 15.99); //																																			error: there is no version of push_back that takes three arguments
	//TEST! c.push_back(Sales_data("978-0590353403", 25, 15.99)); //																																ok: we create a temporary Sales_data object to pass to push_back

	//TEST! c.emplace_back(); // uses the Sales_data default constructor
	auto iter = c.end(); //MINE // iter refers to an element in c, which holds Sales_data elements
	//TEST! c.emplace(iter, "999-999999999"); // uses Sales_data(string)
	c.emplace_front("978-0590353403", 25, 15.99); // uses the Sales_data constructor that takes an ISBN, a count, and a price
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//mine();
	//Inserting_a_Range_of_Elements();
	Using_the_Return_from_insert();

	return 0;
}
#endif

#ifdef EX_09_19_1

#include <iostream>
#include <list>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	string s;
	list<string> l;
	auto b1 = l.begin();
	
	while (cin >> s)
		b1 = l.insert(b1, s);

	auto b2 = l.cbegin();
	while (b2 != l.cend())
		cout << *b2++ << '\t';
	cout << '\n';

	return 0;
}
#endif

#ifdef EX_09_19_2 // ch09/ex9_19.cpp @ https://github.com/Mooophy/Cpp-Primer/blob/master/ch09/ex9_19.cpp

#include <iostream>
#include <string>
#include <list>
using std::string; using std::list; using std::cout; using std::cin; using std::endl;

int main() {
	list<string> input;

	for (string str; cin >> str; input.push_back(str));

	for (auto iter = input.cbegin(); iter != input.cend(); ++iter)
		cout << *iter << endl;

	return 0;
}
#endif

#ifdef EX_09_20

#include <iostream>
#include <list>
#include <deque>
#include <iterator>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	const list<int> l = {0, 1, 2, -3, 4, 5, 6};
	deque<int> even, odd;

	copy(l.begin(), l.end(), ostream_iterator<int>(cout, " "));
	cout << '\n';
	
	for (auto it = l.begin(); it != l.end(); ++it)
		if (*it % 2)
			odd.push_back(*it);
		else 
			even.push_back(*it);

	copy(even.cbegin(), even.cend(), ostream_iterator<int>(cout, " "));
	cout << '\n';
	copy(odd.cbegin(), odd.cend(), ostream_iterator<int>(cout, " "));
	cout << '\n';

	return 0;
}
#endif

#ifdef EX_09_22

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

using vi = vector<int>;
using vii = vi::iterator;

vii insert_vec(vi &iv, vii &iter, vii &mid, int some_val) {
	while (iter != mid) {
		if (*iter == some_val)
			return iv.insert(iter, some_val * 2);
		++iter;
	}
	return iter;
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	vi iv = {10, 10, 2, -3, 10, 5, 6};
	vii iter = {iv.begin()}, mid = {iv.begin() + iv.size() / 2};
	int some_val{10};

	copy(iv.cbegin(), iv.cend(), ostream_iterator<int>(cout, " "));
	cout << '\n';

	while (iter < mid) {
		iter = insert_vec(iv, iter, mid, some_val);
		iter += 2;
		mid = iv.begin() + (iv.size() + 1) / 2;
	}

	copy(iv.cbegin(), iv.cend(), ostream_iterator<int>(cout, " "));
	cout << '\n';

	return 0;
}
#endif

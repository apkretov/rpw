#ifdef ON

#include <iostream>
#include <list>
using namespace std;

void Insert_Iterators() {
	list<int> lst = {1,2,3,4};
	list<int> lst2, lst3; // empty lists
	auto lst4(lst2); //MINE
	ostream_iterator<int> out (cout, " "); //MINE
	
	copy(lst.begin(), lst.end(), out); cout << '\n'; //MINE

	copy(lst.cbegin(), lst.cend(), front_inserter(lst2)); //TEST!  //																														after copy completes, lst2 contains 4 3 2 1
	copy(lst2.cbegin(), lst2.cend(), out); cout << '\n'; //MINE
	
	copy(lst.cbegin(), lst.cend(), inserter(lst3, lst3.begin())); //TEST! //																												after copy completes, lst3 contains 1 2 3 4
	copy(lst3.cbegin(), lst3.cend(), out); cout << '\n'; //MINE

	//MINE
	copy(lst.cbegin(), lst.cend(), back_inserter(lst4));
	copy(lst4.cbegin(), lst4.cend(), out); cout << '\n';
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	Insert_Iterators();

	return 0;
}
#endif

#ifdef EX_10_27

#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <memory>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	initializer_list<int> il{1, 2, 0, 2, 1, 0};
	vector<int> v1(il), v2(il);

	list<iterator_traits<decltype(v1)::iterator>::value_type> l;
	ostream_iterator<int> out(cout, " ");

	cout << "Vector d1\n";
	copy(v1.cbegin(), v1.cend(), out);
	cout << '\n';

	sort(v1.begin(), v1.end());
	cout << "\nVector d1 sorted\n";
	copy(v1.cbegin(), v1.cend(), out);
	cout << '\n';

	auto it = unique(v1.begin(), v1.end());
	v1.erase(it, v1.end());
	cout << "\nVector d1 made unique\n";
	copy(v1.cbegin(), v1.cend(), out);
	cout << '\n';

	sort(v2.begin(), v2.end());
	unique_copy(v2.cbegin(), v2.cend(), back_inserter(l));
	cout << "\nList l\n";
	copy(l.cbegin(), l.cend(), out);
	cout << '\n';

	return 0;
}
#endif

#ifdef EX_10_28

#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";
	
	ifstream in(argv[1]);
	string s;
	vector<int> v;
	int i{};

	while (in >> s) {
		try {
			i = stoi(s);
			v.push_back(i);
		}
		catch (const exception &e) {
			cerr << "Exceptin on i = stoi(s) with s = " << s << ": " << e.what() << '\n';
		}
	}	
	sort(v.begin(), v.end());
	
	deque<int> d1, d2, d3, d4;
	auto it1 = inserter(d1, d1.begin());
	auto it2 = inserter(d2, d2.end());
	auto it3 = back_inserter(d3);
	auto it4 = front_inserter(d4);

	copy(v.cbegin(), v.cend(), it1);
	copy(v.cbegin(), v.cend(), it2);
	copy(v.cbegin(), v.cend(), it3);
	copy(v.cbegin(), v.cend(), it4);

	ostream_iterator<int> out(cout, " ");
	cout << '\n'; 
	copy(d1.cbegin(), d1.cend(), out); 

	cout << '\n';
	copy(d2.cbegin(), d2.cend(), out);

	cout << '\n';
	copy(d3.cbegin(), d3.cend(), out);

	cout << '\n';
	copy(d4.cbegin(), d4.cend(), out);
	cout << '\n';

	return 0;
}
#endif
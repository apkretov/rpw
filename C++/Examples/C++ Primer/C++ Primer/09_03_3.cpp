#ifdef ON

#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
using namespace std;

void process(int) { //MINE
	return;
}

void The_pop_front_and_pop_back_Members() {
	list<int> ilist(10);
	
	while (!ilist.empty()) {
		process(ilist.front()); // do something with the current top of ilist
		//TEST! ilist.pop_front(); //																																									done; remove the first element
	}
}

void Removing_an_Element_from_within_the_Container() {
	list<int> lst = {0,1,2,3,4,5,6,7,8,9};
	
	copy(lst.cbegin(), lst.cend(), ostream_iterator<int>(cout, " "));
	cout << '\n';

#ifdef OFF
	auto itl = lst.begin();
	while (itl != lst.end())
		if (*itl % 2) // if the element is odd
			//TEST! it = lst.erase(it); //																																								erase this element
		else
			++itl;
#endif

	copy(lst.cbegin(), lst.cend(), ostream_iterator<int>(cout, " "));
	cout << '\n';
}

void mine() {
	list<int> slist = {0, 1, 2, 3, 4, 5, 6};
	auto elem1 = slist.begin();
	//TEST! auto it2 = next(it1);

	copy(slist.cbegin(), slist.cend(), ostream_iterator<int>(cout, " "));
	cout << '\n';
#ifdef OFF
	auto elem3 = slist.erase(elem1, elem2);
	copy(slist.cbegin(), slist.cend(), ostream_iterator<int>(cout, " "));
	cout << '\n' << *elem3 << '\n';
#endif
}

void Removing_Multiple_Elements() {
	//MINE
	list<string> slist = {"one", "two", "three", "four"};
	auto elem1 = slist.begin();
	//TEST! auto elem2 = next(elem1, 2);
	copy(slist.cbegin(), slist.cend(), ostream_iterator<string>(cout, " ")); cout << '\n';

#ifdef OFF
	// delete the range of elements between two iterators // returns an iterator to the element just after the last removed element
	//TEST! elem1 = sList.erase(elem1, elem2); //																																						after the call elem1 == elem2

	//MINE
	copy(slist.cbegin(), slist.cend(), ostream_iterator<string>(cout, " "));
	cout << '\n' << *elem1 << '\n' << *elem2 << '\n';
#endif

	slist.clear(); //																																													delete all the elements within the container
	//TEST! slist.erase(slist.begin(), slist.end()); //																																					equivalent
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//The_pop_front_and_pop_back_Members();
	//Removing_an_Element_from_within_the_Container();
	//mine();
	Removing_Multiple_Elements();

	return 0;
}
#endif

#ifdef EX_09_25

#include <iostream>
#include <array>
#include <list>
#include <iterator>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	const array<string, 6> sarray = {"one", "two", "three", "four", "five", "six"};
	list<string> slist(sarray.begin(), sarray.end());
	auto elem1 = slist.begin(), elem2{elem1};

	copy(slist.cbegin(), slist.cend(), ostream_iterator<string>(cout, " ")); cout << '\n';
	auto elem3 = slist.erase(elem1, elem2);
	copy(slist.cbegin(), slist.cend(), ostream_iterator<string>(cout, " ")); cout << '\n';
	const auto print_item3 = [&slist, &elem3]() { cout << (elem3 != slist.end() ? *elem3 : "") << '\n'; };
	print_item3();

	elem2 = slist.end();
	elem3 = slist.erase(elem1, elem2);
	copy(slist.cbegin(), slist.cend(), ostream_iterator<string>(cout, " ")); cout << '\n';
	print_item3();

	slist.insert(slist.begin(), sarray.begin(), sarray.end());
	elem1 = elem2 = slist.end();
	elem3 = slist.erase(elem1, elem2);
	copy(slist.cbegin(), slist.cend(), ostream_iterator<string>(cout, " ")); cout << '\n';
	print_item3();

	return 0;
}
#endif

#ifdef EX_09_26

#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
using namespace std;

template <typename T>
void print_c(const T &c) {
	//TEST! copy(c.cbegin(), c.cend(), ostream_iterator<typename T::value_type>(cout, " "));
	cout << '\n';
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	int ia[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89};
	vector<int> v(begin(ia), end(ia));
	list<int> l(begin(ia), end(ia));

#ifdef OFF
	print_c(v);
	print_c(l);
#endif

	auto print_c_lmd = [](const auto &c) {
#ifdef OFF
#ifndef GPT_1
		//TEST! using value_type = typename remove_reference<decltype(c)>::type::value_type;
#elif !GPT_2
		//TEST! using value_type = std::decay_t<decltype(*c.begin())>;
#endif
		std::copy(c.begin(), c.end(), std::ostream_iterator<value_type>(std::cout, " "));
#endif
		std::cout << '\n';
	};
	print_c_lmd(v);
	print_c_lmd(l);

	auto itl = l.begin();
	while (itl != l.end())
		if (!(*itl % 2))
			itl = l.erase(itl);
		else
			++itl;
	print_c_lmd(l);

	auto itv = v.begin();
	while (itv != v.end())
		if (*itv % 2)
			itv = v.erase(itv);
		else
			++itv;
	print_c_lmd(v);

	return 0;
}
#endif

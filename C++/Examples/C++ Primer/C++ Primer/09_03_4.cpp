#include <iostream>
#include <forward_list>
#include <iterator>
#include <algorithm>
using namespace std;

#ifdef ON

void Specialized_forward_list_Operations() {
	forward_list<int> flst = {0,1,2,3,4,5,6,7,8,9};
	//TEST! auto prev = flst.before_begin(); //																																						denotes element "off the start" of flst
	auto curr = flst.begin(); // denotes the first element in flst
	
	copy(flst.cbegin(), flst.cend(), ostream_iterator<int>(cout, " "));	cout << '\n'; //MINE
#ifdef OFF
	while (curr != flst.end()) { // while there are still elements to process
		if (*curr % 2) // if the element is odd
			//TEST! curr = flst.erase_after(prev); //																																				erase it and move curr
		else {
			prev = curr; // move the iterators to denote the next
			++curr; // element and one before the next element
		}
	}
#endif
	copy(flst.cbegin(), flst.cend(), ostream_iterator<int>(cout, " "));	cout << '\n'; //MINE
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	Specialized_forward_list_Operations();

	return 0;
}
#endif

#ifdef EX_09_28

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	std::cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	const string s1{"five"}, s2{"FOUR"};
	forward_list<string> fl = {"zero", "one", "two", "three"};
	auto it = fl.begin(), prev{it};

	std::copy(fl.cbegin(), fl.cend(), ostream_iterator<string>(std::cout, " "));
	std::cout << '\n';

	while (it != fl.end()) {
		if (*it == s1) {
			fl.insert_after(it, s2);
			break;
		}
		prev = it;
		++it;
	}

	if (it == fl.end())
		fl.insert_after(prev, s2);

	std::copy(fl.cbegin(), fl.cend(), ostream_iterator<string>(std::cout, " "));
	std::cout << '\n';

	return 0;
}
#endif

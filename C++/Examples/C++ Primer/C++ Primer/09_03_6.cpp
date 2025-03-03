#ifdef ON

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

void Writing_Loops_That_Change_a_Container() {
	vector<int> vi = {0,1,2,3,4,5,6,7,8,9};
	auto iter = vi.begin(); // call begin, not cbegin because we’re changing vi
	
	copy(vi.cbegin(), vi.cend(), ostream_iterator<int>(cout, " ")); cout << '\n'; //MINE
	while (iter != vi.end()) { // silly loop to remove even-valued elements and insert a duplicate of odd-valued elements
		if (*iter % 2) {
			iter = vi.insert(iter, *iter); // duplicate the current element
			iter += 2; //TEST! //																																											advance past this element and the one inserted before it
		} else
			iter = vi.erase(iter); // remove even elements // don’t advance the iterator; iter denotes the element after the one we erased
	}
	copy(vi.cbegin(), vi.cend(), ostream_iterator<int>(cout, " ")); cout << '\n'; //MINE
}

void Avoid_Storing_the_Iterator_Returned_from_end() {
	constexpr int n{10};
	vector<int> v = {0,1,2,3,4,5,6,7,8,9};

#ifdef OFF
	auto begin = v.begin(), //																																											disaster: the behavior of this loop is undefined
		//TEST! end = v.end(); //																																										bad idea, saving the value of the end iterator
	while (begin != end) {
		// do some processing // insert the new value and reassign begin, which otherwise would be invalid
		++begin; // advance begin because we want to insert after this element
		begin = v.insert(begin, 42); // insert the new value
		++begin; // advance begin past the element we just added
	}
#endif

	copy(v.cbegin(), v.cend(), ostream_iterator<int>(cout, " ")); cout << '\n'; //MINE
	auto begin = v.begin(); //																																											safer: recalculate end on each trip whenever the loop adds/erases elements
	while (begin != v.end()) {
		// do some processing
		++begin; // advance begin because we want to insert after this element
		begin = v.insert(begin, 42); // insert the new value
		++begin; // advance begin past the element we just added
	}
	copy(v.cbegin(), v.cend(), ostream_iterator<int>(cout, " ")); cout << '\n'; //MINE
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	Writing_Loops_That_Change_a_Container();
	//Avoid_Storing_the_Iterator_Returned_from_end();

	return 0;
}
#endif

#ifdef EX_09_31

#include <iostream>
#include <list>
#include <forward_list>
#include <iterator>
#include <algorithm>
using namespace std;

void process_list() {
	list<int> l = {0,1,2,3,4,5,6,7,8,9};
	auto iter = l.begin();

	copy(l.cbegin(), l.cend(), ostream_iterator<int>(cout, " ")); 
	cout << '\n';
	
	while (iter != l.end()) {
		if (*iter % 2) {
			iter = l.insert(iter, *iter);
			iter = next(iter, 2);
		} else
			iter = l.erase(iter);
	}
	
	copy(l.cbegin(), l.cend(), ostream_iterator<int>(cout, " ")); 
	cout << '\n';
}

void process_forward_list() {
	forward_list<int> vi = {0,1,2,3,4,5,6,7,8,9};
	auto iter = vi.begin(), prev = vi.before_begin();

	copy(vi.cbegin(), vi.cend(), ostream_iterator<int>(cout, " "));
	cout << '\n';

	while (iter != vi.end()) {
		if (*iter % 2) {
			iter = vi.insert_after(prev, *iter);
			iter = next(iter, 2);
			prev = next(prev, 2);
		} else
			iter = vi.erase_after(prev);
	}

	copy(vi.cbegin(), vi.cend(), ostream_iterator<int>(cout, " "));
	cout << '\n';
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	process_list();
	cout << '\n';
	process_forward_list();

	return 0;
}
#endif

#ifdef EX_09_32

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	vector<int> vi = {0,1,2,3,4,5,6,7,8,9};
	auto iter = vi.begin();

	copy(vi.cbegin(), vi.cend(), ostream_iterator<int>(cout, " ")); cout << '\n';
	while (iter != vi.end()) { 
		if (*iter % 2) {
			//TEST! iter = vi.insert(iter, *iter++); 
			++iter;
		} else
			iter = vi.erase(iter);
	}
	copy(vi.cbegin(), vi.cend(), ostream_iterator<int>(cout, " ")); cout << '\n'; 

	return 0;
}
#endif

#ifdef EX_09_33

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	constexpr int n{10};
	vector<int> v = {0,1,2,3,4,5,6,7,8,9,10};

	copy(v.cbegin(), v.cend(), ostream_iterator<int>(cout, " ")); 
	cout << '\n';

	auto begin = v.begin();
	while (begin != v.end()) {
		++begin; 
		//TEST! /*begin =*/ v.insert(begin, 42);
		++begin;
	}
	
	copy(v.cbegin(), v.cend(), ostream_iterator<int>(cout, " ")); 
	cout << '\n';

	return 0;
}
#endif

#ifdef EX_09_34

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	vector<int> vi = {0,1,2,3,4,5,6,7,8,9,10};

	copy(vi.cbegin(), vi.cend(), ostream_iterator<int>(cout, " "));
	cout << '\n';

	auto iter = vi.begin();
	while (iter != vi.end()) {
		if (*iter % 2)
			iter = vi.insert(iter, *iter);
		copy(vi.cbegin(), vi.cend(), ostream_iterator<int>(cout, " "));
		cout << "\n\n";
	}
	++iter;
	
	copy(vi.cbegin(), vi.cend(), ostream_iterator<int>(cout, " "));
	cout << '\n';

	return 0;
}
#endif
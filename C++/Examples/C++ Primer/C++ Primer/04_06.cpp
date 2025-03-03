#ifdef ON

#include <iostream>
#include <string>
using namespace std;

void The_Member_Access_Operators() {
	string s1 = "v string", *p = &s1;
	auto n = s1.size(); // run the size member of the string s1
	
	n = (*p).size(); // run size on the object to which p points
	n = p->size(); // equivalent to (*p).size()

	// run the size member of p, then dereference the result!
	//TEST *p.size(); //																																										error: p is a pointer and has no member named size
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	The_Member_Access_Operators();

	return 0;
}
#endif

#ifdef EX_04_20

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	vector<string> vec{"", "two", "three"};
	auto iter{vec.begin()};

	//TEST! cout << *iter++ << '\n'; // (a)
	//TEST (*iter)++; // (b)
	//TEST! *iter.empty(); // (c)
	//TEST iter->empty(); // (d)
	//TEST ++*iter; // (e)
	//TEST! iter++->empty(); // (f)

	return 0;
}
#endif

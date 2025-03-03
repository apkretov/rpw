#undef EX_04_31
#ifdef EX_04_31

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	vector<int> ivec(5);
	vector<int>::size_type cnt = ivec.size();
	ostream_iterator<int> out(cout, "\t");

	copy(ivec.cbegin(), ivec.cend(), out);
	cout << '\n';

	for (vector<int>::size_type scr_ix = 0; scr_ix != ivec.size(); ++scr_ix, --cnt) // assign values from size ... 1 to the elements in ivec
		ivec[scr_ix] = cnt;
	copy(ivec.cbegin(), ivec.cend(), out);
	cout << '\n';

	fill(ivec.begin(), ivec.end(), 0);
	copy(ivec.cbegin(), ivec.cend(), out);
	cout << '\n';

	for (decltype(cnt) scr_ix = 0, cnt = ivec.size(); scr_ix != ivec.size(); scr_ix++, cnt--)
		ivec[scr_ix] = cnt;
	copy(ivec.cbegin(), ivec.cend(), out);
	cout << '\n';

	return 0;
}
#endif

#undef EX_04_32
#ifdef EX_04_32

#include<iostream>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	constexpr int size = 5;
	int ia[size] = {1,2,3,4,5};

	for (int *ptr = ia, scr_ix = 0;	scr_ix != size && ptr != ia + size;	++scr_ix, ++ptr) 
		cout << ia[scr_ix] << ' ';
	cout << '\n';

	return 0;
}
#endif
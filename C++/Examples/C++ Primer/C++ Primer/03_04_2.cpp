#undef ON
#ifdef ON

#include <iostream>
#include <vector>
#include <string>
using namespace std;

static const vector<string> text{"aaa", "bbb", "ccc", "ddd"};
static auto &sought{text.at(2)};

void Using_Iterator_Arithmetic() {
	// text must be sorted
	// beg and end will denote the range we’re searching
	auto beg = text.begin(), end = text.end();
	auto mid = text.begin() + (end - beg) / 2; // original midpoint
	// while there are still elements to look at and we haven’t yet found sought
	while (mid != end && *mid != sought) {
		if (sought < *mid) // is the element we want in the first half?
			end = mid; // if so, adjust the range to ignore the second half
		else // the element we want is in the second half
			beg = mid + 1; // start looking with the element just after mid
		mid = beg + (end - beg) / 2; // new midpoint
	}
	cout << *mid << '\n';
}

void mine() {
	auto beg = text.cbegin(), end = text.cend();
	decltype(beg) mid;

	while (beg != end && *(mid = beg + (end - beg) / 2) != sought)
		if (*mid > sought)
			end = mid;
		else
			beg = mid + 1;
	cout << *mid << '\n';
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	mine();
	Using_Iterator_Arithmetic();

	return 0;
}
#endif

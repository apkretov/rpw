#undef ON
#ifdef ON

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	// count the number of grades by clusters of ten: 0--9, 10--19, . . . 90--99, 100
	unsigned scores[11] = {}; // 11 buckets, all value initialized to 0
	unsigned grade;
	
	while (cin >> grade) {
		if (grade <= 100)
			++scores[grade / 10]; // increment the counter for the current cluster
	}

	for (auto i : scores) // for each counter in scores
		cout << i << " "; // print the value of that counter
	cout << endl;

	return 0;
}
#endif

#undef EX_03_32
#ifdef EX_03_32

#include <iostream>
#include <vector>
using namespace std;

static const size_t len{10};

template <typename T> void copyArr(T &src, T &dest) {
	for (unsigned n = 0; n < len; ++n)
		src[n] = n;

	for (auto n : src)
		cout << n << ' ';
	cout << '\n';

	for (size_t i = 0; i < len; ++i)
		dest[i] = src[i];

	for (auto n : dest)
		cout << n << ' ';
	cout << '\n';

}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	unsigned arr[len], arrCopy[len];
	vector<unsigned> vec(len), vecCopy(len);

	copyArr(arr, arrCopy);
	cout << '\n';
	copyArr(vec, vecCopy);
	cout << '\n';

	return 0;
}
#endif
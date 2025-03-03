#undef ON
#ifdef ON

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void Computing_a_vector_Index() {
	const vector<unsigned> grades{42, 65, 95, 100, 39, 67, 95, 76, 88, 76, 83, 92, 76, 93};
	auto it = grades.cbegin();
	ostream_iterator<unsigned> out(cout, " ");

	copy(grades.cbegin(), grades.cend(), out);
	cout << '\n';

	// count the number of grades by clusters of ten: 0--9, 10--19, . .. 90--99, 100
	vector<unsigned> scores(11, 0); // 11 buckets, all initially 0
	unsigned grade;
	//ORIG while (cin >> grade) { // read the grades
	for (grade = *it; it != grades.cend(); grade = *it++) { //MINE
		if (grade <= 100) // handle only valid grades
			++scores[grade / 10]; // increment the counter for the current cluster
	}

	copy(scores.cbegin(), scores.cend(), out);
	cout << '\n';
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	Computing_a_vector_Index();

	return 0;
}
#endif

#undef EX_03_16
#ifdef EX_03_16

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
		for (auto item : v)
			cout << ' ' << item;
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

#undef EX_03_17
#ifdef EX_03_17

#include <iostream>
using std::cout;
using std::cin;
#include <vector>
using std::vector;
#include <string>
using std::string;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	string text;
	vector<string> v;

	while (cin >> text)
		v.push_back(text);
	
	for (string &text : v)
		for (char &c : text)
			c = toupper(c);

	for (size_t i = 0; i < v.size(); i++) {
		if (i % 8 == 0)
			cout << '\n';
		cout << v.at(i) << ' ';
	}
	
	cout << '\n';

	return 0;
}
#endif

#undef EX_03_18
#ifdef EX_03_18

#include <iostream>
using std::cout;
#include <vector>
using std::vector;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	vector<int> ivec;
	//ERR ivec[0] = 42;
	ivec.push_back(42);

	cout << ivec[0] << '\n';

	return 0;
}
#endif

#undef EX_03_19
#ifdef EX_03_19

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	ostream_iterator<int> out(cout, " ");
	vector<int> v1{42, 42, 42, 42, 42, 42, 42, 42, 42, 42};
	vector<int> v2(10, 42);
	vector<int> v3;

	for (size_t i = 0; i < 10; i++)
		v3.push_back(42);
	
	copy(v1.cbegin(), v1.cend(), out);
	cout << "\n\n";
	copy(v2.cbegin(), v2.cend(), out);
	cout << "\n\n";
	copy(v3.cbegin(), v3.cend(), out);
	cout << "\n\n";

	return 0;
}
#endif
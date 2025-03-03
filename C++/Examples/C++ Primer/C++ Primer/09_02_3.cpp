#ifdef EX_09_10

#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	vector<int> v1;
	const vector<int> v2;
	//TEST! auto it1 = v1.begin(), it2 = v2.begin();
	auto it3 = v1.cbegin(), it4 = v2.cbegin();

	return 0;
}
#endif

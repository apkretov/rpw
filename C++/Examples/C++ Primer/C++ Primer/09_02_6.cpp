#ifdef ON

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	vector<int> vi;
	vector<double> vd;
	vector<string> vs;
	
	cout << vi.max_size() << '\n';
	cout << vd.max_size() << '\n';
	cout << vs.max_size() << '\n';

	return 0;
}
#endif
#ifdef ON

#include <iostream>
#include <vector>
using namespace std;

void The_pair_Type() {
	pair<string, string> anon; // holds two strings
	pair<string, size_t> word_count; // holds a string and an size_t
	pair<string, vector<int>> line; // holds string and vector<int>

	pair<string, string> author{"James", "Joyce"};
}

#ifdef A_Function_to_Create_pair_Objects
pair<string, int> process(vector<string> &v) {
	if (!v.empty()) // process v
#ifdef _1
		//TEST! return {v.back(), v.back().size()}; //																																			list initialize
#elif _2
		//TEST! return pair<string, int>{v.back(), v.size()};
#elif! _3
		//TEST! return make_pair(v.back(), v.size());
#endif
	else
		//TEST! return pair<string, int>(); //																																					explicitly constructed return value
}
#endif

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	return 0;
}
#endif

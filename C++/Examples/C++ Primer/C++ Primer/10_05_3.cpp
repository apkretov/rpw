#ifdef ON

#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
using namespace std;

void Distinguishing_Versions_That_Copy_from_Those_That_Do_Not() {
	vector<int> v1, v2; //MINE

	remove_if(v1.begin(), v1.end(),	[](int i) { return i % 2; }); //																																removes the odd elements from v1
	//TEST! remove_copy_if(v1.begin(), v1.end(), back_inserter(v2),	[](int i) { return i % 2; }); //																								copies only the even elements from v1 into v2; v1 is unchanged
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";
	
	Distinguishing_Versions_That_Copy_from_Those_That_Do_Not();

	return 0;
}

#endif

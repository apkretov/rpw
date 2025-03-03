#ifdef ON

#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

void Read_Only_Algorithms() {
	const vector<int> vec = {0, 1, 2, 3, 4, 5}; //MINE
	//TEST! int sum = accumulate(vec.cbegin(), vec.cend(), 0); //																																	sum the elements in vec starting the summation with the value 0
}

void Algorithms_and_Element_Types() {
	const vector<string> v = {"aaa", "bbb", "ccc"}; //MINE
	
	//TEST!! string sum = accumulate(v.cbegin(), v.cend(), string(""));
	//TEST!! fstring sum = accumulate(v.cbegin(), v.cend(), ""); //																																	error: no + on const char*
}

void Algorithms_That_Operate_on_Two_Sequences() {
	//TEST! equal(roster1.cbegin(), roster1.cend(), roster2.cbegin()); // roster2 should have at least as many elements as roster1
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//Read_Only_Algorithms();
	Algorithms_and_Element_Types();

	return 0;
}
#endif
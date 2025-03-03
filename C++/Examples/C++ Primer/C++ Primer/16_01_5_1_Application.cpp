#include <iostream>
#include <string>
#include "16_01_4_1.h"
#include "16_01_1.h"
using namespace std;

#pragma region Controlling Instantiations
extern template class Blob<string>; //TEST! //																													these template types must be instantiated elsewhere in the program
extern template int compare(const int &, const int &); //TEST!

void Controlling_Instantiations_() {
	Blob<string> sa1, sa2; // instantiation will appear elsewhere

	//MINE
	sa1.push_back("aaa");
	sa1.push_back("bbb");
	//OFF cout << "sa1: " << sa1 << '\n';

	Blob<int> a1{0,1,2,3,4,5,6,7,8,9}; //ORIG Blob<int> a1 = {0,1,2,3,4,5,6,7,8,9}; // Blob<int> and its initializer_list constructor instantiated in this file
	Blob<int> a2(a1); // copy constructor instantiated in this file
	//OFF cout << "a2 : " << a2 << '\n'; //MINE

	int i = compare(a1[0], a2[0]); // instantiation will appear elsewhere
	cout << "compare("<< a1[0] << ", " << a2[0] << ") = " << i << '\n'; //MINE
}
#pragma endregion

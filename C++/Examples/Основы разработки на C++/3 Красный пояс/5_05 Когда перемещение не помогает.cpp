#if 0

#include <array>
#include <iostream>
#include <vector>
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

const int SIZE = 10'000;

array<int, SIZE> MakeArray() {
	array<int, SIZE> a;
	a.fill(8);
	return a;
}

void MoveStackVars() {
	{
		LOG_DURATION("with variable");
		vector<array<int, SIZE>> arrays;
		for (int i = 0; i < 10'000; ++i) {
			auto heavy_array = MakeArray();
			arrays.push_back(heavy_array);

		}
	}
	{
		LOG_DURATION("without variable");
		vector<array<int, SIZE>> arrays;
		for (int i = 0; i < 10'000; ++i) {
			arrays.push_back(MakeArray()); //TEST! //																										No move semantics for const variables.																										No move semantics for the stack, only for the heap.
		}
	}
}

string MakeString() {
	return "C++";
}

void MoveConstVars() {
	vector<string> strings;
	const string s = MakeString();
	cout << s << '\n';
	strings.push_back(move(s)); //TEST!	
	cout << s << '\n';
}

int main() {
	PRINT_FILE_LINE();

	//MoveStackVars();
	MoveConstVars();

	return 0;
}
#endif //1
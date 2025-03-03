#if 0

#include <iostream>
#include <vector>
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

string MakeString() {
	return string(100'000'000, 'a');
}

int main() {
	PRINT_FILE_LINE();

	{
		LOG_DURATION("with variable");
		vector<string> strings;
		string heavy_string = MakeString();
		strings.push_back(heavy_string);
	}
	{
		LOG_DURATION("without variable");
		vector<string> strings;
		strings.push_back(MakeString());
	}
	{
		LOG_DURATION("ctor: with variable");
		vector<string> strings;
		string heavy_string = string(100'000'000, 'a');
		strings.push_back(heavy_string);
	}
	{
		LOG_DURATION("ctor: without variable");
		vector<string> strings;
		strings.push_back(string(100'000'000, 'a'));
	}

	return 0;
}
#endif //1
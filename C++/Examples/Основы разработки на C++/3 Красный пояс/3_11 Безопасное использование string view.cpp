#if 0

#include <iostream>
#include "3_09 Класс string view.h"
using namespace std;

#define VER_3
#ifdef VER_1
vector<string_view> SplitIntoWordsView(const string &s) {
	string_view str = s;
#elif defined(VER_2) //ERR
vector<string_view> SplitIntoWordsView(const string &str) {
#elif defined(VER_3) // Universal for string and string_view parameters.
vector<string_view> SplitIntoWordsView(string_view str) {
#endif 
	vector<string_view> result;
	size_t pos = 0;
	const size_t pos_end = str.npos;

	while (true) {
		size_t space = str.find(' ', pos);
		result.push_back(space == pos_end ? str.substr(pos) : str.substr(pos, space - pos)); //TEST! //														Unlike string_view::substr(), string::substr() creates a new temporary string. It is deleted on returning from the function. But the string_view (a dangling pointer) still points to a deleted string...

		if (space == pos_end)
			break;
		else
			pos = space + 1;
	}

	return result;
}

int main(int argc, char *argv[]) {
	PRINT_FILE_LINE();

	string text = GenerateText();
	{
		LOG_DURATION("string");
		const auto words = SplitIntoWords(text);
		cout << words[0] << '\n';
	}
	{
		LOG_DURATION("string_view");
		const auto words = SplitIntoWordsView(text);
		cout << words[0] << '\n';
	}

	return 0;
}
#endif //1
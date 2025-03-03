#if 0

#include <iostream>
#include "3_09 Класс string view.h"
using namespace std;

vector<string_view> SplitIntoWordsView(const string &s) {
	string_view str = s;
	vector<string_view> result;

	while (true) {
		size_t space = str.find(' ');
		result.push_back(str.substr(0, space));

		if (space == str.npos)
			break;
		else
			str.remove_prefix(space + 1); //TEST!
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
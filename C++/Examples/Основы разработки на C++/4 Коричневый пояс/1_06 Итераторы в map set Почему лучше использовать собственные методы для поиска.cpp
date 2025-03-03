#if 0

#include <fstream>
#include <iostream>
#include <set>
#include "../../stdafx.h"
#include "../3 Красный пояс/1_10 Автоматический вывод типа возвращаемого функцией.h"
using namespace std;

int main(int argc, char *argv[]) {
	PRINT_FILE_LINE();

	set<string> s_words;
	ifstream fs("1_01 Введение в ассоциативные контейнеры - Input.txt");
	string text;
	while (fs >> text)
		s_words.insert(text);
	for (const auto &s : Head(s_words, 5))
		cout << s << endl;
	cout << endl;

	{
		LOG_DURATION("set::lower_bound method");
		for (char c = 'a'; c < 'z'; ++c) {
			string s(c, 1);
			s_words.lower_bound(s);
		}
	}
	{
		LOG_DURATION("global lower_bound in set");
		for (char c = 'a'; c < 'z'; ++c) {
			string s(c, 1);
			lower_bound(begin(s_words), end(s_words), s);
		}
	}

	cout << endl; //MINE
	vector<string> v_words(s_words.begin(), s_words.end());
	for (const auto &s : Head(s_words, 5))
		cout << s << endl;
	cout << endl;
	{
		LOG_DURATION("global lower_bound in vector");
		for (char c = 'a'; c < 'z'; ++c) {
			string s(c, 1);
			lower_bound(begin(v_words), end(v_words), s);
		}
	}

	return 0;
}
#endif //1
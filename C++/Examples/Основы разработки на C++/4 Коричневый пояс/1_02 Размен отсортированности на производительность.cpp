#if 0

#include <fstream>
#include <iostream>
#include <map>
#include <unordered_map>
#include "../../stdafx.h"
#include "../test_runner.h"
#include "../3 Красный пояс/1_10 Автоматический вывод типа возвращаемого функцией.h"
using namespace std;

int main(int argc, char *argv[]) {
	PRINT_FILE_LINE();

#ifdef MAP
	map<string, int> freqs;
#else //UNORDERED_MAP
	unordered_map<string, int> freqs;
#endif //UNORDERED_MAP

	{
		LOG_DURATION("Fill");
		ifstream fs("1_01 Введение в ассоциативные контейнеры - Input.txt");
		string text;
		while (fs >> text)
			++freqs[text];

		for (const auto &[k, v] : Head(freqs, 10))
			cout << k << '\t' << v << '\n'; //ORIG endl;
	}
	cout << '\n'; //MINE
	{
		LOG_DURATION("Copy and sort");
		vector<pair<string, int>> words(freqs.begin(), freqs.end());
		sort(words.begin(), words.end(), [](const auto &l, const auto &r) { return l.second > r.second; });

		for (const auto &[k, v] : Head(words, 10))
			cout << k << '\t' << v << '\n'; //ORIG endl;
	}

	return 0;
}
#endif //1

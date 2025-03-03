#if 0

#include <fstream>
#include <iostream>
#include <map>
#include "../../stdafx.h"
#include "../3 Красный пояс/1_10 Автоматический вывод типа возвращаемого функцией.h"
using namespace std;

int main(int argc, char *argv[]) {
	PRINT_FILE_LINE();

	map<string, int> freqs;
	ifstream fs("1_01 Введение в ассоциативные контейнеры - Input.txt");
	string text;
	while (fs >> text)
		++freqs[text];

	for (const auto &[k, v] : Head(freqs, 10))
		cout << k << '\t' << v << endl;
	cout << endl;

	vector<pair<string, int>> words(freqs.begin(), freqs.end());
	sort(words.begin(), words.end(), [](const auto &l, const auto &r) { return l.second > r.second; });
	
	for (const auto &[k, v] : Head(words, 10))
		cout << k << '\t' << v << endl;
	cout << endl;

	return 0;
}
#endif //1
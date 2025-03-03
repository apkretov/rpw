#pragma once

#include <string>
#include <vector>
#include "../../stdafx.h"
using namespace std;

vector<string> SplitIntoWords(const string &str) {
	vector<string> result;
	auto str_begin = begin(str);
	const auto str_end = end(str);

	while (true) {
		auto it = find(str_begin, str_end, ' ');
		result.push_back(string(str_begin, it));

		if (it == str_end)
			break;
		else
			str_begin = it + 1;
	}

	return result;
}

string GenerateText() {
	const int SIZE = 10'000'000;
	string text(SIZE, 'a');

	for (int i = 100; i < SIZE; i += 100)
		text[i] = ' ';

	return text;
}


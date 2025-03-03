#if 0 //@ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/tree/main/Week_2/02%20Programming%20Assignment

#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include "../../stdafx.h"
using namespace std;

#undef GITHUB_VECTOR
#define MINE
#undef GITHUB_SET

#ifdef GITHUB_VECTOR //@ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/blob/main/Week_2/02%20Programming%20Assignment/Source/learner.cpp
class Learner {
private:
	vector<string> dict;
public:
	int Learn(const vector<string> &words) {
		int newWords = 0;
		for (const auto &word : words) {
			if (find(dict.begin(), dict.end(), word) == dict.end()) {
				++newWords;
				dict.push_back(word);
			}
		}
		return newWords;
	}

	vector<string> KnownWords() {
		sort(dict.begin(), dict.end());
		dict.erase(unique(dict.begin(), dict.end()), dict.end());
		return dict;
	}
};
#endif //VECTOR

#ifdef MINE
class Learner {
private:
	set<string> dict;

public:
	int Learn(const vector<string> &words) {
		int newWords = 0;
		for (const auto &word : words)
			if (auto [iter, is_inserted] = dict.insert(word); is_inserted) 
				++newWords;
		return newWords;
	}

	vector<string> KnownWords() {
		return {dict.cbegin(), dict.cend()};
	}
};
#endif //SET

#ifdef GITHUB_SET //@ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/blob/main/Week_2/02%20Programming%20Assignment/Solution/learner.cpp
class Learner {
private:
	std::set<std::string> dict;
public:
	int Learn(const std::vector<std::string> &words) {
		int newWords = 0;

		for (const auto &word : words) {
			if (dict.find(word) == dict.end()) {
				newWords++;
				dict.insert(word);
			}
		}
		return newWords;
	}

	std::vector<std::string> KnownWords() {
		return {dict.begin(), dict.end()};
	}
};
#endif //GITHUB

int main() {
	PRINT_FILE_LINE();

	LOG_DURATION();

	Learner learner;
	string line;
	while (getline(cin, line)) {
		vector<string> words;
		stringstream ss(line);
		string word;
		while (ss >> word) {
			words.push_back(word);
		}
		cout << learner.Learn(words) << "\n";
	}
	cout << "=== known words ===\n";
	for (auto word : learner.KnownWords()) {
		cout << word << "\n";
	}
}
#endif //1

/*
�������� ������ �����
�������

�������� ��������� �������� ����� Learner, ���������� ������� ����������� ����. � ��������� ���������� ������ ������ ���� ��� �������:

int Learn(const vector<string>& words);
vector<string> KnownWords();

������� Learn ������ �������� ������ ����, "����������" �� � ���������� ���������� ��������� ����� ����. ������� KnownWords ������ ���������� ��������������� �� �������� ������ ���� ��������� ����. � ������ �� ������ ���� ��������.

������� ������� ��������� ������� ���� ������, ������ ��� ������-�� �������� ����� ��������. ��� ���� ��� ��������.

��� ��� ���� learner.cpp � ��������� �������� ������. �� ����� ��������� ��������� ������ Learner, ������� � �� ����� �����, ��������� �� � ������ ������������ ����� � ����������� �������.

learner.cpp

��� ��� ����� ������������� ���:

int main() {
  Learner learner;
  string line;
  while (getline(cin, line)) {
	vector<string> words;
	stringstream ss(line);
	string word;
	while (ss >> word) {
	  words.push_back(word);
	}
	cout << learner.Learn(words) << "\n";
  }
  cout << "=== known words ===\n";
  for (auto word : learner.KnownWords()) {
	cout << word << "\n";
  }
}

���������

��� ���� ������ ���� ���������, ������� ������ ������ ��� � ��������. ���� ��� �� ������ ������ ������ � �� ����������, ��� � ��� ��������� ����, �� ������ ���������������. �� ������� ����������� ���������� ������ ������ ��� ���������.

���������
*/
#if 0

#include <iostream>
#include <map>
#include <vector>
#include "../../stdafx.h"
using namespace std;

#ifdef MINE
using char_map = map<char, string::size_type>;

char_map BuildCharCounters(string_view word) {
	return char_map{};
}

struct word_pair {
	word_pair(const string &, const string &);
	string word1;
	string word2;
	bool is_anarg{};
};

inline word_pair::word_pair(const string &w1, const string &w2) : word1(w1), word2(w2) {
	char_map char_map1 = BuildCharCounters(w1);
	char_map char_map2 = BuildCharCounters(w2);
	is_anarg = char_map1 == char_map2;
}

int main() {
	cout << "Enter two words:\n";
	string word1;
	string word2;
	cin >> word1 >> word2;
	cout << word1 << '\t' << word2 << '\n';

	vector<word_pair> wp;
	wp.emplace_back(word1, word2);
}
#endif // MINE

#ifndef GITHUB //@ https://github.com/avtomato/Basics-of-C-plus-plus-development-white-belt/blob/master/week-02/11-Practice-Programming-Assignment/anagrams.cpp

map<char, int> BuildCharCounters(string &s) {
	map<char, int> counters;
	for (const char &c : s) {
		++counters[c];
	}
	return counters;
}

int main() {
	PRINT_FILE_LINE();

	int q;
	cin >> q;

	for (int i = 0; i < q; ++i) {
		string s1, s2;
		cin >> s1 >> s2;

		map<char, int> t = BuildCharCounters(s1);
		map<char, int> t2 = BuildCharCounters(s2);
		if (t == t2) {
			cout << "YES" << endl;
		} else {
			cout << "NO" << endl;
		}
	}

	return 0;
}
#endif // GITHUB
#endif //1

/*
������������� ������� �� ����������������: ���������

����� ���������� ����������� ���� �����, ���� ���� �� ��� ����� �������� ������������� ���� � ������. ��������, ����� �eat� ����� �������� ������������� ���� ����� �tea�, ������� ��� ����� �������� ����������� ���� �����. ���� ���� ����, ��������� ��� ������ �� ���, �������� �� ����� ���� ���� ����������� ���� �����.
��������

���� �� �������� �������� ����, �������� �� ����� ����������� ���� �����, ����������� � ���������. ��� ������� ����� � ������� ������� ����������, ������� ��� � �� ����������� ������ �����. ���� ��� ����� ���� ��� ������� ����� (� ��� ����������� � ������� �������� ��������� ==), �� ����� �������� ����������� ���� �����, � ��������� ������ �� ��������.

��� ���� ���������� ������ ������� �� ����� ������ ������� � ��������� ������� BuildCharCounters.
������ �����

������� ���� ����� ��� ���� N, ����� � N ������� ���������� ���� ����, ������� ���������� ���������. �������������, ��� ��� ����� ������� ���� �� �������� ��������� ����.
������ ������

�������� N �����: ��� ������ �������� ���� ���� YES, ���� ��� ����� �������� �����������, � NO � ��������� ������.
������
����

3
eat tea
find search
master stream

�����

YES
NO
YES
*/
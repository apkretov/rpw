#if 0 //@ https://github.com/avtomato/Basics-of-C-plus-plus-development-white-belt/blob/master/week-03/02-Programming-Assignment/Solution/main.cpp

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "../../stdafx.h" //MINE
using namespace std;

int main() {
	PRINT_FILE_LINE(); //MINE

	int n; // ��������� ������ �����
	cin >> n;
	vector<string> v(n);
	for (string &s : v) {
		cin >> s;
	}

	sort(begin(v), end(v), // ���������
		[](const string &l, const string &r) { // ���������� ��� ���������� � ������-�������, ������������ ������ ��� ����� ��������
			return lexicographical_compare( //TEST!																										// ���������� �����������������...
				begin(l), end(l), // ... ��� ������� ������ l ...
				begin(r), end(r), // ... �� ����� ��������� ������ r ...
				[](char cl, char cr) { return tolower(cl) < tolower(cr); } //TEST!																		// ..., ��������� � �������� ����������� ��������� ��������� �������� ��� ����� ��������
			);
		}
	);

	for (const string &s : v) { // ������� ��������������� ������
		cout << s << ' ';
	}

	return 0;
}
#endif // ON

/*
������� �� ���������������� : ���������� ��� ����� ��������
�������

� ����������� ������ ���� ���� ������, ��������� �� ����� N � ��������� �� ��� N ����� S.����� ����� ����� � ������ ��������� ��������.

������������ ������ S � ������������������ ������� �� �����������, ��������� ������� ����, � �������� �� � ����������� ����� ������.
�����������

0 <= N <= 1000
1 <= |S| <= 15
������ ������ S[i] ����� �������� �� ��������� �������� : [0 - 9, a - z, A - Z]

�������
stdin 	stdout
2 q A 	A q
3 a C b a b C
���������
�������� �������� �� ������� tolower.
*/
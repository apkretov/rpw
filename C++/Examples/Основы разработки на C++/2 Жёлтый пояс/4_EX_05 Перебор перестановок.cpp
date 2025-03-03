#if 0 // @ https://github.com/avtomato/Basics-of-C-plus-plus-development-yellow-belt/blob/master/week-04/05-Programming-Assignment/Solution/print_permutations.cpp

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include "../../stdafx.h"
using namespace std;

int main() {
	PRINT_FILE_LINE(); //MINE

	int range_length;
	cin >> range_length;
	vector<int> permutation(range_length);

	iota(permutation.begin(), permutation.end(), 1); //TEST! //																									��������� �������� ��������������� ������������� ���������� // iota -> http://ru.cppreference.com/w/cpp/algorithm/iota 
	reverse(permutation.begin(), permutation.end());

	do { // ����������� �������� � ���������� (�����������������) ������������, // ���� ��� ����������, � ���������� true, // ����� (���� �� ����������) - � ��������� (����������) � ���������� false // prev_permutation ->  http://ru.cppreference.com/w/cpp/algorithm/prev_permutation
		for (int num : permutation)
			cout << num << ' ';
		cout << endl;
	} while (prev_permutation(permutation.begin(), permutation.end()));
}
#endif //1

/*
������� �� ����������������: ������� ������������

���� ����� ������������� ����� N, �� ����������� 9. �������� ��� ������������ ����� �� 1 �� N � �������� ������������������ ������� (��. ������).
������
����

3

�����

3 2 1
3 1 2
2 3 1
2 1 3
1 3 2
1 2 3

���������
���������� �������� ������� �������, ����������� ������ ��� ������.
*/
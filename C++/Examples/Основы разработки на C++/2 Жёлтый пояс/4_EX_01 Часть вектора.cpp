#if 0 // @ https://github.com/avtomato/Basics-of-C-plus-plus-development-yellow-belt/blob/master/week-04/01-Practice-Programming-Assignment/Solution/print_vector_part.cpp

#include <algorithm>
#include <iostream>
#include <vector>
#include "../../stdafx.h"
using namespace std;

void PrintVectorPart(const vector<int> &numbers) {
	auto negative_it = find_if(
		numbers.begin(), numbers.end(),
		[](int number) {
			return number < 0;
		}
	);

	for (auto it = negative_it; it != numbers.begin(); ) {
		cout << *(--it) << " ";
	}
}

int main() {
	PRINT_FILE_LINE();

	PrintVectorPart({6, 1, 8, -5, 4});
	cout << '\n';
	PrintVectorPart({-6, 1, 8, -5, 4});  // ������ �� ���������
	cout << '\n';
	PrintVectorPart({6, 1, 8, 5, 4});
	cout << '\n';
}
#endif //1

/*
������������� ������� �� ����������������: ����� �������

�������� ������� PrintVectorPart, ����������� ������ ����� ����� numbers, ����������� ����� ������� �������������� ����� � �� � ��������� � ����������� ����� ��� �����, ������������� ����� ����������, � �������� �������. ���� ������ �� �������� ������������� �����, �������� ��� ����� � �������� �������.

void PrintVectorPart(const vector<int>& numbers);

������ ����

int main() {
  PrintVectorPart({6, 1, 8, -5, 4});
  PrintVectorPart({-6, 1, 8, -5, 4});  // ������ �� ���������
  PrintVectorPart({6, 1, 8, 5, 4});
  return 0;
}

�����

8 1 6

4 5 8 1 6
*/
#if 0 //@ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/blob/main/Week_5/06%20Programming%20Assignment/Solution/merge_sort_3.cpp

#include <algorithm>
#include <iostream>
#include <memory>
#include <ranges>
#include <vector>
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

#ifdef GITHUB //@ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/blob/main/Week_5/06%20Programming%20Assignment/Example.cpp
template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	const int range_length = range_end - range_begin; // 1. ���� �������� �������� ������ 2 ���������, ������� �� �������
	if (range_length < 2)
		return;

	vector<typename RandomIt::value_type> elements(make_move_iterator(range_begin), make_move_iterator(range_end)); //TEST! // 2. ������� ������, ���������� ��� �������� �������� ���������
	auto one_third = begin(elements) + range_length / 3; // 3. ��������� ������ �� ��� ������ �����
	auto two_third = begin(elements) + range_length * 2 / 3;

	MergeSort(begin(elements), one_third); // 4. �������� ������� MergeSort �� ������ ����� �������
	MergeSort(one_third, two_third);
	MergeSort(two_third, end(elements));

	vector<typename RandomIt::value_type> interim_result; // 5. � ������� ��������� merge c������ ������ ��� ����� �� ��������� ������ back_inserter -> http://ru.cppreference.com/w/cpp/iterator/back_inserter
	merge(make_move_iterator(begin(elements)), make_move_iterator(one_third), make_move_iterator(one_third), make_move_iterator(two_third), back_inserter(interim_result)); //TEST!
	merge(make_move_iterator(begin(interim_result)), make_move_iterator(end(interim_result)), make_move_iterator(two_third), make_move_iterator(end(elements)), range_begin); // 6. � ������� ��������� merge ������� ��������������� ����� � �������� �������� merge -> http://ru.cppreference.com/w/cpp/algorithm/merge
}
#endif //GITHUB

#ifndef MINE
template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	if (distance(range_begin, range_end) < 2) // 1. ���� �������� �������� ������ 2 ���������, ����� �� �������.
		return;

	using type = iterator_traits<RandomIt>::value_type;
	vector<type> vec(make_move_iterator(range_begin), make_move_iterator(range_end)); // 2. ������� ������, ���������� ��� �������� �������� ���������.
	
	auto one_third = distance(vec.begin(), vec.end()) / 3; // 3. ������� ������ �� ��� ������ �����. (� ���� ������ �������������, ��� ����� ������������� ��������� �������� �������� ������, ��� ��� ������ ������ ����� ������� �� ��� ������ �����.)	
	auto sub_range2_beg = vec.begin() + one_third;
	auto sub_range3_beg = vec.begin() + 2 * one_third;
	
	MergeSort(vec.begin(), vec.begin() + one_third); // 4. ������� ������� MergeSort �� ������ ����� �������.
	MergeSort(sub_range2_beg, sub_range2_beg + one_third);
	MergeSort(sub_range3_beg, vec.end());

	vector<type> temp; // 5. ����� ������ ��� ����� ������� � ������� ��������� merge, �������� ��������� �� ��������� ������ � ������� back_inserter.
	auto temp_inserter = back_inserter(temp);
	merge(make_move_iterator(vec.begin()), make_move_iterator(vec.begin() + one_third), make_move_iterator(sub_range2_beg), make_move_iterator(sub_range2_beg + one_third), temp_inserter);

	merge(make_move_iterator(temp.begin()), make_move_iterator(temp.end()), make_move_iterator(sub_range3_beg), make_move_iterator(vec.end()), range_begin); // 6. ����� ��������� ������ �� ����������� ������ � ��������� ������ ������� �� �. 2, ������� ���������� ��������������� �������� ������ ���������.
}
#endif //MINE

void TestIntVector() {
	vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};

	ostream_iterator<int> out(cout, " ");
	ranges::copy(numbers, out); cout << '\n';

	MergeSort(begin(numbers), end(numbers));
	ASSERT(is_sorted(begin(numbers), end(numbers)));

	ranges::copy(numbers, out); cout << '\n';
}

int main() {
	PRINT_FILE_LINE();

	TestRunner tr;
	tr.RunTest(TestIntVector, "TestIntVector");
	return 0;
}
#endif //1

/*
���������� �������� � 3
�������

������ ����������� �������� � ����������� �������� � 2� ���� � �Ƹ���� ����� �� �++�
�������

�������� ��������� ������� MergeSort, ����������� ��� ��������� ���������� ���� RandomIt � ����������� �������� ��� �������� � ������� ���������� ��������. �������������, ���:

	��������� ���� RandomIt ���������� �� ���������������� ���������� ������� � ������, �� ���� �� ����� ���������� � ������� ���������� <, <=, > � >=, � ����� �������� � ���������� � �������;
	����������� ������� ����� ���������� � ������� ��������� <.

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end);

��������

� ���� ������ �� ������ ����������� ����-�-���� ��������, �������������� ����; ����������� ������� ����� ���������, ��� �� ���������� � ���������� ������ ��� ��������:

	���� �������� �������� ������ 2 ���������, ����� �� �������.
	������� ������, ���������� ��� �������� �������� ���������.
	������� ������ �� ��� ������ �����. (� ���� ������ �������������, ��� ����� ������������� ��������� �������� �������� ������, ��� ��� ������ ������ ����� ������� �� ��� ������ �����.)
	������� ������� MergeSort �� ������ ����� �������.
	����� ������ ��� ����� ������� � ������� ��������� merge, �������� ��������� �� ��������� ������ � ������� back_inserter.
	����� ��������� ������ �� ����������� ������ � ��������� ������ ������� �� �. 2, ������� ���������� ��������������� �������� ������ ���������.

� �������� ������ ������ ��������� �� ������ ����������� ����������� ����������� ���������. ���� �� ����������� �����������, ��� �������� �� �������� ������� �� ��������������.
���� � ���������� �������

merge_sort_3.cpp
*/
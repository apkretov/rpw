#if 0 //@ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/tree/main/Week_5/02%20Practice%20Programming%20Assignment

#include <algorithm>
#include <iostream> 
#include <map>
#include <set>
#include <vector>
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

template <typename String> // ��������� Group<String> ��� ������������� ���� String // ��������� vector<String>. // ��������� ����� � �������� ������������� �������� // ������� ����� ������� �� ������������ ������ ��������, // � ������ ����� � vector<Group<String>>.
using Group = vector<String>;

template <typename String> // ��� ���� ��������� ������� ���� // ��������� ������ ����������� typename String::value_type // ������������ Char<String>
using Char = typename String::value_type;

template <typename String> //GITHUB @ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/blob/main/Week_5/02%20Practice%20Programming%20Assignment/Solution/group_heavy_strings.cpp
vector<Group<String>> GroupHeavyStrings(vector<String> strings) { // �������� ���������� �������, // ����������� �� ����� 1 ����������� ������� �������
	map<set<Char<String>>, Group<String>> groups; 
	vector<Group<String>> result;

	for (auto &str : strings)
		groups[{begin(str), end(str)}].push_back(move(str));

	result.reserve(groups.size());
	for (auto &[key, group] : groups)
		result.push_back(move(group));

	return result;
}

void TestGroupingABC() {
	vector<string> strings = {"caab", "abc", "cccc", "bacc", "c"};
	auto groups = GroupHeavyStrings(strings);
	ASSERT_EQUAL(groups.size(), 2);
	sort(begin(groups), end(groups));  // ������� ����� �� ����� ��������
	ASSERT_EQUAL(groups[0], vector<string>({"caab", "abc", "bacc"}));
	ASSERT_EQUAL(groups[1], vector<string>({"cccc", "c"}));
}

void TestGroupingReal() {
	vector<string> strings = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
	auto groups = GroupHeavyStrings(strings);
	ASSERT_EQUAL(groups.size(), 4);
	sort(begin(groups), end(groups));  // ������� ����� �� ����� ��������
	ASSERT_EQUAL(groups[0], vector<string>({"laptop", "paloalto"}));
	ASSERT_EQUAL(groups[1], vector<string>({"law", "wall", "awl"}));
	ASSERT_EQUAL(groups[2], vector<string>({"port"}));
	ASSERT_EQUAL(groups[3], vector<string>({"top", "pot"}));
}

int main() {
	PRINT_FILE_LINE();

	TestRunner tr;
	RUN_TEST(tr, TestGroupingABC);
	RUN_TEST(tr, TestGroupingReal);

	return 0;
}
#endif //1

/*
����������� �����
�������

��� ����� �����. ���������� ������� �� �� ������, � ������ �� ������� ��� ������ ����� ���������� ����� ��������.

��������, ���� ���� ������ law, port, top, laptop, pot, paloalto, wall, awl, ����� ������� �� �� 4 ������:

	������, ��������� ������ �� ���� a, l � w: law, wall, awl;
	������, ��������� ������ �� ���� o, p, r � t: port;
	������, ��������� ������ �� ���� o, p � t: top, pot;
	������, ��������� ������ �� ���� a, l, o, p, t: laptop, paloalto.

��������� �� ������ ������ ���� ����������� � ���� �������

template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings);

����� Group � ������� ��� vector:

template <typename String>
using Group = vector<String>;

������� ������ �������� ��������� �������� ������������ ��� ������� GroupHeavyString � ���� vector<Group>, ��� �������� ��������, ��� vector<vector>.

����� � ������ ������ ������ ������������� � ��� �� �������, ��� � � �������� ������. ��� ���� ������� ����� ����� �������� �� �����.

������ ���� String �� ������� �������� �� �������� ���� char. ��� ������� ����� �������� � ������� ��������� typename String::value_type ��� Char, ���� ���������� ��������������� �������:

template <typename String>
using Char = typename String::value_type;

��� ��� String ����� ����, ��������, ������� ������� (string) ��� �������� ��������.

��� ��� Char �������� ���������:

	������� ����� ���� ����� ���������� � ������� ���������� == � <.
	�������� ����� ���� �� ������ ���� ������, �� � ��������� �������. ������� �� ����� �������� ����������, �� ����������� ������ ������ � ������� ����� �� ����� ������ ���� (��� ����� ����������� ��� �������� ��������� strings �� ��������). � ��������� ������ �� �������� ������� ������������� ����� � ��������������� ������������.

�����������

�� 1 ������� ������� ������ ���������� �������� 100000 ����� ����� �� ����� 100. ��� ������ ��������� ������ �������, ��� ����������� ������� ������� ����� ������� 100 ������������ ��������.
���� � ���������� �������

group_heavy_strings.cpp
*/
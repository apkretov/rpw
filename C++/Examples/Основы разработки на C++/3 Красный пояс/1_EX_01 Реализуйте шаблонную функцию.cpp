#if 0 // @ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/tree/main/Week_1/01%20Practice%20Programming%20Assignment

#include <forward_list>
#include <iterator>
#include <list>
#include <numeric>
#include <string>
#include <vector>
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

#ifndef MINE
template<typename ForwardIterator, typename UnaryPredicate>
ForwardIterator max_element_if(ForwardIterator first, ForwardIterator last, UnaryPredicate pred) {
	auto it_max = find_if(first, last, pred);;
	for (auto it = it_max; it != last; it = find_if(next(it), last, pred)) {
		if (*it > *it_max)
			it_max = it;
	}
	return it_max;
}

#else //GITHUB @ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/blob/main/Week_1/01%20Practice%20Programming%20Assignment/Solution/max_element_if.cpp
template<typename ForwardIterator, typename UnaryPredicate>
ForwardIterator max_element_if(ForwardIterator first, ForwardIterator last, UnaryPredicate pred) {
	auto res = std::find_if(first, last, pred);

	if (res == last) {
		return res;
	}

	for (auto it = res; it != last; it = std::find_if(std::next(it), last, pred)) {
		if (it != last && *res < *it) {
			res = it;
		}
	}
	return res;
}
#endif //

void TestUniqueMax() {
	auto IsEven = [](int x) { return x % 2 == 0; };

	const list<int> hill{2, 4, 8, 9, 6, 4, 2};
	auto max_iterator = hill.begin();
	advance(max_iterator, 2);

	vector<int> numbers(10);
	iota(numbers.begin(), numbers.end(), 1);

	Assert( // �� �� ���������� AssertEqual, ������ ��� ��� ���������� ����������� ���������� ��������� ������ � ����� ostream. ������������� ����� ����� �����������, ��� ��� ��� ����� ������� �������������� ���������, ���� ������� max_element_if, � �������, ������� ��������, ����������� �� ����� ����������.
		max_element_if(numbers.begin(), numbers.end(), IsEven) == --numbers.end(),
		"Expect the last element"
	);
	Assert(
		max_element_if(hill.begin(), hill.end(), IsEven) == max_iterator,
		"Expect the maximal even number"
	);
}

void TestSeveralMax() {
	struct IsCapitalized {
		bool operator()(const string &s) {
			return !s.empty() && isupper(s.front());
		}
	};

	const forward_list<string> text{"One", "two", "Three", "One", "Two", "Three", "one", "Two", "three"};
	auto max_iterator = text.begin();
	advance(max_iterator, 4);

	Assert(
		max_element_if(text.begin(), text.end(), IsCapitalized()) == max_iterator,
		"Expect thr first \"Two\""
	);
}

void TestNoMax() {
	const vector<int> empty;
	const string str = "Non-empty string";

	auto AlwaysTrue = [](int) { return true; };
	Assert(
		max_element_if(empty.begin(), empty.end(), AlwaysTrue) == empty.end(),
		"Expect end for empty container"
	);

	auto AlwaysFalse = [](char) { return false; };
	Assert(
		max_element_if(str.begin(), str.end(), AlwaysFalse) == str.end(),
		"Expect end for AlwaysFalse predicate"
	);
}

int main() {
	PRINT_FILE_LINE();

	TestRunner tr;
	tr.RunTest(TestUniqueMax, "TestUniqueMax");
	tr.RunTest(TestSeveralMax, "TestSeveralMax");
	tr.RunTest(TestNoMax, "TestNoMax");
}
#endif //1

/*
�����������

���� �� �� �������, ����� �� ��� ������� ������ ����� ������ ���� �����, ��� � ��� ���������� ������, ����� ������ � ��������� �����, ���������� ������ ��� ������. ���� �� �� ��������� � ������� ��� �� ������ ������ ������, ������ �����, ��� ���� ������� ������ �Ƹ���� ����
������� ������

���������� ��������� �������

template<typename ForwardIterator, typename UnaryPredicate>
ForwardIterator max_element_if(
  ForwardIterator first, ForwardIterator last, UnaryPredicate pred);

������������ �������� �� ������������ ������� � ��������� first, last, ��� �������� �������� pred ���������� true. ���� �������� �������� ��������� ���������� ��������� � ������������ ���������, �� ����������� ����� ������ ��������� ������ ��������. ���� �������� �� �������� ���������� ���������, �� ������� ������ ������� last.
������� ������

	pred ��������� �������� ���� ����, ������� ����� �������� ���������
	��� ForwardIterator ���������� ��������� ++, ==, !=, * (�������������)
	��� ����, �� ������� ��������� ��������, �������� �������� < (�������)

��������� �������:

max_element_if.cpp

����� ������ � ����� ����������

P.S. � ����� max_element_if.cpp ������������ ������������ ���� test_runner.h. ��� ����-���� ���������, ������� �� ����������� � �Ƹ���� ����� �� C++�.

test_runner.h
*/
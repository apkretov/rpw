#if 0 //@ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/tree/main/Week_5/08%20Practice%20Programming%20Assignment

#include <future>
#include <iostream>
#include <vector>
#include "1_EX_09 ������ Paginator.h"
#include "5_15 ������ ��������� � ������������ �������.h"
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

int64_t CalculateMatrixSum(const vector<vector<int>> &matrix) {
	constexpr size_t page_size = 2000;
	vector<future<int64_t>> futures;
	size_t first_row = 0;
	for (auto page : Paginate(matrix, page_size)) {
		futures.push_back(async(launch::async, [page, first_row, page_size] { return SumSingleThread(page); }));
		first_row += page_size;
	}

	int64_t sum = 0;
	for (auto &f : futures)
		sum += f.get();

	return sum;
}

void TestCalculateMatrixSum() {
	const vector<vector<int>> matrix = {
	  {1, 2, 3, 4},
	  {5, 6, 7, 8},
	  {9, 10, 11, 12},
	  {13, 14, 15, 16}
	};
	ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

void TestMine() {
	constexpr size_t matrix_size = 9000;
	const vector<vector<int>> matrix = GenerateSingleThread(matrix_size);

	cout << '\n';
	{
		LOG_DURATION("Multi thread summing");
		cout << AS_KV(CalculateMatrixSum(matrix)) << '\n';
	}
	{
		LOG_DURATION("Single thread summing");
		cout << AS_KV(SumSingleThread(matrix)) << '\n';
	}
}

int main(int argc, char *argv[]) {
	PRINT_FILE_LINE();

	TestRunner tr;
	RUN_TEST(tr, TestCalculateMatrixSum);
	RUN_TEST(tr, TestMine);

	return 0;
}
#endif //1

/*
������������ �������
�������

� ������� �� ����������� ������, � ������� ������� ����������� ��������� ���������� �������, � ����� ���������� ����� ��������� � ���. ��� ���� ��� ������� �������� ��������� ������� �� ���� ���������� ���������������. � ���� ������ ��� ����� ������� �� �� ����� ��� ������������ ��������� �������.

��� ����� �������� ������� int64_t CalculateMatrixSum(const vector<vector>& matrix), ������� �������� �� ���� ���������� ������� � ���������� ����� ��������� � ���.

���� ���������� ����� ������������� ��������� �������:

	�� ���� ����� ������� ����� ���������� ���������� ������� �������� �� 9000 (� ������ ������ ������ ������� � ��� ���������� ����� � ���);
	��� ����� � ��� �� ������� ������� CalculateMatrixSum ����� ����������� ��������� ���; ������� ����� ������ ������ ������ � ����� ����������� ������� �� ������ ��������� 15 ��;

���� � ���������� �������

matrix_sum.cpp
*/
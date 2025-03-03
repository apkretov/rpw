#if 0 //@ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/tree/main/Week_1/07%20Practice%20Programming%20Assignment

#include <iostream>
#include <vector>
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

template <typename T>
class Table {
	friend static ostream &operator<<(ostream &os, const Table<T> &t) { //MINE
		os << "{\n";
		for (const auto &row : t.cells) {
			os << "{ ";
			for (const auto &item : row)
				os << item << ' ';
			os << "}\n";
		}
		os << "}\n";
		return os;
	}
public:
	Table(size_t rows, size_t cols) : cells(rows, vector<T>(cols)) {}
	const vector<T> &operator[](size_t) const;
	vector<T> &operator[](size_t);
	void Resize(size_t, size_t);
	pair<size_t, size_t> Size() const;
private:
	vector<vector<T>> cells;
};
	
template <typename T>
const vector<T> &Table<T>::operator[](size_t row) const {
	return cells.at(row);
}

template <typename T>
vector<T> &Table<T>::operator[](size_t row) {
	return cells.at(row);
}

template <typename T>
void Table<T>::Resize(size_t rows, size_t cols) {
	cells.resize(rows);
	for (auto &row : cells) {
		row.resize(cols);
	}
}

template <typename T>
pair<size_t, size_t> Table<T>::Size() const {
	//ERR return {cells.size(), cells.front().size()}; //MINE
	return {cells.size(), cells.empty() ? 0 : cells.front().size()}; //GITHUB @ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/blob/main/Week_1/07%20Practice%20Programming%20Assignment/Solution/table.cpp
}

void TestTable() {
#ifndef GITHUB
	Table<int> t(1, 1);
	cout << t << '\n'; //MINE
	ASSERT_EQUAL(t.Size().first, 1u);
	ASSERT_EQUAL(t.Size().second, 1u);
	t[0][0] = 42;
	ASSERT_EQUAL(t[0][0], 42);
	cout << t << '\n'; //MINE
	cout << "t[0][0] = " << t[0][0] << '\n'; //MINE
	t.Resize(3, 4);
	cout << t << '\n'; //MINE
	ASSERT_EQUAL(t.Size().first, 3u);
	cout << "t.Size().first = " << t.Size().first << '\n'; //MINE
	ASSERT_EQUAL(t.Size().second, 4u);
	cout << "t.Size().second = " << t.Size().second << '\n'; //MINE

#else //MINE
	Table<int> t(0, 0);
	t.Size();
#endif //MINE
}

int main() {
	PRINT_FILE_LINE(); //MINE

	TestRunner tr;
	RUN_TEST(tr, TestTable);
	//TestTable();

	return 0;
}
#endif //1

/*
�������

��� ���� �������� ��������� ����� Table ��� ����������� �������. ��� �������� ����� �������, ��� ��� ������ ������� ����� ���� � ��� �� ��� ������ T. ������� ������ ����� ������ ���� ������ �� ���������� ������������. ����� ��������� ������ ������ ����������� ���������� �� ��������� ���� T.

���������� � ������ �����:

	����� ������ ���������� Table.
	� ������ ������ ���� ��������� �������� T - ��� �������� � ������.
	� ������ ������ ���� �����������, ���������� �� ����� ��� ����� ���� size_t, - ���������� ����� � �������� ��������������.
	� ������ ������ ���� ����������� � ������������� ������ ��������� [], ������������� ����� �����, � ���� ����� ����� ���� �� ��������� �������� []. �� ����, ������ �������� ����������� ���� cout << table[i][j];� table[i][j] = value;. ��������� ������������ �������� ��� ���� �� �����.
	� ������ ������ ���� ������� Resize, ���������� �� ���� ��� ��������� ���� size_t � �������� ������ �������. ������ ������, ����������� � ����� ������, ������ ��� ���� �����������.
	� ������ ������ ���� ����������� ����� Size, ������������ pair<size_t, size_t> ������ ������� (� ��� �� �������, � ������� ��� ��������� ������������ � �����������).

��������� ������� ������:

table.cpp
*/
#if 0 //@ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/blob/main/Week_3/02%20Practice%20Programming%20Assignment/Solution/swap_sort_copy.cpp#L10

#include <algorithm>
#include <iostream>
#include "../../stdafx.h"
using namespace std;

template <typename T>
void Swap(T *first, T *second) {
	std::swap(*first, *second);
}

template <typename T>
void SortPointers(vector<T *> &pointers) {
	sort(pointers.begin(), pointers.end(), [](T *lhs, T *rhs) {return *lhs < *rhs;}); //TEST!
}

int main() {
	PRINT_FILE_LINE();
	return 0;
}
#endif //1

/*
Swap, SortPointers, ReversedCopy
�������

� ���� ������ ��� ����� ����������� ��� ��������� �������:

	template void Swap(T* first, T* second) � ���������� ������� ��������, �� ������� ��������� ��������� first � second
	template void SortPointers(vector<T*>& pointers) � ��������� ��������� �� ���������, �� ������� ��� ���������
	template void ReversedCopy(T* src, size_t count, T* dst) � �������� � �������� ������� count ���������, ������� � ������ � ��������� src, � ������� ������, ������������ �� ������ dst. ��� ����

	������ ������ �� ��������� [src; src + count) ������ ���� ���������� �� ����� ������ ����;
	��������� [src; src + count) � [dst; dst + count) ����� ������������;
	�������� � ����� ��������� [src; src + count), ������� �� ������������ � [dst; dst + count), ������ �������� �����������.

������� ���������� �������� �������� � ������ � ��������� �������.

swap_sort_copy.cpp
*/
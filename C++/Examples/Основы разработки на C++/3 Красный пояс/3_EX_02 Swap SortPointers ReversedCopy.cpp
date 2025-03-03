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
Условие

В этой задаче вам нужно реализовать три шаблонных функции:

	template void Swap(T* first, T* second) — обменивает местами значения, на которые указывают указатели first и second
	template void SortPointers(vector<T*>& pointers) — сортирует указатели по значениям, на которые они указывают
	template void ReversedCopy(T* src, size_t count, T* dst) — копирует в обратном порядке count элементов, начиная с адреса в указателе src, в область памяти, начинающуюся по адресу dst. При этом

	каждый объект из диапазона [src; src + count) должен быть скопирован не более одного раза;
	диапазоны [src; src + count) и [dst; dst + count) могут пересекаться;
	элементы в части диапазона [src; src + count), которая не пересекается с [dst; dst + count), должны остаться неизменными.

Примеры применения шаблонов смотрите в тестах в заготовке решения.

swap_sort_copy.cpp
*/
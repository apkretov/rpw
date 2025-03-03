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
	const int range_length = range_end - range_begin; // 1. Если диапазон содержит меньше 2 элементов, выходим из функции
	if (range_length < 2)
		return;

	vector<typename RandomIt::value_type> elements(make_move_iterator(range_begin), make_move_iterator(range_end)); //TEST! // 2. Создаем вектор, содержащий все элементы текущего диапазона
	auto one_third = begin(elements) + range_length / 3; // 3. Разбиваем вектор на три равные части
	auto two_third = begin(elements) + range_length * 2 / 3;

	MergeSort(begin(elements), one_third); // 4. Вызываем функцию MergeSort от каждой трети вектора
	MergeSort(one_third, two_third);
	MergeSort(two_third, end(elements));

	vector<typename RandomIt::value_type> interim_result; // 5. С помощью алгоритма merge cливаем первые две трети во временный вектор back_inserter -> http://ru.cppreference.com/w/cpp/iterator/back_inserter
	merge(make_move_iterator(begin(elements)), make_move_iterator(one_third), make_move_iterator(one_third), make_move_iterator(two_third), back_inserter(interim_result)); //TEST!
	merge(make_move_iterator(begin(interim_result)), make_move_iterator(end(interim_result)), make_move_iterator(two_third), make_move_iterator(end(elements)), range_begin); // 6. С помощью алгоритма merge сливаем отсортированные части в исходный диапазон merge -> http://ru.cppreference.com/w/cpp/algorithm/merge
}
#endif //GITHUB

#ifndef MINE
template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	if (distance(range_begin, range_end) < 2) // 1. Если диапазон содержит меньше 2 элементов, выйти из функции.
		return;

	using type = iterator_traits<RandomIt>::value_type;
	vector<type> vec(make_move_iterator(range_begin), make_move_iterator(range_end)); // 2. Создать вектор, содержащий все элементы текущего диапазона.
	
	auto one_third = distance(vec.begin(), vec.end()) / 3; // 3. Разбить вектор на три равные части. (В этой задаче гарантируется, что длина передаваемого диапазона является степенью тройки, так что вектор всегда можно разбить на три равные части.)	
	auto sub_range2_beg = vec.begin() + one_third;
	auto sub_range3_beg = vec.begin() + 2 * one_third;
	
	MergeSort(vec.begin(), vec.begin() + one_third); // 4. Вызвать функцию MergeSort от каждой части вектора.
	MergeSort(sub_range2_beg, sub_range2_beg + one_third);
	MergeSort(sub_range3_beg, vec.end());

	vector<type> temp; // 5. Слить первые две трети вектора с помощью алгоритма merge, сохранив результат во временный вектор с помощью back_inserter.
	auto temp_inserter = back_inserter(temp);
	merge(make_move_iterator(vec.begin()), make_move_iterator(vec.begin() + one_third), make_move_iterator(sub_range2_beg), make_move_iterator(sub_range2_beg + one_third), temp_inserter);

	merge(make_move_iterator(temp.begin()), make_move_iterator(temp.end()), make_move_iterator(sub_range3_beg), make_move_iterator(vec.end()), range_begin); // 6. Слить временный вектор из предыдущего пункта с последней третью вектора из п. 2, записав полученный отсортированный диапазон вместо исходного.
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
Сортировка слиянием — 3
Условие

Задачи «Сортировка слиянием» и «Сортировка слиянием — 2» были в «Жёлтом поясе по С++»
Условие

Напишите шаблонную функцию MergeSort, принимающую два итератора шаблонного типа RandomIt и сортирующую заданный ими диапазон с помощью сортировки слиянием. Гарантируется, что:

	итераторы типа RandomIt аналогичны по функциональности итераторам вектора и строки, то есть их можно сравнивать с помощью операторов <, <=, > и >=, а также вычитать и складывать с числами;
	сортируемые объекты можно сравнивать с помощью оператора <.

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end);

Алгоритм

В этой задаче вы должны реализовать точь-в-точь алгоритм, представленный ниже; тестирующая система будет проверять, что вы выполняете с элементами именно эти действия:

	Если диапазон содержит меньше 2 элементов, выйти из функции.
	Создать вектор, содержащий все элементы текущего диапазона.
	Разбить вектор на три равные части. (В этой задаче гарантируется, что длина передаваемого диапазона является степенью тройки, так что вектор всегда можно разбить на три равные части.)
	Вызвать функцию MergeSort от каждой части вектора.
	Слить первые две трети вектора с помощью алгоритма merge, сохранив результат во временный вектор с помощью back_inserter.
	Слить временный вектор из предыдущего пункта с последней третью вектора из п. 2, записав полученный отсортированный диапазон вместо исходного.

В процессе работы вашего алгоритма не должно происходить копирования сортируемых элементов. Если вы используете копирование, при отправке не проверку решение не скомпилируется.
Файл с заготовкой решения

merge_sort_3.cpp
*/
#if 0

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include "../../stdafx.h"
using namespace std;

#ifndef MINE
template <typename T>
vector<T> FindGreaterElements(const set<T> &elements, const T &border) {
#ifdef _1
	auto border_it = elements.find(border);
	vector<T> v;

	if (border_it != elements.cend())
		for (auto it = next(border_it); it != elements.cend(); it = next(it))
			v.push_back(*it);

	return v;
#else //_2
	if (auto border_it = elements.find(border); border_it != elements.cend())
		return {next(border_it), elements.cend()};
	else
		return {};
#endif //_2
}

#else //GITHUB @ https://github.com/avtomato/Basics-of-C-plus-plus-development-yellow-belt/blob/master/week-04/02-Programming-Assignment/Solution/find_greater_elements.cpp
template <typename T>
vector<T> FindGreaterElements(const set<T> &elements, const T &border) {
	auto it = begin(elements); // Начнём итерироваться по множеству
	while (it != end(elements) && *it <= border) { // Цель — найти первый элемент, больший border // Если итератор не достиг конца и указывает не туда, двигаем
		++it;
	}
	return {it, end(elements)}; // Возвращаем вектор, созданный из элементов множества, начиная с it
}
#endif //GITHUB

int main() {
	PRINT_FILE_LINE();

	for (int x : FindGreaterElements(set<int>{1, 5, 7, 8}, 5)) {
		cout << x << " ";
	}
	cout << endl;

	string to_find = "Python";
	cout << FindGreaterElements(set<string>{"C", "C++"}, to_find).size() << endl;
}
#endif //1

/*
Задание по программированию: Часть множества

Напишите шаблонную функцию FindGreaterElements, принимающую множество elements объектов типа T и ещё один объект border типа T и возвращающую вектор из всех элементов множества, бо́льших border, в возрастающем порядке.

template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border);

Пример кода

int main() {
  for (int x : FindGreaterElements(set<int>{1, 5, 7, 8}, 5)) {
	cout << x << " ";
  }
  cout << endl;

  string to_find = "Python";
  cout << FindGreaterElements(set<string>{"C", "C++"}, to_find).size() << endl;
  return 0;
}

Вывод

7 8
0
*/
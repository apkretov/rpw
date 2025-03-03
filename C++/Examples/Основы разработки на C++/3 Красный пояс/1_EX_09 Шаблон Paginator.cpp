#if 0

#include <iostream>
#include <numeric>
#include <string>
#include "../../stdafx.h"
#include "../test_runner.h"
#include "1_EX_09 Шаблон Paginator.h"
#ifndef USE_TESTRUNNERUTILITY
#else
template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v) {
	os << '{';
	for (const auto &item : v)
		os << item << ' ';
	os << '}';
	return os;
}
#endif //USE_TESTRUNNERUTILITY

using namespace std;
using Application = int; //MINE

vector<vector<Application>> DistributeAmongScreens(const vector<Application> &apps) {
	vector<vector<Application>> result;
	for (const auto &page : Paginate(apps, 20)) {
		result.push_back({page.begin(), page.end()});
	}
	// result[0] - все приложения, которые попадают на первый экран,
	// result[1] - все приложения, которые попадают на второй экран и т.д.
	return result;
}

void TestPageCounts() {
	vector<int> v(15);

	ASSERT_EQUAL(Paginate(v, 1).size(), v.size());
	ASSERT_EQUAL(Paginate(v, 3).size(), 5u);
	ASSERT_EQUAL(Paginate(v, 5).size(), 3u);
	ASSERT_EQUAL(Paginate(v, 4).size(), 4u);
	ASSERT_EQUAL(Paginate(v, 15).size(), 1u);
	ASSERT_EQUAL(Paginate(v, 150).size(), 1u);
	ASSERT_EQUAL(Paginate(v, 14).size(), 2u);
}

void TestLooping() {
	vector<int> v(15);
	iota(begin(v), end(v), 1);

	Paginator<vector<int>::iterator> paginate_v(v.begin(), v.end(), 6);
	ostringstream os;
	for (const auto &page : paginate_v) {
		for (int x : page) {
			os << x << ' ';
		}
		os << '\n';
	}

	ASSERT_EQUAL(os.str(), "1 2 3 4 5 6 \n7 8 9 10 11 12 \n13 14 15 \n");
	cout << boolalpha << AS_KV((string{os.str()} == string{"1 2 3 4 5 6 \n7 8 9 10 11 12 \n13 14 15 \n"})) << '\n'; //MINE
}

void TestModification() {
	vector<string> vs = {"one", "two", "three", "four", "five"};
	for (auto page : Paginate(vs, 2)) {
		for (auto &word : page) {
			word[0] = toupper(word[0]);
		}
	}

	const vector<string> expected = {"One", "Two", "Three", "Four", "Five"};
	ASSERT_EQUAL(vs, expected);
	cout << boolalpha << AS_KV((vs == expected)) << '\n'; //MINE
}

void TestPageSizes() {
	string letters(26, ' ');

	Paginator letters_pagination(letters.begin(), letters.end(), 11);
	vector<size_t> page_sizes;
	for (const auto &page : letters_pagination) 
		page_sizes.push_back(page.size());

	const vector<size_t> expected = {11, 11, 4};
	ASSERT_EQUAL(page_sizes, expected);
}

void TestConstContainer() {
	const string letters = "abcdefghijklmnopqrstuvwxyz";

	vector<string> pages;
	for (const auto &page : Paginate(letters, 10)) {
		pages.push_back(string(page.begin(), page.end()));
	}

	const vector<string> expected = {"abcdefghij", "klmnopqrst", "uvwxyz"};
	ASSERT_EQUAL(pages, expected);
	cout << boolalpha << AS_KV((pages == expected)) << '\n'; //MINE
}

void TestPagePagination() {
	vector<int> v(22);
	iota(begin(v), end(v), 1);

	vector<vector<int>> lines;
	for (const auto &split_by_9 : Paginate(v, 9)) {
		for (const auto &split_by_4 : Paginate(split_by_9, 4)) {
			lines.push_back({});
			for (int item : split_by_4) {
				lines.back().push_back(item);
			}
		}
	}

	const vector<vector<int>> expected = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9},
		{10, 11, 12, 13},
		{14, 15, 16, 17},
		{18},
		{19, 20, 21, 22}
	};
	ASSERT_EQUAL(lines, expected);
	cout << boolalpha << AS_KV((lines == expected)) << '\n'; //MINE
}

int main() {
	PRINT_FILE_LINE();

	TestRunner tr;
	RUN_TEST(tr, TestPageCounts);
	RUN_TEST(tr, TestLooping);
	TestLooping();
	RUN_TEST(tr, TestModification);
	TestModification();
	RUN_TEST(tr, TestPageSizes);
	RUN_TEST(tr, TestConstContainer);
	TestConstContainer();
	RUN_TEST(tr, TestPagePagination);
	TestPagePagination();
}
#endif //1

/*
Шаблон Paginator
Условие

В лекции мы разработали функцию Head, которая позволяет пройтись циклом for по началу контейнера. В этой задаче мы сделаем шаг вперёд и разработаем шаблон Paginator, который разбивает содержимое контейнера на несколько страниц. Классический пример, когда такое может пригодиться на практике, — это распределение списка мобильных приложений по экранам телефона. Допустим, у нас есть вектор всех приложений нашего телефона и на одном экране мы можем разместить 20 иконок приложений. Тогда распределить приложения по экранам мы можем вот таким кодом:

vector<vector<Application>> DistributeAmongScreens(const vector<Application>& apps) {
  vector<vector<Application>> result;
  for (const auto& page : Paginate(apps, 20)) {
	result.push_back({page.begin(), page.end()});
  }
  // result[0] - все приложения, которые попадают на первый экран,
  // result[1] - все приложения, которые попадают на второй экран и т.д.
  return result;
}

Заметьте, наш код получился коротким и элегантным. Нам не пришлось писать какой-то отдельный код для обработки последнего экрана, который может содержать меньше 20 приложений.

Итак, разработайте шаблон класса Paginator со следующими свойствами:

	он имеет один шаблонный параметр — тип итератора
	конструктор класса Paginator принимает три параметра:

	Iterator begin
	Iterator end — пара итераторов begin и end задают полуинтервал begin; end, который мы будем нарезать на страницы
	size_t page_size — размер одной страницы

	по объектам класса Paginator можно проитерироваться с помощью цикла range-based for
	класс Paginator имеет метод size_t size() const, который возвращает количество страниц, на которые был разбит переданный контейнер
	сами страницы должны так же поддерживать итерацию с помощью range-based for и иметь метод size_t size() const, возвращающий количество объектов в этой странице
	подробные примеры использования смотрите в юнит-тестах в шаблоне решения

Кроме того разработайте шаблон функции Paginate, которая принимает ссылку на контейнер и размер страницы, и возвращает объект класса Paginator:

template <typename C> ??? Paginate(C& c, size_t page_size)

Файл с заготовкой решения задачи

paginator.cpp

Возможно, в шаблоне у вас будет некорректно работать вызов ASSERT_EQUAL в функции TestLooping. Разберитесь, почему это происходит, внесите правку в свою локальную версию файла test_runner.h, чтобы подобная ошибка не возникала в других задачах.
Подсказки

Для этой задачи есть набор подсказок, которые должны помочь вам с решением. Если вам не удаётся решить задачу и вы чувствуете, что у вас кончились идеи, вы можете ими воспользоваться. Но сначала обязательно попробуйте решить задачу без подсказок.

Подсказска 1

Подсказска 2

Подсказска 3
*/
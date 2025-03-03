#if 0 //@ https://github.com/avtomato/Basics-of-C-plus-plus-development-white-belt/blob/master/week-03/02-Programming-Assignment/Solution/main.cpp

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "../../stdafx.h" //MINE
using namespace std;

int main() {
	PRINT_FILE_LINE(); //MINE

	int n; // считываем вектор строк
	cin >> n;
	vector<string> v(n);
	for (string &s : v) {
		cin >> s;
	}

	sort(begin(v), end(v), // сортируем
		[](const string &l, const string &r) { // компаратор для сортировки — лямбда-функция, сравнивающая строки без учёта регистра
			return lexicographical_compare( //TEST!																										// сравниваем лексикографически...
				begin(l), end(l), // ... все символы строки l ...
				begin(r), end(r), // ... со всеми символами строки r ...
				[](char cl, char cr) { return tolower(cl) < tolower(cr); } //TEST!																		// ..., используя в качестве компаратора сравнение отдельных символов без учёта регистра
			);
		}
	);

	for (const string &s : v) { // выводим отсортированный вектор
		cout << s << ' ';
	}

	return 0;
}
#endif // ON

/*
Задание по программированию : Сортировка без учёта регистра
Условие

В стандартном потоке дана одна строка, состоящая из числа N и следующих за ним N строк S.Между собой число и строки разделены пробелом.

Отсортируйте строки S в лексикографическом порядке по возрастанию, игнорируя регистр букв, и выведите их в стандартный поток вывода.
Ограничения

0 <= N <= 1000
1 <= |S| <= 15
Каждая строка S[i] может состоять из следующих символов : [0 - 9, a - z, A - Z]

Примеры
stdin 	stdout
2 q A 	A q
3 a C b a b C
Подсказка
Обратите внимание на функцию tolower.
*/
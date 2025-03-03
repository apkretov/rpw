#if 0 //@ https://github.com/avtomato/Basics-of-C-plus-plus-development-yellow-belt/tree/master/week-01/03-Practice-Programming-Assignment

#include <iostream>
#include <map>
#include <tuple>
#include <vector>
#include "../../stdafx.h"
using namespace std;

enum class Lang {
	DE, FR, IT
};

struct Region {
	string std_name;
	string parent_std_name;
	map<Lang, string> names;
	int64_t population;
};

bool operator<(const Region &lhs, const Region &rhs) {
	return tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population) <
		tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}

int FindMaxRepetitionCount(const vector<Region> &regions) {
	int result = 0;
	map<Region, int> repetion_count;
	for (const Region &region : regions) {
		result = max(result, ++repetion_count[region]); //TEST!
	}
	return result;
}

int main() {
	PRINT_FILE_LINE();

	cout << FindMaxRepetitionCount({
		{
			"Moscow",
			"Russia",
			{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
			89
		}, {
			"Russia",
			"Eurasia",
			{{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
			89
		}, {
			"Moscow",
			"Russia",
			{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
			89
		}, {
			"Moscow",
			"Russia",
			{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
			89
		}, {
			"Russia",
			"Eurasia",
			{{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
			89
		},
		}) << endl;

	cout << FindMaxRepetitionCount({
		{
			"Moscow",
			"Russia",
			{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
			89
		}, {
			"Russia",
			"Eurasia",
			{{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
			89
		}, {
			"Moscow",
			"Russia",
			{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
			89
		}, {
			"Moscow",
			"Toulouse",
			{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
			89
		}, {
			"Moscow",
			"Russia",
			{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
			31
		},
		}) << endl;

	return 0;
}
#endif //1

/*
Тренировочное задание по программированию: База регионов

Имеется база регионов, представленная вектором структур Region:

struct Region {
  string std_name;
  string parent_std_name;
  map<Lang, string> names;
  int64_t population;
};

Здесь Lang — идентификатор языка:

enum class Lang {
  DE, FR, IT
};

Напишите функцию FindMaxRepetitionCount, принимающую базу регионов и определяющую, какое максимальное количество повторов она содержит. Две записи (объекты типа Region) считаются различными, если они отличаются хотя бы одним полем.

int FindMaxRepetitionCount(const vector<Region>& regions);

Если все записи уникальны, считайте максимальное количество повторов равным 1. Если записи отсутствуют, верните 0. Гарантируется, что типа int достаточно для хранения ответа.
Пример кода

int main() {
  cout << FindMaxRepetitionCount({
	  {
		  "Moscow",
		  "Russia",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
		  89
	  }, {
		  "Russia",
		  "Eurasia",
		  {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
		  89
	  }, {
		  "Moscow",
		  "Russia",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
		  89
	  }, {
		  "Moscow",
		  "Russia",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
		  89
	  }, {
		  "Russia",
		  "Eurasia",
		  {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
		  89
	  },
  }) << endl;

  cout << FindMaxRepetitionCount({
	  {
		  "Moscow",
		  "Russia",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
		  89
	  }, {
		  "Russia",
		  "Eurasia",
		  {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
		  89
	  }, {
		  "Moscow",
		  "Russia",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
		  89
	  }, {
		  "Moscow",
		  "Toulouse",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
		  89
	  }, {
		  "Moscow",
		  "Russia",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
		  31
	  },
  }) << endl;

  return 0;
}

Вывод

3
1

Пояснение
В этой задаче вам надо прислать на проверку файл с реализацией функции FindMaxRepetitionCount, а также дополнительных функций, если это необходим. Этот файл не должен содержать функцию main и типы Lang и Region. В противном случае вы получите ошибку компиляции.
*/
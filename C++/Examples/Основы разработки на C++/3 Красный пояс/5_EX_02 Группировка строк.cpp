#if 0 //@ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/tree/main/Week_5/02%20Practice%20Programming%20Assignment

#include <algorithm>
#include <iostream> 
#include <map>
#include <set>
#include <vector>
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

template <typename String> // Объявляем Group<String> для произвольного типа String // синонимом vector<String>. // Благодаря этому в качестве возвращаемого значения // функции можно указать не малопонятный вектор векторов, // а вектор групп — vector<Group<String>>.
using Group = vector<String>;

template <typename String> // Ещё один шаблонный синоним типа // позволяет вместо громоздкого typename String::value_type // использовать Char<String>
using Char = typename String::value_type;

template <typename String> //GITHUB @ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/blob/main/Week_5/02%20Practice%20Programming%20Assignment/Solution/group_heavy_strings.cpp
vector<Group<String>> GroupHeavyStrings(vector<String> strings) { // Напишите реализацию функции, // использовав не более 1 копирования каждого символа
	map<set<Char<String>>, Group<String>> groups; 
	vector<Group<String>> result;

	for (auto &str : strings)
		groups[{begin(str), end(str)}].push_back(move(str));

	result.reserve(groups.size());
	for (auto &[key, group] : groups)
		result.push_back(move(group));

	return result;
}

void TestGroupingABC() {
	vector<string> strings = {"caab", "abc", "cccc", "bacc", "c"};
	auto groups = GroupHeavyStrings(strings);
	ASSERT_EQUAL(groups.size(), 2);
	sort(begin(groups), end(groups));  // Порядок групп не имеет значения
	ASSERT_EQUAL(groups[0], vector<string>({"caab", "abc", "bacc"}));
	ASSERT_EQUAL(groups[1], vector<string>({"cccc", "c"}));
}

void TestGroupingReal() {
	vector<string> strings = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
	auto groups = GroupHeavyStrings(strings);
	ASSERT_EQUAL(groups.size(), 4);
	sort(begin(groups), end(groups));  // Порядок групп не имеет значения
	ASSERT_EQUAL(groups[0], vector<string>({"laptop", "paloalto"}));
	ASSERT_EQUAL(groups[1], vector<string>({"law", "wall", "awl"}));
	ASSERT_EQUAL(groups[2], vector<string>({"port"}));
	ASSERT_EQUAL(groups[3], vector<string>({"top", "pot"}));
}

int main() {
	PRINT_FILE_LINE();

	TestRunner tr;
	RUN_TEST(tr, TestGroupingABC);
	RUN_TEST(tr, TestGroupingReal);

	return 0;
}
#endif //1

/*
Группировка строк
Условие

Дан набор строк. Необходимо разбить их на группы, в каждой из которых все строки имеют одинаковый набор символов.

Например, если даны строки law, port, top, laptop, pot, paloalto, wall, awl, нужно разбить их на 4 группы:

	строки, состоящие только из букв a, l и w: law, wall, awl;
	строки, состоящие только из букв o, p, r и t: port;
	строки, состоящие только из букв o, p и t: top, pot;
	строки, состоящие только из букв a, l, o, p, t: laptop, paloalto.

Разбиение на группы должно быть реализовано в виде функции

template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings);

Здесь Group — синоним для vector:

template <typename String>
using Group = vector<String>;

Наличие такого синонима позволяет записать возвращаемый тип функции GroupHeavyString в виде vector<Group>, что читается понятнее, чем vector<vector>.

Слова в каждой группе должны располагаться в том же порядке, что и в исходном наборе. При этом порядок самих групп значения не имеет.

Строка типа String не обязана состоять из символов типа char. Тип символа можно получить с помощью выражения typename String::value_type или Char, если определить соответствующий синоним:

template <typename String>
using Char = typename String::value_type;

Сам тип String может быть, например, обычной строкой (string) или вектором символов.

Про тип Char известно следующее:

	Объекты этого типа можно сравнивать с помощью операторов == и <.
	«Тяжёлыми» могут быть не только сами строки, но и отдельные символы. Поэтому их можно свободно перемещать, но скопировать каждый символ в функции можно не более одного раза (без учёта копирования при передаче аргумента strings по значению). В противном случае вы получите вердикт «неправильный ответ» с соответствующим комментарием.

Ограничения

За 1 секунду функция должна обработать максимум 100000 строк длины не более 100. При оценке сложности можете считать, что копирование каждого символа стоит порядка 100 элементарных операций.
Файл с заготовкой решения

group_heavy_strings.cpp
*/
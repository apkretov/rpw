#if 0

#include <algorithm>
#include <iostream>
#include <map>
#include "../../stdafx.h"
using namespace std;

#pragma region MINE

using names_map = map<int, string>;

string GetFirstName(int year, const names_map &firstname) { //TO DO: The logic is incorrect.
	auto it = find_if_not(firstname.crbegin(), firstname.crend(),
		[year](const auto &firstname_pr) { return year >= firstname_pr.first; });
	if (it != firstname.crend())
		return it->second;
	else
		return "Incognito";
}

string FindNameByYear(const map<int, string> &names, int year);

int main() {
	PRINT_FILE_LINE();

	names_map firstname = {{1965, "Polina"},
							{1967, "Valentina"}};

	for (int year : {1900, 1965, 1990})
		cout << "Year: " << year << " name: " << GetFirstName(year, firstname) << '\n';


	map<int, string> firstname2 = {{1965, "Polina"},
							{1967, "Valentina"}};

	cout << '\n';
	for (int year : {1900, 1965, 1990})
		cout << "Year: " << year << " name: " << FindNameByYear(firstname2, year) << '\n';
}

#pragma endregion //MINE

#pragma region //GITHUB @ https://github.com/avtomato/Basics-of-C-plus-plus-development-white-belt/blob/master/week-03/04-Programming-Assignment/Solution/main.cpp

string FindNameByYear(const map<int, string> &names, int year) { // если имя неизвестно, возвращает пустую строку
	string name;  // изначально имя неизвестно

	for (const auto &item : names) // перебираем всю историю по возрастанию ключа словаря, то есть в хронологическом порядке
		if (item.first <= year) // если очередной год не больше данного, обновляем имя
			name = item.second;
		else
			break; // иначе пора остановиться, так как эта запись и все последующие относятся к будущему

	return name;
}

class Person { //VER1
public:
	void ChangeFirstName(int year, const string &first_name) {
		first_names[year] = first_name;
	}

	void ChangeLastName(int year, const string &last_name) {
		last_names[year] = last_name;
	}

	string GetFullName(int year) {
		const string first_name = FindNameByYear(first_names, year); // получаем имя и фамилию по состоянию на год year
		const string last_name = FindNameByYear(last_names, year);

		if (first_name.empty() && last_name.empty()) // если и имя, и фамилия неизвестны
			return "Incognito";
		else if (first_name.empty()) // если неизвестно только имя
			return last_name + " with unknown first name";
		else if (last_name.empty()) // если неизвестна только фамилия
			return first_name + " with unknown last name";
		else // если известны и имя, и фамилия
			return first_name + " " + last_name;
	}
private:
	map<int, string> first_names;
	map<int, string> last_names;
};
#pragma endregion //GITHUB
#endif //1

/*
Задание по программированию: Имена и фамилии — 1

Реализуйте класс для человека, поддерживающий историю изменений человеком своих фамилии и имени.

class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
	// добавить факт изменения имени на first_name в год year
  }
  void ChangeLastName(int year, const string& last_name) {
	// добавить факт изменения фамилии на last_name в год year
  }
  string GetFullName(int year) {
	// получить имя и фамилию по состоянию на конец года year
  }
private:
  // приватные поля
};

Считайте, что в каждый год может произойти не более одного изменения фамилии и не более одного изменения имени. При этом с течением времени могут открываться всё новые факты из прошлого человека, поэтому года́ в последовательных вызовах методов ChangeLastName и ChangeFirstName не обязаны возрастать.

Гарантируется, что все имена и фамилии непусты.

Строка, возвращаемая методом GetFullName, должна содержать разделённые одним пробелом имя и фамилию человека по состоянию на конец данного года.

	Если к данному году не случилось ни одного изменения фамилии и имени, верните строку "Incognito".
	Если к данному году случилось изменение фамилии, но не было ни одного изменения имени, верните "last_name with unknown first name".
	Если к данному году случилось изменение имени, но не было ни одного изменения фамилии, верните "first_name with unknown last name".

Пример
Код

int main() {
  Person person;

  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
	cout << person.GetFullName(year) << endl;
  }

  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
	cout << person.GetFullName(year) << endl;
  }

  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
	cout << person.GetFullName(year) << endl;
  }

  return 0;
}

Вывод

Incognito
Polina with unknown last name
Polina Sergeeva
Polina Sergeeva
Appolinaria Sergeeva
Polina Volkova
Appolinaria Volkova

Пояснение
В этой задаче вам надо прислать файл с реализацией класса Person. Этот файл не должен содержать функцию main. Если в нём будет функция main, вы получите ошибку компиляции.
*/
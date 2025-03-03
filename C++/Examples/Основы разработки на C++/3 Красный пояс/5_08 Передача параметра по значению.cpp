#if 0

#include <algorithm>
#include <iostream>
#include <map>
#include "../../stdafx.h"
using namespace std;

string FindNameByYear(const map<int, string> &names, int year) { // если имя неизвестно, возвращает пустую строку
	string name;  // изначально имя неизвестно

	for (const auto &item : names) // перебираем всю историю по возрастанию ключа словаря, то есть в хронологическом порядке
		if (item.first <= year) // если очередной год не больше данного, обновляем имя
			name = item.second;
		else
			break; // иначе пора остановиться, так как эта запись и все последующие относятся к будущему

	return name;
}

class Person { //VER2 Move semantics.
public:
	void ChangeFirstName(int year, string first_name) { //TEST! //																						1) call for temporary: move -> move; 2) else: copy -> move.
		first_names[year] = move(first_name); //TEST!
	}

	void ChangeLastName(int year, string &&last_name) {
		last_names[year] = move(last_name);
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

int main() {
	PRINT_FILE_LINE();
}
#endif //1

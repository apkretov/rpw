#if 0

#include <algorithm>
#include <iostream>
#include <map>
#include "../../stdafx.h"
using namespace std;

string FindNameByYear(const map<int, string> &names, int year) { // ���� ��� ����������, ���������� ������ ������
	string name;  // ���������� ��� ����������

	for (const auto &item : names) // ���������� ��� ������� �� ����������� ����� �������, �� ���� � ��������������� �������
		if (item.first <= year) // ���� ��������� ��� �� ������ �������, ��������� ���
			name = item.second;
		else
			break; // ����� ���� ������������, ��� ��� ��� ������ � ��� ����������� ��������� � ��������

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
		const string first_name = FindNameByYear(first_names, year); // �������� ��� � ������� �� ��������� �� ��� year
		const string last_name = FindNameByYear(last_names, year);

		if (first_name.empty() && last_name.empty()) // ���� � ���, � ������� ����������
			return "Incognito";
		else if (first_name.empty()) // ���� ���������� ������ ���
			return last_name + " with unknown first name";
		else if (last_name.empty()) // ���� ���������� ������ �������
			return first_name + " with unknown last name";
		else // ���� �������� � ���, � �������
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

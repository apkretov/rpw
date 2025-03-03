#if 0 // @ https://github.com/avtomato/Basics-of-C-plus-plus-development-yellow-belt/tree/master/week-04/06-Practice-Programming-Assignment

#include <ranges> //MINE
#include "../../stdafx.h"
using namespace std;

enum class Gender {
	FEMALE,
	MALE
};

struct Person {
	int age;  // �������
	Gender gender;  // ���
	bool is_employed;  // ����� �� ������
};

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) { // ��� ������ �������, ��� �� ����� ���������� ������ � �������� PrintStats
	if (range_begin == range_end) 
		return 0;

	vector<typename InputIt::value_type> range_copy(range_begin, range_end);
	auto middle = begin(range_copy) + range_copy.size() / 2;
	ranges::nth_element(range_copy, middle, [](const Person &lhs, const Person &rhs) {return lhs.age < rhs.age;}); //TEST! //ORIG //nth_element(begin(range_copy), middle, end(range_copy), [](const Person &lhs, const Person &rhs) {return lhs.age < rhs.age;});
	return middle->age;
}

#pragma region MINE
ostream &operator<<(ostream &os, const Person &p) {
	os << format("{}, {}, {}", p.age, (p.gender == Gender::MALE ? "male" : "female"), p.is_employed);
	return os;
}

ostream &operator<<(ostream &os, const vector<Person> &v) {
	for (auto const &i : v)
		os << i << '\n';
	return os;
}
#pragma endregion //MINE

void PrintStats(vector<Person> persons) { // @ https://github.com/avtomato/Basics-of-C-plus-plus-development-yellow-belt/blob/master/week-04/06-Practice-Programming-Assignment/Solution/print_stats.cpp

	cout << "persons:\n" << persons << '\n'; //MINE

	// ����������� ������� ����� � ����������:
	//                  persons
	//                 /      \
    //          females        males
	//         /       \     /      \
    //      empl.  unempl. empl.   unempl.
	auto females_end = partition(begin(persons), end(persons), [](const Person &p) {return p.gender == Gender::FEMALE;});
	auto employed_females_end = partition(begin(persons), females_end, [](const Person &p) {return p.is_employed;}); //TEST!!
	auto employed_males_end = partition(females_end, end(persons), [](const Person &p) {return p.is_employed;}); //TEST!!
	cout << "persons partitioned:\n" << persons << '\n'; //MINE

	cout << "Median age = " << ComputeMedianAge(begin(persons), end(persons)) << endl; // ������ ������������ ��� ������ ��������� � ������� ����������
	cout << "Median age for females = " << ComputeMedianAge(begin(persons), females_end) << endl;
	cout << "Median age for males = " << ComputeMedianAge(females_end, end(persons)) << endl;
	cout << "Median age for employed females = " << ComputeMedianAge(begin(persons), employed_females_end) << endl;
	cout << "Median age for unemployed females = " << ComputeMedianAge(employed_females_end, females_end) << endl;
	cout << "Median age for employed males = " << ComputeMedianAge(females_end, employed_males_end) << endl;
	cout << "Median age for unemployed males = " << ComputeMedianAge(employed_males_end, end(persons)) << endl;
}

int main() {
	PRINT_FILE_LINE(); //MINE

	vector<Person> persons = {
		{31, Gender::MALE, false},
		{40, Gender::FEMALE, true},
		{24, Gender::MALE, true},
		{20, Gender::FEMALE, true},
		{80, Gender::FEMALE, false},
		{78, Gender::MALE, false},
		{10, Gender::FEMALE, false},
		{55, Gender::MALE, true},
	};
	PrintStats(persons);
	return 0;
}
#endif //1

/*
������������� ������� �� ����������������: ��������������� ����������

� ���� ������ ��� ���������� ��������� ��������� ��������������� ���������� ��� ������ �����. ������� �������������� ���������� Person:

struct Person {
  int age;  // �������
  Gender gender;  // ���
  bool is_employed;  // ����� �� ������
};

��� Gender �������� ��������� �������:

enum class Gender {
  FEMALE,
  MALE
};

��� ���������� �������� ������� PrintStats, ���������� ������ �����, ����������� � ��������� ��������� ������� ��� ������ �� ��������� ����� �����:

	��� ����;
	��� �������;
	��� �������;
	��� ����������� �������;
	��� ������� �������;
	��� ����������� �������;
	��� ������� �������.

��� 7 ����� ����� ������� � ������� ������������ � �������� (��. ������).

void PrintStats(vector<Person> persons);

�������� ������ �� �������� (� �� �� ����������� ������), �� ��������� ����������� �������������� ��� ����� ������������ ������� � ��� ����� ����� ���������� ����������.
���������

����������� �������� partition.
���������� ���������� ��������

��� ���������� ���������� �������� ������ ����� �� ������ ������������ ������� ComputeMedianAge:

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end);

��� ������� �� ����� ������������� ��������������: �� ����������� � �� ��� � ������������� ������� � ������� ������ �������.

������� ComputeMedianAge ����� ������� � ��� ������� ������ �����: � ��������� � ���� ������ � ����� ������� ��������� ��������� ������� ������ �����.
������ ����

// ��� ������ �������, ��� �� ����� ���������� ������ � �������� PrintStats
template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
  if (range_begin == range_end) {
	return 0;
  }
  vector<typename InputIt::value_type> range_copy(range_begin, range_end);
  auto middle = begin(range_copy) + range_copy.size() / 2;
  nth_element(
	  begin(range_copy), middle, end(range_copy),
	  [](const Person& lhs, const Person& rhs) {
		return lhs.age < rhs.age;
	  }
  );
  return middle->age;
}

void PrintStats(vector<Person> persons);

int main() {
  vector<Person> persons = {
	  {31, Gender::MALE, false},
	  {40, Gender::FEMALE, true},
	  {24, Gender::MALE, true},
	  {20, Gender::FEMALE, true},
	  {80, Gender::FEMALE, false},
	  {78, Gender::MALE, false},
	  {10, Gender::FEMALE, false},
	  {55, Gender::MALE, true},
  };
  PrintStats(persons);
  return 0;
}

�����

Median age = 40
Median age for females = 40
Median age for males = 55
Median age for employed females = 40
Median age for unemployed females = 80
Median age for employed males = 55
Median age for unemployed males = 78

���������

� ���� ������ ��� ���� �������� �� �������� ���� � ����������� ������� PrintStats. ���� ���� �� ������ ��������� ����������� ������� ComputeMedianAge � ����� Person � Gender. � ��������� ������ �� �������� ������ ����������.

�������������, ��� ���� Person � Gender ��������� � �������� ��� ��, ��� � ���� ����.
*/
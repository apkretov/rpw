#if 0 //@ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/tree/main/Week_2/01%20Programming%20Assignment

#include <iostream>
#include <map>
#include "../../stdafx.h"
using namespace std;

struct Student {
	string first_name;
	string last_name;
	map<string, double> marks;
	double rating;

	bool operator< (const Student &other) const {
		return GetName() < other.GetName();
	}

	bool Less(const Student &other) const {
		return rating > other.rating;
	}

	string GetName() const {
		return first_name + " " + last_name;
	}
};

bool Compare(Student first, Student second) {
	return first.Less(second);
}

bool CompareByRef(const Student &first, const Student &second) {
	return first.Less(second);
}

int main(int argc, char *agrv[]) {
	PRINT_FILE_LINE();

	Student stud1 = {"First_name1", "Last_name1", {{"Subjec1", 1.0}, {"Subjec2", 2.0}}, 1};
	Student stud2 = {"First_name2", "Last_name2", {{"Subjec1", 1.0}, {"Subjec2", 2.0}}, 2};

	{
		LOG_DURATION("Pass by reference");
		for (size_t count = 0; count < 1000000; ++count) {
			CompareByRef(stud1, stud2);
		}
	}
	{
		LOG_DURATION("Pass by value");
		for (size_t count = 0; count < 1000000; ++count) {
			Compare(stud1, stud2);
		}
	}

	return 0;
}
#endif //1

/*
���������� ��������� �� ��������
�������

� ������ ������ ���������� �������������� ���, �������������� ��� ���������� ��������� �� ��������. ������ ������� �������� ��������� � ��������� Student, ����������� � ����� student.h. ������� �������� ������� � ���� rating:

struct Student {
  string first_name;
  string last_name;
  map<string, double> marks;
  double rating;

  bool operator < (const Student& other) const {
	return GetName() < other.GetName();
  }

  bool Less(const Student& other) const {
	return rating > other.rating;
  }

  string GetName() const {
	return first_name + " " + last_name;
  }
};

��� ���������� ��������� �� �������� ������������ ������� ���������, ������������ true, ���� ������� �������� first ���� �������� �������� second.

bool Compare(Student first, Student second) {
  return first.Less(second);
}

���� ��������, ��� ��� ������� �������� ����� ������ �������� ����������, � ������ � ����� ��������������.

�������� �� �������� ����, ���������� ���������������� ������ ������� Compare. ���� ���� ���������� ����� ������������ �����������, �� ������� �� �������� � ����������� �� �������.\

student.h

sort_students.cpp
*/
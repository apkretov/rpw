#if 0 // @ https://github.com/avtomato/Basics-of-C-plus-plus-development-white-belt/tree/master/week-04/01-Programming-Assignment

#include <iostream>
#include "../../stdafx.h"
using namespace std;

#ifndef MINE

struct Specialization {
	explicit Specialization(string_view s) : specialization(s) {}
	string specialization;
};

struct Course {
	explicit Course(string_view c) : course(c) {}
	string course;
};

struct Week {
	explicit Week(string_view w) : week(w) {}
	string week;
};

struct LectureTitle {
	LectureTitle(const Specialization &s, const Course &c, const Week &w) : specialization(s.specialization), course(c.course), week(w.week) {}
	string specialization;
	string course;
	string week;
};

int main() {
	PRINT_FILE_LINE();

	LectureTitle title(
		Specialization("C++"),
		Course("White belt"),
		Week("4th")
	);

#ifdef OFF
	LectureTitle title2("C++", "White belt", "4th");
	LectureTitle title = {"C++", "White belt", "4th"};
	LectureTitle title = {{"C++"}, {"White belt"}, {"4th"}};

	LectureTitle title(
		Course("White belt"),
		Specialization("C++"),
		Week("4th")
	);

	LectureTitle title(
		Specialization("C++"),
		Week("4th"),
		Course("White belt")
	);

#endif // OFF
}

#else //GITHUB

struct Specialization {
	string value;
	explicit Specialization(string other_value) {
		value = other_value;
	}
};

struct Course {
	string value;
	explicit Course(string other_value) {
		value = other_value;
	}
};

struct Week {
	string value;
	explicit Week(string other_value) {
		value = other_value;
	}
};

struct LectureTitle {
	string specialization;
	string course;
	string week;

	LectureTitle(Specialization other_specialization, Course other_course, Week other_week) {
		specialization = other_specialization.value;
		course = other_course.value;
		week = other_week.value;
	}
};

int main() {
	PRINT_FILE_LINE();

	LectureTitle title(
		Specialization("C++"),
		Course("White belt"),
		Week("4th")
	);

	return 0;
}
#endif // MINE
#endif //1

/*
Задание по программированию: Структура LectureTitle

Дана структура LectureTitle:

struct LectureTitle {
  string specialization;
  string course;
  string week;
};

Допишите конструктор и структуры Specialization, Course, Week так, чтобы объект LectureTitle можно было создать с помощью кода

LectureTitle title(
	Specialization("C++"),
	Course("White belt"),
	Week("4th")
);

но нельзя было с помощью следующих фрагментов кода:

LectureTitle title("C++", "White belt", "4th");

LectureTitle title = {"C++", "White belt", "4th"};

LectureTitle title = {{"C++"}, {"White belt"}, {"4th"}};

LectureTitle title(
	Course("White belt"),
	Specialization("C++"),
	Week("4th")
);

LectureTitle title(
	Specialization("C++"),
	Week("4th"),
	Course("White belt")
);

Пояснение
В этой задаче вам надо прислать на проверку файл с реализацией необходимых классов. Этот файл не должен содержать функцию main. Если в нём будет функция main, вы получите ошибку компиляции.
*/
#if 0

#include <iostream>
#include <vector>
#include "../../stdafx.h"
using namespace std;

#ifdef MINE
using Incognizable = vector<int>;
#else //GITHUB @ https://github.com/avtomato/Basics-of-C-plus-plus-development-white-belt/blob/master/week-03/08-Practice-Programming-Assignment/incognizable.cpp
struct Incognizable {
	int first = 0;
	int second = 0;
};
#endif //MINE

int main() {
	PRINT_FILE_LINE();

	Incognizable a;
	Incognizable b = {};
	Incognizable c = {0};
	Incognizable d = {0, 1};
}
#endif //1

/*
Тренировочное задание по программированию: Способы инициализации

Определите тип Incognizable, для которого следующий код будет корректен:

int main() {
  Incognizable a;
  Incognizable b = {};
  Incognizable c = {0};
  Incognizable d = {0, 1};
  return 0;
}

Пояснение
В этой задаче вам надо прислать на проверку файл с реализацией структуры или класса Incognizable. Этот файл не должен содержать функцию main. Если в нём будет функция main, вы получите ошибку компиляции.
*/
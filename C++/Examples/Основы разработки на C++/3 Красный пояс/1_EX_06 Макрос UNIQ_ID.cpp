#if 0 //@ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/tree/main/Week_1/06%20Practice%20Programming%20Assignment

#include <iostream>
#include <vector>
#include "../../stdafx.h"
using namespace std;

#ifdef MINE //ERR
#define GENERATE_ID(id, line) id##line
#define UNIQ_ID GENERATE_ID(uniq_id_, __LINE__)

#else //GITHUB @ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/blob/main/Week_1/06%20Practice%20Programming%20Assignment/Solution/uniq_id.cpp
#define UNIQ_ID_IMPL_2(lineno) _a_local_var_##lineno //TEST!
#define UNIQ_ID_IMPL(lineno) UNIQ_ID_IMPL_2(lineno)
#define UNIQ_ID UNIQ_ID_IMPL(__LINE__)
#endif 

int main() {
	PRINT_FILE_LINE();

	int UNIQ_ID = 0;
	string UNIQ_ID = "hello";
	vector<string> UNIQ_ID = {"hello", "world"};
	vector<int> UNIQ_ID = {1, 2, 3, 4};
}
#endif //1

/*
Макрос UNIQ_ID

Разработать макрос UNIQ_ID, который будет формировать идентификатор, уникальный в пределах данного cpp-файла. Например, следующий код должен компилироваться и работать:

int UNIQ_ID = 5;
string UNIQ_ID = "hello!";

В рамках данной задачи допускается, что код

int UNIQ_ID = 5; string UNIQ_ID = "hello"; // оба определения на одной строке

uniq_id.cpp

не будет компилироваться. Заготовка решения:
Подсказки:

	подумайте, как можно применить макрос LINE
	ознакомьтесь с конкатенацией в макросах
	а также с макросами в качестве параметров других макросов
*/
#if 0

#include <iostream>
#include <vector>
#include "../../stdafx.h"
#include "3_12 Конструкторы по умолчанию, использование конструкторов.h"

#pragma region Примеры использования конструкторов
void PrintRoute(const Route &r) {
	cout << "void PrintRoute(const Route &r)\n";
}

void Примеры_использования_конструкторов() {
	PrintRoute(Route()); // По умолчанию
	PrintRoute({}); //TEST!

	PrintRoute(Route("Zvenigorod", "Istra")); // Параметризированный
	PrintRoute({"Zvenigorod", "Istra"}); //TEST

	vector<Route> routes;
	routes.push_back({"Zvenigorod", "Istra"}); //TEST
}
#pragma endregion

int main() {
	PRINT_FILE_LINE();

	Примеры_использования_конструкторов();
}
#endif
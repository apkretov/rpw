#if 0

#include <iostream>
#include <vector>
#include "../../stdafx.h"
#include "3_12 ������������ �� ���������, ������������� �������������.h"

#pragma region ������� ������������� �������������
void PrintRoute(const Route &r) {
	cout << "void PrintRoute(const Route &r)\n";
}

void �������_�������������_�������������() {
	PrintRoute(Route()); // �� ���������
	PrintRoute({}); //TEST!

	PrintRoute(Route("Zvenigorod", "Istra")); // �������������������
	PrintRoute({"Zvenigorod", "Istra"}); //TEST

	vector<Route> routes;
	routes.push_back({"Zvenigorod", "Istra"}); //TEST
}
#pragma endregion

int main() {
	PRINT_FILE_LINE();

	�������_�������������_�������������();
}
#endif
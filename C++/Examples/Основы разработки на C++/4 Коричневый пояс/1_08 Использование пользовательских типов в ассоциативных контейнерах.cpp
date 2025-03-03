#if 0 //@ https://youtu.be/kKblzb-QSQg?si=7OfX89HT74Y14NbA

#include <set>
#include <unordered_set>
#include "../../stdafx.h"
#include "1_08 Использование пользовательских типов в ассоциативных контейнерах.h"

struct PlateHasher {
	size_t operator()(const Plate &p) const { return p.Number; }
};

int main() {
	PRINT_FILE_LINE();

	PlateGenerator pg;
	set<Plate> s_plates;
	unordered_set<Plate, PlateHasher> h_plates;
	const int N = 10;

#pragma region set
	for (int i = 0; i < N; ++i)
		s_plates.insert(pg.GetRundomPlate());

	for (const auto &p : s_plates)
		cout << p << endl;
	cout << endl;
#pragma endregion //set

#pragma region unordered_set
	for (int i = 0; i < N; ++i)
		h_plates.insert(pg.GetRundomPlate());

	for (const auto &p : h_plates)
		cout << p << endl;
	cout << endl;
#pragma endregion //unordered_set

	return 0;
}
#endif

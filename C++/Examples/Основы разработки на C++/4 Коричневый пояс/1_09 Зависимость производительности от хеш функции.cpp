#if 0 //@ https://youtu.be/6hs19tXfdpk?si=_ok6ORZPy7cY2rmr

#include <set>
#include <unordered_set>
#include "../../stdafx.h"
#include "1_08 Использование пользовательских типов в ассоциативных контейнерах.h"

#undef HASHER_1
#undef HASHER_2
#define HASHER_3

#undef NUMBER 50'000;
#define NUMBER 1'000'000;

#ifdef HASHER_1
struct PlateHasher {
	size_t operator()(const Plate &p) const { 
		return p.Number; 
	}
};
#endif //HASHER_1

#ifdef HASHER_2
struct PlateHasher {
	size_t operator()(const Plate &p) const { 
		size_t result = p.Number; 
		result *= 100;
		result += p.Region;
		return result;
	}
};
#endif //HASHER_2

#ifdef HASHER_3
#include "1_09 Зависимость производительности от хеш функции.h"
#endif //HASHER_3

int main() {
	PRINT_FILE_LINE();

	PlateGenerator pg;
	set<Plate> s_plates;
	unordered_set<Plate, PlateHasher> h_plates;
	const int N = NUMBER;

	{
		LOG_DURATION("set");
		for (int i = 0; i < N; ++i)
			s_plates.insert(pg.GetRundomPlate());
		for (const auto &p : s_plates)
			s_plates.find(pg.GetRundomPlate());
	}

	{
		LOG_DURATION("unordered_set");
		for (int i = 0; i < N; ++i)
			h_plates.insert(pg.GetRundomPlate());
		for (const auto &p : h_plates)
			h_plates.find(pg.GetRundomPlate());
	}

	return 0;
}
#endif

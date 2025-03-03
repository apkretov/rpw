#pragma once

#include "1_08 Использование пользовательских типов в ассоциативных контейнерах.h"

struct PlateHasher {
	size_t operator()(const Plate &p) const {
		size_t result = p.Number;
		result *= 100;
		result += p.Region;

		int s1 = p.C1 - 'A';
		int s2 = p.C2 - 'A';
		int s3 = p.C3 - 'A';
		int s = (s1 * 100 + s2) * 100 + s3;
		result *= 1'000'000;
		result += s;

		return result;
	}
};

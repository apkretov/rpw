#pragma once

#include <array>
#include <iomanip>
#include <iostream>
#include <random>
using namespace std;

struct Plate {
	char C1;
	int Number;
	char C2;
	char C3;
	int Region;
};

ostream &operator<<(ostream &out, const Plate &p) {
	out << p.C1;
	out << setw(3) << setfill('0') << p.Number;
	out << p.C2;
	out << p.C3;
	out << setw(2) << setfill('0') << p.Region;
	return out;
}

bool operator<(const Plate &l, const Plate &r) {
	return tie(l.C1, l.Number, l.C2, l.C3, l.Region) < tie(r.C1, r.Number, r.C2, r.C3, r.Region);
}

bool operator==(const Plate &l, const Plate &r) {
	return (l.C1 == r.C1)
		&& (l.Number == r.Number)
		&& (l.C2 == r.C2)
		&& (l.C3 == r.C3)
		&& (l.Region == r.Region);
}

class PlateGenerator {
public:
	Plate GetRundomPlate() {
		Plate p;
		p.C1 = Letters[LettersDist(RandEng)];
		p.Number = NumberDist(RandEng);
		p.C2 = Letters[LettersDist(RandEng)];
		p.C3 = Letters[LettersDist(RandEng)];
		p.Region = RegionDist(RandEng);
		return p;
	}
private:
	const static int N = 12;
	const array<char, N> Letters = {'A', 'B', 'C', 'E', 'H', 'K', 'M', 'O', 'P', 'T', 'X', 'Y'};
	default_random_engine RandEng;
	uniform_int_distribution<int> LettersDist{0, N - 1};
	uniform_int_distribution<int> NumberDist{1, 999};
	uniform_int_distribution<int> RegionDist{1, 99};
};
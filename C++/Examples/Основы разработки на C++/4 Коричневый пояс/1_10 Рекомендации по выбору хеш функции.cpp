#if 0 //@ https://youtu.be/DK69bkPfP88?si=XgzKIFt-HlFaRakL

#include <set>
#include <unordered_set>
#include "../../stdafx.h"
#include "1_09 Зависимость производительности от хеш функции.h"

struct MyType {
	double d;
	string str;
	Plate plate;
};

class MyHasher { //struct MyHasher {
public: //MINE
	size_t operator()(const MyType &p) const {
		size_t r1 = dhash(p.d);
		size_t r2 = shash(p.str);
		size_t r3 = phash(p.plate);
		constexpr size_t x = 37; //ORIG size_t x = 37; // A prime number.
		return (r1 * x * x) + r2 * x + r3; // Ax^2 + Bx + C
	}
private: //MINE
	hash<double> dhash;
	hash<string> shash;
	PlateHasher phash;
};

int main() {
	PRINT_FILE_LINE();

	unordered_set<Plate, PlateHasher> ht;
	unordered_set<MyType, MyHasher> ht2;

	return 0;
}
#endif

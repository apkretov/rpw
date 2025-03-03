#pragma once

#include <string>
using namespace std;

#pragma region MINE
class Route {
	string source;
	string destination;
	int length{};
public:
	Route() {
		source = "Moscow";
		destination = "Saint-Petersburg";
	};

	Route(const string &src, const string &dst) {
		source = src;
		destination = dst;
	}
};
#pragma endregion
#if 0

#include <iostream>
#include <map>
#include <set>
#include "../../stdafx.h"
using namespace std;

//MINE
const string mow = "Moscow";
const string ldn = "London";

class Cities {
public:
	tuple<bool, string> FindCountry(const string &city) const {
		//ORIG if (city_to_country.count(city) == 1)
		if (city_to_country.contains(city)) //MINE
			return {true, city_to_country.at(city)};
		//ORIG else if (ambiguious_cities.count(city) == 1)
		else if (ambiguious_cities.contains(city)) //MINE
			return {false, "Ambiguous"};
		else
			return {false, "Not found"};
	}
private:
	map<string, string> city_to_country = {{mow, "Russia"}, {"New York", "US"}}; //MINE
	set<string> ambiguious_cities = {ldn}; //MINE
};

int main(int agrc, char *argv[]) {
	PRINT_FILE_LINE();

	Cities cities;
#ifdef VER1 // The worst.
	tuple res = cities.FindCountry("Volgograd");
	cout << get<0>(res) << " " << get<1>(res) << '\n';
#elif VER2 // Better.
	bool success;
	string message;
	tie(success, message) = cities.FindCountry(ldn); //TEST!
#else VER3 // The best.
	auto [success, message] = cities.FindCountry(mow); //TEST!
	//ORIG cout << success << " " << message << '\n';
	cout << format("{} {}\n", success, message);
#endif

	return 0;
}
#endif
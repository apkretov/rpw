#include "../../stdafx.h"
#include "WeatherStationCorrect.h"
using std::cout;

int main() {
	print_file_line();

	WeatherStation weatherStation;
	cout << "Temperature: " << weatherStation.getTemperature() << '\n';

	return 0;
}
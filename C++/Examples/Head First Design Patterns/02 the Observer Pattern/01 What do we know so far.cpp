#if 1

#include "../../stdafx.h"
using namespace std;

struct Measurement { // TO DO: Make three different measurements for temperature, humidity, and pressure.
	int value;
}; 

class Display {
	vector<Measurement> measurements; // TO DO: Choose the right data structure, maybe unordered_set;
public:
	~Display() = default;
	void setMeasurement(const Measurement &measurement) { measurements.push_back(measurement); }
	virtual void show() const = 0; // TO DO: Print measurements.
};

struct CurrentConditions : public Display {
	CurrentConditions() {}
};

struct WeatherStats : public Display {
	WeatherStats() {}
};

struct Forecast : public Display {
	Forecast() {}
};

struct WeatherData {
	int getTemperature() const { /*TO DO: Return a random value.*/ return 0; } // These three methods return the most recent weather measurements for temperature, humidity and barometric pressure respectively. We don’t care HOW these variables are set; the WeatherData object knows how to get updated info from the Weather Station.
	int getHumidity() const { /*TO DO: Return a random value.*/ return 0; }
	int getPressure() const { /*TO DO: Return a random value.*/ return 0; }
	void measurementsChanged(const Measurement &mesurement) {} // This method gets called whenever the weather measurements have been updated. It updates the three displays for current conditions, weather stats, and forecast.
};

int main(int argc, char *argv[]) {
	print_file_line();
	return 0;
}
#endif //1
#if 0

#include <memory>
#include "../../stdafx.h"
using namespace std;

#ifdef VER_1
class Measurement {
	int data_;
public:
	~Measurement() = default;
	void setData(int data) { data_ = data; }
	int getData() const { return data_; }
	virtual void display() const = 0;
};

struct Temperature : public Measurement {
	void display() const override { cout << "The temperature: " << Measurement::getData() << '\n';; }
};

struct Humidity : public Measurement {
	void display() const override { cout << "The humidity: " << Measurement::getData() << '\n'; }
};

struct Pressure : public Measurement {
	void display() const override { cout << "The pressure: " << Measurement::getData() << '\n'; }
};

class Display {
	vector<unique_ptr<Measurement>> measurements; // TO DO: Choose the right data structure, maybe unordered_set;
public:
	~Display() = default;
	void setMeasuremens(unique_ptr<Measurement> measurement) { measurements.push_back(std::move(measurement)); }
	virtual void showData() const = 0; // TO DO: Print measurements.
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
#endif //VER_1

struct WeatherData {
	int getTemperature() const { /*TO DO: Return a random value.*/ return 0; } // These three methods return the most recent weather measurements for temperature, humidity and barometric pressure respectively. We don’t care HOW these variables are set; the WeatherData object knows how to get updated info from the Weather Station.
	int getHumidity() const { /*TO DO: Return a random value.*/ return 0; }
	int getPressure() const { /*TO DO: Return a random value.*/ return 0; }
#ifdef VER_1
	void measurementsChanged(const unique_ptr<Measurement> &mesurement) {} // This method gets called whenever the weather measurements have been updated. It updates the three displays for current conditions, weather stats, and forecast.  
#endif //VER_1
	void measurementsChanged() {} // This method gets called whenever the weather measurements have been updated. It updates the three displays for current conditions, weather stats, and forecast.  
};

int main(int argc, char *argv[]) {
	print_file_line();
	return 0;
}
#endif //1
#if 0

#define ORIG // Must be defined because of 03 Implementing the Weather Station.cpp

#include "../../stdafx.h"
#include "03 Implementing the Weather Station.h"
using namespace std;

class HeatIndexDisplay : public Observer, public DisplayElement { // This display implements Observer so it can get changes from the WeatherData object. // It also implements DisplayElement, because our API is going to require all display elements to implement this interface.
	double heat_index = 0;
	Subject &weatherData_;
public:
	explicit HeatIndexDisplay(Subject &weatherData) : weatherData_(weatherData) { weatherData_.registerObserver(this); } // The constructor is passed the weatherData object (the Subject) and we use it to register the display as an observer.

	void update(double temperature, double humidity, double pressure) override {
		static constexpr double c[] = { // Coefficients from National Weather Service formula
			-42.379f,
			2.04901523f,
			10.14333127f,  // Fix: Original text had typo (10.1433127)
			-0.22475541f,
			-6.83783e-3f,
			-5.481717e-2f,
			1.22874e-3f,
			8.5282e-4f,
			-1.99e-6f
		};
		heat_index = c[0] + c[1] * temperature + c[2] * humidity + c[3] * temperature * humidity // Direct multiplication is more efficient than pow() for squares
			+ c[4] * temperature * temperature + c[5] * humidity * humidity
			+ c[6] * temperature * temperature * humidity + c[7] * temperature * humidity * humidity
			+ c[8] * temperature * temperature * humidity * humidity;
		display();
	}

	void display() override { print("Heat index is {:.5f}\n", heat_index); }
};

int main() {
	print_file_line();

	WeatherData weatherData; 
	CurrentConditionsDisplay currentDisplay(weatherData); 
	StatisticsDisplay statisticsDisplay(weatherData); 
	ForecastDisplay forecastDisplay(weatherData);
	HeatIndexDisplay heatIndexDisplay(weatherData);
	weatherData.setMeasurements(80, 65, 30.4); 
	weatherData.setMeasurements(82, 70, 29.2);
	weatherData.setMeasurements(78, 90, 29.2);

	return 0;
}
#endif //1
#if 0

#include "../../stdafx.h"
using namespace std;

/* Java
public class WeatherData {
	// instance variable declarations
	public void measurementsChanged() {
		float temp = getTemperature(); // Grab the most recent measuremets by calling the WeatherData’s getter methods(already implemented).
		float humidity = getHumidity();
		float pressure = getPressure();
		currentConditionsDisplay.update(temp, humidity, pressure); // Now update the displays... // Call each display element to update its display, passing it the most recent measurements.
		statisticsDisplay.update(temp, humidity, pressure);
		forecastDisplay.update(temp, humidity, pressure);
	}
	// other WeatherData methods here
}
*/

#ifdef SUSPENDED
struct Display {
	~Display() = default;
	virtual void update(int temp, int humidity, int pressure) = 0;
};

struct CurrentConditions : public Display {
	void update(int temp, int humidity, int pressure) override {
		cout << "Temp: " << temp << '\n';
		cout << "Humidity: " << humidity << '\n';
		cout << "Pressure: " << pressure << '\n';
	};
};

class WeatherData {
	struct RndMeasurements {
		Rnd rnd_temp{-30, 50};
		Rnd rnd_humidity{0, 100};
		Rnd rnd_pressure{870, 1084}; // The standard air pressure at sea level is 1013.25 millibars (mb). The highest recorded air pressure was 1084 mb in Siberia, and the lowest was 870 mb during a typhoon in the Pacific Ocean.
	};
	RndMeasurements rnd_measurs;

	struct Measurements {
		int temp = 0;
		int humidity = 0;
		int pressure = 0;
	};
	Measurements measurs;
public:
	explicit WeatherData(Displays &displays) : displays_(displays) {}
	int getTemperature() const { return measurs.temp; } // These three methods return the most recent weather measurements for temperature, humidity and barometric pressure respectively. We don�t care HOW these variables are set; the WeatherData object knows how to get updated info from the Weather Station.
	int getHumidity() const { return measurs.humidity; }
	int getPressure() const { return measurs.pressure; }

	// instance variable declarations
	void measurementsChanged() {
		double temp = getTemperature();
		double humidity = getHumidity();
		double pressure = getPressure();
		currentConditionsDisplay.update(temp, humidity, pressure);
		statisticsDisplay.update(temp, humidity, pressure);
		forecastDisplay.update(temp, humidity, pressure);
	}
	// other WeatherData methods here
};
#endif //SUSPENDED

int main() {
	print_file_line();
	return 0;
}
#endif //1
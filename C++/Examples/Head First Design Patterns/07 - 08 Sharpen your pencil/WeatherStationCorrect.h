#ifndef WEATHER_STATION_H
#define WEATHER_STATION_H

#include "Thermometer.h"

class WeatherStation {
private:
	Thermometer thermometer;

public:
	// Constructor and other methods would go here

	// This method provides direct access to the temperature
	// without exposing the internal Thermometer
	float getTemperature() {
		return thermometer.getTemperature();
	}

	// Original method that violates Law of Demeter
	Thermometer getThermometer() {
		return thermometer;
	}
};

#endif // WEATHER_STATION_H
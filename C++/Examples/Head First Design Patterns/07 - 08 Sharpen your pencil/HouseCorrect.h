#ifndef HOUSE_H
#define HOUSE_H

#include "WeatherStationCorrect.h"

class House {
private:
	WeatherStation station;

public:
	// Constructor and other methods would go here

	// Better implementation that follows the Principle of Least Knowledge
	float getTemp() {
		return station.getTemperature(); // Only interacts with immediate dependency
	}

	// Previous implementations can be kept for reference
};

#endif // HOUSE_H
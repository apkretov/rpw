#ifndef WEATHER_STATION_H
#define WEATHER_STATION_H

#include "Thermometer.h"

class WeatherStation {
private:
    Thermometer thermometer;

public:
    // Constructor and other methods would go here
    
    Thermometer getThermometer() {
        return thermometer;
    }
};

#endif // WEATHER_STATION_H
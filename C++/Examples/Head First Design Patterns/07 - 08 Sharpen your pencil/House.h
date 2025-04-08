#ifndef HOUSE_H
#define HOUSE_H

#include "WeatherStation.h"
#include "Thermometer.h"

class House {
private:
    WeatherStation station;

public:
    // Constructor and other methods would go here

    // First implementation
    /*
    public House {
        WeatherStation station;
        
        // other methods and constructor
        
        public float getTemp() {
            return station.getThermometer().getTemperature(); // Violates the Principle of Least Knowledge! You are calling the method of an object returned from another call.
        }
    }
    */
    
    // C++ implementation of first version
    float getTemp() {
        return station.getThermometer().getTemperature(); // Violates the Principle of Least Knowledge! You are calling the method of an object returned from another call.
    }

    // Second implementation
    /*
    public House {
        WeatherStation station;
        
        // other methods and constructor
        
        public float getTemp() {
            Thermometer thermometer = station.getThermometer();
            return getTempHelper(thermometer);
        }
        
        public float getTempHelper(Thermometer thermometer) {
            return thermometer.getTemperature();
        }
    }
    */
    
    // C++ implementation of second version
    float getTemp2() {
        Thermometer thermometer = station.getThermometer();
        return getTempHelper(thermometer);
    }
    
    float getTempHelper(Thermometer thermometer) {
        return thermometer.getTemperature(); // Doesn't violate Principle of Least Knowledge! This seems like hacking our way around the principle. Has anything really changed since we just moved out the call to another method?
    }
};

#endif // HOUSE_H
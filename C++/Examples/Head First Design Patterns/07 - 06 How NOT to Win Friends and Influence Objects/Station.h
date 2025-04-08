#pragma once

#include "Thermometer.h"

class Station {
    Thermometer thermometer;
public:
    Thermometer getThermometer() const { return thermometer; }
    double getTemperature() { return thermometer.getTemperature(); } // Added when applying the principle
};

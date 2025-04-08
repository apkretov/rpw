#include <iostream>
#include "Station.h"
#include "Thermometer.h"
using std::cout;

#pragma region How NOT to Win Friends and Influence Objects
/*
public float getTemp() { // Without the Principle
	Thermometer thermometer = station.getThermometer(); // Here we get the thermometer object from the station and then call the getTemperature() method ourselves.
	return thermometer.getTemperature();
}
*/
double getTempWithoutPrinciple(Station &station) { // Without the Principle
	Thermometer thermometer = station.getThermometer(); // Here we get the thermometer object from the station and then call the getTemperature() method ourselves.
	return thermometer.getTemperature();
}

/*
public float getTemp() { // With the Principle
	return station.getTemperature(); // When we apply the principle, we add a method to the Station class that makes the request to the thermometer for us. This reduces the number of classes we're dependent on.
}
*/
double getTempWithPrinciple(Station &station) { // With the Principle
	return station.getTemperature(); // When we apply the principle, we add a method to the Station class that makes the request to the thermometer for us. This reduces the number of classes we're dependent on.
}
#pragma endregion //How NOT to Win Friends and Influence Objects

int main() {
    Station station;
    
    cout << "Temperature without principle: " << getTempWithoutPrinciple(station) << '\n';
    cout << "Temperature with principle: " << getTempWithPrinciple(station) << '\n';
    
    return 0;
}
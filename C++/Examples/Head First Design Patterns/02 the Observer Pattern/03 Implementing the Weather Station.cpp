#if 1

#define ORIG
#undef AMAZON_Q_COMPOSITION
#undef AMAZON_Q_SINGLE_INHERITANCE
#undef AMAZON_Q_USING_CPP20_CONCEPTS

#include <numeric>
#include "../../stdafx.h"
#include "03 Implementing the Weather Station.h"  
using namespace std;

#pragma region Amazon Q
// Multiple inheritance in C++ can lead to several problems. There are several better alternatives.
#ifdef AMAZON_Q_COMPOSITION
class CurrentConditionsDisplay {
	class ObserverImpl : public Observer { //TEST!
		CurrentConditionsDisplay &display_;
	public:
		explicit ObserverImpl(CurrentConditionsDisplay &display) : display_(display) {}
		void update(double temp, double humidity, double pressure) override { display_.update(temp, humidity, pressure); }
	};

	ObserverImpl observer_;
	double temperature_ = 0;
	double humidity_ = 0;
	Subject &weatherData_;
public:
	explicit CurrentConditionsDisplay(Subject &weatherData) : observer_(*this), weatherData_(weatherData) { weatherData_.registerObserver(&observer_); } //TEST!
	void display() { cout << "Current conditions: " << temperature_ << "F degrees and " << humidity_ << "% humidity\n"; }

	void update(double temp, double humidity, double pressure) {
		temperature_ = temp;
		humidity_ = humidity;
		display();
	}
};
#endif //AMAZON_Q_COMPOSITION

#ifdef AMAZON_Q_SINGLE_INHERITANCE
class CurrentConditionsDisplay : public Observer {
private:
	double temperature_;
	double humidity_;
	Subject &weatherData_;
public:
	explicit CurrentConditionsDisplay(Subject &weatherData) : weatherData_(weatherData) { weatherData_.registerObserver(this); }

	void update(double temp, double humidity, double pressure) override {
		temperature_ = temp;
		humidity_ = humidity;
		display();
	}

	void display() { cout << "Current conditions: " << temperature_ << "F degrees and " << humidity_ << "% humidity\n"; }
};
#endif //AMAZON_Q_SINGLE_INHERITANCE

#ifdef AMAZON_Q_USING_CPP20_CONCEPTS
/* The main differences from traditional interface approach:
		Interfaces are defined as concepts instead of abstract classes
		Compile-time interface checking instead of runtime
		No virtual functions or inheritance overhead */
template<typename T> // Concepts
concept Observable = requires(T t, double temp, double humidity, double pressure) { //TEST! //																				Uses C++20 concepts to define Observable and Displayable interfaces
	{ t.update(temp, humidity, pressure) } -> same_as<void>;
};

template<typename T>
concept Displayable = requires(T t) {
	{ t.display() } -> same_as<void>;
};

class Subject; // Forward declaration

class CurrentConditionsDisplay { // The concrete display class
public:
	class ObserverImpl {
		CurrentConditionsDisplay &display_;
	public:
		explicit ObserverImpl(CurrentConditionsDisplay &display) : display_(display) {}
		void update(double temp, double humidity, double pressure) { display_.update(temp, humidity, pressure); }
	};
private:
	ObserverImpl observer_;
	double temperature_;
	double humidity_;
	Subject &weatherData_;
public:
	explicit CurrentConditionsDisplay(Subject &weatherData) : observer_(*this), weatherData_(weatherData) { registerWithSubject(); }
	ObserverImpl *getObserver() { return &observer_; }
	void display() const { cout << "Current conditions: " << temperature_ << "F degrees and " << humidity_ << "% humidity\n"; }

	void update(double temp, double humidity, double pressure) {
		temperature_ = temp;
		humidity_ = humidity;
		display();
	}
private:
	void registerWithSubject();
};

static_assert(Observable<CurrentConditionsDisplay>); //TEST! //																								Verify that CurrentConditionsDisplay satisfies both concepts
static_assert(Displayable<CurrentConditionsDisplay>);

class Subject { // The Subject class
	vector<CurrentConditionsDisplay::ObserverImpl *> observers_;
public:
	void registerObserver(CurrentConditionsDisplay::ObserverImpl *o) { observers_.push_back(o); }

	void removeObserver(CurrentConditionsDisplay::ObserverImpl *o) {
		auto it = find(observers_.begin(), observers_.end(), o);
		if (it != observers_.end())
			observers_.erase(it);
	}

	void notifyObservers(double temp, double humidity, double pressure) {
		for (auto observer : observers_)
			observer->update(temp, humidity, pressure);
	}
};

void CurrentConditionsDisplay::registerWithSubject() { weatherData_.registerObserver(&observer_); } // Implementation of registerWithSubject

class WeatherData : public Subject { // The WeatherData class
	double temperature_;
	double humidity_;
	double pressure_;
public:
	void setMeasurements(double temperature, double humidity, double pressure) {
		temperature_ = temperature;
		humidity_ = humidity;
		pressure_ = pressure;
		measurementsChanged();
	}
private:
	void measurementsChanged() { notifyObservers(temperature_, humidity_, pressure_); }
};
#endif //AMAZON_Q_USING_CPP20_CONCEPTS
#pragma endregion //Amazon Q

#pragma region Power up the Weather Station
/* Java
public class WeatherStation {
	public static void main(String[] args) {
		WeatherData weatherData = new WeatherData(); // First, create the WeatherData object.
		CurrentConditionsDisplay currentDisplay = new CurrentConditionsDisplay(weatherData); // Create the three displays and pass them the WeatherData object.
		StatisticsDisplay statisticsDisplay = new StatisticsDisplay(weatherData); // If you don’t want to download the code, you can comment out these two lines and run it.
		ForecastDisplay forecastDisplay = new ForecastDisplay(weatherData);
		weatherData.setMeasurements(80, 65, 30.4f); // Simulate new weather measurements.
		weatherData.setMeasurements(82, 70, 29.2f);
		weatherData.setMeasurements(78, 90, 29.2f);
	}
}
*/

int main() {
	print_file_line();

	WeatherData weatherData; // First, create the WeatherData object.
	CurrentConditionsDisplay currentDisplay(weatherData); // Create the three displays and pass them the WeatherData object.
#ifdef ORIG 
	StatisticsDisplay statisticsDisplay(weatherData); // If you don’t want to download the code, you can comment out these two lines and run it.
	ForecastDisplay forecastDisplay(weatherData);
#endif //ORIG
	weatherData.setMeasurements(80, 65, 30.4); // Simulate new weather measurements.
	weatherData.setMeasurements(82, 70, 29.2);
	weatherData.setMeasurements(78, 90, 29.2);

	return 0;
}
#pragma endregion Power up the Weather Station
#endif //1

#if 1

#include "../../stdafx.h"
using namespace std;

#pragma region Implementing the Weather Station
/* Java
public interface Subject{
	public void registerObserver(Observer o); // Both of these methods take an Observer as an argument; that is, the Observer to be registered or removed.
	public void removeObserver(Observer o);
	public void notifyObservers(); // This method is called to notify all observers when the Subject�s state has changed.
}

public interface Observer{ // The Observer interface is implemented by all observers, so they all have to implement the update() method. Here we�re following Mary and Sue�s lead and passing the measurements to the observers.
	public void update(float temp, float humidity, float pressure); // These are the state values the Observers get from the Subject when a weather measurement changes.
}

public interface DisplayElement { // The DisplayElement interface just includes one method, display(), that we will call when the display element needs to be displayed.
	public void display();
}
*/

struct Observer { // The Observer interface is implemented by all observers, so they all have to implement the update() method. Here we�re following Mary and Sue�s lead and passing the measurements to the observers.
	virtual void update(double temp, double humidity, double pressure) = 0; // These are the state values the Observers get from the Subject when a weather measurement changes.
};

struct Subject {
	virtual void registerObserver(Observer *o) = 0; // Both of these methods take an Observer as an argument; that is, the Observer to be registered or removed.
	virtual void removeObserver(Observer *o) = 0;
	virtual void notifyObservers() = 0; // This method is called to notify all observers when the Subject�s state has changed.
};

class DisplayElement { // Define the DisplayElement interface
public:
	virtual void display() = 0; // Pure virtual function
};
#pragma endregion Implementing the Weather Station

#pragma region Implementing the Subject interface in WeatherData
/* Java
public class WeatherData implements Subject { // WeatherData now implements the Subject interface.
	private ArrayList observers; // We�ve added an ArrayList to hold the Observers, and we create it in the constructor.
	private float temperature;
	private float humidity;
	private float pressure;

	public WeatherData() { observers = new ArrayList();	}

	// Here we implement the Subject Interface.
	public void registerObserver(Observer o) { observers.add(o); } // When an observer registers, we just add it to the end of the list.

	public void removeObserver(Observer o) { // Likewise, when an observer wants to un-register, we just take it off the list.
		int i = observers.indexOf(o);
		if (i >= 0)
			observers.remove(i);
	}

	public void notifyObservers() { // Here�s the fun part; this is where we tell all the observers about the state. Because they are all Observers, we know they all implement update(), so we know how to notify them.
		for (int i = 0; i < observers.size(); i++) {
			Observer observer = (Observer)observers.get(i);
			observer.update(temperature, humidity, pressure);
		}
	}

	public void measurementsChanged() {	notifyObservers(); // We notify the Observers when we get updated measurements from the Weather Station.}

	public void setMeasurements(float temperature, float humidity, float pressure) { // Okay, while we wanted to ship a nice little weather station with each book, the publisher wouldn�t go for it. So, rather than reading actual weather data off a device, we�re going to use this method to test our display elements. Or, for fun, you could write code to grab measurements off the web.
		this.temperature = temperature;
		this.humidity = humidity;
		this.pressure = pressure;
		measurementsChanged();
	}
	// other WeatherData methods here
}
*/

class WeatherData : public Subject { // Implement the WeatherData class
	std::vector<Observer *> observers; // We�ve added an ArrayList to hold the Observers, and we create it in the constructor.
	double temperature;
	double humidity;
	double pressure;
public:
	WeatherData() {}

#pragma region Here we implement the Subject Interface.
	void registerObserver(Observer *o) override { observers.push_back(o); } // When an observer registers, we just add it to the end of the list.

	void removeObserver(Observer *o) override { // Likewise, when an observer wants to un-register, we just take it off the list.
		for (auto it = observers.begin(); it != observers.end(); ++it) {
			if (*it == o) { //TEST
				observers.erase(it);
				break;
			}
		}
	}

	void notifyObservers() override { // Here�s the fun part; this is where we tell all the observers about the state. Because they are all Observers, we know they all implement update(), so we know how to notify them.
		for (Observer *observer : observers)
			observer->update(temperature, humidity, pressure);
	}
#pragma endregion Here we implement the Subject Interface.

	void measurementsChanged() { notifyObservers(); } //TEST //																						We notify the Observers when we get updated measurements from the Weather Station.

	void setMeasurements(double temperature, double humidity, double pressure) { // Okay, while we wanted to ship a nice little weather station with each book, the publisher wouldn�t go for it. So, rather than reading actual weather data off a device, we�re going to use this method to test our display elements. Or, for fun, you could write code to grab measurements off the web.
		this->temperature = temperature; //TEST
		this->humidity = humidity;
		this->pressure = pressure;
		measurementsChanged();
	}
};
#pragma endregion Implementing the Subject interface in WeatherData

#pragma region Now lets build those display elements // Now, let�s build those display elements
/*
public class CurrentConditionsDisplay implements Observer, DisplayElement { // This display implements Observer so it can get changes from the WeatherData object. // It also implements DisplayElement, because our API is going to require all display elements to implement this interface.
	private float temperature;
	private float humidity;
	private Subject weatherData;

	public CurrentConditionsDisplay(Subject weatherData) { // The constructor is passed the weatherData object (the Subject) and we use it to register the display as an observer.
		this.weatherData = weatherData;
		weatherData.registerObserver(this);
	}

	public void update(float temperature, float humidity, float pressure) { // When update() is called, we save the temp and humidity and call display().
		this.temperature = temperature;
		this.humidity = humidity;
		display();
	}

	public void display() { System.out.println("Current conditions : " + temperature + "F degrees and " + humidity + " % humidity"); } // The display() method just prints out the most recent temp and humidity.
}
*/

#if 0
class CurrentConditionsDisplay : public Observer, public DisplayElement { // This display implements Observer so it can get changes from the WeatherData object. // It also implements DisplayElement, because our API is going to require all display elements to implement this interface.
	double temperature = 0;
	double humidity = 0;
	Subject &weatherData_;
public:
	explicit CurrentConditionsDisplay(Subject &weatherData) : weatherData_(weatherData) { weatherData_.registerObserver(this); } // The constructor is passed the weatherData object (the Subject) and we use it to register the display as an observer.

	void update(double temperature, double humidity, double pressure) override { // When update() is called, we save the temp and humidity and call display().
		this->temperature = temperature;
		this->humidity = humidity;
		display();
	}

	void display() override { std::cout << "Current conditions: " << temperature << "F degrees and " << humidity << "% humidity" << std::endl; } // The display() method just prints out the most recent temp and humidity.
};
#endif // 0
#pragma endregion Now lets build those display elements // Now, let�s build those display elements

#pragma region MINE
#ifdef PERPLEXITY_ERR
class CurrentConditionsDisplay : public Observer {
	DisplayElement displayImpl;
	double temperature = 0;
	double humidity = 0;
	Subject &weatherData_;
public:
	explicit CurrentConditionsDisplay(Subject &weatherData) : weatherData_(weatherData) { weatherData_.registerObserver(this); }

	void update(double temperature, double humidity, double) override {
		this->temperature = temperature;
		this->humidity = humidity;
		displayImpl.show(temperature, humidity);
	}
};

struct DisplayElement {
	void show(double temp, double humidity) { cout << "Current conditions: " << temp << "F degrees and " << humidity << "% humidity\n"; }
};
#endif // PERPLEXITY_ERR

#ifdef AMAZON_Q_COMPOSITION_OVER_INHERITANCE
class CurrentConditionsDisplay {
private:
	class ObserverImpl : public Observer {
		CurrentConditionsDisplay &display_;
	public:
		explicit ObserverImpl(CurrentConditionsDisplay &display) : display_(display) {}
		void update(double temp, double humidity, double pressure) override { display_.onUpdate(temp, humidity, pressure); }
	};

	ObserverImpl observer_;
	double temperature_;
	double humidity_;
	Subject &weatherData_;
public:
	explicit CurrentConditionsDisplay(Subject &weatherData)	: observer_(*this), weatherData_(weatherData) {	weatherData_.registerObserver(&observer_); }
	void display() { std::cout << "Current conditions: " << temperature_ << "F degrees and " << humidity_ << "% humidity\n"; }
private:
	void onUpdate(double temp, double humidity, double pressure) {
		temperature_ = temp;
		humidity_ = humidity;
		display();
	}
};
#endif // AMAZON_Q_COMPOSITION_OVER_INHERITANCE

#ifndef AMAZON_Q_INTERFACE_SEGREGATION
class CurrentConditionsDisplay : public Observer {
private:
	double temperature_;
	double humidity_;
	Subject &weatherData_;
public:
	explicit CurrentConditionsDisplay(Subject &weatherData)	: weatherData_(weatherData) { weatherData_.registerObserver(this); }

	void update(double temp, double humidity, double pressure) override {
		temperature_ = temp;
		humidity_ = humidity;
		display();
	}

	void display() { cout << "Current conditions: " << temperature_ << "F degrees and " << humidity_ << "% humidity\n"; }
};
#endif // AMAZON_Q_INTERFACE_SEGREGATION

//class StatisticsDisplay : public Observer, public DisplayElement { // This display implements Observer so it can get changes from the WeatherData object. // It also implements DisplayElement, because our API is going to require all display elements to implement this interface.
//	double temperature = 0;
//	double humidity = 0;
//	Subject &weatherData_;
//public:
//	explicit StatisticsDisplay(Subject &weatherData) : weatherData_(weatherData) { weatherData_.registerObserver(this); } // The constructor is passed the weatherData object (the Subject) and we use it to register the display as an observer.
//
//	void update(double temperature, double humidity, double pressure) override {
//		this->temperature = temperature;
//		this->humidity = humidity;
//		display();
//	}
//
//	void display() override { std::cout << "Current conditions: " << temperature << "F degrees and " << humidity << "% humidity" << std::endl; }
//};
#pragma endregion MINE

#pragma region Power up the Weather Station
/* Java
public class WeatherStation {
	public static void main(String[] args) {
		WeatherData weatherData = new WeatherData();
		CurrentConditionsDisplay currentDisplay = new CurrentConditionsDisplay(weatherData);
		StatisticsDisplay statisticsDisplay = new StatisticsDisplay(weatherData);
		ForecastDisplay forecastDisplay = new ForecastDisplay(weatherData);
		weatherData.setMeasurements(80, 65, 30.4f);
		weatherData.setMeasurements(82, 70, 29.2f);
		weatherData.setMeasurements(78, 90, 29.2f);
	}
}
*/

int main() {
	print_file_line();

#if 1
	WeatherData weatherData;
	CurrentConditionsDisplay currentDisplay(weatherData);
	currentDisplay.update(0, 0, 0); //MINE
	//StatisticsDisplay statisticsDisplay(weatherData);
	//ForecastDisplay forecastDisplay(weatherData);
	weatherData.setMeasurements(80, 65, 30.4);
	weatherData.setMeasurements(82, 70, 29.2);
	weatherData.setMeasurements(78, 90, 29.2);
#endif // 0

	return 0;
}
#pragma endregion Power up the Weather Station
#endif // 1

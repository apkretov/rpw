#if 1

#define ORIG
#undef AMAZON_Q_COMPOSITION
#undef AMAZON_Q_SINGLE_INHERITANCE
#undef AMAZON_Q_USING_CPP20_CONCEPTS

#include <numeric>
#include "../../stdafx.h"
using namespace std;

#pragma region Implementing the Weather Station
/* Java
public interface Subject{
	public void registerObserver(Observer o); // Both of these methods take an Observer as an argument; that is, the Observer to be registered or removed.
	public void removeObserver(Observer o);
	public void notifyObservers(); // This method is called to notify all observers when the Subject's state has changed.
}

public interface Observer{ // The Observer interface is implemented by all observers, so they all have to implement the update() method. Here we're following Mary and Sue's lead and passing the measurements to the observers.
	public void update(float temp, float humidity, float pressure); // These are the state values the Observers get from the Subject when a weather measurement changes.
}

public interface DisplayElement { // The DisplayElement interface just includes one method, display(), that we will call when the display element needs to be displayed.
	public void display();
}
*/

struct Observer { // The Observer interface is implemented by all observers, so they all have to implement the update() method. Here we're following Mary and Sue's lead and passing the measurements to the observers.
	virtual void update(double temp, double humidity, double pressure) = 0; // These are the state values the Observers get from the Subject when a weather measurement changes.
};

#ifndef AMAZON_Q_USING_CPP20_CONCEPTS
struct Subject {
	virtual void registerObserver(Observer *o) = 0; // Both of these methods take an Observer as an argument; that is, the Observer to be registered or removed.
	virtual void removeObserver(Observer *o) = 0;
	virtual void notifyObservers() = 0; // This method is called to notify all observers when the Subject's state has changed.
};
#endif //AMAZON_Q_USING_CPP20_CONCEPTS

struct DisplayElement { // Define the DisplayElement interface
	virtual void display() = 0; // Pure virtual function
};
#pragma endregion Implementing the Weather Station

#pragma region Implementing the Subject interface in WeatherData
/* Java
public class WeatherData implements Subject { // WeatherData now implements the Subject interface.
	private ArrayList observers; // We've added an ArrayList to hold the Observers, and we create it in the constructor.
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

	public void notifyObservers() { // Here's the fun part; this is where we tell all the observers about the state. Because they are all Observers, we know they all implement update(), so we know how to notify them.
		for (int i = 0; i < observers.size(); i++) {
			Observer observer = (Observer)observers.get(i);
			observer.update(temperature, humidity, pressure);
		}
	}

	public void measurementsChanged() {	notifyObservers(); // We notify the Observers when we get updated measurements from the Weather Station.}

	public void setMeasurements(float temperature, float humidity, float pressure) { // Okay, while we wanted to ship a nice little weather station with each book, the publisher wouldn't go for it. So, rather than reading actual weather data off a device, we're going to use this method to test our display elements. Or, for fun, you could write code to grab measurements off the web.
		this.temperature = temperature;
		this.humidity = humidity;
		this.pressure = pressure;
		measurementsChanged();
	}
	// other WeatherData methods here
}
*/

#ifndef AMAZON_Q_USING_CPP20_CONCEPTS
class WeatherData : public Subject { // Implement the WeatherData class
	vector<Observer *> observers; // We've added an ArrayList to hold the Observers, and we create it in the constructor.
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

	void notifyObservers() override { // Here's the fun part; this is where we tell all the observers about the state. Because they are all Observers, we know they all implement update(), so we know how to notify them.
		for (Observer *observer : observers)
			observer->update(temperature, humidity, pressure);
	}
#pragma endregion //Here we implement the Subject Interface.

	void measurementsChanged() { notifyObservers(); } //TEST //																						We notify the Observers when we get updated measurements from the Weather Station.

	void setMeasurements(double temperature, double humidity, double pressure) { // Okay, while we wanted to ship a nice little weather station with each book, the publisher wouldn't go for it. So, rather than reading actual weather data off a device, we're going to use this method to test our display elements. Or, for fun, you could write code to grab measurements off the web.
		this->temperature = temperature; //TEST
		this->humidity = humidity;
		this->pressure = pressure;
		measurementsChanged();
	}
};
#endif //AMAZON_Q_USING_CPP20_CONCEPTS
#pragma endregion Implementing the Subject interface in WeatherData

#pragma region Now lets build those display elements // Now, let's build those display elements
/* Java
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

#ifdef ORIG
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

	void display() override { cout << "Current conditions: " << fixed << setprecision(1) << temperature << "F degrees and " << humidity << "% humidity" << endl; } // The display() method just prints out the most recent temp and humidity.
};

#pragma region MINE

class StatisticsDisplay : public Observer, public DisplayElement { // This display implements Observer so it can get changes from the WeatherData object. // It also implements DisplayElement, because our API is going to require all display elements to implement this interface.
	vector<double> temp_measurs;
	double avg_temp = 0;
	double min_temp = 0;
	double max_temp = 0;
	Subject &weatherData_;
public:
	explicit StatisticsDisplay(Subject &weatherData) : weatherData_(weatherData) { weatherData_.registerObserver(this); } // The constructor is passed the weatherData object (the Subject) and we use it to register the display as an observer.

	void update(double temperature, double humidity, double pressure) override {
		temp_measurs.push_back(temperature);
		avg_temp = accumulate(temp_measurs.begin(), temp_measurs.end(), 0.0) / temp_measurs.size();
		min_temp = *min_element(temp_measurs.begin(), temp_measurs.end());
		max_temp = *max_element(temp_measurs.begin(), temp_measurs.end());
		display();
	}

	void display() override { cout << "Avg/Max/Min temperature = " << fixed << setprecision(1) << avg_temp << '/' << max_temp << '/' << min_temp << '\n'; }
};

class ForecastDisplay : public Observer, public DisplayElement { // This display implements Observer so it can get changes from the WeatherData object. // It also implements DisplayElement, because our API is going to require all display elements to implement this interface.
	double temperature = 0;
	double humidity = 0;
	Subject &weatherData_;
public:
	explicit ForecastDisplay(Subject &weatherData) : weatherData_(weatherData) { weatherData_.registerObserver(this); } // The constructor is passed the weatherData object (the Subject) and we use it to register the display as an observer.

	void update(double temperature, double humidity, double pressure) override {
		this->temperature = temperature + 10;
		this->humidity = min(humidity + 10.0, 100.0);		
		display();
	}

	void display() override { cout << "Forecast: " << temperature << "F degrees and " << humidity << "% humidity" << endl; }
};
#pragma endregion //MINE
#endif //ORIG
#pragma endregion //Now lets build those display elements

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

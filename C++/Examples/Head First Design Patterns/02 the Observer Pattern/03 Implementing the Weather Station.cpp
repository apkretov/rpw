#if 1

#include "../../stdafx.h"
using namespace std;

#pragma region Implementing the Weather Station
/* Java
public interface Subject{
	public void registerObserver(Observer o); // Both of these methods take an Observer as an argument; that is, the Observer to be registered or removed.
	public void removeObserver(Observer o);
	public void notifyObservers(); // This method is called to notify all observers when the Subject’s state has changed.
}

public interface Observer{ // The Observer interface is implemented by all observers, so they all have to implement the update() method. Here we’re following Mary and Sue’s lead and passing the measurements to the observers.
	public void update(float temp, float humidity, float pressure); // These are the state values the Observers get from the Subject when a weather measurement changes.
}

public interface DisplayElement { // The DisplayElement interface just includes one method, display(), that we will call when the display element needs to be displayed.
	public void display();
}
*/

struct Observer { // The Observer interface is implemented by all observers, so they all have to implement the update() method. Here we’re following Mary and Sue’s lead and passing the measurements to the observers.
	virtual void update(double temp, double humidity, double pressure) = 0; // These are the state values the Observers get from the Subject when a weather measurement changes.
};

struct Subject {
	virtual void registerObserver(Observer *o) = 0; // Both of these methods take an Observer as an argument; that is, the Observer to be registered or removed.
	virtual void removeObserver(Observer *o) = 0;
	virtual void notifyObservers() = 0; // This method is called to notify all observers when the Subject’s state has changed.
};

class DisplayElement { // Define the DisplayElement interface
public:
	virtual void display() = 0; // Pure virtual function
};
#pragma endregion Implementing the Weather Station

#pragma region Implementing the Subject interface in WeatherData
/* Java
public class WeatherData implements Subject { // WeatherData now implements the Subject interface.
	private ArrayList observers; // We’ve added an ArrayList to hold the Observers, and we create it in the constructor.
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

	public void notifyObservers() { // Here’s the fun part; this is where we tell all the observers about the state. Because they are all Observers, we know they all implement update(), so we know how to notify them.
		for (int i = 0; i < observers.size(); i++) {
			Observer observer = (Observer)observers.get(i);
			observer.update(temperature, humidity, pressure);
		}
	}

	public void measurementsChanged() {	notifyObservers(); // We notify the Observers when we get updated measurements from the Weather Station.}

	public void setMeasurements(float temperature, float humidity, float pressure) { // Okay, while we wanted to ship a nice little weather station with each book, the publisher wouldn’t go for it. So, rather than reading actual weather data off a device, we’re going to use this method to test our display elements. Or, for fun, you could write code to grab measurements off the web.
		this.temperature = temperature;
		this.humidity = humidity;
		this.pressure = pressure;
		measurementsChanged();
	}
	// other WeatherData methods here
}
*/

class WeatherData : public Subject { // Implement the WeatherData class
	std::vector<Observer *> observers; // We’ve added an ArrayList to hold the Observers, and we create it in the constructor.
	double temperature;
	double humidity;
	double pressure;
public:
	WeatherData() {}

#pragma region Here we implement the Subject Interface.
	void registerObserver(Observer *o) override { observers.push_back(o); } // When an observer registers, we just add it to the end of the list.

	void removeObserver(Observer *o) override { // Likewise, when an observer wants to un-register, we just take it off the list.
		for (auto it = observers.begin(); it != observers.end(); ++it) {
			if (*it == o) { //TEST!
				observers.erase(it);
				break;
			}
		}
	}

	void notifyObservers() override { // Here’s the fun part; this is where we tell all the observers about the state. Because they are all Observers, we know they all implement update(), so we know how to notify them.
		for (Observer *observer : observers)
			observer->update(temperature, humidity, pressure);
	}
#pragma endregion Here we implement the Subject Interface.

	void measurementsChanged() { notifyObservers(); } //TEST //																						We notify the Observers when we get updated measurements from the Weather Station.

	void setMeasurements(double temperature, double humidity, double pressure) { // Okay, while we wanted to ship a nice little weather station with each book, the publisher wouldn’t go for it. So, rather than reading actual weather data off a device, we’re going to use this method to test our display elements. Or, for fun, you could write code to grab measurements off the web.
		this->temperature = temperature; //TEST
		this->humidity = humidity;
		this->pressure = pressure;
		measurementsChanged();
	}
};
#pragma endregion Implementing the Subject interface in WeatherData

#pragma region Now, let’s build those display elements
// ...
#pragma endregion Now, let’s build those display elements

int main() {
	print_file_line();
	return 0;
}
#endif // 1

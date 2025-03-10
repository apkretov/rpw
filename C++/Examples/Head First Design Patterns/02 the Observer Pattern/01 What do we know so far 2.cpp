#if 1

#include <memory>
#include <numeric>
#include <unordered_map>
#include "../../stdafx.h"
using namespace std;

struct Display;

class WeatherData{
	//vector<unique_ptr<Display>> displays;
public:
	int getTemperature() const { /*TO DO: Return a random value.*/ return 0; } // These three methods return the most recent weather measurements for temperature, humidity and barometric pressure respectively. We don�t care HOW these variables are set; the WeatherData object knows how to get updated info from the Weather Station.
	int getHumidity() const { /*TO DO: Return a random value.*/ return 0; }
	int getPressure() const { /*TO DO: Return a random value.*/ return 0; }
	void measurementsChanged() { /*TO DO: Loop through displays.*/ } // This method gets called whenever the weather measurements have been updated. It updates the three displays for current conditions, weather stats, and forecast.
	//void addDisplay(unique_ptr<Display> display) { displays.push_back(std::move(display)); }
};

class Display {
	const string name_;
public:
	explicit Display(string_view name) : name_(name) {}
	~Display() = default;
	string getName() const { return name_; }
	virtual void update(const WeatherData &) = 0;
};

struct CurrentConditions : public Display {
	CurrentConditions() : Display::Display(typeid(CurrentConditions).name()) {}
	
	void update(const WeatherData &wd ) override {
		cout << "Temp: " << wd.getTemperature() << '\n';
		cout << "Humidity: " << wd.getHumidity() << '\n';
		cout << "Pressure: " << wd.getPressure() << '\n';
	};
};

class WeatherStats : public Display {
	vector<int> temp_measuremens;
public:
	WeatherStats() : Display::Display(typeid(WeatherStats).name()) {}

	void update(const WeatherData &wd) override { 
		temp_measuremens.push_back(wd.getTemperature()); 
		cout << "Avg. temp: " << accumulate(temp_measuremens.begin(), temp_measuremens.end(), 0.0) / temp_measuremens.size() << '\n';
		cout << "Min. temp: " << *min_element(temp_measuremens.begin(), temp_measuremens.end()) << '\n';
		cout << "Max. temp: " << *max_element(temp_measuremens.begin(), temp_measuremens.end()) << '\n';
	}
};

class Displays {
	unordered_map<string, unique_ptr<Display>> displays_;
public:
	Displays() = default;

	Displays(initializer_list<unique_ptr<Display>> displays) {
		for (auto &display : displays)
			displays_.emplace(display->getName(), std::move(display));
	}

	void add(unique_ptr<Display> display) { displays_.emplace(display->getName(), std::move(display)); }
	void remove(unique_ptr<Display> display) { displays_.emplace(display->getName(), std::move(display)); }
	unique_ptr<Display> &begin() { return displays_.begin()->second; }
	unique_ptr<Display> &end() { return displays_.end()->second; }
};

int main(int argc, char *argv[]) {
	print_file_line();

	WeatherData wd;
	//Displays displays();

	CurrentConditions cc;
	cc.update(wd);
	cout << '\n';

	WeatherStats ws;
	ws.update(wd);

	return 0;
}
#endif //1
#if 1

#include <memory>
#include <numeric>
#include <unordered_map>
#include "../../stdafx.h"
using namespace std;

class Displays;

class WeatherData{
	Displays &displays_;
public:
	explicit WeatherData(Displays &displays) : displays_(displays) {}
	int getTemperature() const { /*TO DO: Return a random value.*/ return 0; } // These three methods return the most recent weather measurements for temperature, humidity and barometric pressure respectively. We don�t care HOW these variables are set; the WeatherData object knows how to get updated info from the Weather Station.
	int getHumidity() const { /*TO DO: Return a random value.*/ return 0; }
	int getPressure() const { /*TO DO: Return a random value.*/ return 0; }
	void measurementsChanged(); // This method gets called whenever the weather measurements have been updated. It updates the three displays for current conditions, weather stats, and forecast.
};

struct Display {
	~Display() = default;
	virtual void update(const WeatherData &) = 0;
};

struct CurrentConditions : public Display {
	static constexpr const char *name = "CurrentConditions";

	void update(const WeatherData &wd ) override {
		cout << "Temp: " << wd.getTemperature() << '\n';
		cout << "Humidity: " << wd.getHumidity() << '\n';
		cout << "Pressure: " << wd.getPressure() << '\n';
	};
};

class WeatherStats : public Display {
	vector<int> temp_measuremens;
public:
	static constexpr const char *name = "WeatherStats";
	void update(const WeatherData &wd) override { 
		temp_measuremens.push_back(wd.getTemperature()); 
		cout << "Avg. temp: " << accumulate(temp_measuremens.begin(), temp_measuremens.end(), 0.0) / temp_measuremens.size() << '\n';
		cout << "Min. temp: " << *min_element(temp_measuremens.begin(), temp_measuremens.end()) << '\n';
		cout << "Max. temp: " << *max_element(temp_measuremens.begin(), temp_measuremens.end()) << '\n';
	}
};

struct Forecast : public Display {
	static constexpr const char *name = "Forecast";

	void update(const WeatherData &wd) override {
		cout << "Temp forecast: " << wd.getTemperature() + 10 << '\n';
		cout << "Humidity forecast: " << wd.getHumidity() + 10 << '\n';
		cout << "Pressure forecast: " << wd.getPressure() + 10 << '\n';
	};
};

class Displays {
	unordered_map<string, unique_ptr<Display>> displays_;
public:
	Displays() = default;
	Displays(const Displays &) = delete;
	Display &operator=(const Displays &) = delete;
	Displays(Displays &&) = default;
	Displays &operator=(Displays &&) = default;

	void add(string_view display_name, unique_ptr<Display> display) { displays_.emplace(display_name, std::move(display)); }
	void remove(const string &display_name) { displays_.erase(display_name); }
	auto begin() -> decltype(displays_)::iterator{ return displays_.begin(); }
	auto end() -> decltype(displays_)::iterator{ return displays_.end(); }
};

void WeatherData::measurementsChanged() { // This method gets called whenever the weather measurements have been updated. It updates the three displays for current conditions, weather stats, and forecast.
	for (auto &pair : displays_) {
		pair.second->update(*this);
		cout << '\n';
	}
}

int main(int argc, char *argv[]) {
	print_file_line();

	Displays displays;
	displays.add(CurrentConditions::name, make_unique<CurrentConditions>());
	displays.add(WeatherStats::name, make_unique<WeatherStats>());
	displays.add(Forecast::name, make_unique<Forecast>());
	WeatherData wd(displays);
	wd.measurementsChanged();

	displays.remove(WeatherStats::name);
	displays.remove(Forecast::name);
	wd.measurementsChanged();

	return 0;
}
#endif //1
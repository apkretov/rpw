#ifndef MINE

#include <memory>
#include <numeric>
#include <unordered_map>
#include "../../stdafx.h"
using namespace std;

class Displays;

class WeatherData{
	Displays &displays_;

	struct RndMeasurements {
		Rnd rnd_temp{-30, 50};
		Rnd rnd_humidity{0, 100};
		Rnd rnd_pressure{870, 1084}; // The standard air pressure at sea level is 1013.25 millibars (mb). The highest recorded air pressure was 1084 mb in Siberia, and the lowest was 870 mb during a typhoon in the Pacific Ocean.
	};
	RndMeasurements rnd_measurs;

	struct Measurements {
		int temp = 0;
		int humidity = 0;
		int pressure = 0; 
	};
	Measurements measurs;
public:
	explicit WeatherData(Displays &displays) : displays_(displays) {}
	int getTemperature() const noexcept { return measurs.temp; } // These three methods return the most recent weather measurements for temperature, humidity and barometric pressure respectively. We don�t care HOW these variables are set; the WeatherData object knows how to get updated info from the Weather Station.
	int getHumidity() const noexcept { return measurs.humidity; }
	int getPressure() const noexcept { return measurs.pressure; }
	void measurementsChanged(); // This method gets called whenever the weather measurements have been updated. It updates the three displays for current conditions, weather stats, and forecast.
};

struct Display {
	~Display() = default;
	virtual void update(const WeatherData &) = 0;
};

struct CurrentConditions : Display {
	static constexpr const char *name = "CurrentConditions";

	void update(const WeatherData &wd) override {
		cout << "Temp: " << wd.getTemperature() << '\n';
		cout << "Humidity: " << wd.getHumidity() << '\n';
		cout << "Pressure: " << wd.getPressure() << '\n';
	};
};

class WeatherStats : public Display {
	size_t count = 0;
	double running_sum = 0;
	int min_temp = numeric_limits<int>::max();
	int max_temp = numeric_limits<int>::min();
public:
	static constexpr const char *name = "WeatherStats";

	void update(const WeatherData &wd) override {
		++count;
		int temp = wd.getTemperature();
		running_sum += temp;
		min_temp = min(min_temp, temp);
		max_temp = max(max_temp, temp);

		cout << "Avg. temp: " << running_sum / count << '\n';
		cout << "Min. temp: " << min_temp << '\n';
		cout << "Max. temp: " << max_temp << '\n';
	}
};

struct Forecast : Display {
	static constexpr const char *name = "Forecast";

	void update(const WeatherData &wd) override { // TO DO: Split this function and void show().
		cout << "Temp forecast: " << wd.getTemperature()<< '\n';
		cout << "Humidity forecast: " << wd.getHumidity() << '\n';
		cout << "Pressure forecast: " << wd.getPressure() << '\n';
	};
};

class Displays {
	unordered_map<string, unique_ptr<Display>> displays_;
public:
	Displays() = default;
	explicit Displays(size_t count) { displays_.reserve(3); }
	Displays(const Displays &) = delete;
	Display &operator=(const Displays &) = delete;
	Displays(Displays &&) = default;
	Displays &operator=(Displays &&) = default;
	void add(string_view display_name, unique_ptr<Display> display) { displays_.try_emplace(string(display_name), std::move(display)); }
	void remove(const string &display_name) { displays_.erase(display_name); }
	auto begin() noexcept { return displays_.begin(); }
	auto end() noexcept { return displays_.end(); }
	auto begin() const noexcept { return displays_.begin(); }
	auto end() const noexcept { return displays_.end(); }
};

void WeatherData::measurementsChanged() { // This method gets called whenever the weather measurements have been updated. It updates the three displays for current conditions, weather stats, and forecast.
	measurs = Measurements{rnd_measurs.rnd_temp(), rnd_measurs.rnd_humidity(), rnd_measurs.rnd_pressure()}; // Assign all at once to avoid multiple updates.
	for (auto &pair : displays_) {
		pair.second->update(*this);
		cout << '\n';
	}
}

int main(int argc, char *argv[]) {
	print_file_line();

	Displays displays{3};
	displays.add(CurrentConditions::name, make_unique<CurrentConditions>());
	displays.add(WeatherStats::name, make_unique<WeatherStats>());
	displays.add(Forecast::name, make_unique<Forecast>());
	WeatherData wd(displays);
	wd.measurementsChanged();

	displays.remove(Forecast::name);
	wd.measurementsChanged();

	return 0;
}
#endif //MINE
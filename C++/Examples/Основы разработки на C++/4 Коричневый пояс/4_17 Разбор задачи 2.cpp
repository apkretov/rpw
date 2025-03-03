#if 0

#undef VER_1
#define VER_2 //Better

#include "../../stdafx.h"
#include "4_16 Разбор задачи 1.h"
using namespace std;

#ifdef VER_1
struct Trip {
	vector<HotelProvider::BookingID> hotels;
	vector<FlightProvider::BookingID> flights;
};

class TripManager {
	FlightProvider flight_provider;
	HotelProvider hotel_provider;
public:
	using BookingId = string;

	struct BookingData {
		string city_from;
		string city_to;
		string date_from;
		string date_to;
	};

	Trip Book(const BookingData &data) {
		Trip trip;
		try {
			{
				FlightProvider::BookingData data;
				trip.flights.push_back(flight_provider.Book(data));
			}
			{
				HotelProvider::BookingData data;
				trip.hotels.push_back(hotel_provider.Book(data));
			}
			{
				FlightProvider::BookingData data;
				trip.flights.push_back(flight_provider.Book(data));
			}
		}
		catch (...) {
			Cancel(trip); //TEST!!
			throw;
		}
		return trip;
	}

	void Cancel(Trip &trip) {
		for (auto &id : trip.hotels)
			hotel_provider.Cancel(id);
		trip.hotels.clear();
		for (auto &id : trip.flights)
			flight_provider.Cancel(id);
		trip.flights.clear();
	}
};
#endif //VER_1

#ifdef VER_2
class Trip {
	HotelProvider &hotel_provider;
	FlightProvider &flight_provider;
public:
	Trip(HotelProvider &hp, FlightProvider &fp) : hotel_provider(hp), flight_provider(fp) {}
	Trip(const Trip &) = delete;
	Trip(Trip &&) = default;
	Trip &operator=(const Trip &) = delete;
	Trip &operator=(Trip &&) = default;
	~Trip() { Cancel(); } //TEST!! //																													No try-catch! By RAII, it is canceled inside the class when destructed.

	vector<HotelProvider::BookingID> hotels;
	vector<FlightProvider::BookingID> flights;

	void Cancel() { 
		for (auto &id : hotels) 
			hotel_provider.Cancel(id);
		hotels.clear();
		for (auto &id : flights) 
			flight_provider.Cancel(id);
		flights.clear();
	}
};

class TripManager {
	FlightProvider flight_provider;
	HotelProvider hotel_provider;
public:
	using BookingId = string;

	struct BookingData {
		string city_from;
		string city_to;
		string date_from;
		string date_to;
	};

	Trip Book(const BookingData &data) {
		Trip trip(hotel_provider, flight_provider);
		{
			FlightProvider::BookingData data;
			trip.flights.push_back(flight_provider.Book(data));
		}
		{
			HotelProvider::BookingData data;
			trip.hotels.push_back(hotel_provider.Book(data));
		}
		{
			FlightProvider::BookingData data;
			trip.flights.push_back(flight_provider.Book(data));
		}
		return trip;
	}

	void Cancel(Trip &trip) { trip.Cancel(); }
};
#endif //VER_2

int main() {
	PRINT_FILE_LINE();

	try {
		TripManager tm;
		auto trip = tm.Book({});
		tm.Cancel(trip);
	}
	catch (...) {
		cerr << "Exception\n";
	}

	return 0;
}
#endif //1
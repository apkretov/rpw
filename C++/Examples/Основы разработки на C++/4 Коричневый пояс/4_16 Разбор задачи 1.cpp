#if 0

#include "../../stdafx.h"
#include "4_16 Разбор задачи 1.h"
using namespace std;

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

	void Cancel(Trip &trip) {
		for (auto &id : trip.hotels)
			hotel_provider.Cancel(id);
		trip.hotels.clear();
		for (auto &id : trip.flights) 
			flight_provider.Cancel(id);
		trip.flights.clear();
	}
};

#ifdef MINE
void mine() {
	TripManager tm;
	Trip trip;
	try {
		trip = tm.Book({});
	}
	catch (...) {
		cerr << "Exception while booking\n";
	}
	try {
		tm.Cancel(trip);
	}
	catch (...) {
		cerr << "Exception while canceling\n";
	}
}
#endif //MINE

int main() {
	PRINT_FILE_LINE();
	
#ifdef MINE
	mine();
	return 0;
#endif //MINE

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
#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
using std::string;
using std::cerr;
using std::runtime_error;
using std::vector;

class FlightProvider {
	int counter = 0;
public:
	using BookingID = int;

	struct BookingData {
		string city_from;
		string city_to;
		string date;
	};

	BookingID Book(const BookingData &data) {
		++counter;

		if (counter > 1) // Overbooking.
			throw runtime_error("Overbooking");

		cerr << "Flight booking: " << counter << "\n";
		return counter;
	}

	void Cancel(const BookingID &id) {
		--counter;
		cerr << "Cancel flight: " << id << "\n";
	}
};

class HotelProvider {
	int counter = 0;
public:
	using BookingID = int;

	struct BookingData {
		string city;
		string date_from;
		string date_to;
	};

	BookingID Book(const BookingData &data) {
		++counter;
		cerr << "Hotel booking: " << counter << "\n";
		return counter;
	}

	void Cancel(const BookingID &id) {
		--counter;
		cerr << "Cancel hotel: " << id << "\n";
	}
};

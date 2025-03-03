#ifdef MINE //@ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/tree/main/Week_2/05%20Programming%20Assignment

#include <format>
#include <iostream>
#include <map>
#include <queue>
#include "../../stdafx.h"
using namespace std;

struct WrongHotelName : out_of_range {
	using out_of_range::out_of_range;

	const char *what() const noexcept final {
		return (string(out_of_range::what()) + " - Hotel name not found").c_str();
	}
};

struct RoomsBooking {
	int64_t time = 0;
	int clientID = 0;
	int roomCount = 0;
};

#ifdef VER_1
class HotelTotals {
public:
	void increment(int roomCount) {
		++clients_count;
		rooms_count += roomCount;
	}

	void decrement(int roomCount) {
		--clients_count;
		rooms_count -= roomCount;
	}

	int cliensCount() const {
		return clients_count;
	}

	int roomsCount() const {
		return rooms_count;
	}
private:
	int clients_count = 0;
	int rooms_count = 0;
};

class Booking {
public:
	void bookRooms(const string &hotelName, const RoomsBooking &roomsBooking) {
		removeOldBookings(hotelName, roomsBooking.time);
		auto &[rooms_booking, hotel_totals] = hotelsBookings[hotelName];
		rooms_booking.emplace(roomsBooking.time, roomsBooking.clientID, roomsBooking.roomCount);
		hotel_totals.increment(roomsBooking.roomCount);
		currentTime = roomsBooking.time;
	}

	int clientsCount(const string &hotelName) const {
		try {
			if (!hotelsBookings.contains(hotelName))
				return 0;
			return hotelsBookings.at(hotelName).second.cliensCount();
		}
		catch (const out_of_range &e) {
			cerr << e.what() << '\n';
			PRINT_FILE_LINE();
			throw(WrongHotelName(e.what()));
		}
	}

	int roomsCount(const string &hotelName) const {
		try {
			if (!hotelsBookings.contains(hotelName))
				return 0;
			return hotelsBookings.at(hotelName).second.roomsCount();
		}
		catch (const out_of_range &e) {
			cerr << e.what() << '\n';
			PRINT_FILE_LINE();
			throw(WrongHotelName(e.what()));
		}
	}
private:
	map<string, pair<queue<RoomsBooking>, HotelTotals>, less<>> hotelsBookings;
	int64_t currentTime = 0;

	void removeOldBookings(const string &hotelName, int64_t time) { // Remove bookings older than a day before the last booking (current_time).
		if (!hotelsBookings.contains(hotelName))
			return;

		try {
			auto &[roomsBooking, hotelTotals] = hotelsBookings.at(hotelName);
			if (roomsBooking.empty())
				return;
			while (!roomsBooking.empty() && roomsBooking.front().time <= currentTime - 86400) { //TO DO: Use std::lower_bound.
				hotelTotals.decrement(roomsBooking.front().roomCount);
				roomsBooking.pop();
			}
		}
		catch (const out_of_range &e) {
			cerr << e.what() << '\n';
			PRINT_FILE_LINE();
			throw(WrongHotelName(e.what()));
		}
	}
};

#endif //VER_1

#ifndef VER_2
class Hotel {
public:
	void bookRooms(const RoomsBooking &roomsBooking) {
		removeOldBookings(roomsBooking.time);
		bookings.emplace(roomsBooking.time, roomsBooking.clientID, roomsBooking.roomCount);
		++clients_count;
		rooms_count += roomsBooking.roomCount;
	}

	int cliensCount() const {
		return clients_count;
	}

	int roomsCount() const {
		return rooms_count;
	}
private:
	queue<RoomsBooking> bookings;
	int clients_count = 0;
	int rooms_count = 0;

	void removeOldBookings(int64_t currentTime) { // Remove bookings older than a day before the last booking (current_time).
		constexpr int secondsInDay = 86400;
		try {
			if (bookings.empty())
				return;
			while (!bookings.empty() && bookings.front().time <= currentTime - secondsInDay) {
				--clients_count;
				rooms_count -= bookings.front().roomCount;
				bookings.pop();
			}
		}
		catch (const out_of_range &e) {
			cerr << e.what() << '\n';
			PRINT_FILE_LINE();
			throw(WrongHotelName(e.what()));
		}
	}
};

class Booking {
public:
	void bookRooms(const string &hotelName, const RoomsBooking &roomsBooking) {
		hotelsBookings[hotelName].bookRooms(roomsBooking);
	}

	int clientsCount(const string &hotelName) const {
		try {
			if (!hotelsBookings.contains(hotelName))
				return 0;
			return hotelsBookings.at(hotelName).cliensCount();
		}
		catch (const out_of_range &e) {
			cerr << e.what() << '\n';
			PRINT_FILE_LINE();
			throw(WrongHotelName(e.what()));
		}
	}

	int roomsCount(const string &hotelName) const {
		try {
			if (!hotelsBookings.contains(hotelName))
				return 0;
			return hotelsBookings.at(hotelName).roomsCount();
		}
		catch (const out_of_range &e) {
			cerr << e.what() << '\n';
			PRINT_FILE_LINE();
			throw(WrongHotelName(e.what()));
		}
	}
private:
	map<string, Hotel, less<>> hotelsBookings;
};
#endif //VER_2

int main(int argc, char *arg[]) {
	PRINT_FILE_LINE();
	LOG_DURATION("Total");

	try {
		Booking booking;
		int queryCount;

		cin.tie(nullptr);
		cin >> queryCount;
		for (int queryID = 0; queryID < queryCount; ++queryID) {
			string queryType;
			cin >> queryType;
			if (queryType == "BOOK") {
				string hotelName;
				RoomsBooking roomsBooking;
				cin >> roomsBooking.time >> hotelName >> roomsBooking.clientID >> roomsBooking.roomCount;
				booking.bookRooms(hotelName, roomsBooking);
			} else {
				string hotelName;
				cin >> hotelName;
				if (queryType == "CLIENTS")
					cout << format("{}\n", booking.clientsCount(hotelName));
				else if (queryType == "ROOMS")
					cout << format("{}\n", booking.roomsCount(hotelName));
			}
		}
	}
	catch (const WrongHotelName &e) {
		cerr << e.what() << '\n';
		PRINT_FILE_LINE();
	}
	catch (const exception &e) {
		cerr << e.what() << '\n';
		PRINT_FILE_LINE();
	}
	catch (...) {
		cerr << "Error in ";
		PRINT_FILE_LINE();
	}
	return 0;
}
#endif //MINE

#ifdef GITHUB //@ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/blob/main/Week_2/05%20Programming%20Assignment/Solution/booking.cpp
#include <iostream>
#include <cstdint>
#include <map>
#include <queue>
#include "../../stdafx.h"

//----------------------------------------------------------------------------------------------------
struct booking {
	int64_t time;
	int client_id;
	int room_count;
};
//----------------------------------------------------------------------------------------------------
class hotel_info {
public:
	void book(const booking &booking) {
		booking_history.push(booking);
		room_count += booking.room_count;
		++client_booking_counts[booking.client_id];
	}

	int clients(const int64_t &current_time) {
		remove_old_books(current_time);
		return client_booking_counts.size();
	}

	int rooms(const int64_t &current_time) {
		remove_old_books(current_time);
		return room_count;
	}
private:
	static const int SECONDS_IN_DAYS = 86400;

	std::queue<booking> booking_history;
	int room_count = 0;
	std::map<int, int> client_booking_counts;

	void pop_booking() {
		const booking &booking = booking_history.front();
		room_count -= booking.room_count;
		const auto client_stat_it = client_booking_counts.find(booking.client_id);

		if (--client_stat_it->second == 0) {
			client_booking_counts.erase(client_stat_it);
		}
		booking_history.pop();
	}

	void remove_old_books(const int64_t &current_time) {
		while (!booking_history.empty() && booking_history.front().time <= current_time - SECONDS_IN_DAYS) {
			pop_booking();
		}
	}
};
//----------------------------------------------------------------------------------------------------
class booking_manager {
public:
	void book(const int64_t &time, const std::string &hotel_name, int client_id, short int room_count) {
		current_time = time;
		hotels[hotel_name].book({time, client_id, room_count});
	}

	int clients(const std::string &hotel_name) {
		return hotels[hotel_name].clients(current_time);
	}

	int rooms(const std::string &hotel_name) {
		return hotels[hotel_name].rooms(current_time);
	}
private:
	int64_t current_time = 0;
	std::map<std::string, hotel_info> hotels;
};
//----------------------------------------------------------------------------------------------------
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	LOG_DURATION("Total");

	booking_manager manager;

	int query_count;
	std::cin >> query_count;

	for (int query_id = 0; query_id < query_count; ++query_id) {
		std::string query_type;
		std::cin >> query_type;

		if (query_type == "BOOK") {
			int64_t time = 0;
			std::cin >> time;

			std::string hotel_name;
			std::cin >> hotel_name;

			int client_id = 0;
			std::cin >> client_id;

			short int room_count = 0;
			std::cin >> room_count;

			manager.book(time, hotel_name, client_id, room_count);
		} else
			if (query_type == "CLIENTS") {
				std::string hotel_name;
				std::cin >> hotel_name;

				std::cout << manager.clients(hotel_name) << "\n";
			} else
				if (query_type == "ROOMS") {
					std::string hotel_name;
					std::cin >> hotel_name;

					std::cout << manager.rooms(hotel_name) << "\n";
				}
	}
	return 0;
}
//----------------------------------------------------------------------------------------------------
#endif //GITHUB

/*
Система бронирования отелей
Условие

Разработайте систему бронирования отелей, позволяющую бронировать номера клиентами и контролировать спрос владельцами отелей. Ваша программа должна обрабатывать следующие события:

	BOOK time hotel_name client_id room_count — забронировать клиентом client_id room_count номеров в отеле hotel_name в момент времени time. Время измеряется в секундах, отсчитываемых от некоторого момента.
	CLIENTS hotel_name — вывести количество различных клиентов, бронировавших номера в отеле hotel_name за последние сутки. Более формально интересующий диапазон времени описывается следующим образом: пусть current_time — время последнего события BOOK, тогда в данном запросе нужно учесть все события с current_time − 86400 < time <= current_time, где 86400 — количество секунд в сутках. Обратите внимание, что последнее бронирование должно учитываться, а бронирование, случившееся ровно за сутки до него, учитываться не должно.
	ROOMS hotel_name — вывести количество номеров, забронированных за последние сутки в отеле hotel_name.

Формат входных данных

В первой строке вводится количество запросов Q — натуральное число, не превосходящее 10^5. В следующих Q строках в соответствии с описанным выше форматом вводятся запросы. Гарантируется, что:

	time — целое число в диапазоне от −10^18 до 10^18 и не убывает от события к событию.
	hotel_name — строка из латинских букв и цифр, имеющая длину не более 12 символов.
	client_id — натуральное число, не превосходящее 10^9.
	room_count — целое положительное число, не превосходящее 1000.

Формат выходных данных

Для каждого запроса CLIENTS и ROOMS выведите единственное целое число — ответ на запрос. Если указанный в запросе отель пока не имеет ни одного бронирования, выведите 0.
Ограничения

1 секунда на выполнение всех запросов. Все описанные в условии гарантии действительно справедливы для всех тестов, на которых будет запускаться ваша программа. Проверять корректность тестов не нужно.
Пример

Ввод

11
CLIENTS Marriott
ROOMS Marriott
BOOK 10 FourSeasons 1 2
BOOK 10 Marriott 1 1
BOOK 86409 FourSeasons 2 1
CLIENTS FourSeasons
ROOMS FourSeasons
CLIENTS Marriott
BOOK 86410 Marriott 2 10
ROOMS FourSeasons
ROOMS Marriott

Вывод

0
0
2
3
1
1
10

Комментарии к примеру

После бронирования, случившегося в момент времени 86410, в статистике перестают учитываться бронирования, случившиеся в момент времени 10.
Подсказки

Если задача вызывает непреодолимые трудности, вы можете воспользоваться подсказками. Они помогут быстрее сдать задачу, но в итоге вы получите меньше пользы от процесса поиска решения.

Не нужно открывать все подсказки сразу. Используйте их последовательно.

booking-1.pdf

booking-2.pdf

booking-3.pdf

booking-4.pdf

booking-5.pdf
*/
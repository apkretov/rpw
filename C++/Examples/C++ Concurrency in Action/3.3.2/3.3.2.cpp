#pragma region MINE

#include <chrono>
#include <print>
#include <string>
#include <thread>
#include <vector>
#include "Listing 3.13.h"
#include "../../stdafx.h"

using namespace std;

void reader_thread(const dns_cache& cache, const string& domain, int id) {
	for (int i = 0; i < 5; ++i) {
		dns_entry entry = cache.find_entry(domain);
		print("Reader {} (in cycle {}) found IP for {}: {}\n", id, i + 1, domain, entry.get_ip());
		this_thread::sleep_for(chrono::milliseconds(100));
	}
}

void writer_thread(dns_cache& cache, const string& domain, const string& ip, int id) {
	for (int i = 0; i < 3; ++i) {
		cache.update_or_add_entry(domain, dns_entry(ip));
		print("Writer {} (in cycle {}) updated {} to IP {}\n", id, i + 1, domain, ip);
		this_thread::sleep_for(chrono::milliseconds(150));
	}
}

int main() {
	print_file_line();

	dns_cache cache;

	cache.update_or_add_entry("example.com", dns_entry("93.184.216.34")); // Prepopulate cache with some entries
	cache.update_or_add_entry("test.com", dns_entry("192.0.2.1"));

	vector<jthread> readers; // Start reader threads that concurrently read the cache entries
	readers.emplace_back(reader_thread, cref(cache), "example.com", 1);
	readers.emplace_back(reader_thread, cref(cache), "test.com", 2);
	readers.emplace_back(reader_thread, cref(cache), "example.com", 3);

	jthread writer1(writer_thread, ref(cache), "example.com", "93.184.216.35", 1); // Start writer threads that update the cached entries
	jthread writer2(writer_thread, ref(cache), "newsite.com", "198.51.100.42", 2);

	return 0;
}
#pragma endregion //MINE

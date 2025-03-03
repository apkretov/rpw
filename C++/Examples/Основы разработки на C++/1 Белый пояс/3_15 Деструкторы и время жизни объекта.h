#pragma once

#include <iostream>
using namespace std;

int ComputeDistance(const string &source, const string &destination) {
	return source.length() - destination.length();
}

class Route {
public:
	Route() {
		source = "Moscow";
		destination = "Saint-Petersburg";
		UpdateLength();
		cout << this << " Default constructed\n";
	}

	Route(const string &new_source, const string &new_destination) {
		source = new_source;
		destination = new_destination;
		UpdateLength();
		cout << "Constructed\n";
	}

	~Route() {
		printf("%p Destructed\n", this); //ORIG cout << "Destructed\n";
	}

	string GetSource() const {
		return source;
	}

	string GetDestination() const {
		return destination;
	}

	void SetSource(const string &new_source) {
		source = new_source;
		UpdateLength();
	}

	void SetDestination(const string &new_destination) {
		destination = new_destination;
		UpdateLength();
	}
private:
	void UpdateLength() {
		length = ComputeDistance(source, destination);
	}

	string source;
	string destination;
	int length{};
};

#pragma once

#include <iostream>
#include <memory>
using namespace std;

#pragma region Sharpen your pencil
class ChocolateBoiler {
	static unique_ptr<ChocolateBoiler> uniqueInstance;
    bool empty;
    bool boiled;

    ChocolateBoiler() { // This code is only started when the boiler is empty!
        empty = true;
        boiled = false;
    }
public:
	friend unique_ptr<ChocolateBoiler> std::make_unique<ChocolateBoiler>();

	ChocolateBoiler(const ChocolateBoiler &) = delete; 
	void operator=(const ChocolateBoiler &) = delete;
	ChocolateBoiler(ChocolateBoiler &&) = delete;
	ChocolateBoiler &operator=(ChocolateBoiler &&) = delete;

	static ChocolateBoiler *getInstance() { 
		if (uniqueInstance == nullptr)
			uniqueInstance = make_unique<ChocolateBoiler>(); 
		cout << "ChocolateBoiler::getInstance()\n";
		return uniqueInstance.get();
	}

	void fill() {
		cout << "ChocolateBoiler::fill()\n";
		if (isEmpty()) { // To fill the boiler it must be empty, and, once it's full, we set the empty and boiled flags.
			empty = false;
			boiled = false;
			// fill the boiler with a milk/chocolate mixture
		}
	}

	void drain() {
		if (!isEmpty() && isBoiled()) { // To drain the boiler, it must be full (non empty) and also boiled.Once it is drained we set empty back to true.
			// drain the boiled milk and chocolate
			empty = true;
		}
	}

	void boil() {
		if (!isEmpty() && !isBoiled()) { // To boil the mixture, the boiler has to be full and not already boiled.Once it's boiled we set the boiled flag to true.
			// bring the contents to a boil
			boiled = true;
		}
	}

	bool isEmpty() const { return empty; }
	bool isBoiled() const { return boiled; }
};

unique_ptr<ChocolateBoiler> ChocolateBoiler::uniqueInstance = nullptr;
#pragma endregion //Sharpen your pencil

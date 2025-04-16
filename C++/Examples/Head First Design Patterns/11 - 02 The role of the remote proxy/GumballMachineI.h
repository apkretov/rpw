#pragma once
#include <string>
#include <memory>

#pragma region Trae
class IGumballMachine { // The interface for the GumballMachine
public:
	virtual ~IGumballMachine() = default;
	virtual std::string getLocation() const = 0;
	virtual int getCount() const = 0;
	virtual std::string getStateString() const = 0;
};
#pragma endregion //Trae

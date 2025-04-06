#pragma once

#pragma region MINE
class Iterator {
public:
	virtual bool hasNext() = 0;
	virtual void* next() = 0;
	virtual void remove() = 0;
};
#pragma endregion //MINE

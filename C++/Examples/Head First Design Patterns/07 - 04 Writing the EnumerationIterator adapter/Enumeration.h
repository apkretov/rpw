#pragma once

#pragma region MINE
class Enumeration {
public:
	virtual bool hasMoreElements() = 0;
	virtual void* nextElement() = 0;
};
#pragma endregion //MINE

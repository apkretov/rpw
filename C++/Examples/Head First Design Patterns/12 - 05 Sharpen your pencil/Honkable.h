#pragma once

#include <memory>

#pragma region Sharpen your pencil
class Honkable {
public:
	virtual ~Honkable() = default;
	virtual void honk() = 0;
};

using HonkablePtr = std::unique_ptr<Honkable>;
#pragma endregion //Sharpen your pencil

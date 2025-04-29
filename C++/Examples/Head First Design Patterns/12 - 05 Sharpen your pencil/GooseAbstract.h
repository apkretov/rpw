#pragma once

#include <memory>

#pragma region Sharpen your pencil
class AbstractGoose {
public:
	virtual ~AbstractGoose() = default;
	virtual void sound() = 0;
};

using AbstractGoosePtr = std::unique_ptr<AbstractGoose>;
#pragma endregion //Sharpen your pencil

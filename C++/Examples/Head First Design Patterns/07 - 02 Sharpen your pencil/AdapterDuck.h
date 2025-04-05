#pragma once

#include <memory>
#include "Duck.h"
#include "Turkey.h"
using std::shared_ptr;

#pragma region Sharpen your pencil
class DuckAdapter : public Turkey {
	shared_ptr<Duck> duck;
public:
	DuckAdapter(shared_ptr<Duck> duck) : duck(duck) {}
	void gobble() override { duck->quack(); }
	void fly() override { duck->fly(); }
};
#pragma endregion //Sharpen your pencil

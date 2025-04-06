#pragma once

#include "Duck.h"
#include "Turkey.h"

#pragma region Sharpen your pencil
class DuckAdapter : public Turkey {
    Duck& duck;
public:
    DuckAdapter(Duck& duck) : duck(duck) {}
    void gobble() override { duck.quack(); }
    void fly() override { duck.fly(); }
};
#pragma endregion //Sharpen your pencil

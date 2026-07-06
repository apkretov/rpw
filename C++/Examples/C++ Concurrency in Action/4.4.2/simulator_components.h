#pragma once

#pragma region MINE
#include "sender.h"
#include <string>

struct display_enter_card {};
struct display_enter_pin {};

struct verify_pin {
	verify_pin(std::string a, std::string p, messaging::sender r) : acc(a), pin(p), reply_to(r) {}
	std::string acc;
	std::string pin;
	messaging::sender reply_to;
};

struct digit_pressed {
	explicit digit_pressed(char d) : digit(d) {}
	char digit;
};

struct clear_last_pressed {};
struct cancel_pressed {};
#pragma endregion //MINE
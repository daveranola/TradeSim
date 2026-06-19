#pragma once

#include <string>
#include "strategy/Signal.hpp"

struct Trade {
	std::string timestamp;
	std::string symbol;
	SignalType type{ SignalType::HOLD };
	int quantity{ 0 };
	double price{ 0.0 };
};
#pragma once

#include "market/Bar.hpp"
#include "strategy/Signal.hpp"	

class Strategy {
public:
	virtual ~Strategy() = default;
	virtual Signal onBar(const Bar& bar) = 0;
};
#pragma once

#include "market/Bar.hpp"
#include "strategy/Signal.hpp"
#include "trading/Portfolio.hpp"

class PaperBroker {
public:
	bool execute(const Signal& signal, const Bar& bar, Portfolio& portfolio) const;
};
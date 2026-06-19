#pragma once

#include <vector>

#include "market/Bar.hpp"
#include "strategy/Strategy.hpp"
#include "trading/PaperBroker.hpp"
#include "trading/Portfolio.hpp"

class BacktestEngine {
public:	
	BacktestEngine(Strategy& strategy, PaperBroker& broker, Portfolio& portfolio);

	void run(const std::vector<Bar>& bars);

private:
	Strategy& strategy_;
	PaperBroker& broker_;
	Portfolio& portfolio_;
};
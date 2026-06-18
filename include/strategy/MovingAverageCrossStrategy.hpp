#pragma once

#include "strategy/Strategy.hpp"

#include <vector>

class MovingAverageCrossStrategy : public Strategy {
public:
	MovingAverageCrossStrategy(int fastWindow, int slowWindow, int quantity);

	Signal onBar(const Bar& bar) override;

private:
	double averageLast(int window) const;

	int fastWindow_{};
	int slowWindow_{};
	int quantity_{};

	std::vector<double> prices_;
	bool currentlyHolding_{ false };
};
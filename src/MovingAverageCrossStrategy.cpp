#include "strategy/MovingAverageCrossStrategy.hpp"

#include <stdexcept>

MovingAverageCrossStrategy::MovingAverageCrossStrategy(
	int fastWindow, 
	int slowWindow, 
	int quantity) : fastWindow_(fastWindow), 
					slowWindow_(slowWindow), 
					quantity_(quantity) {

	if (fastWindow <= 0 || slowWindow <= 0 || quantity <= 0) {
		throw std::invalid_argument("Windows and quantity must be positive");
	}
	
	if (quantity <= 0) {
		throw std::invalid_argument("Quantity must be positive");
	}
}

Signal MovingAverageCrossStrategy::onBar(const Bar& bar) {
	prices_.push_back(bar.close);

	if (prices_.size() < static_cast<size_t>(slowWindow_)) {
		return Signal{ SignalType::HOLD, 0 };
	}

	double fastAverage = averageLast(fastWindow_);
	double slowAverage = averageLast(slowWindow_);

	if (fastAverage > slowAverage && !currentlyHolding_) {
		currentlyHolding_ = true;
		return Signal{ SignalType::BUY, quantity_ };
	}

	if (fastAverage < slowAverage && currentlyHolding_) {
		currentlyHolding_ = false;
		return Signal{ SignalType::SELL, quantity_ };
	}

	return Signal{ SignalType::HOLD, 0 };
}

double MovingAverageCrossStrategy::averageLast(int window) const {
	double sum = 0.0;

	for (size_t i = prices_.size() - window; i < prices_.size(); ++i) {
		sum += prices_[i];
	}

	return sum / window;
}
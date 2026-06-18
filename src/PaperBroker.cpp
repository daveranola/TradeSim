#include "trading/PaperBroker.hpp"

bool PaperBroker::execute(const Signal& signal, const Bar& bar, Portfolio& portfolio) const {
	if (signal.quantity <= 0) {
		return false;
	}

	if (signal.type == SignalType::BUY) {
		return portfolio.buy(bar.symbol, signal.quantity, bar.close);
	}

	else if (signal.type == SignalType::SELL) {
		return portfolio.sell(bar.symbol, signal.quantity, bar.close);
	}

	return false;
}
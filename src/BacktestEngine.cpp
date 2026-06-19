#include "engine/BacktestEngine.hpp"
#include "trading/Trade.hpp"

#include <iostream>
#include <vector>

BacktestEngine::BacktestEngine(
	Strategy& strategy, 
	PaperBroker& broker, 
	Portfolio& portfolio
) : strategy_(strategy), 
	  broker_(broker), 
	  portfolio_(portfolio) {
}

void BacktestEngine::run(const std::vector<Bar>& bars) {
	double initialCash = portfolio_.cash();
	std::vector<Trade> trades;


	for (const Bar& bar : bars) {
		Signal signal = strategy_.onBar(bar);

		bool executed = broker_.execute(signal, bar, portfolio_);

		if (executed) {
			Trade trade;
			trade.price = bar.close;
			trade.quantity = signal.quantity;
			trade.symbol = bar.symbol;
			trade.timestamp = bar.timestamp;
			trade.type = signal.type;

			trades.push_back(trade);
		}
	}

	if (!bars.empty()) {
		const Bar& lastBar = bars.back();
		double finalValue = portfolio_.totalValue(lastBar.symbol, lastBar.close);
		double returnPercentage = (finalValue - initialCash) / initialCash * 100.0;


		std::cout << "\n--- Backtest Report ---\n";
		std::cout << "Initial Cash: " << initialCash << "\n";
		std::cout << "Final Cash: " << portfolio_.cash() << "\n";
		std::cout << "Final Position: " << portfolio_.position(lastBar.symbol) << "\n";
		std::cout << "Final Value: " << finalValue << "\n";
		std::cout << "Return: " << returnPercentage << "%\n";
		std::cout << "Total Trades: " << trades.size() << "\n";

		std::cout << "\n--- Trades Executed ---\n";
		for (const Trade& trade : trades) {
			std::cout << trade.timestamp << " | " << trade.symbol << " | "
				<< (trade.type == SignalType::BUY ? "BUY" : "SELL")
				<< " | Quantity: " << trade.quantity
				<< " | Price: " << trade.price << "\n";
		}
	}
}
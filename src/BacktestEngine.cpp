#include "engine/BacktestEngine.hpp"

#include <iostream>

BacktestEngine::BacktestEngine(
	Strategy& strategy, 
	PaperBroker& broker, 
	Portfolio& portfolio
) : strategy_(strategy), 
	  broker_(broker), 
	  portfolio_(portfolio) {
}

void BacktestEngine::run(const std::vector<Bar>& bars) {
	for (const Bar& bar : bars) {
		Signal signal = strategy_.onBar(bar);

		bool executed = broker_.execute(signal, bar, portfolio_);

		if (executed) {
			std::cout << bar.timestamp << " ";

			if (signal.type == SignalType::BUY) {
				std::cout << "BUY ";
			} else if (signal.type == SignalType::SELL) {
				std::cout << "SELL ";
			}
			std::cout << signal.quantity
					  << " " << bar.symbol
				      << " at " << bar.close << std::endl;
		}
	}

	if (!bars.empty()) {
		const Bar& lastBar = bars.back();

		std::cout << "\nFinal Cash: " << portfolio_.cash() << "\n";
		std::cout << "Final Position: " << portfolio_.position(lastBar.symbol) << "\n";
		std::cout << "Final Value: "
			<< portfolio_.totalValue(lastBar.symbol, lastBar.close)
			<< "\n";
	}

}
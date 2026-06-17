#include <iostream>
#include "market/CsvMarketDataSource.hpp"

int main() {
	CsvMarketDataSource dataSource;

	std::vector<Bar> bars = dataSource.load("C:/Projects/trade-sim/data/sample.csv", "AAPL");

	for (const Bar& bar : bars) {
		std::cout << "Symbol: " << bar.symbol
			<< ", Timestamp: " << bar.timestamp
			<< ", Open: " << bar.open
			<< ", High: " << bar.high
			<< ", Low: " << bar.low
			<< ", Close: " << bar.close
			<< ", Volume: " << bar.volume
			<< std::endl;
	}

	return 0;
}
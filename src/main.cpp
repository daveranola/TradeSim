#include <iostream>

#include "engine/BacktestEngine.hpp"
#include "market/CsvMarketDataSource.hpp"
#include "strategy/MovingAverageCrossStrategy.hpp"
#include "trading/PaperBroker.hpp"
#include "trading/Portfolio.hpp"

int main() {
    CsvMarketDataSource dataSource;
    std::vector<Bar> bars = dataSource.load("C:\\Projects\\trade-sim\\data\\sample.csv", "AAPL");

    Portfolio portfolio(10000.0);
    PaperBroker broker;
    MovingAverageCrossStrategy strategy(3, 5, 10);

    BacktestEngine engine(strategy, broker, portfolio);
    engine.run(bars);

    return 0;
}
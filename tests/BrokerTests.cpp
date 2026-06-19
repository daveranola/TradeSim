#include <cassert>
#include <cmath>
#include <iostream>

#include "market/Bar.hpp"
#include "strategy/Signal.hpp"
#include "trading/PaperBroker.hpp"
#include "trading/Portfolio.hpp"

bool almostEqual(double a, double b) {
    return std::fabs(a - b) < 0.000001;
}

int main() {
    Portfolio portfolio(1000.0);
    PaperBroker broker;

    Bar bar;
    bar.symbol = "AAPL";
    bar.timestamp = "2024-01-01";
    bar.close = 100.0;

    // Buy 5 AAPL at 100
    Signal buySignal{ SignalType::BUY, 5 };
    bool bought = broker.execute(buySignal, bar, portfolio);

    assert(bought == true);
    assert(almostEqual(portfolio.cash(), 500.0));
    assert(portfolio.position("AAPL") == 5);

    // Hold should do nothing
    Signal holdSignal{ SignalType::HOLD, 0 };
    bool held = broker.execute(holdSignal, bar, portfolio);

    assert(held == false);
    assert(almostEqual(portfolio.cash(), 500.0));
    assert(portfolio.position("AAPL") == 5);

    // Sell 2 AAPL at 100
    Signal sellSignal{ SignalType::SELL, 2 };
    bool sold = broker.execute(sellSignal, bar, portfolio);

    assert(sold == true);
    assert(almostEqual(portfolio.cash(), 700.0));
    assert(portfolio.position("AAPL") == 3);

    // Cannot sell more than owned
    Signal invalidSell{ SignalType::SELL, 10 };
    bool invalidSold = broker.execute(invalidSell, bar, portfolio);

    assert(invalidSold == false);
    assert(almostEqual(portfolio.cash(), 700.0));
    assert(portfolio.position("AAPL") == 3);

    std::cout << "Broker tests passed\n";
    return 0;
}
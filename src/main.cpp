#include <iostream>

#include "market/Bar.hpp"
#include "strategy/Signal.hpp"
#include "trading/Portfolio.hpp"
#include "trading/PaperBroker.hpp"

int main() {
    Portfolio portfolio(10000.0);
    PaperBroker broker;

    Bar bar;
    bar.symbol = "AAPL";
    bar.timestamp = "2024-01-01";
    bar.close = 150.0;

    Signal buySignal;
    buySignal.type = SignalType::BUY;
    buySignal.quantity = 10;

    bool executed = broker.execute(buySignal, bar, portfolio);

    std::cout << std::boolalpha;
    std::cout << "Executed: " << executed << "\n";
    std::cout << "Cash: " << portfolio.cash() << "\n";
    std::cout << "AAPL position: " << portfolio.position("AAPL") << "\n";

    return 0;
}
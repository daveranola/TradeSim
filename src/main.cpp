#include <iostream>

#include "market/Bar.hpp"
#include "strategy/MovingAverageCrossStrategy.hpp"

int main() {
    MovingAverageCrossStrategy strategy(3, 5, 10);

    std::vector<double> prices = { 100, 101, 102, 103, 104, 105 };

    for (double price : prices) {
        Bar bar;
        bar.symbol = "AAPL";
        bar.close = price;

        Signal signal = strategy.onBar(bar);

        std::cout << "Price: " << price << " Signal: ";

        if (signal.type == SignalType::BUY) {
            std::cout << "Buy ";
        }
        else if (signal.type == SignalType::SELL) {
            std::cout << "Sell ";
        }
        else {
            std::cout << "Hold ";
        }

        std::cout << signal.quantity << "\n";
    }

    return 0;
}
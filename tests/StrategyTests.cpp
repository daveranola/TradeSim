#include <cassert>
#include <iostream>
#include <vector>

#include "market/Bar.hpp"
#include "strategy/MovingAverageCrossStrategy.hpp"
#include "strategy/Signal.hpp"

Bar makeBar(double close) {
    Bar bar;
    bar.symbol = "AAPL";
    bar.timestamp = "2024-01-01";
    bar.close = close;
    return bar;
}

int main() {
    MovingAverageCrossStrategy strategy(3, 5, 10);

    // Not enough data yet, so should HOLD
    Signal s1 = strategy.onBar(makeBar(100));
    Signal s2 = strategy.onBar(makeBar(101));
    Signal s3 = strategy.onBar(makeBar(102));
    Signal s4 = strategy.onBar(makeBar(103));

    assert(s1.type == SignalType::HOLD);
    assert(s2.type == SignalType::HOLD);
    assert(s3.type == SignalType::HOLD);
    assert(s4.type == SignalType::HOLD);

    // Now enough data exists:
    // prices = 100, 101, 102, 103, 104
    // fast avg last 3 = (102 + 103 + 104) / 3 = 103
    // slow avg last 5 = (100 + 101 + 102 + 103 + 104) / 5 = 102
    // fast > slow, so BUY
    Signal buySignal = strategy.onBar(makeBar(104));

    assert(buySignal.type == SignalType::BUY);
    assert(buySignal.quantity == 10);

    // Still fast > slow, but already holding, so HOLD
    Signal holdAfterBuy = strategy.onBar(makeBar(105));

    assert(holdAfterBuy.type == SignalType::HOLD);
    assert(holdAfterBuy.quantity == 0);

    // Price drops enough to make fast avg < slow avg, so SELL
    Signal sellSignal = strategy.onBar(makeBar(90));

    assert(sellSignal.type == SignalType::SELL);
    assert(sellSignal.quantity == 10);

    std::cout << "Strategy tests passed\n";
    return 0;
}
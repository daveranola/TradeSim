#include <cassert>
#include <iostream>

#include "trading/Portfolio.hpp"

int main() {
    Portfolio portfolio(1000.0);

    // Can buy when enough cash
    assert(portfolio.buy("AAPL", 5, 100.0) == true);
    assert(portfolio.cash() == 500.0);
    assert(portfolio.position("AAPL") == 5);

    // Cannot buy without enough cash
    assert(portfolio.buy("AAPL", 100, 100.0) == false);
    assert(portfolio.cash() == 500.0);
    assert(portfolio.position("AAPL") == 5);

    // Cannot sell more than owned
    assert(portfolio.sell("AAPL", 10, 100.0) == false);
    assert(portfolio.position("AAPL") == 5);

    // Can sell valid amount
    assert(portfolio.sell("AAPL", 2, 120.0) == true);
    assert(portfolio.position("AAPL") == 3);
    assert(portfolio.cash() == 740.0);

    // Total value
    assert(portfolio.totalValue("AAPL", 100.0) == 1040.0);

    std::cout << "Portfolio tests passed\n";
    return 0;
}
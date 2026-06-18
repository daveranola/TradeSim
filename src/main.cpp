#include <iostream>
#include "trading/Portfolio.hpp"

int main() {
    Portfolio portfolio(10000.0);

    bool bought = portfolio.buy("AAPL", 10, 150.0);

    std::cout << "Bought: " << bought << "\n";
    std::cout << "Cash: " << portfolio.cash() << "\n";
    std::cout << "AAPL position: " << portfolio.position("AAPL") << "\n";
    std::cout << "Total value at 155: " << portfolio.totalValue("AAPL", 155.0) << "\n";

    Portfolio p(1000.0);

    std::cout << p.buy("AAPL", 5, 100.0) << "\n";   // true
    std::cout << p.buy("AAPL", 100, 100.0) << "\n"; // false, not enough cash
    std::cout << p.sell("AAPL", 10, 100.0) << "\n"; // false, not enough shares
    std::cout << p.sell("AAPL", 2, 120.0) << "\n";  // true


    return 0;
}
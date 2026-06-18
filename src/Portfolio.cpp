#include "trading/Portfolio.hpp"

#include <stdexcept>

Portfolio::Portfolio(double initialCash) {
	if (initialCash < 0) {
		throw std::invalid_argument("Initial cash cannot be negative");
	}
	cash_ = initialCash;
}

bool Portfolio::buy(const std::string& symbol, int quantity, double price) {
	if (quantity <= 0 || price <= 0) {
		throw std::invalid_argument("Quantity and price must be positive");
	}

	double cost = quantity * price;

	if (cost > cash_) {
		return false; 
	}

	cash_ -= cost;
	positions_[symbol] += quantity;

	return true;
}

bool Portfolio::sell(const std::string& symbol, int quantity, double price) {
	if (quantity <= 0 || price <= 0) {
		throw std::invalid_argument("Quantity and price must be positive");
	}

	int owned = position(symbol);

	if (owned < quantity) {
		return false; 
	}

	cash_ += quantity * price;
	positions_[symbol] -= quantity;

	if (positions_[symbol] == 0) {
		positions_.erase(symbol);
	}

	return true;
}

double Portfolio::cash() const {
	return cash_;
}

int Portfolio::position(const std::string& symbol) const {
	auto it = positions_.find(symbol);

	if (it == positions_.end()) {
		return 0;
	}

	return it->second;
}

double Portfolio::totalValue(const std::string& symbol, double currentPrice) const {
	return cash_ + position(symbol) * currentPrice;
}
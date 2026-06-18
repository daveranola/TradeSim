#pragma once

#include <string>
#include <unordered_map>

class Portfolio {
public:
	explicit Portfolio(double initialCash);

	bool buy(const std::string& symbol, int quantity, double price);
	bool sell(const std::string& symbol, int quantity, double price);

	double cash() const;
	int position(const std::string& symbol) const;
	double totalValue(const std::string& symbol, double currentPrice) const;

private:
	double cash_;
	std::unordered_map<std::string, int> positions_;
};
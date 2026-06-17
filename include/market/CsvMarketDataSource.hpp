#pragma once

#include <string>
#include <vector>
#include "market/Bar.hpp"

class CsvMarketDataSource {
public:
	std::vector<Bar> load(const std::string& filePath, const std::string& symbol) const;
};
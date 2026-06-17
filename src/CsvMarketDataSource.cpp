#include "market/CsvMarketDataSource.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

std::vector<Bar> CsvMarketDataSource::load(const std::string& filePath, const std::string& symbol) const {
    std::ifstream file(filePath);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open CSV file: " + filePath);
    }

    std::vector<Bar> bars;
    std::string line;

    // Skip header line
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);

        std::string date;
        std::string open;
        std::string high;
        std::string low;
        std::string close;
        std::string adjClose;
        std::string volume;

        std::getline(ss, date, ',');
        std::getline(ss, open, ',');
        std::getline(ss, high, ',');
        std::getline(ss, low, ',');
        std::getline(ss, close, ',');
        std::getline(ss, adjClose, ',');
        std::getline(ss, volume, ',');

        Bar bar;
        bar.symbol = symbol;
        bar.timestamp = date;
        bar.open = std::stod(open);
        bar.high = std::stod(high);
        bar.low = std::stod(low);
        bar.close = std::stod(close);
        bar.volume = std::stol(volume);

        bars.push_back(bar);
    }

    return bars;
}
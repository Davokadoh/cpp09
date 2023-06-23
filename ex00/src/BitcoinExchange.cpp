#include "BitcoinExchange.hpp"
#include <string>
#include <fstream>

BitcoinExchange::BitcoinExchange(void) {
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &ref) {
	*this = ref;
}

BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange &rhs) {
	if (this != &rhs) {
		map = rhs.map;
	}

	return *this;
}

BitcoinExchange::~BitcoinExchange(void) {
}

BitcoinExchange::BitcoinExchange(std::ifstream &file) {
	std::string		line;

	std::getline(file, line); //skip first line
	while (std::getline(file, line)) {
		map.insert(getPair(line, ','));
	}
	file.close();
}

float	BitcoinExchange::getRate(const std::string &date) const {
	std::map<std::string, float>::const_iterator it = map.upper_bound(date);

    if (date < map.begin()->first) {
		throw std::logic_error("bad input => " + date);
	}

	return (it != map.begin())
		? (--it)->second
		: it->second;
}

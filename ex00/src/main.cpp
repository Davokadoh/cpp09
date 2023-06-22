#include "BitcoinExchange.hpp"
#include "KV.hpp"
#include <iostream>
#include <fstream>

int	print_error(const std::string& msg, int code) {
	std::cout << "Error: " << msg << std::endl;
	return code;
}

void	process(const std::string &line, const BitcoinExchange &db) {
	std::pair<std::string, float>	pair;
	std::string						date;
	float							amount;
	float							rate;

	try {
		pair = getPair(line, '|');
		date = pair.first;
		amount = pair.second;

		if (amount > 1000) {
			throw std::logic_error("too large a number.");
		} else if (amount < 0) {
			throw std::logic_error("not a positive number.");
		}

		rate = db.getRate(date);
		std::cout << date << " => " << amount << " = " << amount * rate << std::endl;

	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

int	main(int argc, char *argv[]) {
	std::ifstream	in_file, db_file;
	std::string		line;
	BitcoinExchange	db;

	if (argc < 2) {
		return print_error("need input file.", 1);
	}

	in_file.open(argv[1]);
	if (!in_file.is_open()) {
		return print_error("could not open input file.", 2);
	}

	db_file.open("data.csv");
	if (!db_file.is_open()) {
		in_file.close();
		return print_error("could not open data.csv.", 3);
	}

	try {
		db = BitcoinExchange(db_file);
	} catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return print_error("failed to load data.", 4);
	}

	std::getline(in_file, line); //skip first line
	for (std::string line; std::getline(in_file, line);) {
		process(line, db);
	}

	in_file.close();
}

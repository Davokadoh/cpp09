#include "btc.hpp"

void	process(std::string line, std::map<std::string, float> &map) {
	std::pair<std::string, float>	date_amount;
	float							rate;

	try {
		date_amount = get_pair(line, '|');

		if (date_amount.second > 1000) {
			throw std::logic_error("too large a number.");
		}

		rate = (map.begin() != map.upper_bound(date_amount.first))
			? std::prev(map.upper_bound(date_amount.first))->second
			: map.lower_bound(date_amount.first)->second;

		std::cout << date_amount.first << " => " << date_amount.second
			<< " = " << date_amount.second * rate << std::endl;
	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

bool	load_database(std::map<std::string, float> &map, const std::string &filename) {
	std::string		line;
	std::ifstream	file;

	file.open(filename);
	if (!file.is_open()) {
		return true;
	}

	try {
		std::getline(file, line); //skip first line
		while (std::getline(file, line)) {
			map.insert(get_pair(line, ','));
		}
	} catch (std::exception& e) {
		file.close();
		return true;
	}

	file.close();

	return false;
}

int	main(int argc, char *argv[])
{
	std::string						line;
	std::ifstream					file;
	std::map<std::string, float>	map;

	if (argc < 2) {
		return print_error("could not open file.", 1);
	}

	if (load_database(map, "data.csv")) {
		return print_error("failed to load map.", 2);;
	}

	file.open(argv[1]);
	if (!file.is_open()) {
		return print_error("could not open file.", 3);
	}

	std::getline(file, line); //skip first line
	for (std::string line; std::getline(file, line);) {
		process(line, map);
	}

	file.close();
}

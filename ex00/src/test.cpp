/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <jleroux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:50:15 by jleroux           #+#    #+#             */
/*   Updated: 2023/03/15 15:59:33 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <utility>
#include <map>
#include <cstdlib>
#include <cstdio>
#include <string.h>
#include <cmath>

float	string_to_positive_float(std::string str)
{
	float	result;

	result = std::strtof(str.c_str(), NULL);

	if (result == HUGE_VALF)
		throw std::logic_error("Too large a number.");
	if (result < 0)
		throw std::logic_error("Not a positive number.");

	return result;
}

//format: "date | amount" or "date | rate"
std::pair<std::string, float>	get_pair(std::string line, char sep)
{
	std::pair<std::string, float>	parsed;
	std::string						sub;
	std::tm t = {};

    std::istringstream ss("2011-Februar-18 23:12:34");
    ss.imbue(std::locale("de_DE.utf-8"));
 
    ss >> std::get_time(&t, "%Y-%b-%d %H:%M:%S");
	sub = line.substr(0, line.find(sep));
	parsed.first = sub;
	sub.erase(sub.find_last_not_of(' ') + 1);
	parsed.second = string_to_positive_float(line.substr(line.find(sep) + 1));

	return parsed;
}

std::map<std::string, float>	load_database(void) //inputfilestream
{
	std::map<std::string, float>	database;
	std::string						line;
	std::ifstream					file;

	file.open("data.csv");
	if (!file.is_open())
		throw std::logic_error("Failed to load database.");

	std::getline(file, line); //skip first line
	while (std::getline(file, line))
		database.insert(get_pair(line, ','));
	
	file.close();

	return database;
}

float	get_rate(std::string key, std::map<std::string, float> database)
{
	std::map<std::string, float>::const_iterator	pos;

	pos = database.find(key);
	std::cout << "1st:" << pos->first << std::endl;
	std::cout << "2nd:" << pos->second << std::endl;
	if (pos == database.end())
		throw std::logic_error("Key not found.");

	return pos->second;
}

int	check_input(int argc, char **argv, std::ifstream &input)
{
	if (argc < 2)
		return 1;

	input.open(argv[1]);

	if (!input.is_open())
		return 1;

	return 0;
}

int	main(int argc, char *argv[])
{
	float							rate;
	std::string						line;
	std::ifstream					input;
	std::pair<std::string, float>	prompt;
	std::map<std::string, float>	database;

	if (check_input(argc, argv, input))
		return 1;

	database = load_database();
	std::cout << database.begin()->first << std::endl;
	std::cout << database.begin()->second << std::endl;

	std::getline(input, line); // skip first line
	while (std::getline(input, line))
	{
		prompt = get_pair(line, '|');
		std::cout << "SEARCHING RATE" << std::endl;
		rate = get_rate(prompt.first, database);
		std::cout << prompt.second * rate << std::endl;
	}
}

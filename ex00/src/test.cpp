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
		throw std::logic_error("Error: too large a number.");
	if (result < 0)
		throw std::logic_error("Error: not a positive number.");

	return result;
}

//format: "date | amount" or "date | rate"
std::pair<std::string, float>	get_pair(std::string line, char sep)
{
	std::pair<std::string, float>	parsed;
	std::string						sub;

	sub = line.substr(0, line.find(sep));
	sub.erase(sub.find_last_not_of(' ')+1);
	parsed.first = sub;
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
		throw std::logic_error("Error: failed to load database.");

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
	if (pos == database.end())
		throw std::logic_error("Error: Key not found.");

	return pos->second;
}

int	main(void)
{
	float							rate;
	std::string						line;
	std::pair<std::string, float>	prompt;
	std::map<std::string, float>	database;

	database = load_database();

	line = "2022-03-29 | 10";
	prompt = get_pair(line, '|'); // "2022-03-29 | 10"

	rate = get_rate(prompt.first, database);

	std::cout
		<< prompt.first
		<< " => "
		<< prompt.second
		<< " = "
		<< prompt.second * rate << std::endl;
}

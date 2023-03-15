/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <jleroux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:50:15 by jleroux           #+#    #+#             */
/*   Updated: 2023/03/15 14:50:18 by jleroux          ###   ########.fr       */
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
#include <ctime>

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

std::tm	string_to_date(std::istringstream iss)
{
	std::string	str;
	std::tm		tm;

	//What happens if date is badly formated ?
	std::getline(iss, str, '-');
	tm.tm_year = std::strtol(str.c_str(), NULL, 10) - 1900;
	std::getline(iss, str, '-');
	tm.tm_mon =	 std::strtol(str.c_str(), NULL, 10);
	std::getline(iss, str, '-');
	tm.tm_mday = std::strtol(str.c_str(), NULL, 10);

	if (std::mktime(&tm) == -1)
		throw std::logic_error("Bad input => " + std::string(str));

	return tm;
}

//format: "date | amount" or "date | rate"
std::pair<std::tm, float>	get_pair(std::string line, char sep)
{
	std::pair<std::tm, float>			parsed;

	parsed.first = string_to_date(std::istringstream(line.substr(0, line.find(sep))));
	parsed.second = string_to_positive_float(line.substr(line.find(sep)));

	return parsed;
}

std::map<std::tm, float>	load_database(void) //inputfilestream
{
	std::map<std::tm, float>	database;
	std::string					line;
	std::ifstream				file;

	file.open("data.csv"); //need protection

	std::getline(file, line); //skip first line
	while (std::getline(file, line))
		database.insert(get_pair(line, ','));
	
	file.close();

	return database;
}

int	main(int argc, char *argv[])
{
	float						rate;
	std::ifstream				input;
	std::string					line;
	std::string					time_str;
	std::map<std::tm, float>	database;
	std::pair<std::tm, float>	prompt;

	if (argc < 2)
		return 1;

	input.open(argv[1]); //need protection

	database = load_database();

	std::getline(input, line); //skip first line
	while (std::getline(input, line))
	{
		prompt = get_pair(line, '|');
		rate = database.find(prompt.first)->second;
		//if (rate == database.end())
		//	throw std::logic_error("Key noy found => " + date_str);
		std::cout << prompt.second * rate << std::endl;
	}

	input.close();
}

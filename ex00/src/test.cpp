/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <jleroux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:50:15 by jleroux           #+#    #+#             */
/*   Updated: 2023/04/14 14:45:38 by jleroux          ###   ########.fr       */
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

std::string trim(const std::string& str,
                 const std::string& whitespace = " \t")
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

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
	std::stringstream	ss(line);
    std::string			date_str, value_str;
    float				value;

	std::getline(ss, date_str, sep);
    std::getline(ss, value_str, sep);

    value = string_to_positive_float(value_str);
    return std::make_pair(trim(date_str), value);
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
	return database.lower_bound(key)->second;
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

bool is_valid_date(const std::string &date_str)
{
    std::tm t = {};
	std::istringstream	ss(date_str);

	ss >> std::get_time(&t, "%Y-%m-%d");

	if (ss.fail())
		return true;

	return false;
}

int	main(int argc, char *argv[])
{
	float							rate;
	std::string						line;
	std::ifstream					inputfile;
	std::pair<std::string, float>	prompt;
	std::map<std::string, float>	database;

	if (check_input(argc, argv, inputfile))
		return 1;

	database = load_database();

	std::getline(inputfile, line); // skip first line
	while (std::getline(inputfile, line))
	{
		try
		{
			prompt = get_pair(line, '|');
			if (prompt.second > 1000)
				throw std::logic_error("Too large a number.");
			if (is_valid_date(prompt.first))
				throw std::logic_error("bad input => " + prompt.first);
			rate = get_rate(prompt.first, database);
			std::cout
				<< prompt.first
				<< " => "
				<< prompt.second
				<< " = "
				<< prompt.second * rate << std::endl;
		}
		catch (std::exception &e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}
}

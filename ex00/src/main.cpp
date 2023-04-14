/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <jleroux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:50:15 by jleroux           #+#    #+#             */
/*   Updated: 2023/04/14 17:13:38 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <map>

std::string rtrim(const std::string &s)
{
	size_t end = s.find_last_not_of(" ");
	return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

float	string_to_positive_float(std::string str)
{
	float	result;

	result = std::strtof(str.c_str(), NULL);

	if (result == HUGE_VALF)
		throw std::logic_error("too large a number.");
	if (result < 0)
		throw std::logic_error("not a positive number.");

	return result;
}

bool	check_valid_date(std::string date_str)
{
    std::tm				time = {};
	std::istringstream	iss(date_str);

	if (date_str < "2009-01-02")
		return true;

	iss >> std::get_time(&time, "%Y-%m-%d");

	if (iss.fail())
		return true;

	return false;
}

//format: "date | amount" or "date,rate"
std::pair<std::string, float>	get_pair(std::string line, char sep)
{
	std::stringstream	ss(line);
    std::string			date_str;
	std::string			val_str;
    float				val;

	std::getline(ss, date_str, sep);
    std::getline(ss, val_str, sep);

	if (check_valid_date(date_str))
		throw std::logic_error("bad input => " + date_str);

    val = string_to_positive_float(val_str);
	
	return std::make_pair(rtrim(date_str), val);
}

std::map<std::string, float>	load_database(void)
{
	std::map<std::string, float>	database;
	std::ifstream					file;
	std::string						line;

	file.open("data.csv");

	if (!file.is_open())
		throw std::logic_error("Failed to load database.");

	std::getline(file, line); //skip first line
	while (std::getline(file, line))
		database.insert(get_pair(line, ','));
	
	file.close();

	return database;
}

int	main(int argc, char *argv[])
{
	float							rate;
	std::string						line;
	std::ifstream					inputfile;
	std::pair<std::string, float>	prompt;
	std::map<std::string, float>	database;

	if (argc < 2)
		return 1;

	database = load_database();
	inputfile.open(argv[1]);
	if (!inputfile.is_open())
		return 1;

	std::getline(inputfile, line); // skip first line
	while (std::getline(inputfile, line))
	{
		try
		{
			prompt = get_pair(line, '|');

			if (prompt.second > 1000)
				throw std::logic_error("too large a number.");

			if (database.begin() != database.upper_bound(prompt.first))
				rate = std::prev(database.upper_bound(prompt.first))->second;
			else
				rate = database.lower_bound(prompt.first)->second;

			std::cout
				<< prompt.first << " => "
				<< prompt.second << " = "
				<< prompt.second * rate << std::endl;
		}
		catch (std::exception &e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}

	inputfile.close();
}

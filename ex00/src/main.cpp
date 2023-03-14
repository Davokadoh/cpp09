/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <jleroux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:50:15 by jleroux           #+#    #+#             */
/*   Updated: 2023/03/14 17:48:06 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <utility>

float	string_to_positive_float(std::string str)
{
	float	result;

	result = strtof(str);
	if (result == HUGE_VALF)
		throw tooLargeNumber(); //Error: too large a number.
	if (result < 0)
		throw negativeNumber(); //Error: not a positive number.
	return result;
}

//Error: bad input => 2001-42-42
std::tm	string_to_date(std::string str)
{
	std::string	split;
    std::tm		tm{};

	split[] = str.split('-'); //need protection

	if (split.size() != 3)
		throw badInput(str);

	//Does this throw if bad date inputed ?
	tm.tm_year = strtol(split[0]) - 1900;
	tm.tm_mon = strtol(split[1]);
    tm.tm_mday = strtol(split[2]);
	//Check with std::mktime(&tm); ?

	return tm;
}

//format: "date | amount" or "date | rate"
std::pair<std::tm, float>	get_pair(std::string line, char sep)
{
	std::pair<std::string, std::string>	raw;
	std::pair<std::tm, float>			parsed;

	raw = line.split(sep);	//need protection
	parsed.first = string_to_date(raw.first);
	parsed.second = string_to_positive_float(raw.second);
	return parsed;
}

std::map<std::tm, float>	load_database(FILE *file) //inputfilestream
{
	std::map<std::tm, float>	map;
	std::pair<std::tm, float>	pair;
	std::string					line;

	std::getline(file, line); //skip first line
	while (std::getline(file, line) > 0)
	{
		pair = get_pair(line, ',');
		map.insert(pair.first, pair.second);
	}
	
	return map;
}

int	main(int argc, char *argv[])
{
	float						rate;
	FILE						*file;
	FILE						*database;
	std::map<std::tm, float>	map;
	std::pair<std::tm, float>	input;

	file = fopen(argv[1]); //need protection
	database = fopen("data.csv"); //need protection

	map = load_database(database);

	std::getline(file, line); //skip first line
	while (std::getline(file, line) > 0)
	{
		input = get_pair(line, '|');
		rate = map.find(input.first);
		if (rate == map.end())
			throw keyNotFound(input.first); //Error: key not found => 2001-42-42
		std::cout << input.second * rate << std::endl;
	}

	file.close();
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <jleroux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:50:15 by jleroux           #+#    #+#             */
/*   Updated: 2023/03/14 17:14:20 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <utility>

//Error: not a positive number.
//Error: too large a number.
string_to_positive_float(std::string str)
{
	float	result;

	result = strtof(str); //Does this throw if too big ?
	if (result < 0)
		throw negativeNumber();
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

	return tm;
}

//format: "date | amount" or "date | rate"
std::pair<date_t, float>	get_pair(std::string line)
{
	std::pair<std::string, std::string>	raw;
	std::pair<date_t, float>			parsed;

	raw = line.split('|');	//need protection
	parsed.first = string_to_date(raw.first);
	parsed.second = string_to_positive_float(raw.second);
	return parsed;
}


std::map<date_t, float>	parse(FILE file) //inputfilestream
{
	std::map<date_t, float>		map;
	std::pair<date_t, float>	pair;

	for (each line in file)
	{
		pair = get_pair(line);
		map.insert(pair.first, pair.second);
	}
	
	return map;
}

int	main(int argc, char *argv[])
{
	float					rate;
	FILE					file;
	std::map<date_t, float>	database;
	std::pair<date_t, float>	input;

	file = open(argv[1]); //need protection
	database = parse("data.csv"); //need protection

	for (each line in file)
	{
		input = get_pair(line);
		rate = database.find(input.first); //need to check if no rate found
		std::cout << input.second *rate << std::endl;
	}
	input.close();
}

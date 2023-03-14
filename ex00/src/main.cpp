/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <jleroux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:50:15 by jleroux           #+#    #+#             */
/*   Updated: 2023/03/14 18:00:23 by jleroux          ###   ########.fr       */
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

std::map<std::tm, float>	load_database(void) //inputfilestream
{
	std::map<std::tm, float>	map;
	std::string					line;
	FILE						*file;

	file = fopen("data.csv"); //need protection

	std::getline(file, line); //skip first line
	while (std::getline(file, line) > 0)
		map.insert(get_pair(line, ','));
	
	file.close();

	return map;
}

int	main(int argc, char *argv[])
{
	float						rate;
	FILE						*input;
	std::string					line;
	std::map<std::tm, float>	map;
	std::pair<std::tm, float>	prompt;

	input = fopen(argv[1]); //need protection

	map = load_database(database);

	std::getline(input, line); //skip first line
	while (std::getline(input, line) > 0)
	{
		prompt = get_pair(line, '|');
		rate = map.find(prompt.first);
		if (rate == map.end())
			throw keyNotFound(prompt.first); //Error: key not found => 2001-42-42
		std::cout << prompt.second * rate << std::endl;
	}

	input.close();
}

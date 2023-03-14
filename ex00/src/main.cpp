/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <jleroux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:50:15 by jleroux           #+#    #+#             */
/*   Updated: 2023/03/14 16:43:34 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

//format: "date | amount" or "date | rate"
//Error: not a positive number.
//Error: bad input => 2001-42-42
//Error: too large a number.

std::pair<date_t, float>	get_pair(std::string line)
{
	std::pair<std::string, std::string>	raw;
	std::pair<date_t, float>				parsed;

	raw = line.split('|');
	date = string_to_date(raw.first);
	amount = string_to_positive_float(raw.second);
	check_valid_date(line);
	check_valid_value(line);
	return std::make_pair<date_t, float>(date, amount);
}


std::map<date_t, float>	parse(FILE file) //inputfilestream
{
	std::map<date_t, float>	map;
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

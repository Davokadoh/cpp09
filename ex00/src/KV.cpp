/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KV.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:53:26 by jleroux           #+#    #+#             */
/*   Updated: 2023/06/23 14:53:28 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "KV.hpp"
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

std::string rtrim(const std::string &s) {
	size_t end = s.find_last_not_of(" ");
	return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

float	string_to_positive_float(const std::string &str) {
	float	result;

	result = std::strtof(str.c_str(), NULL);

	if (result == HUGE_VALF) {
		throw std::logic_error("too large a number.");
	} else if (result < 0) {
		throw std::logic_error("not a positive number.");
	}

	return result;
}

bool validDate(const std::string &date_str) {
	std::istringstream iss(date_str);
	std::tm time = {};

    if (date_str.length() != 10) {
        return true;
    }

	int year, month, day;
	char dash1, dash2;
	iss >> year >> dash1 >> month >> dash2 >> day;

	if (iss.fail() || dash1 != '-' || dash2 != '-') {
		return true;
	}

	time.tm_year = year - 1900;
	time.tm_mon = month - 1;
	time.tm_mday = day;

	year = time.tm_year;
	month = time.tm_mon;
	day = time.tm_mday;

	int r = mktime(&time);
	if (r == -1 || (day != time.tm_mday) || (month != time.tm_mon) || (year != time.tm_year)) {
		return true;
	}
	return false;
}

//format: "date | amount" or "date,rate"
std::pair<std::string, float>	getPair(const std::string &line, char sep) {
	std::stringstream	ss(line);
    std::string			date_str;
	std::string			val_str;
    float				val;

	std::getline(ss, date_str, sep);
    std::getline(ss, val_str, '\n');

	date_str = rtrim(date_str);
	if (validDate(date_str)) {
		throw std::logic_error("bad input => " + date_str);
	}

	if (val_str.empty()) {
		throw std::logic_error("bad input => " + date_str);
	}

	val = string_to_positive_float(val_str);

	return std::make_pair(date_str, val);
}

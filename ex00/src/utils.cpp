#include "btc.hpp"

std::string rtrim(const std::string &s)
{
	size_t end = s.find_last_not_of(" ");
	return (end == std::string::npos)
		? ""
		: s.substr(0, end + 1);
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

int	print_error(const std::string& msg, int code)
{
	std::cout << "Error: " << msg << std::endl;
	return code;
}

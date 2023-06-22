#ifndef BTC_HPP
#define BTC_HPP

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>

std::pair<std::string, float>	get_pair(const std::string &line, char sep);
int								print_error(const std::string& msg, int code);

#endif

#ifndef KV_HPP
# define KV_HPP

# include <string>

std::string						getDate(const std::string &line);
std::pair<std::string, float>	getPair(const std::string &line, char separator);

#endif

#ifndef BITCOIN_EXCHANGE_HPP
# define BITCOIN_EXCHANGE_HPP

# include <string>
# include <map>
# include "KV.hpp"

class	BitcoinExchange {
	private:
		std::map<std::string, float>	map;

	public:
		BitcoinExchange(void);
		BitcoinExchange(std::ifstream &file);
		BitcoinExchange(const BitcoinExchange &ref);
		BitcoinExchange	&operator=(const BitcoinExchange &rhs);
		~BitcoinExchange(void);

		float	getRate(const std::string &date) const;
};

#endif

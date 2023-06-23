/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:52:36 by jleroux           #+#    #+#             */
/*   Updated: 2023/06/23 14:52:38 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

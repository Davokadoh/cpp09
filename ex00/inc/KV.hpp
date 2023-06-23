/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KV.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:52:42 by jleroux           #+#    #+#             */
/*   Updated: 2023/06/23 15:22:53 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KV_HPP
# define KV_HPP

# include <string>

std::string						rtrim(const std::string &s)
float							stringToPositive(const std::string &str);
bool							validDate(const std::string &date_str);
std::pair<std::string, float>	getPair(const std::string &line, char sep);

#endif

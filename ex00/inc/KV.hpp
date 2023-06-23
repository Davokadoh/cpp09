/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KV.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:52:42 by jleroux           #+#    #+#             */
/*   Updated: 2023/06/23 14:52:47 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KV_HPP
# define KV_HPP

# include <string>

std::string						getDate(const std::string &line);
std::pair<std::string, float>	getPair(const std::string &line, char separator);

#endif

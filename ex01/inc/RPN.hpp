/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:54:44 by jleroux           #+#    #+#             */
/*   Updated: 2023/06/23 14:54:45 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

#include <string>
#include <stack>
#include <sstream>

class	RPN {
	private:
		RPN(const RPN &ref);
		RPN &operator=(const RPN &rhs);

		double	op(const char op);

		double				a, b;
		std::stack<double>	stack;
		std::string			token;

	public:
		RPN(void);
		~RPN(void);

		double	calculate(const std::string &str);
};

#endif

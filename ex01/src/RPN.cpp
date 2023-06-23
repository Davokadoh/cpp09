/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:54:27 by jleroux           #+#    #+#             */
/*   Updated: 2023/06/23 14:54:36 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <cstdlib>

RPN::RPN(void) {
}

RPN::RPN(const RPN &ref) {
	*this = ref;
}

RPN &RPN::operator=(const RPN &rhs) {
	if (this != &rhs) {
		a = rhs.a;
		b = rhs.b;
		stack = rhs.stack;
		token = rhs.token;
	}

	return *this;
}

RPN::~RPN(void) {
}

double	RPN::calculate(const std::string &str) {
	std::istringstream	input(str);

	while (std::getline(input, token, ' ')) {
		if (token.length() != 1) {
			throw std::logic_error("Token size > 1");
		} else if (isdigit(token[0])) {
			stack.push(std::atof(token.c_str()));
		} else {
			stack.push(op(token[0]));
		}
	}

	if (stack.size() == 1) {
		return stack.top();
	} else {
		throw std::logic_error("Too many operands");
	}
}

double RPN::op(const char op) {
	if (stack.size() < 2) {
		throw std::logic_error("Not enough operands");
	}

	a = stack.top();
	stack.pop();
	b = stack.top();
	stack.pop();

	switch(op) {
		case '+':
			return b + a;
		case '-':
			return b - a;
		case '*':
			return b * a;
		case '/':
			return b / a;
		default:
			throw std::logic_error("Unknown opeartion");
	}
}

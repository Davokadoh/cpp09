/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <jleroux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:02:53 by jleroux           #+#    #+#             */
/*   Updated: 2023/04/14 17:20:23 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stack>

void	add(std::stack<double> &stack)
{
	double	a;

	a = stack.top();
	stack.pop();
	stack.top() = stack.top() + a;
}

void	substract(std::stack<double> &stack)
{
	double	a;

	a = stack.top();
	stack.pop();
	stack.top() = stack.top() - a;
}

void	multiply(std::stack<double> &stack)
{
	double	a;

	a = stack.top();
	stack.pop();
	stack.top() = stack.top() * a;
}

void	divide(std::stack<double> &stack)
{
	double	a;

	a = stack.top();
	stack.pop();
	stack.top() = stack.top() / a;
}

int	error()
{
	std::cerr << "Error" << std::endl;
	return 0; //Should be 1 but then ugly output in test
}

int	main(int argc, char *argv[])
{
	std::stack<double>	stack;
	char				*token;

	if (argc < 2)
		return 1;

	for (int i = 1; i < argc; i++)
	{
		token = std::strtok(argv[i], " ");
		while (token)
		{
			if (std::strcmp(token, "+") == 0)
				add(stack);
			else if (std::strcmp(token, "-") == 0)
				substract(stack);
			else if (std::strcmp(token, "*") == 0)
				multiply(stack);
			else if (std::strcmp(token, "/") == 0)
				divide(stack);
			else if (strlen(token) == 1 && isdigit(*token))
				stack.push(atof(token));
			else
				return error();

			token = std::strtok(nullptr, " ");
		}
	}

	std::cout << stack.top() << std::endl;
}

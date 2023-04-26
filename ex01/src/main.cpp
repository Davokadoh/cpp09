/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <jleroux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:02:53 by jleroux           #+#    #+#             */
/*   Updated: 2023/04/26 11:02:42 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <stack>

int	error(void)
{
	std::cerr << "Error" << std::endl;
	return 0; //0 to unblock makefile
}

int	op(int op, std::stack<double> &stack)
{
	double	a, b;

	if (stack.empty())
		return 1;
	a = stack.top();
	stack.pop();

	if (stack.empty())
		return 1;
	b = stack.top();
	stack.pop();

	switch(op)
	{
		case 0:
			stack.push(b + a);
			break;
		case 1:
			stack.push(b - a);
			break;
		case 2:
			stack.push(b * a);
			break;
		case 3:
			stack.push(b / a);
			break;
		default:
			return 1;
			break;
	}
	return 0;
}

int	main(int argc, char *argv[])
{
	std::stack<double>	stack;
	char				*token;

	if (argc < 2)
		return error();

	for (int i = 1; i < argc; i++)
	{
		token = std::strtok(argv[i], " ");
		while (token)
		{
			if (std::strlen(token) == 1)
			{
				if (std::isdigit(*token))
					stack.push(std::atof(token));
				else if (!std::strcmp(token, "+"))
				{
					if (op(0, stack))
						return error();
				}
				else if (!std::strcmp(token, "-"))
				{
					if (op(1, stack))
						return error();
				}
				else if (!std::strcmp(token, "*"))
				{
					if (op(2, stack))
						return error();
				}
				else if (!std::strcmp(token, "/"))
				{
					if (op(3, stack))
						return error();
				}
			}
			else
				return error();

			token = std::strtok(NULL, " ");
		}
	}

	if (stack.size() == 1)
		std::cout << stack.top() << std::endl;
	else
		return error();
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <jleroux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:02:53 by jleroux           #+#    #+#             */
/*   Updated: 2023/03/14 18:07:28 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	main(int argc, char *argv[])
{
	std::stack	stack;

	for each str
	{
		tokens = str.split(' ');
		for each token in tokens //for (token : tokens)
			stack.push(token);
	}

	while (!stack.empty())
	{
		op = get_operation(stack.top());
		stack.pop();
		first = get_first_operand(stack.top());
		stack.pop();
		second = get_second_operand(stack.top());
		stack.pop();
		res += do_operation(op, first, second);
	}

	std::cout << res << std::endl;
}

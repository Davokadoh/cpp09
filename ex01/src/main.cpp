/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <jleroux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:02:53 by jleroux           #+#    #+#             */
/*   Updated: 2023/06/22 17:58:00 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

int	main(int argc, char *argv[]) {
	RPN	rpn;

	if (argc != 2) {
		std::cerr << "Usage: ./RPN \"operations\"" << std::endl;
		return 0;
	}

	try {
		std::cout << rpn.calculate(std::string(argv[1])) << std::endl;
	} catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

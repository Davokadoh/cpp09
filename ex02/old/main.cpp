/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <jleroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:31:27 by jleroux           #+#    #+#             */
/*   Updated: 2023/06/20 15:40:54 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <iterator>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "PmergeMe.hpp"

template<typename C>
void	print(const C &c) {
	typename C::const_iterator	it;

	for (it = c.begin(); it != c.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void	print_time(size_t size, unsigned long int time, std::string c) {
	std::cout
		<< "Time to process a range of " << size
		<< " elements with std::" << c << " : " << time
		<< " ns" << std::endl;
}

template<typename C>
unsigned long int	chrono(C &c) {
	struct timespec		start, end;
	unsigned long int	delta;

	clock_gettime(CLOCK_REALTIME, &start);
	c = fjsort(c);
	clock_gettime(CLOCK_REALTIME, &end);
	delta = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);

	return delta;
}

int	main(int argc, char *argv[]) {
	std::vector<unsigned int>	vec;
	std::deque<unsigned int>	deq;
	unsigned long int			delta1, delta2;
	int							pos_int;

	if (argc <= 1) {
		std::cout << "Error, argc = " << argc << std::endl;
		return 1;
	}

	//see https://stackoverflow.com/questions/2797813/how-to-convert-a-command-line-argument-to-int
	//Or use istringstream >> may be faster bc stream
	// !(cin >> int) does this fail on input different from int type ?
	for (int i = 1; i < argc; ++i) {
		if (!isdigit(argv[i][0]) && argv[i][0] != '0') {
			std::cout << "Error, not a positive integer" << std::endl;
			return 1;
		}
		pos_int = std::atoi(argv[i]);
		if (pos_int < 0) {
			std::cout << "Error, not a positive integer" << std::endl;
			return 1;
		}
		vec.push_back(pos_int);
		deq.push_back(pos_int);
	}

	std::cout << "Before: ";
	print(vec);

	delta1 = chrono(vec);
	delta2 = chrono(deq);

	std::cout << "After:  ";
	print(vec);
	print_time(vec.size(), delta1, "vector");
	print_time(deq.size(), delta2, "deque");
}

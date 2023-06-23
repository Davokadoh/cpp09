/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <jleroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:31:27 by jleroux           #+#    #+#             */
/*   Updated: 2023/06/23 14:56:45 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "PmergeMe.hpp"

void	printTime(size_t size, std::string c, unsigned long int time) {
	std::cout
		<< "Time to process a range of " << size
		<< " elements with std::" << c << " : " << time
		<< " μs" << std::endl;
}

int	main(int argc, char *argv[]) {
	struct timespec		start, end;
	unsigned long int	delta;
	PmergeMe			tmp;
	PmergeMe			p;

	if (argc < 2) {
		std::cerr << "Error, wrong number of arguments" << std::endl;
		return 0;
	}

	if (tmp.readToVector(argc, argv)) {
		std::cerr << "Error while reading input" << std::endl;
		return 0;
	}
	std::cout << "Before : ";
	tmp.printVector();
	tmp.fjSortVector();
	std::cout << "After  : ";
	tmp.printVector();

	clock_gettime(CLOCK_REALTIME, &start);
	if (p.readToVector(argc, argv)) {
		std::cerr << "Error while reading input" << std::endl;
		return 0;
	}
	p.fjSortVector();
	clock_gettime(CLOCK_REALTIME, &end);
	delta = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
	printTime(argc - 1, "vector", delta);

	clock_gettime(CLOCK_REALTIME, &start);
	if (p.readToDeque(argc, argv)) {
		std::cerr << "Error while reading input" << std::endl;
		return 0;
	}
	p.fjSortDeque();
	clock_gettime(CLOCK_REALTIME, &end);
	delta = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
	printTime(argc - 1, "deque ", delta);
}

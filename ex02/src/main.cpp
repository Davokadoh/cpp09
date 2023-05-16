/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <jleroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:31:27 by jleroux           #+#    #+#             */
/*   Updated: 2023/05/16 13:17:30 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <iterator>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <list>

#define K 256

template<typename Container>
void	print(const Container &container) {
	typename Container::const_iterator	it;

	for (it = container.begin(); it != container.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void	print_time(size_t size, double time, std::string container) {
	std::cout << std::fixed << std::setprecision(1)
		<< "Time to process a range of " << size
		<< " elements with std::" << container << " : " << time
		<< " ns" << std::endl;
}

template<class BidirIt>
BidirIt previous(BidirIt it) {
	std::advance(it, -1);
	return it;
}

template<typename Iterator, typename Container>
void	insertion_sort(Container &container, Iterator begin, Iterator end) {
	for (Iterator it = begin; it != end; ++it) {
		Iterator	key = it;
		while (key != container.begin() && *(key) < *(previous(key))) {
			std::iter_swap(key, previous(key));
			--key;
		}
	}
}

template<typename Iterator, typename Container>
void	merge_insertion_sort(Container &container, Iterator begin, Iterator end) {
	unsigned int	dist = std::distance(begin, end);

	if (dist > K) {
		Iterator mid = begin;
		std::advance(mid, dist / 2);
		merge_insertion_sort(container, begin, mid);
		merge_insertion_sort(container, mid, end);
		std::inplace_merge(begin, mid, end);
	} else {
		insertion_sort(container, begin, end);
	}
}

template<typename Container>
double	chrono(Container &container) {
	struct timespec		start, end;
	double				delta;

	clock_gettime(CLOCK_REALTIME, &start);
	merge_insertion_sort(container, container.begin(), container.end());
	clock_gettime(CLOCK_REALTIME, &end);
	delta = (end.tv_sec * 1000000000UL + end.tv_nsec) -
		(start.tv_sec * 1000000000UL + start.tv_nsec);

	return delta;
}

int	main(int argc, char *argv[]) {
	std::vector<unsigned int>	vec;
	std::list<unsigned int>		lst;
	double						delta1, delta2;
	int							pos_int;

	if (argc <= 2) {
		std::cout << "Error" << std::endl;
		return 1;
	}

	for (int i = 1; i < argc; i++) {
		pos_int = std::atoi(argv[i]);
		if (pos_int < 0) {
			std::cout << "Error" << std::endl;
			return 1;
		}
		vec.push_back(pos_int);
		lst.push_back(pos_int);
	}

	std::cout << "Before: ";
	print(vec);

	delta1 = chrono(vec);
	delta2 = chrono(lst);

	std::cout << "After: ";
	print(vec);
	print_time(vec.size(), delta1, "vector");
	print_time(lst.size(), delta2, "list");
}

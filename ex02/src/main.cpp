/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <jleroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:31:27 by jleroux           #+#    #+#             */
/*   Updated: 2023/06/14 12:58:42 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <iterator>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <list>
#include "fjvec.cpp"
#include "fjlst.cpp"

/*
template<typename C>
void	print(const C &c) {
	typename C::const_iterator	it;

	for (it = c.begin(); it != c.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}
*/

void	print_time(size_t size, double time, std::string c) {
	std::cout << std::fixed << std::setprecision(1)
		<< "Time to process a range of " << size
		<< " elements with std::" << c << " : " << time
		<< " us" << std::endl;
}

/*
template <typename T, template <typename V, typename Allocator = std::allocator<T> > class C>
void	fjsort(C<T> &c) {
	std::vector<std::pair<T, T> >	pairs;
	typename C<T>::value_type		tmp;
	bool							odd;

	if (c.size() < 2)
		return;

	odd = c.size() % 2;
	for (typename C<T>::iterator it = c.begin(); it != c.end(); it++) {
		tmp = *it;
		if (++it == c.end()) {
			break;
		} else {
			pairs.push_back(std::make_pair(tmp, *it));
		}
	}

	for (typename std::vector<std::pair<T, T> >::iterator it = pairs.begin(); it != pairs.end(); it++) {
		if (it->first > it->second)
			std::swap(it->first, it->second);
	}

	//std::sort(pairs.begin(), pairs.end());
	fjsort(pairs);

	c.clear();
	for (typename std::vector<std::pair<T, T> >::iterator it = pairs.begin(); it != pairs.end(); it++) {
		c.push_back(it->first);
	}
	for (typename std::vector<std::pair<T, T> >::iterator it = pairs.begin(); it != pairs.end(); it++) {
		c.insert(std::lower_bound(c.begin(), c.end(), it->second), it->second);
	}
	if (odd) {
		c.insert(std::lower_bound(c.begin(), c.end(), tmp), tmp);
	}
}
*/

template<typename C>
double	chrono(C &c) {
	struct timespec		start, end;
	double				delta;

	clock_gettime(CLOCK_REALTIME, &start);
	fjsort(c, c.size());
	clock_gettime(CLOCK_REALTIME, &end);
	delta = (end.tv_sec * 1000000 + end.tv_nsec) -
		(start.tv_sec * 1000000 + start.tv_nsec);

	return delta;
}

int	main(int argc, char *argv[]) {
	std::vector<int>	vec;
	std::list<int>		lst;
	double						delta1, delta2;
	int							pos_int;


	if (argc <= 2) {
		std::cout << "Error" << argc << std::endl;
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
	delta2 = 0;//chrono(lst);

	std::cout << "After: ";
	print(vec);
	print_time(vec.size(), delta1, "vector");
	print_time(lst.size(), delta2, "list");
}

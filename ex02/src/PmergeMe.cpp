#include "PmergeMe.hpp"
#include <sstream>
#include <iostream>

PmergeMe::PmergeMe(void) {
}

//copy & op =

PmergeMe::~PmergeMe(void) {
}

unsigned int	PmergeMe::jacobstahl(unsigned int n) {
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	else
		return jacobstahl(n-1) + 2*jacobstahl(n-2);
}

bool	PmergeMe::readToVector(int argc, char *argv[]) {
	for (int i = 1; i < argc; ++i) {
		unsigned int		tmp;
		std::stringstream	stream(argv[i]);
		if (!(stream >> tmp)) {
			return true;
		} else if (!stream.eof()) {
			return true;
		}
		vec.push_back(tmp);
	}
	return false;
}

void	PmergeMe::fjSortVector(void) {
	vec = fjSort(vec);
}

void	PmergeMe::printVector(void) {
	for (std::vector<unsigned int>::const_iterator it = vec.begin(); it != vec.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

bool	PmergeMe::readToDeque(int argc, char *argv[]) {
	for (int i = 1; i < argc; ++i) {
		unsigned int		tmp;
		std::stringstream	stream(argv[i]);
		if (!(stream >> tmp)) {
			return true;
		} else if (!stream.eof()) {
			return true;
		}
		deq.push_back(tmp);
	}
	return false;
}

void	PmergeMe::fjSortDeque(void) {
	deq = fjSort(deq);
}

void	PmergeMe::printDeque(void) {
	for (std::deque<unsigned int>::const_iterator it = deq.begin(); it != deq.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

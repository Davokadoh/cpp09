#include <algorithm>
#include <iterator>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <list>

template<typename C>
void	print(const C &c) {
	typename C::const_iterator	it;

	for (it = c.begin(); it != c.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

unsigned int	jacobstahl(unsigned int n) {
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	else
		return jacobstahl(n-1) + 2*jacobstahl(n-2);
}

std::vector<int>	fjsort(std::vector<int> c) {
	if (c.size() < 2)
		return c;

	size_t				i;
	size_t				j;
	size_t const		half_size = c.size() / 2;
	std::vector<int>	a(c.begin(), c.begin() + half_size);
	std::vector<int>	b(c.begin() + half_size, c.end());
	std::vector<int>	sorted_a;
	std::vector<int>	sorted_b;

	for (i = 0; i < a.size(); ++i) {
		if (a[i] < b[i]) {
			std::swap(a[i], b[i]);
		}
	}

	sorted_a = fjsort(a);
	for (i = 0; i < sorted_a.size(); ++i) {
		for (j = 0; j < a.size(); ++j) {
			if (a[j] == sorted_a[i]) {
				sorted_b.push_back(b[j]);
				break;
			}
		}
	}
	if (b.size() > a.size()) {
		sorted_b.push_back(b[b.size()-1]);
	}

	std::cout << "------------------" << std::endl;

	std::cout << "sorted_b[" << 0 << "]: " << sorted_b[0] << std::endl;
	sorted_a.insert(sorted_a.begin(), sorted_b[0]);
	std::cout << "sorted_b[" << 1 << "]: " << sorted_b[1] << std::endl;
	sorted_a.insert(std::lower_bound(sorted_a.begin(), sorted_a.begin()+1, sorted_b[1]), sorted_b[1]);
	j = 3;
	size_t last = 0;
	size_t next = 0;
	size_t jacobIndex = 1;
	for (i = 2; i < sorted_b.size(); ++i) {
		j = std::min(j, sorted_b.size()-1);
		std::cout << "sorted_b[" << j << "]: " << sorted_b[j] << std::endl;
		sorted_a.insert(std::lower_bound(sorted_a.begin(), sorted_a.begin()+j+i, sorted_b[j]), sorted_b[j]);
		--j;
		if (j <= last) {
			//std::cout << "j < last: " << j << "<" << last << std::endl;
			last = next;
			next = jacobstahl(jacobIndex++);
			j = next+1;
		}
	}

	/*
	if (b.size() > a.size()) {
		sorted_a.insert(std::lower_bound(sorted_a.begin(), sorted_a.end(), sorted_b[i]), sorted_a[i]);
	}
	*/

	return sorted_a;
}

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

void	fjsort(std::vector<int> &c, unsigned int n) {
	unsigned int	i;
	unsigned int	j;
	bool			odd;

	odd = n % 2;
	n /= 2;
	for (i = 0; i < n; ++i) {
		if (c[i] < c[i+n]) {
			std::swap(c[i], c[i+n]);
		}
	}

	if (n > 1)
		fjsort(c, n);

	std::cout << n << "---" << std::endl;

	for (j = 0; j < n; ++j) {
		int dst = std::distance(c.begin(), std::lower_bound(c.begin(), c.begin()+2*n-1, c[j+n]));
		for (i = n; i < c.size(); i+=2*n) {
			unsigned int	tmp = c[j+i];
			std::cout << "i: " << i << std::endl;
			print(c);
			c.erase(c.begin()+j+i);
			print(c);
			c.insert(c.begin()+dst+i-n, tmp);
			print(c);
			std::cout << std::endl;
		}
	}
	if (odd) {
		unsigned int	tmp = c[j+n];
		int dst = std::distance(c.begin(), std::lower_bound(c.begin(), c.begin()+2*n, c[j+n]));
			print(c);
			c.erase(c.begin()+j+n);
			print(c);
			c.insert(c.begin()+dst, tmp);
			print(c);
			std::cout << std::endl;
	}
}

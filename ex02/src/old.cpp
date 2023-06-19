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
	unsigned int	half;
	bool			odd;

	odd = n%2;
	half = n/2;
	for (i = 0; i < half; ++i) {
		for (j = 0; j < half; j+=half) {
			if (c[i+j] < c[i+j+half]) {
				std::swap(c[i+j], c[i+j+half]);
			}
		}
	}

	if (half > 0)
		fjsort(c, half);

	std::cout << n << "---" << std::endl;

	for (j = 0; j < half; ++j) {
		int dst = std::distance(c.begin(), std::lower_bound(c.begin(), c.begin()+n, c[j+half]));
		for (i = half; i+j < c.size() && i+dst-half < c.size(); i+=n) {
			unsigned int	tmp = c[j+i];
			//print(c);
			c.erase(c.begin()+j+i);
			//print(c);
			c.insert(c.begin()+dst+i-half, tmp);
			//print(c);
			//std::cout << std::endl;
		}
	}
	if (odd) {
		int dst = std::distance(c.begin(), std::lower_bound(c.begin(), c.begin()+n, c[j+half]));
			unsigned int	tmp = c[j+half];
			//print(c);
			c.erase(c.begin()+j+half);
			//print(c);
			c.insert(c.begin()+dst, tmp);
			print(c);
			std::cout << std::endl;
	}
}

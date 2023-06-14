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

	for (unsigned int j = 0; j < n; j++) {
		int idx = std::distance(c.begin(), std::lower_bound(c.begin(), c.begin()+n, c[n-j]));
		for (i = 2*n-1; i < c.size(); i+=2*n) {
			print(c);
			c.insert(c.begin()+idx+i-1, c[i]);
			print(c);
			c.erase(c.begin()+i+1);
			print(c);
			std::cout << std::endl;
		}
	}

}

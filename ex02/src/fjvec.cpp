#include <algorithm>
#include <iterator>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>

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

	bool				odd;
	size_t				i;
	size_t				j;
	size_t const		half_size = c.size() / 2;
	std::vector<int>	a(c.begin(), c.begin() + half_size);
	std::vector<int>	b(c.begin() + half_size, c.end());
	std::vector<int>	sorted_a;
	std::vector<int>	sorted_b;
	std::vector<int>	done;

	for (i = 0; i < a.size(); ++i) {
		if (a[i] < b[i]) {
			std::swap(a[i], b[i]);
		}
	}

	for (i = 0; i < a.size(); ++i) {
		done.push_back(0);
	}
	sorted_a = fjsort(a);
	odd = b.size() > a.size();
	for (i = 0; i < sorted_a.size(); ++i) {
		for (j = 0; j < a.size(); ++j) {
			if (a[j] == sorted_a[i] && done[j]==0) {
				sorted_b.push_back(b[j]);
				done[j]=1;
				break;
			}
		}
	}
	if (odd) {
		sorted_b.push_back(b[b.size()-1]);
	}

	sorted_a.insert(sorted_a.begin(), sorted_b[0]);
	if (b.size() >= 2) {
		sorted_a.insert(std::lower_bound(sorted_a.begin(), sorted_a.begin()+2, sorted_b[1]), sorted_b[1]);
	}
	j = 3;
	size_t last = 2;
	size_t next = 3;
	size_t jacobIndex = 4;
	for (i = 2; i < sorted_b.size(); ++i) {
		j = std::min(j, sorted_b.size()-1);
		sorted_a.insert(std::lower_bound(sorted_a.begin(), sorted_a.begin()+j+i, sorted_b[j]), sorted_b[j]);
		if (j <= last) {
			last = next+1;
			next = jacobstahl(jacobIndex++);
			j = next+1;
		}
		--j;
	}

	return sorted_a;
}

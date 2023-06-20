#include "PmergeMe.hpp"

std::vector<unsigned int>	fjsort(std::vector<unsigned int> c) {
	std::vector<unsigned int>	d(c);
	if (c.size() < 2)
		return d;

	std::size_t					i;
	std::size_t					j;
	std::size_t 				last;
	std::size_t 				next;
	std::size_t 				jacobIndex;
	std::size_t const			half_size = c.size() / 2;
	std::vector<unsigned int>	a(c.begin(), c.begin() + half_size);
	std::vector<unsigned int>	b(c.begin() + half_size, c.end());
	std::vector<unsigned int>	sorted_a;
	std::vector<unsigned int>	sorted_b;
	std::vector<unsigned int>	done(a.size(), 0);

	for (i = 0; i < a.size(); ++i) {
		if (a[i] < b[i]) {
			std::swap(a[i], b[i]);
		}
	}

	sorted_a = fjsort(a);
	for (i = 0; i < sorted_a.size(); ++i) {
		for (j = 0; j < a.size(); ++j) {
			if (a[j] == sorted_a[i] && done[j]==0) {
				sorted_b.push_back(b[j]);
				done[j]=1;
				break;
			}
		}
	}
	if (b.size() > a.size()) {
		sorted_b.push_back(b[b.size()-1]);
	}

	sorted_a.insert(sorted_a.begin(), sorted_b[0]);
	if (b.size() >= 2) {
		sorted_a.insert(std::lower_bound(sorted_a.begin(), sorted_a.begin()+2, sorted_b[1]), sorted_b[1]);
	}
	j = 3;
	last = 2;
	next = 3;
	jacobIndex = 4;
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

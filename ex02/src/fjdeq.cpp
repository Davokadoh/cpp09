#include <algorithm>
#include <iterator>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <deque>

std::deque<int>	fjsort(std::deque<int> c) {
	if (c.size() < 2)
		return c;

	bool				odd;
	size_t				i;
	size_t				j;
	size_t const		half_size = c.size() / 2;
	std::deque<int>	a(c.begin(), c.begin() + half_size);
	std::deque<int>	b(c.begin() + half_size, c.end());
	std::deque<int>	sorted_a;
	std::deque<int>	sorted_b;
	std::deque<int>	done;

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

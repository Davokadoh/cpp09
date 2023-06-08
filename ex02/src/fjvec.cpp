#include <algorithm>
#include <iterator>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <list>

template<typename T>
void	fjsort(std::vector<T> &c) {
	std::vector<std::pair<T, T> >	pairs;
	T		tmp;
	bool									odd;

	if (c.size() < 2)
		return;

	odd = c.size() % 2;
	for (typename std::vector<T>::iterator it = c.begin(); it != c.end(); it++) {
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

	fjsort(pairs);
	//std::sort(pairs.begin(), pairs.end());

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
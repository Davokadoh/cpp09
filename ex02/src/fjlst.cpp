#include <algorithm>
#include <iterator>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <list>

template<typename T>
void	fjsort(std::list<T> &c) {
	std::list<std::pair<T, T> >	pairs;
	typename std::list<T>::value_type		tmp;
	bool									odd;

	if (c.size() < 2)
		return;

	odd = c.size() % 2;
	for (typename std::list<T>::iterator it = c.begin(); it != c.end(); it++) {
		tmp = *it;
		if (++it == c.end()) {
			break;
		} else {
			pairs.push_back(std::make_pair(tmp, *it));
		}
	}

	for (typename std::list<std::pair<T, T> >::iterator it = pairs.begin(); it != pairs.end(); it++) {
		if (it->first > it->second)
			std::swap(it->first, it->second);
	}

	//fjsort(pairs);
	std::sort(pairs.begin(), pairs.end());

	c.clear();
	for (typename std::list<std::pair<T, T> >::iterator it = pairs.begin(); it != pairs.end(); it++) {
		c.push_back(it->first);
	}
	for (typename std::list<std::pair<T, T> >::iterator it = pairs.begin(); it != pairs.end(); it++) {
		c.insert(std::lower_bound(c.begin(), c.end(), it->second), it->second);
	}
	if (odd) {
		c.insert(std::lower_bound(c.begin(), c.end(), tmp), tmp);
	}
}

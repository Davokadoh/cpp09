/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <jleroux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:31:27 by jleroux           #+#    #+#             */
/*   Updated: 2023/04/25 16:31:15 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <iterator>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>

#define K 4

template<typename Container>
void print(const Container& container)
{
	typename Container::const_iterator	it;

    for (it = container.begin(); it != container.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

void	print_time(size_t size, double time1, double time2) //time in ns
{
	std::cout
		<< "Time to process a range of " << size
		<< " elements with std::vector : " << time1 / 1000
		<< " us" << std::endl;

	std::cout
		<< "Time to process a range of " << size
		<< " elements with std::list : " << time2 / 1000
		<< " us" << std::endl;
}

template<class BidirIt>
BidirIt prev(BidirIt it, typename std::iterator_traits<BidirIt>::difference_type n = 1)
{
    std::advance(it, -n);
    return it;
}

template<typename Iterator, typename Container>
void	insertion_sort(Container &container, Iterator begin, Iterator end)
{
	Iterator	key;

	for (Iterator it = begin; it != end; ++it)
	{
        key = it;
		while (key != container.begin() && *(key) < *(prev(key)))
		{
            std::iter_swap(key, prev(key));
            --key;
        }
	}
}

template<typename Iterator, typename Container>
void	merge_insertion_sort(Container &container, Iterator begin, Iterator end)
{
	unsigned int	dist = std::distance(begin, end);
	if (dist > K)
	{
		Iterator mid = begin;
		std::advance(mid, dist / 2);
		merge_insertion_sort(container, begin, mid);
		merge_insertion_sort(container, mid, end);
		std::inplace_merge(begin, mid, end);
	}
	else
	{
		insertion_sort(container, begin, end);
	}
}

int	error(void)
{
	std::cout << "Error" << std::endl;
	return 1;
}

int	main(int argc, char *argv[])
{
	std::vector<unsigned int>	vec;
	std::list<unsigned int>		lst;
	struct timespec				start1, end1, start2, end2;
	double						duration1, duration2;
	int							pos_int;

	if (argc <= 2)
			return (error());

	for (int i = 1; i < argc; i++)
	{
		pos_int = std::atoi(argv[i]);
		if (pos_int < 0)
			return (error());
		vec.push_back(pos_int);
		lst.push_back(pos_int);
	}

	std::cout << "Before: " <<std::endl;
	print(vec);

    clock_gettime(CLOCK_REALTIME, &start1);
	merge_insertion_sort(vec, vec.begin(), vec.end());
    clock_gettime(CLOCK_REALTIME, &end1);
	duration1 = static_cast<double>(end1.tv_sec - start1.tv_sec) * 1000000000UL +
                      static_cast<double>(end1.tv_nsec - start1.tv_nsec);

    clock_gettime(CLOCK_REALTIME, &start2);
	merge_insertion_sort(lst, lst.begin(), lst.end());
    clock_gettime(CLOCK_REALTIME, &end2);
	duration2 = static_cast<double>(end2.tv_sec - start2.tv_sec) * 1000000000UL +
                      static_cast<double>(end2.tv_nsec - start2.tv_nsec);

	std::cout << "After: " <<std::endl;
	print(vec);
	print_time(vec.size(), duration1, duration2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <jleroux@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:31:27 by jleroux           #+#    #+#             */
/*   Updated: 2023/04/12 16:14:19 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

{
	void	print(std::vector<unsigned int> vec)
	{
		for (int i = 0; i < argc; i++)
			std::cout << vec[i] << " ";
		std::cout << std::endl;
	}

	void	print_time(size_t size, micro_sec time1, micro_sec time2)
	{
		std::cout
			<< "Time to process a range of " << size
			<< " elements with std::vector : " << time1
			<< " us" << std::endl;

		std::cout
			<< "Time to process a range of " << size
			<< " elements with std::list : " << time2
			<< " us" << std::endl;
	}

	micro_sec	chrono(void *function_ptr, std::vector &vec)
	{
		micro_sec	start = now();
		function_ptr(vec);
		return now() - start;
	}
}

void	make_pairs()
{
	vecA = vec[0..vec.size()/2];
	vecB = vec[vec.size()/2..vec.size()];
	/*
	for (unsigned int it = vec.begin(); it < begin.end(); it += 2)
	{

	}
	*/
}

void	merge_insertion_sort_vec(std::vector &vec)
{
	std::vector<std::vector<unsigned int>>	a;
	unsigned int							solo;

	//if odd, save last value
	//make pairs
	//sort inside pairs
	//sort among pairs.first
	//sort jacobsthal
}

int	main(int argc, char *argv[])
{
	std::vector<unsigned int>	vec;
	std::list<unsigned int>		lst;

	if (argc <= 2)
		return 1;

	for (int i = 1; i < argc; i++)
	{
		vec.push(argv[i]);
		lst.push_back(argv[i]);
	}

	print(vec);

	time1 = chrono(merge_insertion_sort_vec, vec);
	time2 = chrono(merge_insertion_sort_lst, lst);

	assert(vec == list);

	print(vec);
	print_time(vec.size(), time1, time2);
}

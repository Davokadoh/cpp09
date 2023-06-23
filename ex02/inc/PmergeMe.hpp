#ifndef PMERGE_ME
# define PMERGE_ME

# include <vector>
# include <deque>

class	PmergeMe {
	private:
		PmergeMe(const PmergeMe &ref);
		PmergeMe	&operator=(const PmergeMe &rhs);

		unsigned int				jacobstahl(unsigned int n);
		std::vector<unsigned int>	fjSort(std::vector<unsigned int> &c);
		std::vector<unsigned int>	sortByPair(std::vector<unsigned int> &a, std::vector<unsigned int> &sorted_a, std::vector<unsigned int> &b);
		std::deque<unsigned int>	fjSort(std::deque<unsigned int> &v);
		std::deque<unsigned int>	sortByPair(std::deque<unsigned int> &a, std::deque<unsigned int> &sorted_a, std::deque<unsigned int> &b);

		std::vector<unsigned int>	vec;
		std::deque<unsigned int>	deq;

	public:
		PmergeMe(void);
		~PmergeMe(void);

		bool	readToVector(int argc, char *argv[]);
		void	fjSortVector(void);
		void	printVector(void);

		bool	readToDeque(int argc, char *argv[]);
		void	fjSortDeque(void);
		void	printDeque(void);
};

#endif

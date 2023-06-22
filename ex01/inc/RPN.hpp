#ifndef RPN_HPP
# define RPN_HPP

#include <string>
#include <stack>
#include <sstream>

class	RPN {
	private:
		RPN(const RPN &ref);
		RPN &operator=(const RPN &rhs);

		double	op(const char op);

		double				a, b;
		std::stack<double>	stack;
		std::string			token;

	public:
		RPN(void);
		~RPN(void);

		double	calculate(const std::string &str);
};

#endif

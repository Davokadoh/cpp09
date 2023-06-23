unsigned int	jacobstahl(unsigned int n) {
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	else
		return jacobstahl(n-1) + 2*jacobstahl(n-2);
}

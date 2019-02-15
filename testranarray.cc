#include "ranarray.h"

int main()
{
	RandVector<int> rvi;
	std::cout << rvi.uniform(10, 1, 100) << std::endl;
	std::cout << rvi.ordered(10, 10, 100) << std::endl;
	std::cout << rvi.locally_ordered(10, 10, 100, 3) << std::endl;
	std::cout << rvi.locally_permuted(20, 0, 100, 6, 2, 3) << std::endl;


	std::cout << "****************************" << std::endl;

	RandVector<double> rvd;
	std::cout << rvd.uniform(10, 10, 100) << std::endl;
	std::cout << rvd.ordered(10, 10, 100) << std::endl;
	std::cout << rvd.locally_ordered(10, 10, 100, 3) << std::endl;
	std::cout << rvd.locally_permuted(20, 0, 100, 6, 2, 3) << std::endl;

	std::cout << "****************************" << std::endl;

	RandVector<std::string> rvs;
	std::cout << rvs.uniform(10, 10, 10) << std::endl;
	std::cout << rvs.ordered(10, 10, 10) << std::endl;
	std::cout << rvs.locally_ordered(10, 10, 10, 3) << std::endl;
	std::cout << rvs.locally_permuted(20, 10, 10, 6, 2, 3) << std::endl;
}
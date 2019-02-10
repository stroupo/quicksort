#include <random>
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

template<typename T>
std::ostream &operator <<(std::ostream &os, const std::vector<T> &v)
{
	os << "( ";
	for(auto &e: v) os << e << " ";
	os << ")";
	return os;
}
std::vector<int> uniform_random_vector(int size, int min, int max)
{
	// std::mt19937 engine{std::random_device{}()};
	std::mt19937 engine{0};
	std::uniform_int_distribution<int> dist(min, max);
	std::vector<int> v(size);
	auto generator = [&dist, &engine](){return dist(engine);};
	std::generate(begin(v), end(v), generator);
	return v;
}
std::vector<int> shuffled_vector(int size, int min, int max)
{
	return uniform_random_vector(size, min, max);
}
std::vector<int> ordered_vector(int size, int min, int max, bool reverse=false)
{
	std::vector<int> vec = uniform_random_vector(size, min, max);
	auto cmp = [reverse](int i, int j){return (reverse) ? (i > j) : (i < j);};
	std::sort(vec.begin(), vec.end(), cmp);
	return vec;
}
int main()
{
	std::vector<int> urv = uniform_random_vector(10, 1, 5);
	std::cout << urv << std::endl;

	std::vector<int> urv_s = ordered_vector(10, 1, 5, false);
	std::cout << urv_s << std::endl;
	
	std::vector<int> urv_r = ordered_vector(10, 1, 5, true);
	std::cout << urv_r << std::endl;
}
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
std::vector<int> locally_ordered_vector(int size, int min, int max, int window)
{
	std::vector<int> vec = shuffled_vector(size, min, max);
	auto it = vec.begin();
	auto ed = it + window;
	while(ed < vec.end())
	{
		std::sort(it, ed);
		it = ed;
		ed += window;
	}
	std::sort(it, vec.end());
	return vec;
}
void vector_permutation(std::vector<int> &vec, std::vector<int>::iterator left, std::vector<int>::iterator right, int permutations)
{
	std::mt19937 engine{std::random_device{}()};
	auto distance = std::distance(left, right);
	std::uniform_int_distribution<int> dist(0, distance);

	for(int i=0; i<permutations; i++)
	{
		auto a = left + dist(engine);
		auto b = left + dist(engine);
		std::iter_swap(a, b);

		std::cout << *a << "<->" << *b << std::endl;
	}
}
std::vector<int> locally_permuted_vector(int size, int min, int max, int window, int overlap, int permutations)
{
	std::vector<int> vec = ordered_vector(size, min, max);
	auto it = vec.begin();
	auto ed = it + window - 1;
	std::cout << vec << std::endl;
	while(ed < vec.end())
	{

		vector_permutation(vec, it, ed, permutations);
		std::cout << vec << std::endl;
		it = ed - overlap;
		ed = ed + window - overlap;
	}
	vector_permutation(vec, it, vec.end(), permutations);
	std::cout << vec << std::endl;
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

	std::vector<int> vec = locally_ordered_vector(20, 0, 9, 3);
	std::cout << vec << std::endl;

	// std::vector<int> lpv = locally_permuted_vector(20, 0, 100, 3, 0, 1);
	// std::cout << lpv << std::endl;
	// std::vector<int> vec{9,8,7,6,
	// 					 5,4,3,2,
	// 					 1,0, -1};
	// std::cout << vec << std::endl;
	// int window = 4;
	// auto it = vec.begin();
	// auto ed = it + window;

	std::cout << vec << std::endl;
	std::vector<int> v{0,1,2,3,4,5,6,7,8,9};
	vector_permutation(vec, begin(v), end(v), 10);
	std::cout << v << std::endl;

}
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

class RandVector
{
private:
	int _seed;
public:
	RandVector() : _seed(std::random_device{}()) {};
	RandVector(int seed) : _seed(seed) {};

	std::vector<int> uniform(int size, int min, int max)
	{
		std::mt19937 engine{_seed};
		std::uniform_int_distribution<int> dist(min, max);
		std::vector<int> v(size);
		auto generator = [&dist, &engine](){return dist(engine);};
		std::generate(begin(v), end(v), generator);
		return v;
	}
	std::vector<int> uniform_shuffled(int size, int min, int max)
	{
		return uniform(size, min, max);
	}
	
	std::vector<int> ordered(int size, int min, int max, bool reverse=false)
	{
		std::vector<int> vec = uniform(size, min, max);
		auto cmp = [reverse](int i, int j){return (reverse) ? (i > j) : (i < j);};
		std::sort(vec.begin(), vec.end(), cmp);
		return vec;
	}
	std::vector<int> locally_ordered(int size, int min, int max, int window)
	{
		std::vector<int> vec = uniform_shuffled(size, min, max);
		auto it = vec.begin();
		auto ed = it + window;
		while(ed < vec.end())
		{
			std::sort(it, ed);
			it = ed;
			ed = ed + window;
		}
		std::sort(it, vec.end());
		return vec;
	}
	void window_permutation(std::vector<int> &vec, std::vector<int>::iterator left, std::vector<int>::iterator right, int permutations)
	{
		std::mt19937 engine{std::random_device{}()};
		auto distance = std::distance(left, right);
		std::uniform_int_distribution<int> dist(0, distance - 1); // permute on half open intrval [ )

		for(int i=0; i<permutations; i++)
		{
			auto a = left + dist(engine);
			auto b = left + dist(engine);
			std::cout << a - vec.begin() << " <-> " << b - vec.begin() << " : " << *a << " <-> " << *b << std::endl;
			std::iter_swap(a, b);

		}
	}
	void sliding_window_permutation(std::vector<int> &vec, int window, int overlap, int permutations)
	{
		auto it = vec.begin();
		auto ed = it + window;
		while(ed < vec.end())
		{
			std::cout << "[" << it - vec.begin() << " - " << ed - vec.begin() << ")" << std::endl;
			window_permutation(vec, it, ed, permutations);
			it = ed - overlap;
			ed = ed + window - overlap;
		}
		window_permutation(vec, it, vec.end(), permutations);
	}
	std::vector<int> locally_permuted_vector(int size, int min, int max, int window, int overlap, int permutations)
	{
		std::vector<int> vec = ordered(size, min, max);
		sliding_window_permutation(vec, window, overlap, permutations);
		std::reverse(vec.begin(), vec.end());
		sliding_window_permutation(vec, window, overlap, permutations);
		std::reverse(vec.begin(), vec.end());
		return vec;
	}
};

int main()
{
	RandVector rv;

	std::vector<int> a = rv.locally_permuted_vector(1000, 0, 1000, 100, 50, 50);
	std::cout << a << std::endl;

}
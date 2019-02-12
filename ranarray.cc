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
	std::mt19937 _engine;
public:
	RandVector() : _engine(std::random_device{}()) {};
	RandVector(int seed) : _engine(seed) {};

	std::vector<int> uniform(int size, int min, int max)
	{
		std::uniform_int_distribution<int> dist(min, max);
		std::vector<int> v(size);
		auto generator = [&dist, this](){return dist(_engine);};
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
		auto distance = std::distance(left, right);
		std::uniform_int_distribution<int> dist(0, distance - 1); // permute on half open intrval [ )

		for(int i=0; i<permutations; i++)
		{
			auto a = left + dist(_engine);
			auto b = left + dist(_engine);
			std::cout << a - vec.begin() << " <-> " << b - vec.begin() << " : " << *a << " <-> " << *b << std::endl;
			std::iter_swap(a, b);

		}
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
private:
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

};

int main()
{
	RandVector rv;

	std::vector<int> a = rv.locally_permuted_vector(100, 0, 100, 20, 10, 10);
	std::cout << a << std::endl;

}
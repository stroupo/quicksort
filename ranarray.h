#ifndef RANARRAY_H_
#define RANARRAY_H_

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

template<class T>
class RandVector
{
private:
	std::mt19937 _engine;
public:
	RandVector() : _engine(std::random_device{}()) {};
	RandVector(int seed) : _engine(seed) {};

	std::vector<T> uniform(int size, int min, int max);
	std::vector<T> ordered(int size, int min, int max, bool reverse=false);
	std::vector<T> locally_ordered(int size, int min, int max, int window);
	std::vector<T> locally_permuted(int size, int min, int max, int window, int overlap, int permutations);
private:
	void window_permutation(std::vector<T> &vec, typename std::vector<T>::iterator left, typename std::vector<T>::iterator right, int permutations);
	void sliding_window_permutation(std::vector<T> &vec, int window, int overlap, int permutations);
};

#endif // RANARRAY_H_
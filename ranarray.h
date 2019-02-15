#ifndef RANARRAY_H_
#define RANARRAY_H_

#include <iostream>
#include <random>

#include <algorithm>
#include <functional>
#include <vector>

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
  os << "( ";
  for (auto &e : v)
    os << e << " ";
  os << ")";
  return os;
}

template <class T> class RandVector {
private:
  std::mt19937 _engine;

public:
  RandVector() : _engine(std::random_device{}()){};
  RandVector(const int seed) : _engine(seed){};

  std::vector<T> uniform(const int size, const int min, const int max);
  std::vector<T> ordered(const int size, const int min, const int max,
                         const bool reverse = false);
  std::vector<T> locally_ordered(const int size, const int min, const int max,
                                 const int window);
  std::vector<T> locally_permuted(const int size, const int min, const int max,
                                  const int window, const int overlap,
                                  const int permutations);

private:
  void window_permutation(std::vector<T> &vec,
                          const typename std::vector<T>::iterator left,
                          const typename std::vector<T>::iterator right,
                          const int permutations);
  void sliding_window_permutation(std::vector<T> &vec, const int window,
                                  const int overlap, const int permutations);
};

#endif // RANARRAY_H_
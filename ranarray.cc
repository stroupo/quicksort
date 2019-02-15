#include "ranarray.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <random>
#include <string>
#include <vector>

template <>
std::vector<int> RandVector<int>::uniform(const int size, const int min,
                                          const int max) {
  std::uniform_int_distribution<int> dist(min, max);
  std::vector<int> v(size);
  std::generate(begin(v), end(v), [&dist, this]() { return dist(_engine); });
  return v;
}


template <>
std::vector<std::string>
RandVector<std::string>::uniform(const int size, const int min, const int max) {
  static const std::string a{"0123456789"
                             "abcdefghijklmnopqrstuvwxyz"
                             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

  std::uniform_int_distribution<int> dist(min, max);

  std::vector<std::string> v(size);

  for (auto &item : v)
    std::sample(a.begin(), a.end(), std::back_inserter(item), dist(_engine), _engine);
  return v;
}

template <typename T>
std::vector<T> RandVector<T>::uniform(const int size, const int min,
                                                const int max) {
  std::uniform_real_distribution<T> dist(min, max);
  std::vector<T> v(size);
  std::generate(begin(v), end(v), [&dist, this]() { return dist(_engine); });
  return v;
}

template <typename T>
std::vector<T> RandVector<T>::ordered(const int size, const int min,
                                      const int max, const bool reverse) {
  std::vector<T> vec = uniform(size, min, max);
  auto cmp = [reverse](T i, T j) { return (reverse) ? (i > j) : (i < j); };
  std::sort(vec.begin(), vec.end(), cmp);
  return vec;
}

template <typename T>
std::vector<T> RandVector<T>::locally_ordered(const int size, const int min,
                                              const int max, const int window) {
  std::vector<T> vec = uniform(size, min, max);
  auto it = vec.begin();
  for(auto ed = it + window; ed < vec.end(); it = ed, ed += window)
    std::sort(it, ed);
  std::sort(it, vec.end());
  return vec;
}

template <typename T>
void RandVector<T>::window_permutation(
    std::vector<T> &vec, const typename std::vector<T>::iterator left,
    const typename std::vector<T>::iterator right, const int permutations) {
  // permute on  [left right)
  std::uniform_int_distribution<int> dist(0, std::distance(left, right) - 1);

  for (int i = 0; i < permutations; i++)
    std::iter_swap(left + dist(_engine), left + dist(_engine));
}

template <typename T>
void RandVector<T>::sliding_window_permutation(std::vector<T> &vec,
                                               const int window,
                                               const int overlap,
                                               const int permutations) {
  auto it = vec.begin();
  for(auto ed = it + window; ed < vec.end(); it = ed - overlap, ed = ed + window - overlap)
      window_permutation(vec, it, ed, permutations);
  window_permutation(vec, it, vec.end(), permutations);
}


template <typename T>
std::vector<T> RandVector<T>::locally_permuted(const int size, const int min,
                                               const int max, const int window,
                                               const int overlap,
                                               const int permutations) {
  std::vector<T> vec = ordered(size, min, max);
  sliding_window_permutation(vec, window, overlap, permutations);
  std::reverse(vec.begin(), vec.end());
  sliding_window_permutation(vec, window, overlap, permutations);
  std::reverse(vec.begin(), vec.end());
  return vec;
}

template class RandVector<int>;
template class RandVector<float>;
template class RandVector<double>;
template class RandVector<std::string>;
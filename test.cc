#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>
#include "quicksort.h"

// template<class RandomIt >
// void sort( RandomIt first, RandomIt last );
// typedef void(sorter_type)()

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
  os << "( ";
  for (auto &e : v)
    os << e << " ";
  os << ")";
  return os;
}

// template<typename T,
// 		 typedef U  = std::vector<T>::iterator,
// 		 void sorter(U u1, U u2)>
// void call_sort(std::vector<T> &v) {
//    sorter(v.begin(), v.end());
// }

template<typename T,
		 typename U,
		 void sorter(U u1, U u2)>
void call_sort(std::vector<T> &v) {
   sorter(v.begin(), v.end());
}

int main()
{
	std::vector<int> v {9,8,7,6,5,4,3,2,1,0, 10};
	call_sort<int, std::vector<int>::iterator, std::sort>(v);
	std::cout << v << std::endl;
}
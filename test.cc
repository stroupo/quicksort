#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>

using namespace std;


template<typename T>
std::ostream &operator <<(std::ostream &os, const std::vector<T> &v)
{
	os << "( ";
	for(auto &e: v) os << e << " ";
	os << ")";
	return os;
}

using namespace std;

class LongestConsec
{
public:
    static std::string longestConsec(std::vector<std::string> &strarr, int k);
};
void insert(vector<string> &v, string element)
{
	vector<string>::iterator it = v.begin();
	for(; it < v.end(); it++)
	{
  	if(element == *it)
	{
		return;
	}
	if(element.size() > (*it).size())
	{
		break;
	}
        }
        v.insert(it, element);
}
std::string LongestConsec::longestConsec(vector<string> &strarr, int k)
{
  if(strarr.size() == 0 or k > strarr.size() or k <= 0)
    return "";
  vector<string> maxstrarr;
  for(auto &e : strarr)
  {
  	insert(maxstrarr, e);
  }
  string res = std::accumulate(maxstrarr.begin(), maxstrarr.begin() + k, string(""));
  return res;
}

int main()
{
 vector<string> v{"abcde", "abcdefx", "abcdefx", "abcdefg", "abc", "a", "ab", "abcdefgh"};
 auto b = next(v.begin(), 2);
 // auto e = next(v.end(), -1);
 std::cout << *b << std::endl;
}
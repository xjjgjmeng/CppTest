#include <algorithm>
#include <vector>

#include <fmt/core.h>
#include <fmt/ranges.h>

int main()
{
	// 合并两个sorted ranges
	std::vector<int> v0 = { 1,5,8 };
	std::vector<int> v1 = { 3,4,9 };
	std::vector<int> v;
	std::merge(std::begin(v0), std::end(v0), std::begin(v1), std::end(v1), std::back_inserter(v));
	fmt::println("{}", v);
	// v:{1,3,4,5,8,9}

	// Merges two consecutive sorted ranges [first, middle) and [middle, last) into one sorted range [first, last)
	int arr[] = { 1,3,5,7,9,2,5,7,8 };
	std::inplace_merge(std::begin(arr), std::begin(arr) + 5, std::end(arr));
	fmt::println("{}", arr);
	// std::begin(arr) + 5:the end of the first sorted range and the beginning of the second
	// arr = {1, 2, 3, 5, 5, 7, 7, 8, 9}

	return 0;
}
#include <algorithm>
#include <vector>

#include <fmt/core.h>
#include <fmt/ranges.h>

int main()
{
	auto printBound = [](auto& arr, auto v)
		{
			fmt::println("arr: {}", arr);
			fmt::println("v: {}", v);
			// 返回第一个小于v为假的元素（第一个大于等于v的）
			const auto lb = std::lower_bound(std::begin(arr), std::end(arr), v);
			// 返回容器中第一个v小于的元素（第一个大于v的）
			const auto ub = std::upper_bound(std::begin(arr), std::end(arr), v);
			fmt::println("lower_bound: {}\tupper_bound: {}", *lb, *ub);
			// <= v <
			const auto [lb_, ub_] = std::equal_range(std::begin(arr), std::end(arr), v);
			fmt::println("equal_range: {} {}", *lb_, *ub_);
			fmt::println("");
		};
	{
		int arr[]{ 1,2,3,4,5,6 };
		printBound(arr, 5);
		/*
			lower_bound: 5  upper_bound: 6
			equal_range: 5 6
		*/
	}

	{
		double arr[]{ 1,2,2.1,2.3,2.5,2.7,2.9,3,3.1,3.3,3.5,3.7,3.9,4,4.1,4.3,4.5,4.7,4.9,5,6 };
		printBound(arr, 3);
		/*
			lower_bound: 3  upper_bound: 3.1
			equal_range: 3 3.1
		*/
	}

	{
		int arr[]{ 1,3,5,7,9 };
		printBound(arr, 6);
		/*
			lower_bound: 7  upper_bound: 7
			equal_range: 7 7
		*/
	}

	{
		std::vector<int> data = { 1, 1, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 6 };

		auto lower = std::lower_bound(data.begin(), data.end(), 4);
		auto lowerIdx = std::distance(std::begin(data), lower);
		// 查找第一个值不小于4的位置
		// lower:{4}
		// lowerIdx:7
		auto upper = std::upper_bound(data.begin(), data.end(), 4);
		auto upperIdx = std::distance(std::begin(data), upper);
		// 查找第一个值大于4的位置
		// upper:{5}
		// upperIdx:10
		auto b = std::binary_search(std::begin(data), std::end(data), 4);
		// b:true
		b = std::binary_search(std::begin(data), std::end(data), 666);
		// b:false
		auto p = std::equal_range(std::begin(data), std::end(data), 4);
		// p = ({4}, {5})
		auto firstIdx = std::distance(std::begin(data), p.first);
		auto secondIdx = std::distance(std::begin(data), p.second);
		// firstIdx:7
		// secondIdx:10
	}

	return 0;
}
#include <random>
#include <iostream>

int main()
{
	// 生成一个[0, 0xffff]之间的随机数
	std::random_device rd;
	std::uniform_int_distribution<int> dist(0, 0xFFFF);
	auto i = dist(rd);
	std::cout << i << std::endl;

	return 0;
}
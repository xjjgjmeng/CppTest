#include <random>
#include <iostream>

// RAND_MAX：std::rand返回的最大值

int main()
{
	// use current time as seed for random generator
	std::srand(std::time(nullptr));
	int random_variable = std::rand();
	std::cout << "Random value on [0 " << RAND_MAX << "]: " << random_variable << '\n';

	// 给std::srand的种子相同，std::rand产生的随机数也相同（pseudo-random）
	for (auto i = 0; i < 3; ++i)
	{
		std::srand(666);
		std::cout << "666: " << std::rand() << '\n';
	}

	/*
	要取得[a,b)的随机整数，使用`(rand() % (b-a))+ a` （结果值含a不含b）。
	要取得[a,b]的随机整数，使用`(rand() % (b-a+1))+ a` （结果值含a和b）。
	要取得(a,b]的随机整数，使用`(rand() % (b-a))+ a + 1` （结果值不含a含b）。
	要取得0～1之间的浮点数，可以使用`rand() / double(RAND_MAX)`。
	*/

	return 0;
}
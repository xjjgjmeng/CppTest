#include <functional>

#include <fmt/core.h>

void cpp14()
{
	// Generic (Polymorphic) Lambda Expressions
	{
		// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3649.html
		auto variadic_generic_Lambda = [](auto... param)
			{
				return sizeof...(param);
			}; // 14 or 17??
		fmt::println("{}", variadic_generic_Lambda(1, 3, 5, 7, 9)); // 5

		std::function<void(int&)> myfunc = [](auto i) { i = 123; };
		int a = 0;
		myfunc(a);
		fmt::println("{}", a);
		// 输出0，i被推倒为int，使用通用引用（auto &&i）i才会被被推倒为int&
	}

	// Generalized lambda capture
	{
		// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3648.html
		int value0{};
		int value1{};
		auto func = [x = 999, &ref = value0, value1 = value1 + 1]() {};
		// 捕获x，且赋初值为999
		// 用ref引用捕获value0
		// 用value1值捕获value1+1
	}
}

void cpp17()
{
	// Constexpr lambdas
	// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0170r1.pdf
	{
		// 即使你没有指定constexpr关键字，如果函数调用运算符恰好满足所有constexpr函数的要求，那么它也将是constexpr
		auto add = [](int a, int b) constexpr { return a + b; };
		int arr[add(1, 2)]{};
		fmt::println("{}", std::size(arr));
	}
}

/*
捕获列表可以理解为匿名类型的ctor的参数列表(的传入参数)，lambda的参数是operator()的参数
*/

int main()
{
	// 表示声明类型并创建此类型的对象
	{
		[]{}; // 构建一个函数对象.相当于创建了一个可调用对象，无参构造，无参调用
		[]{}(); // 构建一个函数对象然后调用.IIFE(immediately invoked function expression)
		auto a = []{}; // 构建一个函数对象然后赋值给a
	}

	// mutable
	{
		// 如果要在lambda表达式中使用mutable，不管表达式中有没有参数选项，都要把参数列表加上
		// mutable的作用就是要取消const的作用
		[]()mutable {}; // ok
		// []mutable {}; // error
	}

	// lambda and std::function and std::bind
	{
		std::function<void()> fr = std::bind([](int a) { fmt::println("{}", a); }, 123);
		fr();
	}

	// 转化为C函数指针
	{
		/*
		This user-defined conversion function is only defined if the capture list of the lambda-expression is empty
		using F = ret(*)(params);
		operator F() const;
		*/

		void(*p)() = [] {};
		// void(*p_)() = [=] {}; // error C2440: “初始化”: 无法从“main::<lambda_ec87c1c8cb72939303febca25fa923d1>”转换为“void (__cdecl *)(void)”
	}

	// 高阶函数：Lambda可以作为参数和返回值
	{
		const auto less_than = [](auto x)
			{
				return [x](auto y) { return y < x; };
			};

		auto less_than_five = less_than(5);
		fmt::println("{}", less_than_five(3)); // true
		fmt::println("{}", less_than_five(10)); // false
	}

	cpp14();
	cpp17();

	return 0;
}
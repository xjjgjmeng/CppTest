#include <memory>
#include <string>

#include <fmt/core.h>

int main()
{
	// 将某个数据成员共享出去且保证生命周期
	{
		/*
			template< class Y > 
			shared_ptr( const shared_ptr<Y>& r, element_type* ptr ) noexcept;
		*/

		{
			struct MyType
			{
				int a;
				int b;
			};

			auto sp = std::make_shared<MyType>();
			std::shared_ptr<int> sp_b{ sp, &sp->b };
			*sp_b = 666; // 在使用sp_b的资源期间，sp的资源一直有效
		}

		{
			struct Foo {};
			auto p1 = std::make_shared<Foo>();
			{
				auto pStr = new std::string("helloword");
				std::shared_ptr<std::string> p2(p1, pStr); // 此刻Foo对象被两个智能指针保护
				p2.get(); // 获得的是helloworld字符串
			}
		}
	}

	// 数组
	{
		// c++17之前
		std::shared_ptr<int> p(new int[10], [](int* p) { delete[] p; });
		std::shared_ptr<int> p_(new int[10], std::default_delete<int[]>());

		// c++17之后
		std::shared_ptr<int[]> p__(new int[10]());

		// 使用make_shared管理数组，需使用c++20
	}

	// void
	{
		std::shared_ptr<void> sp;
		sp = std::make_shared<char>('E');
		fmt::println("{}", *reinterpret_cast<char*>(sp.get()));
		sp = std::make_shared<std::string>("666"); // E
		fmt::println("{}", *reinterpret_cast<std::string*>(sp.get())); // 666

		{
			{
				struct MyType
				{
					MyType() { fmt::println("{}", __func__); }
					~MyType() { fmt::println("{}", __func__); }
				};

				{
					std::shared_ptr<void> sp;
					sp = std::make_shared<MyType>();
					fmt::println("In the scope");
				}
				fmt::println("Out of scope");
			}
			/*
			输出：
			MyType
			In the scope
			~MyType
			Out of scope
			*/
		}
	}

	return 0;
}
#include <iostream>
#include <sstream>
#include <tuple>

// 不限类型和个数的打印函数
void print() {}

template<typename T, typename... Types>
void print(const T& firstArg, const Types&... args)
{
    std::cout << firstArg << " ";
    print(args...); // VOL 1.23 1
}

namespace ns
{
    template <class T>
    void print(T arg)
    {
        std::cout << arg << std::endl;
    }

    template <class ... Args>
    void expand(Args ... args)
    {
        int a[] = { (print(args), 0)... };
    }
}

int main()
{
    print("VOL", 1.23, true);
    ns::expand(1, 2, 3, 4);
    return 0;
}
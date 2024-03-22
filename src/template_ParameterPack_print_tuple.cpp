#include <iostream>
#include <sstream>
#include <tuple>

// helper: print element with index IDX of tuple with MAX elements
template <int IDX, int MAX, typename... Args>
struct PRINT_TUPLE
{
    static void print(std::ostream& strm, const std::tuple<Args...>& t) {
        strm << std::get<IDX>(t) << (IDX + 1 == MAX ? "" : ", ");
        PRINT_TUPLE<IDX + 1, MAX, Args...>::print(strm, t);
    }
};

// partial specialization to end the recursion
template <int MAX, typename... Args>
struct PRINT_TUPLE<MAX, MAX, Args...>
{
    static void print(std::ostream& strm, const std::tuple<Args...>& t) {}
};

// output operator for tuples
template <typename... Args>
std::ostream& operator<<(std::ostream& strm, const std::tuple<Args...>& t)
{
    strm << "[ ";
    PRINT_TUPLE<0, sizeof...(Args), Args...>::print(strm, t);
    return strm << "]";
}

// 利用PRINT_TUPLE很容易写出ImagePlatform使用的且用法更为简单的CMD拼接函数
template <class... Types>
std::string toCmd(Types&&... args)
{
    const auto mytuple = std::make_tuple(std::forward<Types>(args)...);
    std::ostringstream oss{};
    oss << mytuple;
    return oss.str();
}

// ---
// 想要支持更多的类型，重写operator<<即可
struct MyType
{
    MyType(int i) :val{ i } {}
    int val;
};

std::ostream& operator<<(std::ostream& strm, const MyType& v) // 不必放在std下也可以被找到，如果MyType放在std下，那么此函数也必须放在std下，否则也无法被找到
{
    return strm << v.val;
}

namespace std
{
    template <typename T1, typename T2>
    std::ostream& operator<<(std::ostream& strm, const std::pair<T1, T2>& p) // 不放在std下就无法被找到
    {
        return strm <<"[" << p.first << "," << p.second << "]";
    }
}

int main()
{
    std::cout << toCmd("VOL", 1.23, true) << std::endl; // [ VOL, 1.23, 1]
    std::cout << toCmd("MSG", 1.23, true, MyType{666}, std::make_pair(1., 'A')) << std::endl; // [ MSG, 1.23, 1, 666, [1,A]]
    return 0;
}
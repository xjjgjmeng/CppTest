#include <string>
#include <functional>

#include <fmt/core.h>

// 在C++ 的类中，除了类模板参数之外，无法在不同的成员（函数、数据成员）之间共享类型信息
struct MemFunPtr
{
    struct placeholder
    {
        virtual ~placeholder() = default;
    };

    template<typename R, typename Obj, typename... Arg>
    struct holder : placeholder
    {
        using mf_ptr_t = R(Obj::*)(Arg...);

        mf_ptr_t m_mf;

        holder(mf_ptr_t ptr)
            : m_mf(ptr)
        {

        }
    };

    placeholder* m_ph = nullptr;

    template<typename R, typename Obj, typename... Arg>
    MemFunPtr(R(Obj::* ptr)(Arg...))
    {
        m_ph = new holder<R, Obj, Arg...>{ ptr };
    };

    template<typename R = void, typename Obj, typename... Args>
    R call(Obj& obj, Args... args)
    {
        if (auto ptr = dynamic_cast<holder<R, Obj, Args...>*>(m_ph))
        {
            return (obj.*(ptr->m_mf))(args...);
        }

        throw std::bad_function_call{};
    }
};

int main()
{
    MemFunPtr ptr(&std::string::clear);
    std::string str{ "hello" };
    fmt::println("{}", str.size()); // 5
    ptr.call(str);
    fmt::println("{}", str.size()); // 0

	return 0;
}
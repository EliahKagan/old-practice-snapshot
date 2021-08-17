#include <tuple>
#define USE_FOLD false

#if USE_FOLD

template<auto... Vals, typename... Args>
auto dotwith(const Args... args)
{
    return (... + (Vals * args));
}

#else

namespace detail {
    template<typename Acc>
    auto dotwith_helper(const Acc acc)
    {
        return acc;
    }

    template<auto Val, auto... Vals, typename Acc,
             typename Arg, typename... Args>
    auto dotwith_helper(const Acc acc, const Arg arg, const Args... args)
    {
        return dotwith_helper<Vals...>(acc + Val * arg, args...);
    }
}

template<auto Val, auto... Vals, typename Arg, typename... Args>
auto dotwith(const Arg arg, const Args... args)
{
    static_assert(sizeof...(Vals) == sizeof...(Args));
    return detail::dotwith_helper<Vals...>(Val * arg, args...);
}

#endif // ! USE_FOLD

int main()
{
    return dotwith<1, 5, 3, -4, -3>(2, 4, 2, 8, -6);
}

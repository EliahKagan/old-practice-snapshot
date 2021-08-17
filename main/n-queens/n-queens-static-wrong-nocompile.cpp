#include <type_traits>

template<typename T>
constexpr T my_abs(const T x) noexcept
{
    return x < 0 ? -x : x;
}

constexpr bool safe(int, int, int) noexcept
{
    return true;
}

template<typename... Ints>
constexpr bool safe(const int i, const int j, const int qi,
                    const int qj, const Ints... qjs) noexcept
{
    const auto dj = qj - qi;
    return dj != 0 && i - qi != my_abs(dj) && safe(i, j, qi + 1, qjs...);
}

template<int N, typename... Ints, bool IsSolution = sizeof...(Ints) == N>
constexpr int count(const Ints... qjs) noexcept;

template<int n, typename... Ints>
constexpr int do_count(std::true_type, const Ints...) noexcept
{
    return 1;
}

template<int N, typename... Ints>
constexpr int do_count(std::false_type, const Ints... qjs) noexcept
{
    const auto i = static_cast<int>(sizeof...(qjs));

    auto acc = 0;
    for (auto j = 0; j != N; ++j)
        if (safe(i, j, 0, qjs...)) acc += count<N>(qjs..., j);
    
    return acc;
}

template<int N, typename... Ints, bool IsSolution>
constexpr int count(const Ints... qjs) noexcept
{
    return do_count<N>(IsSolution, qjs...);
}

/*
template<typename... Ints>
constexpr int count(const int n, const Ints... qjs)
{
    const auto i = static_cast<int>(sizeof...(qjs));
    
    if (i == n) return 1;

    auto acc = 0;
    for (auto j = 0; j != n; ++j)
        if (safe(i, j, 0, qjs...)) acc += count(n, qjs..., j);
    
    return acc;
}
*/

int main()
{
    return count<4>();
}

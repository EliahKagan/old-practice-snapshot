#include <cstdlib>
#include <type_traits>
using namespace std;

constexpr auto nmax = 20;

constexpr bool safe(const int (&qjs)[nmax], const int i)
{
    for (auto qi = 0; qi != i; ++qi) {
        const auto dj = qjs[i] - qjs[qi];
        if (dj == 0 || i - qi == abs(dj)) return false;
    }

    return true;
}

constexpr int count(const int n)
{
    auto acc = 0;
    int qjs[nmax] {-1};
    
    for (auto i = 0; i != -1; ) {
        if (++qjs[i] == n)
            --i; // retreat
        else if (!safe(qjs, i))
            continue;
        else if (i == n - 1)
            ++acc;
        else
            qjs[++i] = -1; // advance
    }

    return acc;
}

int main()
{
    return integral_constant<int, count(9)>::value;
}

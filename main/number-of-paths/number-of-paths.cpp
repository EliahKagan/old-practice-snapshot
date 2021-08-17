#include <cassert>
#include <iostream>

namespace {
    long long npr(long long n, const long long r) // FIXME: really need nCr
    {
        assert(n >= r);
        auto acc = 1LL;
        for (auto stop = n - r; n > stop; --n) acc *= n;
        return acc;
    }
}

int main()
{
    auto val = npr(18, 9);
}

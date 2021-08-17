#include <iostream>

namespace {
    long long pown(const long long n, const int p)
    {
        if (p < 2) return p == 0 ? 1LL : n;
        const auto r = pown(n, p / 2), s = r * r;
        return p % 2 == 0 ? s : s * n;
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        long long n {};
        int p {};
        std::cin >> n >> p;
        std::cout << pown(n, p) << '\n';
    }
}

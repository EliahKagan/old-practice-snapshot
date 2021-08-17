#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    auto n = 0;
    std::cin >> n;
    std::vector<int> a;
    a.reserve(static_cast<decltype(a)::size_type>(n));

    while (n-- > 0) {
        auto x = 0;
        std::cin >> x;
        a.push_back(x);
    }

    auto q = 0;
    std::cin >> q;

    while (q-- > 0) {
        auto y = 0;
        std::cin >> y;

        const auto beg = a.cbegin();
        const auto p = std::lower_bound(beg, a.cend(), y);
        std::cout << (*p == y ? "Yes" : "No") << ' ' << p - beg + 1 << '\n';
    }
}

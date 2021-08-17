#include <algorithm>
#include <iostream>
#include <vector>

namespace {
    std::vector<int> read_record(const std::vector<int>::size_type n)
    {
        std::vector<int> a (n);
        for (auto& x : a) std::cin >> x;
        return a;
    }

    int get_combined_kth_element(const std::vector<int>& a,
                                 const std::vector<int>& b, int k)
    {
        static constexpr auto no_element = -1;
        if (k < 1) return no_element;

        const auto pp = a.cend(), qq = b.cend();
        auto p = a.cbegin(), q = b.cbegin();

        for (; p != pp && q != qq; ++(*p < *q ? p : q))
            if (--k == 0) return std::min(*p, *q);

        for (; p != pp; ++p)
            if (--k == 0) return *p;

        for (; q != qq; ++q)
            if (--k == 0) return *q;

        return no_element;
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::vector<int>::size_type n {}, m {};
        auto k = 0;
        std::cin >> n >> m >> k;

        const auto a = read_record(n), b = read_record(m);
        std::cout << get_combined_kth_element(a, b, k) << '\n';
    }
}

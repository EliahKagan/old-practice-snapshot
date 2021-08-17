#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

namespace {
    constexpr std::vector<int>::size_type min_size {1u}, max_size {100u};

    // At http://www.practice.geeksforgeeks.org/problem-page.php?pid=574,
    // problem constraints specify 1 as the lower bound for elements, but the
    // immediately following example contains some elements with values as low,
    // as 0, suggesting 0 was meant instead.
    constexpr auto min_element = 0, max_element = 100;

    std::vector<int> get(std::vector<int>::size_type count)
    {
        assert(min_size <= count && count <= max_size);

        std::vector<int> a;
        for (a.reserve(count); count != 0u; --count) {
            auto k = -1;
            std::cin >> k;
            assert(min_element <= k && k <= max_element);
            a.push_back(k);
        }

        return a;
    }

    std::vector<int> polynomial_multiply(std::vector<int>&& u,
                                         std::vector<int>&& v)
    {
        std::vector<int> w (u.size() + v.size() - 1u);

        for (decltype(u.size()) i {0u}; i != u.size(); ++i) {
            for (decltype(v.size()) j {0u}; j != v.size(); ++j)
                w[i + j] += u[i] * v[j];
        }

        return w;
    }

    void put(std::vector<int>&& a)
    {
        auto sep = "";
        for (const auto k : a) {
            std::cout << sep << k;
            sep = " ";
        }

        std::cout << '\n';
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::vector<int>::size_type m {}, n {};
        std::cin >> m >> n;
        auto u = get(m), v = get(n);
        put(polynomial_multiply(std::move(u), std::move(v)));
    }
}

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

namespace {
    // Computes the number permutations that can be made of n distinct elements
    // (n!). Returns one in the undefined case where n is strictly negative.
    template<typename T>
    T factorial(T n)
    {
        constexpr auto one = static_cast<T>(1);

        auto acc = one;
        while (n > one) acc *= n--;
        return acc;
    }

    // Generates permutations by Heap's algorithm and emits them into a vector.
    void collect_permutations(std::string& s, const std::string::size_type n,
                              std::vector<std::string>& v)
    {
        if (n == 1u) {
            v.push_back(s);
            return; 
        }

        const auto m = n - 1u;

        for (std::string::size_type i {0u}; i < m; ++i) {
            collect_permutations(s, m, v);
            std::swap(s[n % 2u == 0u ? i : 0u], s[m]);
        }

        collect_permutations(s, m, v);
    }

    // Prints elements of a vector, separated by spaces.
    template<typename T>
    void put(const std::vector<T>& v)
    {
        auto sep = "";

        for (const auto& x : v) {
            std::cout << sep << x;
            sep = " ";
        }

        std::cout << '\n';
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::string s;
        std::cin >> s;
        const auto n = s.size();

        std::vector<std::string> v;
        v.reserve(factorial(n));
        collect_permutations(s, n, v);

        std::sort(std::begin(v), std::end(v));
        const auto q = std::unique(std::begin(v), std::end(v));
        v.erase(q, std::end(v));

        put(v);
    }
}

#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <vector>

namespace {
    template<typename T>
    std::set<T> get(int count)
    {
        std::set<T> s;
        while (count-- > 0) {
            T x {};
            std::cin >> x;
            s.insert(x);
        }

        return s;
    }

    template<typename T>
    std::vector<T> intersect_to_vector(const std::set<T>& a,
                                       const std::set<T>& b)
    {
        std::vector<int> v;
        std::set_intersection(a.cbegin(), a.cend(), b.cbegin(), b.cend(),
                              std::back_inserter(v));
        return v;
    }

    template<typename T>
    void put(const std::vector<T>& v)
    {
        auto sep = "";
        for (const auto x : v) {
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
        auto n = 0, m = 0;
        std::cin >> n >> m;
        const auto a = get<int>(n), b = get<int>(m);
        
        const auto v = intersect_to_vector(a, b);

        if (v.empty())
            std::cout << "Zero\n";
        else
            put(v);
    }
}

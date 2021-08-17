#include <iostream>
#include <unordered_set>
#include <vector>

namespace {
    template<typename T>
    bool has_pair_sum(const std::vector<T>& values, const T sum)
    {
        std::unordered_set<T> s;

        for (const auto x : values) {
            if (s.find(x) != s.cend()) return true;
            s.insert(sum - x);
        }

        return false;
    }
}

int main()
{
    std::vector<int> a {1, 2, 3, 9}, b {1, 2, 4, 4}, c {1, 2}, d {};

    std::cout << std::boolalpha
        << has_pair_sum(a, 8) << '\n' << has_pair_sum(b, 8) << '\n'
        << has_pair_sum(c, 3) << '\n' << has_pair_sum(c, 2) << '\n'
        << has_pair_sum(d, 0) << '\n';
}

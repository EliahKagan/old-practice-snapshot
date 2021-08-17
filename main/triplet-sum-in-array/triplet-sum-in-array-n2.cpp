#include <iostream>
#include <unordered_set>
#include <vector>

namespace {
    std::vector<int> get_record(std::vector<int>::size_type n)
    {
        std::vector<int> a;

        for (a.reserve(n); n != 0u; --n) {
            auto elem = 0;
            std::cin >> elem;
            a.push_back(elem);
        }

        return a;
    }

    bool has_pair_sum(const std::vector<int>& a, std::vector<int>::size_type j,
                      const int sum)
    {
        for (std::unordered_set<int> s; j != a.size(); ++j) {
            if (s.find(a[j]) != s.cend()) return true;
            s.insert(sum - a[j]);
        }

        return false;
    }

    bool has_triplet_sum(const std::vector<int>& a, const int x)
    {
        if (a.size() < 3u) return false;

        const auto istop = a.size() - 2u;
        for (std::vector<int>::size_type i {0u}; i != istop; ++i)
            if (has_pair_sum(a, i + 1u, x - a[i])) return true;

        return false;
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::vector<int>::size_type n {};
        auto x = 0;
        std::cin >> n >> x;

        std::cout << has_triplet_sum(get_record(n), x) << '\n';
    }
}

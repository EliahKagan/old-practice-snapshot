#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

namespace {
    std::vector<int> read_fixed_zero_permutation()
    {
        std::vector<int>::size_type n {};
        std::cin >> n;

        std::vector<int> a (n + 1);
        std::for_each(std::next(begin(a)), end(a),
                      [](auto& x) noexcept { std::cin >> x; });
        return a;
    }

    int count_inversions(std::vector<int>& a) noexcept
    {
        auto ret = 0;

        static constexpr auto visited = 0;
        const auto n = static_cast<int>(a.size());

        for (auto i = 1; i != n; ++i) {
            if (!a[i]) continue;

            auto j = std::exchange(a[i], visited);

            while (a[j] != visited) {
                ++ret;
                j = std::exchange(a[j], visited);
            }
        }

        return ret;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    auto a = read_fixed_zero_permutation();
    std::cout << count_inversions(a) << '\n';
}

#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <utility>

namespace {
    constexpr auto debug_check_for_overflow = false;

    std::unordered_map<int, int> create_steps_to_zero_memo()
    {
        std::unordered_map<int, int> memo;
        
        memo.emplace(0, 0);
        memo.emplace(1, 1);

        return memo;
    }

    int count_steps_to_zero(const int n, const int maxdepth,
                            std::unordered_map<int, int>& memo)
    {
        // The caller is responsible for setting maxdepth in such a way that
        // they will either not recieve or not rely on a wrong answer.
        if (n > maxdepth) return maxdepth;

        { // If we've already computed the value for this n, we're done.
            const auto p = memo.find(n);
            if (p != memo.end()) return p->second;
        }

        auto acc = n;
        for (auto k = static_cast<int>(std::sqrt(n)); k != 1; --k) {

        }
    }

    int count_steps_to_zeroQQ(const int n, const int maxdepth,
                            std::unordered_map<int, int>& memo)
    {
        const auto p = memo.find(n);
        if (p != memo.end()) return p->second;

        auto acc = n;
        for (auto k = static_cast<int>(std::sqrt(n)); k != 1; --k) {
            if (n % k == 0)
                acc = std::min(acc, count_steps_to_zero(n / k, memo));
        }

        const auto ret = std::min(acc, count_steps_to_zero(n - 1, memo)) + 1;
        memo.emplace(n, ret);
        return ret;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    if (debug_check_for_overflow) {
        constexpr auto nmax = 1000000;

        for (auto i = 0; i <= nmax; ++i) {
            auto m = create_steps_to_zero_memo();

            std::cout << "DEBUG: " << i << ": "
                      << count_steps_to_zero(i, m) << std::endl;
        }
    }

    auto memo = create_steps_to_zero_memo();

    auto q = 0;
    for (std::cin >> q; q > 0; --q) {
        auto n = 0;
        std::cin >> n;
        std::cout << count_steps_to_zero(n, memo) << '\n';
    }
}

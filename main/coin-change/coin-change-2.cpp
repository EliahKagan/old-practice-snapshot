#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <iterator>
#include <unordered_map>
#include <vector>

namespace {
    struct Subproblem {
        int index;
        int subtot;
    };

    constexpr bool
    operator==(const Subproblem lhs, const Subproblem rhs) noexcept
    {
        return lhs.index == rhs.index && lhs.subtot == rhs.subtot;
    }

    constexpr bool
    operator!=(const Subproblem lhs, const Subproblem rhs) noexcept
    {
        return !(lhs == rhs);
    }
}

namespace std {
    template<>
    struct hash<Subproblem> {
        constexpr size_t
        operator()(const Subproblem subproblem) const noexcept;
    };

    constexpr size_t
    hash<Subproblem>::operator()(const Subproblem subproblem) const noexcept
    {
        constexpr size_t seed {17};
        constexpr size_t multiplier {31};

        auto ret = seed;
        ret = ret * multiplier + static_cast<size_t>(subproblem.index);
        ret = ret * multiplier + static_cast<size_t>(subproblem.subtot);
        return ret;
    }
}

namespace {
    long long solve(const std::vector<int>& coins, const int total)
    {
        std::unordered_map<Subproblem, long long> memo;

        const std::function<long long(int, int)>
        count {[&coins, &memo, &count](int index, int subtot) {
            if (subtot == 0) return 1LL;
            if (index == coins.size()) return 0LL;

            const Subproblem subproblem {index, subtot};
            const auto it = memo.find(subproblem);
            if (it != end(memo)) return it->second;

            auto ret = 0LL;
            for (const auto coin = coins[index++]; subtot >= 0; subtot -= coin)
                ret += count(index, subtot);

            memo.emplace(subproblem, ret);
            return ret;
        }};

        return count(0, total);
    }

    std::vector<int> read_coins()
    {
        std::size_t len {};
        std::cin >> len;

        std::vector<int> coins (len);
        std::copy_n(std::istream_iterator<int>{std::cin}, len, begin(coins));
        return coins;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    int total {};
    std::cin >> total;
    std::cout << solve(read_coins(), total) << '\n';
}

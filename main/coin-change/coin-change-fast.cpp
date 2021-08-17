#include <cstddef>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

namespace {
    using Currency = int;
    using Index = std::vector<Currency>::size_type;

    struct Subproblem {
        const Currency total;
        const Index start;
    };

    inline bool operator==(const Subproblem lhs, const Subproblem rhs)
    {
        return lhs.total == rhs.total && lhs.start == rhs.start;
    }

    inline bool operator!=(const Subproblem lhs, const Subproblem rhs)
    {
        return lhs.total != rhs.total || lhs.start != rhs.start;
    }
}

namespace std {
    template<>
    class hash<Subproblem> {
    public:
        std::size_t operator()(const Subproblem subproblem) const
        {
            return static_cast<std::size_t>(subproblem.total) << 16u
                    ^ static_cast<std::size_t>(subproblem.start);
        }
    };
}

namespace {
    using Count = long long;

    Count count_combos(const std::vector<Currency>& coins,
                       const Subproblem subproblem,
                       std::unordered_map<Subproblem, Count>& memo)
    {
        if (subproblem.total == 0) return 1LL;
        if (subproblem.start == coins.size()) return 0LL;

        const auto p = memo.find(subproblem);
        if (p != memo.cend()) return p->second; // *p == (subproblem, combos)

        Count combos = 0LL;
        for (auto subtotal = 0; subtotal <= subproblem.total;
                                subtotal += coins[subproblem.start]) {
            const Subproblem next {subproblem.total - subtotal,
                                   subproblem.start + 1u};
            combos += count_combos(coins, next, memo);
        }

        memo.emplace(subproblem, combos);
        return combos;
    }

    Count count_combos(const std::vector<Currency>& coins,
                       const Currency total)
    {
        std::unordered_map<Subproblem, Count> memo;
        return count_combos(coins, Subproblem{total, 0u}, memo);
    }

    std::vector<Currency> read_coins()
    {
        Index size{};
        std::cin >> size;

        std::vector<Currency> coins;
        coins.reserve(size);

        while (size-- != 0u) {
            Currency c{};
            std::cin >> c;
            coins.push_back(c);
        }

        return coins;
    }
}

int main()
{
    Currency total{};
    std::cin >> total;

    std::cout << count_combos(read_coins(), total) << '\n';
}

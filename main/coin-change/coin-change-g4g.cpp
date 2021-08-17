#include <iostream>
#include <map>
#include <utility>
#include <vector>

namespace {
    using Currency = int;
    using Index = std::vector<Currency>::size_type;
    using Subproblem = std::pair<Currency, Index>;
    using Count = long long;

    Count count_combos(const std::vector<Currency>& coins,
        const Currency total, const Index i,
        std::map<Subproblem, Count>& memo)
    {
        if (total == 0) return 1LL;
        if (i == coins.size()) return 0LL;

        const auto subproblem = std::make_pair(total, i);
        const auto p = memo.find(subproblem);
        if (p != memo.cend()) return p->second; // *p == (subproblem, combos)

        Count combos = 0LL;
        for (auto subtotal = 0; subtotal <= total; subtotal += coins[i])
            combos += count_combos(coins, total - subtotal, i + 1u, memo);

        memo.emplace(subproblem, combos);
        return combos;
    }

    Count count_combos(const std::vector<Currency>& coins,
        const Currency total)
    {
        std::map<Subproblem, Count> memo;
        return count_combos(coins, total, 0u, memo);
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
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        const auto coins = read_coins();

        Currency total{};
        std::cin >> total;

        std::cout << count_combos(coins, total) << '\n';
    }
}

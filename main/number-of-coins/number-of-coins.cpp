#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

namespace {
    using Currency = std::vector<unsigned>::size_type;

    // Computes the smallest number of coins that may be used to make change
    // for total, or -1 if impossible. coins must be sorted nondecreasingly.
    int min_coins(const std::vector<Currency>& coins, const Currency total)
    {
        std::vector<unsigned> memo (total + 1u, static_cast<unsigned>(-1));
        memo[0u] = 0;

        for (Currency subtotal {1u}; subtotal <= total; ++subtotal) {
            for (const auto coin : coins) {
                if (coin > subtotal) break;

                const auto old_count = memo[subtotal - coin];

                if (old_count != static_cast<unsigned>(-1))
                    memo[subtotal] = std::min(memo[subtotal], old_count + 1u);
            }
        }

        return static_cast<int>(memo[total]);
    }

    std::vector<Currency> read_coins()
    {
        std::vector<Currency>::size_type size;
        std::cin >> size;

        std::vector<Currency> coins;
        for (coins.reserve(size); size != 0u; --size) {
            Currency coin {};
            std::cin >> coin;
            coins.push_back(coin);
        }

        std::sort(std::begin(coins), std::end(coins));
        return coins;
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        Currency total {};
        std::cin >> total;

        std::cout << min_coins(read_coins(), total) << '\n';
    }
}

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <unordered_set>
#include <utility>

namespace {
    class BfsException : public std::logic_error {
        using std::logic_error::logic_error;
    };

    int count_steps_to_zero(const int n)
    {
        std::unordered_set<int> cur {n}, next;

        for (auto count = 0; !cur.empty(); ++count) {
            for (const auto x : cur) {
                if (x < 2) return count + x;

                for (auto k = static_cast<int>(std::sqrt(x)); k != 1; --k)
                    if (x % k == 0) next.insert(x / k);

                next.insert(x - 1);
            }

            cur.clear();
            std::swap(cur, next);
        }

        throw BfsException{"bug: the value somehow never reached zero"};
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    auto queries = 0;
    for (std::cin >> queries; queries > 0; --queries) {
        auto n = 0;
        std::cin >> n;
        std::cout << count_steps_to_zero(n) << '\n';
    }
}

#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <stdexcept>

namespace {
    class BfsException : public std::logic_error {
        using std::logic_error::logic_error;
    };

    int count_steps_to_zero(int n)
    {
        std::queue<int> q;
        q.push(n);

        for (auto count = 0; !q.empty(); ++count) {
            for (auto len = q.size(); len != 0u; --len) {
                n = q.front();
                q.pop();

                if (n < 2) return count + n;

                for (auto k = static_cast<int>(std::sqrt(n)); k != 1; --k)
                    if (n % k == 0) q.push(n / k);

                q.push(n - 1);
            }
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

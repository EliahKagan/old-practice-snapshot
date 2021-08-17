#include <cstddef>
#include <functional>
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
public:
    static double knightProbability(int n, int k, int r, int c);
};

namespace {
    struct Subproblem {
        int k, r, c;
    };

    constexpr bool operator==(const Subproblem& lhs,
                              const Subproblem& rhs) noexcept
    {
        return lhs.k == rhs.k && lhs.r == rhs.r && lhs.c == rhs.c;
    }

    constexpr bool operator!=(const Subproblem& lhs,
                              const Subproblem& rhs) noexcept
    {
        return !(lhs == rhs);
    }
}

namespace std {
    template<>
    struct hash<Subproblem> {
        constexpr size_t
        operator()(const Subproblem& subproblem) const noexcept;
    };

    constexpr size_t
    hash<Subproblem>::operator()(const Subproblem& subproblem) const noexcept
    {
        constexpr size_t p {17}, q {31}; // hashing primes

        auto ret = p;
        ret = ret * q + static_cast<size_t>(subproblem.k);
        ret = ret * q + static_cast<size_t>(subproblem.r);
        ret = ret * q + static_cast<size_t>(subproblem.c);
        return ret;
    }
}

namespace {
    constexpr auto a = 1, b = 2; // A chess knight is a Knight(a, b).

    constexpr auto one_eighth = 0.125;
}

double Solution::knightProbability(const int n, const int k,
                                   const int r, const int c)
{
    unordered_map<Subproblem, double> dp;

    const function<double(int, int, int)>
    solve = [n, &dp, &solve](const int depth, const int i, const int j) {
        if (i < 0 || i >= n || j < 0 || j >= n) return 0.0;

        if (depth == 0) return 1.0;

        const Subproblem subproblem {depth, i, j};
        const auto it = dp.find(subproblem);
        if (it != end(dp)) return it->second;

        const auto ret = (solve(depth - 1, i - a, j - b)
                        + solve(depth - 1, i - a, j + b)
                        + solve(depth - 1, i + a, j - b)
                        + solve(depth - 1, i + a, j + b)
                        + solve(depth - 1, i - b, j - a)
                        + solve(depth - 1, i - b, j + a)
                        + solve(depth - 1, i + b, j - a)
                        + solve(depth - 1, i + b, j + a)) * one_eighth;

        dp.emplace(subproblem, ret);
        return ret;
    };

    return solve(k, r, c);
}

int main()
{
	constexpr Solution s;
	std::cout << s.knightProbability(3, 2, 0, 0) << '\n';
}

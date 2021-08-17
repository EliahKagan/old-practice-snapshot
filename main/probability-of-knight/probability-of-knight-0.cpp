#include <cstddef>
#include <functional>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <unordered_map>

namespace {
    struct State {
        int x, y, k;
    };

    constexpr bool operator==(const State& lhs, const State& rhs)
    {
        return lhs.x == rhs.x && lhs.y == rhs.y && lhs.k == rhs.k;
    }

    constexpr bool operator!=(const State& lhs, const State& rhs)
    {
        return !(lhs == rhs);
    }
}

namespace std {
    template<>
    struct hash<State> {
        size_t operator()(const State& state) const noexcept
        {
            return hash_(state.x | state.y << 8 | state.k << 16);
        }

    private:
        hash<int> hash_;
    };
}

namespace {
    class OnBoardProbabilityCalculator {
    public:
        explicit OnBoardProbabilityCalculator(int n);
        double operator()(int x, int y, int k);

    private:
        inline bool check_and_adjust(int& coord) const noexcept;
        double calc(int x, int y, int k);

        std::unordered_map<State, double> memo_;
        int max_, half_;
    };

    OnBoardProbabilityCalculator::OnBoardProbabilityCalculator(const int n)
        : memo_{}, max_{n - 1}, half_{n / 2}
    {
        static constexpr auto min_size = 1, max_size = 255;

        if (n < min_size || n > max_size)
            throw std::out_of_range{"bad board size"};
    }

    double OnBoardProbabilityCalculator::operator()(const int x, const int y,
                                                    const int k)
    {
        if (k < 0) throw std::out_of_range{"can't take negatively many steps"};
        return calc(x, y, k);
    }

    inline bool
    OnBoardProbabilityCalculator::check_and_adjust(int& coord) const noexcept
    {
        if (coord >= half_) coord = max_ - coord;
        return coord >= 0;
    }

    double OnBoardProbabilityCalculator::calc(int x, int y, const int k)
    {
        if (!(check_and_adjust(x) && check_and_adjust(y))) return 0.0;
        if (k == 0) return 1.0;

        State state {x, y, k};

        {
            const auto p = memo_.find(state);
            if (p != memo_.end()) return p->second;
        }

        static constexpr auto a = 1, b = 2; // coord changes a knight can make
        static constexpr auto eighth = 0.125;

        const auto ans = (calc(x + a, y + b, k - 1) + calc(x + a, y - b, k - 1)
                        + calc(x - a, y + b, k - 1) + calc(x - a, y - b, k - 1)
                        + calc(x + b, y + a, k - 1) + calc(x + b, y - a, k - 1)
                        + calc(x - b, y + a, k - 1) + calc(x - b, y - a, k - 1)
                ) * eighth;

        memo_.emplace(state, ans);
        return ans;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto n = 0, x = 0, y = 0, k = 0;
        std::cin >> n >> x >> y >> k;

        std::cout << std::fixed << std::setprecision(6)
                  << OnBoardProbabilityCalculator{n}(x, y, k) << '\n';
    }
}

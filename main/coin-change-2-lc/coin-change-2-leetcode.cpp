namespace {
    constexpr size_t k_hashing_prime {31u};

    struct Subproblem {
        size_t index;
        int subtot;
    };

    inline bool operator==(const Subproblem& lhs, const Subproblem& rhs)
    {
        return lhs.index == rhs.index && lhs.subtot == rhs.subtot;
    }

    inline bool operator!=(const Subproblem& lhs, const Subproblem& rhs)
    {
        return !(lhs == rhs);
    }
}

namespace std {
    template<>
    struct hash<Subproblem> {
        size_t operator()(const Subproblem& key) const noexcept
        {
            return key.index
                 + k_hashing_prime * static_cast<size_t>(key.subtot);
        }
    };
}

class Solution {
public:
    static int change(int amount, const vector<int>& coins);
};

int Solution::change(const int amount, const vector<int>& coins)
{
    const auto len = coins.size();
    unordered_map<Subproblem, int> memo;

    const function<int(size_t,int)>
    ways = [&coins, len, &memo, &ways](size_t index, int subtot) {
        if (subtot == 0) return 1;
        if (index == len) return 0;

        const Subproblem subproblem {index, subtot};
        const auto p = memo.find(subproblem);
        if (p != end(memo)) return p->second;

        auto count = 0;
        for (const auto value = coins[index++]; subtot >= 0; subtot -= value)
            count += ways(index, subtot);

        memo.emplace(subproblem, count);
        return count;
    };

    return ways(0u, amount);
}

class Solution {
public:
    static int findPairs(vector<int>& nums, int k) noexcept;
};

namespace {
    int count_nonunique_values(const vector<int>& nums) noexcept
    {
        unordered_map<int, int> freqs;

        return accumulate(cbegin(nums), cend(nums), 0,
                [&freqs](const auto acc, const auto elem) noexcept {
            return acc + (++freqs[elem] == 2);
        });
    }

    int count_distinct_k_diff_pairs(const vector<int>& nums,
                                    const int k) noexcept
    {
        assert(k > 0);

        unordered_set<int> seen;

        return accumulate(cbegin(nums), cend(nums), 0,
                [k, &seen](const auto acc, const auto elem) noexcept {
            bool inserted {};
            tie(ignore, inserted) = seen.insert(elem);
            if (!inserted) return acc; // value was already processed

            return acc + (seen.count(elem - k) || seen.count(elem + k));
        });
    }
}

int Solution::findPairs(const vector<int>& nums, const int k) noexcept
{
    if (k < 0) return 0; // because it is absolute difference: |x - y| >= 0.
    if (k == 0) return count_nonunique_values(nums);
    return count_unique_k_diff_pairs(nums, k);
}

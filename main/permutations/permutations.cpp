class Solution {
public:
    static vector<vector<int>> permute(const vector<int>& nums) noexcept;
};

namespace {
    using It = vector<int>::const_iterator;

    vector<vector<int>> permute_range(const It first, const It last) noexcept
    {
        vector<vector<int>> permutations;

        if (first == last) {
            permutations.emplace_back();
            return permutations;
        }

        for (auto pos = first; pos != last; ++pos) {
            vector<int> rest;
            copy(first, pos, back_inserter(rest));
            copy(pos + 1, last, back_inserter(rest));

            for (auto& tail : permute_range(cbegin(rest), cend(rest))) {
                tail.insert(cbegin(tail), *pos);
                permutations.push_back(move(tail));
            }
        }

        return permutations;
    }
}

vector<vector<int>> Solution::permute(const vector<int>& nums) noexcept
{
    return permute_range(cbegin(nums), cend(nums));
}

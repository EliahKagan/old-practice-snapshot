class Solution {
public:
    int longestConsecutive(vector<int>& nums)
    {
        const unordered_set<int> s (cbegin(nums), cend(nums));
        const auto absent = s.end();
        auto ret = 0;

        for (const auto i : nums) {
            if (i == numeric_limits<int>::min() || s.find(i - 1) == absent) {
                auto j = i;
                while (j != numeric_limits<int>::max()
                            && s.find(j + 1) != absent)
                    ++j;

                ret = max(ret, j - i + 1);
            }
        }

        return ret;
    }
};

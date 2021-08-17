class Solution {
public:
    int fourSumCount(vector<int>& __restrict a, vector<int>& __restrict b,
                     vector<int>& __restrict c, vector<int>& __restrict d)
    {
        unordered_map<int, int> ab_counts;
        for (const auto w : a)
            for (const auto x : b) ++ab_counts[w + x];

        const auto not_found = end(ab_counts);

        auto count = 0;
        for (const auto y : c) {
            for (const auto z : d) {
                const auto it = ab_counts.find(-(y + z));
                if (it != not_found) count += it->second;
            }
        }

        return count;
    }
};

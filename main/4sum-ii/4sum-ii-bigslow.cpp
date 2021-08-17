class Solution {
public:
    int fourSumCount(vector<int>& __restrict a, vector<int>& __restrict b,
                     vector<int>& __restrict c, vector<int>& __restrict d)
    {
        unordered_map<int, int> history;
        for (const auto w : a) {
            for (const auto x : b) {
                const auto wxsum = w + x;
                for (const auto y : c) ++history[wxsum + y];
            }
        }

        const auto not_found = end(history);

        auto count = 0;
        for (const auto z : d) {
            const auto it = history.find(-z);
            if (it != not_found) count += it->second;
        }

        return count;
    }
};

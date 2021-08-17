class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        string::difference_type best {0};

        unordered_map<char, int> counts;
        const auto stop = s.cend();
        for (auto p = s.cbegin(), q = p; q != stop; ++q) {
            if (++counts[*q] == 2) {
                do --counts[*p];
                while (*p++ != *q);
            }

            best = max(best, q - p + 1);
        }

        return static_cast<int>(best);
    }
};

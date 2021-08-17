#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <unordered_set>
#include <vector>
using namespace std;

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

int main() // unit test
{
    vector<int> a {100, 4, 200, 1, 3, 2};
    cout << Solution{}.longestConsecutive(a) << '\n';

    vector<int> b {71, -43242, 36, 70, 37, 72, 44, 0, 0, 35254, 0, 0, 0};
    cout << Solution{}.longestConsecutive(b) << '\n';

    vector<int> c {71, -43242, 36, 70, 37, 72, 44, 0, 0, 35254, 0, 0, 0,
                   static_cast<int>(-2147483648LL), -2147483647,
                   2147483647, 2147483646};
    cout << Solution{}.longestConsecutive(c) << '\n';
}

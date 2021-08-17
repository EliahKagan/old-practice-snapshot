#include <iostream>
#include <iterator>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

class Solution {
public:
    static bool containsNearbyAlmostDuplicate(const vector<int>& nums,
                                              int k, int t);
};

bool Solution::containsNearbyAlmostDuplicate(const vector<int>& nums,
                                             int k, const int t)
{
    if (k <= 0 || t < 0) return false;
    const long long radius {t};
    
    const auto stop = cend(nums);
    auto left = cbegin(nums), right = left;
    
    set<int> near;
    const auto offer = [radius, &near](const int key) { // true iff near-dupe found
        const auto endpos = end(near);

        set<int>::iterator lower, upper;
        tie(lower, upper) = near.equal_range(key);

        if ((lower != endpos && *lower == key)
                || (lower != begin(near)
                    && static_cast<long long>(key) - *--lower <= radius)
                || (upper != endpos
                    && *upper - static_cast<long long>(key) <= radius))
            return true;
        
        near.insert(upper, key);
        return false;
    };
    
    for (; right != stop && k != 0; ++right, --k)
        if (offer(*right)) return true;
    
    for (; right != stop; ++left, ++right) {
        if (offer(*right)) return true;
        near.erase(*left);
    }
    
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cout << boolalpha;

    Solution s;
    vector<int> a {1, 2, 3, 1};
    cout << s.containsNearbyAlmostDuplicate(a, 2, 0) << '\n';

    vector<int> b {-1, 2147483647};
    cout << s.containsNearbyAlmostDuplicate(b, 1, 2147483647) << '\n';
}

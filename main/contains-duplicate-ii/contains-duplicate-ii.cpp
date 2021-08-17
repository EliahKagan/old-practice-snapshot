class Solution {
public:
    static bool containsNearbyDuplicate(const vector<int>& nums, int k);
};

bool Solution::containsNearbyDuplicate(const vector<int>& nums, int k)
{
    if (k <= 0) return false;

    const auto stop = cend(nums);
    auto left = cbegin(nums), right = left;

    unordered_set<int> near;
    for (; right != stop && k != 0; ++right, --k) {
        if (near.find(*right) != end(near)) return true;
        near.insert(*right);
    }

    for (; right != stop; ++left, ++right) {
        if (near.find(*right) != end(near)) return true;
        near.insert(*right);
        near.erase(*left);
    }

    return false;
}

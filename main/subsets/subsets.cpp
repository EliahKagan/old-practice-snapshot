class Solution {
public:
    static vector<vector<int>> subsets(const vector<int>& nums);
};

vector<vector<int>> Solution::subsets(const vector<int>& nums)
{
    vector<vector<int>> powerset;
    powerset.reserve(size_t{1} << nums.size());
    powerset.emplace_back(); // the empty subset

    for (const auto element : nums) {
        const auto old_size = powerset.size();
        for (size_t i {0}; i != old_size; ++i) {
            powerset.push_back(powerset[i]);
            powerset.back().push_back(element);
        }
    }

    return powerset;
}

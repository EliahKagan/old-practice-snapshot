class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> result;

        unordered_map<int, vector<int>::size_type> history;
        for (vector<int>::size_type i {0u}; i != nums.size(); ++i) {
            const auto p = history.find(target - nums[i]);
            if (p == history.end()) {
                history.emplace(nums[i], i);
            } else {
                result.push_back(static_cast<int>(p->second));
                result.push_back(static_cast<int>(i));
                break;
            }
        }

        return result;
    }
};

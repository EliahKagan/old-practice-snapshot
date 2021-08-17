class Solution {
public:
    static vector<vector<int>> subsets(const vector<int>& nums);

private:
    static vector<vector<int>> subsets(vector<int>::const_iterator first,
                                       vector<int>::const_iterator last);
};

vector<vector<int>> Solution::subsets(const vector<int>& nums)
{
    return subsets(cbegin(nums), cend(nums));
}

vector<vector<int>> Solution::subsets(const vector<int>::const_iterator first,
                                      vector<int>::const_iterator last)
{
    if (first == last) return vector<vector<int>>(1); // {{}}

    auto powerset = subsets(first, --last);
    const auto element = *last;

    const auto old_size = powerset.size();
    for (size_t i {0}; i != old_size; ++i) {
        powerset.push_back(powerset[i]);
        powerset.back().push_back(element);
    }

    return powerset;
}

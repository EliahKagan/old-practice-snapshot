class Solution {
public:
    static vector<int> sortArrayByParity(vector<int>& a) noexcept;
};

vector<int> Solution::sortArrayByParity(vector<int>& a) noexcept
{
    stable_partition(begin(a), end(a),
                     [](const auto x) noexcept { return x % 2 == 0; });

    return std::move(a);
}

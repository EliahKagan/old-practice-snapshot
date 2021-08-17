class Solution {
public:
    static vector<int> plusOne(vector<int>& digits) noexcept;
};

vector<int> Solution::plusOne(vector<int>& digits) noexcept
{
    static constexpr auto base = 10;
    const auto last = rend(digits);

    auto first = rbegin(digits);
    for (; first != last && ++*first == base; ++first) *first = 0;
    if (first == last) digits.insert(cbegin(digits), 1);
    return digits;
}

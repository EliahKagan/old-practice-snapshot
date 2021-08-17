class Solution {
public:
    static vector<int> sortArrayByParityII(vector<int>& a) noexcept;
};

vector<int> Solution::sortArrayByParityII(vector<int>& a) noexcept
{
    const auto n = static_cast<int>(a.size());
    vector<int> b (n);
    auto i = 0, j = 0;

    for (auto k = 0; k < n; k += 2) {
        while (a[i] % 2 != 0) ++i;
        b[k] = a[i++];

        while (a[j] % 2 == 0) ++j;
        b[k + 1] = a[j++];
    }

    return b;
}

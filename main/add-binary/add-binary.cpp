class Solution {
public:
    static string addBinary(const string& a, const string& b) noexcept;
};

string Solution::addBinary(const string& a, const string& b) noexcept
{
    string ret;
    ret.reserve(a.size() + b.size() + 1u);

    auto carry = 0;

    const auto pp = crend(a), qq = crend(b);
    auto p = crbegin(a), q = crbegin(b);

    for (; p != pp && q != qq; ++p, ++q) {
        carry += (*p != '0') + (*q != '0');
        ret.push_back(carry % 2 != 0 ? '1' : '0');
        carry /= 2;
    }

    for (; p != pp; ++p) {
        carry += (*p != '0');
        ret.push_back(carry % 2 != 0 ? '1' : '0');
        carry /= 2;
    }

    for (; q != qq; ++q) {
        carry += (*q != '0');
        ret.push_back(carry % 2 != 0 ? '1' : '0');
        carry /= 2;
    }

    if (carry != 0) ret.push_back('1');
    reverse(begin(ret), end(ret));
    return ret;
}

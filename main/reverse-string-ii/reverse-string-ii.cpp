class Solution {
public:
    static string reverseStr(string s, int k);
};

string Solution::reverseStr(string s, const int k)
{
    auto rev = true;
    const auto q = end(s);
    auto p = begin(s);

    while (q - p >= k) {
        auto pp = p + k;
        if (rev) reverse(p, pp);
        p = pp;
        rev = !rev;
    }

    if (rev) reverse(p, q);

    return s;
}

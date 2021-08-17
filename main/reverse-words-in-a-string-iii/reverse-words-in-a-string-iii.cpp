class Solution {
public:
    string reverseWords(string s);

private:
    template<typename It>
    static bool skipping(It it);
};

string Solution::reverseWords(string s)
{
    const auto qq = end(s);

    for (auto p = begin(s); p != qq; ) {
        while (p != qq && skipping(p)) ++p;

        auto q = p;
        while (q != qq && !skipping(q)) ++q;

        reverse(p, q);
        p = q;
    }

    return s;
}

template<typename It>
inline bool Solution::skipping(const It it)
{
    return isspace(static_cast<unsigned char>(*it));
}

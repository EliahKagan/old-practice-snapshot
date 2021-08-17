class Solution {
public:
    static bool isIsomorphic(string s, string t) noexcept;
};

namespace {
    void canonicalize(string& s)
    {
        auto next_unused = numeric_limits<char>::min();
        unordered_map<char, char> tr;

        for (auto& c : s) {
            const auto p = tr.find(c);

            if (p == end(tr)) {
                tr.emplace(c, next_unused);
                c = next_unused++;
            } else {
                c = p->second;
            }
        }
    }
}

bool Solution::isIsomorphic(string s, string t) noexcept
{
    canonicalize(s);
    canonicalize(t);
    return s == t;
}

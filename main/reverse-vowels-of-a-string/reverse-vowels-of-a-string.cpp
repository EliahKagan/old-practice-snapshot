class Solution {
public:
    static string reverseVowels(string s);

private:
    template<typename It>
    static bool consonant(It it);
};

string Solution::reverseVowels(string s)
{
    if (s.size() < 2u) return s;

    for (auto p = begin(s), q = prev(end(s)); p < q; ) {
        if (consonant(p)) {
            ++p;
        } else if (consonant(q)) {
            --q;
        } else {
            iter_swap(p, q);
            ++p;
            --q;
        }
    }

    return s;
}

template<typename It>
inline bool Solution::consonant(const It it)
{
    switch (*it) {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
    case 'A':
    case 'E':
    case 'I':
    case 'O':
    case 'U':
        return false;

    default:
        return true;
    }
}

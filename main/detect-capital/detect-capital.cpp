class Solution {
public:
    static bool detectCapitalUse(const string& word);

private:
    template<typename It>
    static bool cap(It it);
};

bool Solution::detectCapitalUse(const string& word)
{
    const auto q = cend(word);
    auto p = cbegin(word);
    if (p == q) return true;

    if (!cap(p)) {
        while (++p != q)
            if (cap(p)) return false;

        return true;
    }

    if (++p == q) return true;

    if (cap(p)) {
        while (++p != q)
            if (!cap(p)) return false;

        return true;
    }

    while (++p != q)
        if (cap(p)) return false;

    return true;
}

template<typename It>
inline bool Solution::cap(const It it)
{
    return isupper(static_cast<unsigned char>(*it));
}

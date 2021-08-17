class Solution {
public:
    static bool isAlienSorted(const vector<string>& words,
                              const string& order) noexcept;
};

namespace {
    using Ordinals = array<int, 'z' + 1 - 'a'>;
    
    Ordinals make_ordinals(const string& order) noexcept
    {
        Ordinals ordinals {};
        
        for (auto i = 0; i != order.size(); ++i)
            ordinals[order[i] - 'a'] = i + 1;
        
        return ordinals;
    }
}

bool Solution::isAlienSorted(const vector<string>& words,
                             const string& order) noexcept
{
    const auto ordinals = make_ordinals(order);
    
    return is_sorted(cbegin(words), cend(words),
            [&](const string& lw, const string& rw) noexcept {
        return lexicographical_compare(cbegin(lw), cend(lw),
                                       cbegin(rw), cend(rw),
                [&](const char lc, const char rc) noexcept {
            return ordinals[lc - 'a'] < ordinals[rc - 'a'];
        });
    });
}

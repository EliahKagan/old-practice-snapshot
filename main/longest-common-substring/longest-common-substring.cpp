#include <iostream>
#include <iterator>
#include <string>

namespace {
    using It = std::string::const_iterator;
    
    // Helper for common_length(const std::string&, const std::string&).
    inline int common_length(It s_first, const It& s_last,
                             It t_first, const It& t_last) {
        auto len = 0;
        
        while (s_first != s_last && t_first != t_last
                && *s_first == *t_first) {
            ++len;
            ++s_first;
            ++t_first;
        }
        
        return len;
    }
    
    // Returns the length of the longest common substring. Uses the naive
    // algorithm which completes in O(N**3) for strings of length N, since
    // N is known (from problem constraints) to be no more than 100.
    int common_length(const std::string& s, const std::string& t)
    {
        auto maxlen = 0;
        
        const auto s_last = s.cend(), t_last = t.cend();
        
        for (auto s_first = s.cbegin(); s_first != s_last; ++s_first) {
            for (auto t_first = t.cbegin(); t_first != t_last; ++t_first) {
                if (*s_first != *t_first) continue;
                
                const auto len = 1 + common_length(std::next(s_first), s_last,
                                                   std::next(t_first), t_last);
                
                if (maxlen < len) maxlen = len;
            }
        }
        
        return maxlen;
    }
}

int main()
{
    auto tc = 0;
    for (std::cin >> tc; tc > 0; --tc) {
        int n;
        std::cin >> n >> n;
        
        std::string s, t;
        std::cin >> s >> t;
        
        std::cout << common_length(s, t) << '\n';
    }
}

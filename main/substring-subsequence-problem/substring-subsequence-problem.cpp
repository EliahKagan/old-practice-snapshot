#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

namespace {
    using It = std::string::const_iterator;
    
    // Helper for common_length(const std::string&, const std::string&).
    inline int common_length(const std::string& s,
                             It t_first, const It& t_last)
    {
        auto len = 0;
        
        for (const auto c : s) {
            if (c == *t_first) {
                ++len;
                if (++t_first == t_last) break;
            }
        }
        
        return len;
    }
    
    // Returns the length of the longest (possibly noncontiguous) subsequence
    // of s that is a (contiguous) substring of t.
    int common_length(const std::string& s, const std::string& t)
    {
        auto maxlen = 0;
        
        const auto t_last = t.cend();
        for (auto t_first = t.cbegin(); t_first != t_last; ++t_first)
            maxlen = std::max(maxlen, common_length(s, t_first, t_last));
        
        return maxlen;
    }
}

int main()
{
    auto tc = 0;
    for (std::cin >> tc; tc > 0; --tc) {
        std::string s, t;
        std::cin >> s >> t;
        
        std::cout << common_length(s, t) << '\n';
    }
}

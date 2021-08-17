#include <iostream>
#include <string>

namespace {
    using It = std::string::const_iterator;
    using Offset = std::string::difference_type;
    
    inline bool is_palindrome(It first, It last) // [first, last) is palindrome
    {
        for (; first < last; ++first)
            if (*first != *--last) return false;
        
        return true;
    }
    
    inline bool window_slides_to_palindrome(It left, It mid, const It right)
    {
        for (; ; ++left, ++mid) {
            if (is_palindrome(left, mid)) return true;
            if (mid == right) return false;
        }
    }
    
    Offset find_max_palindrome_length(const std::string& s)
    {
        if (s.empty()) return 0;
        
        
    }
}

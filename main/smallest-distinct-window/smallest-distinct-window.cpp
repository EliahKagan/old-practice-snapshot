#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

namespace {
    using It = std::string::const_iterator;

    // Returns a character frequency table. Stores, in right, an iterator to
    // the rightmost position where a new distinct character was seen.
    inline std::unordered_map<char, int> get_counts(It first, const It& last,
                                                    It& right)
    {
        std::unordered_map<char, int> counts;

        for (; first != last; ++first)
            if (++counts[*first] == 1) right = first;

        return counts;
    }
    
    // Decrements counts table entries for chars in the range [start, stop).
    inline void subtract_counts(std::unordered_map<char, int>& counts,
                                It first, const It& last)
    {
        for (; first != last; ++first) --counts.at(*first);
    }

    // Returns the narrowest width of a window within s in which each
    // distinct character in s appears at least once.
    std::string::difference_type min_cover_size(const std::string& s)
    {
        const auto stop = s.cend();
        auto left = s.cbegin(), right = stop;

        auto counts = get_counts(left, stop, right);
        subtract_counts(counts, right, stop);
        
        auto width = right - left;
        
        for (; right != stop; ++right) {
            ++counts.at(*right);

            while (counts.at(*left) != 1) {
                --counts.at(*left);
                ++left;
            }

            width = std::min(width, right - left);
        }
        
        return width + 1;
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::string s;
        std::cin >> s;
        std::cout << min_cover_size(s) << '\n';
    }
}

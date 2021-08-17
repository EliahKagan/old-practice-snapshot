// Smallest window in a string containing all the characters of another string
//
// This version outputs the widths (rather than the first matching substring)
// and only requires duplicate characters in the pattern be matched by a single
// character in the text.

#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <unordered_map>
#include <utility>

namespace {
    constexpr auto debug_window_validation = true;

    using It = std::string::const_iterator;

    // Returns a character frequency table.
    inline std::unordered_map<char, int> get_counts(It first, const It& last)
    {
        std::unordered_map<char, int> counts;
        for (; first != last; ++first) ++counts[*first];
        return counts;
    }

    // Returns an iterator to the final element in the narrowest subrange
    // beginning at first (and ending before last) that contains at least one
    // of each character with a nonzero count in the counts table, or to last,
    // if there is no such subrange. Updates counts to hold the frequencies of
    // characters in the subrange that were matched (and nothing else).
    It find_leading_cover(std::unordered_map<char, int>& counts,
                          It first, const It& last)
    {
        std::unordered_map<char, int> found;

        const auto q = counts.cend();
        for (auto n = counts.size(); first != last; ++first) {
            if (counts.find(*first) != q && ++found[*first] == 1 && --n == 0)
                break; // we've matched every distinct character
        }

        std::swap(counts, found);
        return first;
    }

    // Returns the narrowest width of a window within s in which each distinct
    // character in t appears at least once, or -1 if there is no such window.
    std::string::difference_type min_cover_size(const std::string& s,
                                                const std::string& t)
    {
        auto counts = get_counts(t.cbegin(), t.cend());
        const auto stop = s.cend();
        auto left = s.cbegin(), right = find_leading_cover(counts, left, stop);
        if (right == stop) return -1;

        auto width = std::numeric_limits<std::string::difference_type>::max();

        const auto trim_left_and_update = [&counts, &left, &right, &width]() {
            // Advance the left edge until we encounter a character we can
            // use but have just one of (and thus mustn't be removed).
            while (counts[*left] != 1) {
                if (counts.at(*left) != 0) --counts.at(*left);
                ++left;
            }

            width = std::min(width, right - left);

            if (debug_window_validation) {
                const std::string window(left, std::next(right));
                std::cerr << "DEBUG: " << window << "\n";
            }
        };

        for (trim_left_and_update(); ++right != stop; ) {
            if (counts[*right] != 0) { // Only use chars from s that are in t.
                ++counts.at(*right);
                trim_left_and_update();
            }
        }

        return width + 1;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    if (debug_window_validation) {
        std::cout << min_cover_size("foobar", "baz") << '\n';
        std::cout << min_cover_size("fozobar", "baz") << '\n';
        std::cout << min_cover_size("foobar", "") << '\n';
        std::cout << min_cover_size("", "baz") << '\n';
        std::cout << min_cover_size("", "") << "\n\n";
    }

    auto tc = 0;
    for (std::cin >> tc; tc > 0; --tc) {
        std::string s, t;
        std::cin >> s >> t;
        std::cout << min_cover_size(s, t) << '\n';
    }
}

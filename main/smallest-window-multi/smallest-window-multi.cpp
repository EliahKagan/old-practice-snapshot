// Smallest window in a string containing all the characters of another string
//
// This version outputs the first minimum-length matching substring.
// Matches must have each character at least as many times as in the pattern.

#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace {
    constexpr auto debug_window_validation = false;

    using Table = std::unordered_map<char, int>;
    using StrIt = std::string::const_iterator;

    // Returns a character frequency table for the "pattern" pat.
    Table get_pattern_freq(const std::string& pat)
    {
        if (pat.empty()) throw std::invalid_argument{"pattern is empty"};

        Table pat_freq;
        for (const auto c : pat) ++pat_freq[c];
        return pat_freq;
    }

    // Returns a character frequency table for the narrowest leading subrange
    // of txt that contains at least as many of each character as are present
    // in pat_freq, and writes an iterator to the last character in the
    // subrange to p. If there is no such subrange, writes a past-the-end
    // iterator to p instead. (Note: may write zero counts to pat_freq.)
    Table find_leading_cover(const std::string& txt, Table& pat_freq, StrIt& p)
    {
        if (txt.empty()) throw std::invalid_argument{"txt is empty"};
        
        Table txt_freq;
        auto pat_distinct = pat_freq.size();

        const auto q = txt.cend();
        for (p = txt.cbegin(); p != q; ++p) {
            // count characters also in pattern, until we've matched them all
            if (++txt_freq[*p] == pat_freq[*p] && --pat_distinct == 0) break;
        }

        return txt_freq;
    }

    inline void update_narrowest_window(StrIt& best_left, StrIt& best_right,
                                        const StrIt& left, const StrIt& right)
    {
        if (debug_window_validation)
            std::cerr << "DEBUG: " << std::string(left, right) << '\n';

        if (right - left < best_right - best_left) { // Is it the new best?
            best_left = left;
            best_right = right;
        }
    }

    // Returns the first minimum-width substring of text that contains every
    // character of pat at least as many times as it appears in pat, or an
    // empty string if text contains no such window.
    std::string get_min_cover(const std::string& txt, const std::string& pat)
    {
        const auto stop = txt.cend();
        auto left = txt.cbegin(), right = stop; // right can start as anything

        auto pat_freq = get_pattern_freq(pat);
        auto txt_freq = find_leading_cover(txt, pat_freq, right);

        if (right == stop) return std::string{};

        for (auto best_left = left, best_right = stop; ; ) {
            ++right; // note: also incremented in the optimization at the end!

            // Advance the left edge to a character whose removal would cause
            // txt no longer to contain the characters of pat.
            for (; txt_freq[*left] > pat_freq[*left]; ++left)
                --txt_freq[*left];

            update_narrowest_window(best_left, best_right, left, right);

            // As an optimization, advance the right edge to a character whose
            // inclusion makes txt _redundantly_ contain the characters of pat.
            for (; ; ++right) {
                // When we reach the end, return the best window.
                if (right == stop) return std::string(best_left, best_right);

                if (txt_freq[*right]++ == pat_freq[*right]) break;
            }
        }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::string txt, pat;
        std::cin >> txt >> pat;

        const auto w = get_min_cover(txt, pat);

        if (w.empty()) std::cout << "-1\n";
        else std::cout << w << '\n';
    }
}

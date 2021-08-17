#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

namespace {
    using Delta = std::string::difference_type;

    using It = std::string::const_iterator;

    // Counts the number of ranges that contain only 0s.
    Delta count_zero_ranges(const std::string& text) noexcept
    {
        Delta count {0};

        const auto last = text.cend();

        for (auto left = text.cbegin(); left != last ; ) {
            left = std::find(left, last, '0');
            const auto right = std::find(left, last, '1');
            
            const auto width = right - left;
            count += width * (width + 1) / 2;

            left = right;
        }

        return count;
    }

    // Counts the number of ranges in [left, last) that contain the same number
    // of 1s as are contained in [left, right). Assumes this number is nonzero.
    Delta count_same_pop_substrs(It left, It right, const It last) noexcept
    {
        for (Delta count {0}; ; ) {
            // consume trailing and leading 0s to count matching subintervals
            const auto prev_right = right, prev_left = left;
            right = std::find(right, last, '1');
            left = std::find(left, last, '1');
            count += (right - prev_right + 1) * (left - prev_left + 1);

            // if we were unable to pick up another 1 on the right, we're done
            if (right == last) return count;

            // otherwise pick up a 1 on the right and drop a 1 on the left
            ++right;
            ++left;
        }
    }

    // Counts the number of ranges that contain exactly pop 1s.
    Delta count_pop_substrs(const std::string& text, Delta pop) noexcept
    {
        if (pop <= 0) return pop == 0 ? count_zero_ranges(text) : 0;
        
        const auto last = text.cend();
        auto left = text.cbegin(), right = left;

        // expand rightward to reach target population
        while (right != last && (*right == '0' || --pop != 0)) ++right;
        if (right == last) return 0;
        assert(pop == 0);

        return count_same_pop_substrs(left, ++right, last);
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::string text;
        Delta pop {};
        std::cin >> text >> pop;

        std::cout << count_pop_substrs(text, pop) << '\n';
    }
}

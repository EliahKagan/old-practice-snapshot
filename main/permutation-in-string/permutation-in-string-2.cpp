class Solution {
public:
    static bool checkInclusion(const string& pattern,
                               const string& text) noexcept;
};

namespace {
    constexpr auto alpha_len = 'z' - 'a' + 1;
    static_assert(alpha_len == 26, "alphabet has unexpected length");

    class CharDiff {
    public:
        constexpr bool zero() const noexcept;

        void inc(char ch) noexcept;

        void dec(char ch) noexcept;

    private:
        array<int, alpha_len> deltas_ {};
        int nonzero_count_ {};
    };

    constexpr bool CharDiff::zero() const noexcept
    {
        return nonzero_count_ == 0;
    }

    inline void CharDiff::inc(const char ch) noexcept
    {
        switch (++deltas_[ch - 'a']) {
        case 0:
            --nonzero_count_; // was negative and is now zero
            break;

        case 1:
            ++nonzero_count_; // was zero and is now positive
            break;

        default:
            ; // was nonzero and still is, so do nothing
        }
    }

    inline void CharDiff::dec(const char ch) noexcept
    {
        switch (--deltas_[ch - 'a']) {
        case 0:
            --nonzero_count_; // was positive and is now zero
            break;

        case -1:
            ++nonzero_count_; // was zero and is now negative
            break;

        default:
            ; // was nonzero and still is, so do nothing
        }
    }
}

bool Solution::checkInclusion(const string& pattern,
                              const string& text) noexcept
{
    if (text.size() < pattern.size()) return false;

    CharDiff diff;
    for (const auto ch : pattern) diff.inc(ch);

    auto left = cbegin(text);

    auto right = left;
    for (const auto stop = right + pattern.size(); right != stop; ++right)
        diff.dec(*right);

    if (diff.zero()) return true;

    for (const auto last = cend(text); right != last; ++left, ++right) {
        diff.inc(*left);
        diff.dec(*right);
        if (diff.zero()) return true;
    }

    return false;
}

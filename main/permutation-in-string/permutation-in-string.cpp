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
        array<int, alpha_len> coords_ {};
        int norm_ {};
    };

    constexpr bool CharDiff::zero() const noexcept
    {
        return norm_ == 0;
    }

    inline void CharDiff::inc(const char ch) noexcept
    {
        if (++coords_[ch - 'a'] > 0) {
            // We started nonnegative and became (more) positive.
            ++norm_;
        } else {
            // We started negative and became less (or not) negative.
            --norm_;
        }
    }

    inline void CharDiff::dec(const char ch) noexcept
    {
        if (--coords_[ch - 'a'] < 0) {
            // We started nonpositive and became (more) negative.
            ++norm_;
        } else {
            // We started positive and became less (or not) positive.
            --norm_;
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

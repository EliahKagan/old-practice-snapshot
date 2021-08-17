class Solution {
public:
    static vector<int> prisonAfterNDays(const vector<int>& cells,
                                        int n) noexcept;
};

namespace {
    constexpr auto len = 8;

    bitset<len> to_bitset(const vector<int>& cells) noexcept
    {
        assert(cells.size() == len);

        bitset<len> bits {};
        for (auto i = 0; i < len; ++i) bits.set(i, cells[i] != 0);
        return bits;
    }

    vector<int> from_bitset(const bitset<len> bits) noexcept
    {
        vector<int> ret (len);
        for (auto i = 0; i < len; ++i) ret[i] = bits[i];
        return ret;
    }

    inline bitset<len> next_day(const bitset<len> bits) noexcept
    {
        bitset<len> ret {};

        for (auto i = 1; i < len - 1; ++i)
            ret.set(i, bits[i - 1] == bits[i + 1]);

        return ret;
    }
}

vector<int> Solution::prisonAfterNDays(const vector<int>& cells,
                                       const int n) noexcept
{
    const auto orig = to_bitset(cells);
    assert(n > 0);

    auto t = 0;
    auto bits = orig;

    while (t < n) {
        ++t;
        bits = next_day(bits);
        if (bits == orig) break;
    }

    assert(t > 0);
    for (auto m = n % t; m > 0; --m) bits = next_day(bits);
    return from_bitset(bits);
}

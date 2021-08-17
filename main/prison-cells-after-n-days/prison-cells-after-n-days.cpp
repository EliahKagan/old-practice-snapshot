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
    assert(n > 0);
    auto t = 0;
    auto bits = to_bitset(cells);
    unordered_map<bitset<len>, int> times;
    times.emplace(bits, t);

    decltype(times)::iterator pos {};
    auto acyclic = true;

    while (acyclic && t < n) {
        ++t;
        bits = next_day(bits);
        tie(pos, acyclic) = times.emplace(bits, t);
    }

    if (t < n) {
        assert(!acyclic);

        for (auto delta = (n - t) % (t - pos->second); delta > 0; --delta)
            bits = next_day(bits);
    }

    return from_bitset(bits);
}

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX
#endif

#ifdef __MINGW32__
#define __USE_MINGW_ANSI_STDIO 1
#endif

#include <cstdint>
#include <cstdio>
#include <limits>
#include <vector>

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

namespace {
    class BitSet {
    public:
        explicit BitSet(std::size_t capacity, bool fill = false);

        void copy_to(std::vector<std::size_t>& dest) const;

        std::size_t capacity() const { return bits_.size() * 64u; }

        bool contains(const std::size_t value) const
        {
            return bits_[value >> 6u] & one << (value & 63u);
        }

        void insert(const std::size_t value)
        {
            bits_[value >> 6u] |= one << (value & 63u);
        }

        void erase(const std::size_t value)
        {
            bits_[value >> 6u] &= ~(one << (value & 63u));
        }

    private:
        static constexpr auto zero = static_cast<std::uint64_t>(0);
        static constexpr auto one = static_cast<std::uint64_t>(1);
        static constexpr auto byte = static_cast<std::uint64_t>(0xFF);
        static constexpr auto max = std::numeric_limits<std::uint64_t>::max();

        static std::size_t length_for(const std::size_t capacity)
        {
            auto length = capacity / 64u;
            if (capacity % 64u != 0) ++length;
            return length;
        }

        std::vector<std::uint64_t> bits_;
    };

    BitSet::BitSet(const std::size_t capacity, const bool fill)
        : bits_ (length_for(capacity), (fill ? max : zero))
    {
        if (fill) {
            const auto tail = capacity % 64u;
            if (tail != 0u) bits_.back() >>= 64u - tail;
        }
    }

    void BitSet::copy_to(std::vector<std::size_t>& dest) const
    {
        const auto imax = bits_.size();
        for (std::size_t i {0u}; i != imax; ++i) {
            if (!bits_[i]) continue;

            const auto ho = i << 6;

            for (std::size_t jmin {0u}; jmin != 64u; jmin += 8u) {
                const auto b = bits_[i] & byte << jmin;
                if (!b) continue;

                const auto jstop = jmin + 8u;
                for (auto j = jmin; j != jstop; ++j)
                    if (b & one << j) dest.push_back(ho | j);
            }
        }
    }
}

int main()
{
    constexpr std::size_t range {1000u}, step {3u};

    BitSet s {range};

    for (std::size_t i {0u}; i < range; i += step) s.insert(i);

    for (std::size_t i {0u}; i != s.capacity(); ++i)
        if (s.contains(i)) std::printf("%zu ", i);

    std::putchar('\n');
}

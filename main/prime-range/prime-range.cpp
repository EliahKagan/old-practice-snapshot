#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX
#endif

#ifdef __MINGW32__
#define __USE_MINGW_ANSI_STDIO 1
#endif

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <limits>
#include <utility>
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

        template<class Transform>
        void copy_to(std::vector<std::size_t>& dest, Transform f) const;

        void copy_to(std::vector<std::size_t>& dest) const
        {
            copy_to(dest, [](const size_t k) { return k; });
        }

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

    template<class Transform>
    void BitSet::copy_to(std::vector<std::size_t>& dest, Transform f) const
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
                    if (b & one << j) dest.push_back(f(ho | j));
            }
        }
    }
}

namespace {
    class Primes {
    public:
        using It = std::vector<std::size_t>::const_iterator; // range iterator

        explicit Primes(std::size_t n);

        std::pair<It, It> range(std::size_t minval, std::size_t maxval) const;

    private:
        static BitSet sieve(std::size_t n);

        static std::size_t dusart_pi(std::size_t n);

        std::vector<std::size_t> elems_;
    };

    Primes::Primes(const std::size_t n) : elems_ {}
    {
        elems_.reserve(dusart_pi(n));
        sieve(n).copy_to(elems_, [](const size_t k) { return k * 2u + 1u; });
        elems_.front() = 2u;
    }

    std::pair<Primes::It, Primes::It>
    Primes::range(const std::size_t minval, const std::size_t maxval) const
    {
        const auto r = elems_.cend();
        auto p = std::lower_bound(elems_.cbegin(), r, minval);
        auto q = std::upper_bound(p, r, maxval);
        return std::make_pair(std::move(p), std::move(q));
    }

    BitSet Primes::sieve(const std::size_t n)
    {
        const auto len = (n + 1u) / 2u;
        BitSet s {len, true};

        const auto istop = static_cast<std::size_t>(std::sqrt(n)) / 2u + 1u;
        for (std::size_t i {1u}; i != istop; ++i) {
            if (s.contains(i)) {
                const auto jstep = i * 2u + 1u;
                for (auto j = (i + 1u) * i * 2u; j < len; j += jstep)
                    s.erase(j);
            }
        }

        return s;
    }

    // Safely overestimates the prime counting function. See:
    // https://arxiv.org/PS_cache/arxiv/pdf/1002/1002.0442v1.pdf p.2; p.9(6.5)
    // https://en.wikipedia.org/wiki/Prime_number_theorem#Bounds_on_the_prime-counting_function
    std::size_t Primes::dusart_pi(const std::size_t n)
    {
        if (n < 60'184) return n;

        const auto x = static_cast<double>(n);
        return static_cast<std::size_t>(x / std::log(x) - 1.1);
    }
}

int main()
{
    const Primes primes {100'000'000u};

    int t {};
    std::size_t minval {}, maxval {};

    for ((void)std::scanf("%d", &t); t > 0; --t) {
        (void)std::scanf("%zu-%zu", &minval, &maxval);
        
        for (auto pq = primes.range(minval, maxval); pq.first != pq.second;
                                                     ++pq.first)
            std::printf("%zu ", *pq.first);

        std::putchar('\n');
    }
}

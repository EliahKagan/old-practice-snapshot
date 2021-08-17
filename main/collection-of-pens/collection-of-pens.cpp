#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

enum class Primality : char {
    prime,    // really means not yet found to be composite (must appear first)
    composite // means definitely composite
};

namespace {
    template<typename T>
    inline T isqrt(const T n)
    {
        // For small ints, a simple cast to/from double is precise.
        return static_cast<T>(std::sqrt(static_cast<double>(n)));
    }

    template<typename T>
    T overestimate_pi_fn(const T n)
    {
        // See https://projecteuclid.org/download/pdf_1/euclid.ijm/1255631807,
        // Theorem 2, Corollary 1, equation 3.6.
        const auto x = static_cast<double>(n);
        return static_cast<T>(std::lround(std::ceil(x * 1.25506 / std::log(x))));
    }

    std::vector<Primality> raw_sieve(const std::vector<Primality>::size_type n)
    {
        std::vector<Primality> a (n + 1u);

        const auto imax = isqrt(n);
        for (std::vector<Primality>::size_type i {3u}; i <= imax; i += 2u) {
            if (a[i] == Primality::prime) {
                const auto jstep = i * 2;
                for (auto j = i * i; j <= n; j += jstep)
                    a[j] = Primality::composite;
            }
        }

        return a;
    }

    template<typename T>
    std::vector<T> sieve(const T bound)
    {
        const auto n = static_cast<std::vector<Primality>::size_type>(bound);
        const auto a = raw_sieve(n);

        std::vector<T> primes;
        primes.reserve(overestimate_pi_fn(n));

        primes.push_back(static_cast<T>(2));
        for (std::vector<Primality>::size_type i {3u}; i <= n; i += 2u)
            if (a[i] == Primality::prime) primes.push_back(static_cast<T>(i));

        return primes;
    }

    template<typename T>
    inline T next_higher(const std::vector<T>& a, T x)
    {
        const auto q = a.cend(), p = std::upper_bound(a.cbegin(), q, x);
        if (p == q) throw std::out_of_range{"no next higher element exists"};
        return *p;
    }

    template<typename T>
    T get_pair_as_sum()
    {
        T val_a {}, val_b {};
        std::cin >> val_a >> val_b;
        return val_a + val_b;
    }
}

int main()
{
    constexpr auto nmax = 2003; // with a = b = 1000, need a prime > 2000
    const auto primes = sieve(nmax);

    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        const auto n = get_pair_as_sum<int>();
        std::cout << next_higher(primes, n) - n << '\n';
    }
}

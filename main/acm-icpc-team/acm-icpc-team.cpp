#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

#include <array>
#include <bitset>
#include <cassert>
#include <cstdio>
#include <memory>

#define XSTR(x) STR(x)
#define STR(x) #x

#define NMAX 500
#define MMAX 500

int main()
{
    constexpr std::size_t nmax {NMAX}, mmax {MMAX};
    std::array<std::unique_ptr<std::bitset<mmax>>, nmax> rows;

    std::size_t n {}, m {};
    (void)std::scanf("%zu %zu", &n, &m);
    assert(n <= nmax && m <= mmax);

    char line[mmax + 1] {};
    for (std::size_t i = 0u; i != n; ++i) {
        (void)std::scanf(" %" XSTR(MMAX) "s", line);
        rows[i].reset(new std::bitset<mmax>{line, m});
    }

    std::size_t topics {0u}, teams {0u};

    const auto jstop = n, istop = jstop - 1u;

    for (std::size_t i = 0u; i != istop; ++i) {
        for (auto j = i + 1u; j != jstop; ++j) {
            const auto count = (*rows[i] | *rows[j]).count();

            if (count < topics) continue;

            if (count == topics) ++teams;
            else {
                topics = count;
                teams = 1u;
            }
        }
    }

    std::printf("%zu\n%zu\n", topics, teams);
}

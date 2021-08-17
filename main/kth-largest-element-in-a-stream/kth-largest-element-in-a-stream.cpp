#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifdef __MINGW32__
#define __USE_MINGW_ANSI_STDIO 1
#endif

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdio>
#include <functional>
#include <limits>
#include <vector>

namespace {
    constexpr std::greater<int> comp {};
    
    constexpr std::size_t nmax {1000u};
    
    inline void read_parameters(std::size_t& k, std::size_t& n)
    {
        (void)std::scanf("%zu%zu", &k, &n);
        
        assert(0 < k && k <= nmax);
        assert(0 < n && n <= nmax);
    }
    
    inline bool solve_if_trivial(const std::size_t k, const std::size_t n)
    {
        if (k > n) {
            for (auto i = n; i != 0u; --i) (void)std::scanf("%*d");
            for (auto i = n; i != 0u; --i) std::printf("-1 ");
            std::putchar('\n');
            
            return true;
        }
        
        return false;
    }
    
    inline void reset(std::vector<int>& a)
    {
        a.clear();
        a.push_back(std::numeric_limits<int>::max()); // for 1-based indexing
    }
    
    inline void process_leading_entries(std::vector<int>& a, std::size_t k)
    {
        // read the first (k - 1) values into the vector
        auto x = 0;
        for (auto i = k; --i != 0u; a.push_back(x))
            (void)std::scanf("%d", &x);
        
        // sort the vector nonincreasingly
        std::sort(a.begin(), a.end(), comp);
        
        // print a -1 for each value (since none is yet the kth highest)
        while (--k != 0u) std::printf("-1 ");
    }
    
    inline void process_remaining_entries(std::vector<int>& a,
                                          const std::size_t k, std::size_t n)
    {
        auto x = 0;
        
        for (n -= (k - 1u); n != 0; --n) {
            (void)std::scanf("%d", &x);
            a.insert(std::upper_bound(a.cbegin(), a.cend(), x, comp), x);
            std::printf("%d ", a[k]);
        }
        
        std::putchar('\n');
    }
    
    inline void run(std::vector<int>& a)
    {
        std::size_t k {}, n {};
        read_parameters(k, n);
        
        if (solve_if_trivial(k, n)) return;
        
        reset(a);
        process_leading_entries(a, k);
        process_remaining_entries(a, k, n);
    }
}

int main()
{
    std::vector<int> a;
    a.reserve(nmax + 1u);
    
    auto t = 0;
    for ((void)std::scanf("%d", &t); t > 0; --t) run(a);
}

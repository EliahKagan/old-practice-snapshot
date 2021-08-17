#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifdef __MINGW32__
#define __USE_MINGW_ANSI_STDIO 1
#endif

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <iterator>
#include <tuple>
#include <vector>

namespace {
    using Elem = std::tuple<int, int>;
    
    enum { value, index };
    
    std::vector<Elem> read_indexed_record()
    {
        std::size_t n {};
        (void)std::scanf("%zu", &n);
        std::vector<Elem> a (n);
        
        auto i = 0;
        for (auto& x : a) {
            (void)std::scanf("%d", &std::get<value>(x));
            std::get<index>(x) = i++;
        }
        
        assert(static_cast<std::size_t>(i) == n);
        return a;
    }
    
    std::vector<Elem> read_sorted_indexed_record()
    {
        auto a = read_indexed_record();
        
        // With distinct elements, there are no stability requirements on the
        // sort used to move them into position with minimal displacement.
        std::sort(std::begin(a), std::end(a), [](const Elem& x,
                                                 const Elem& y) {
            return std::get<value>(x) < std::get<value>(y);
        });
        
        return a;
    }
    
    bool was_k_sorted(const std::vector<Elem>& a, const int k)
    {
        auto i = 0;
        for (const auto& x : a)
            if (std::abs(std::get<index>(x) - i++) > k) return false;
        
        assert(static_cast<std::size_t>(i) == a.size());
        return true;
    }
}

int main()
{
    auto t = 0;
    for ((void)std::scanf("%d", &t); t > 0; --t) {
        const auto a = read_sorted_indexed_record();
        
        auto k = 0;
        (void)std::scanf("%d", &k);
        
        std::printf("%s\n", (was_k_sorted(a, k) ? "Yes": "No"));
    }
}

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <algorithm>
#include <cstdio>
#include <numeric>
#include <stdexcept>
#include <vector>

namespace {
    std::vector<int> read_record()
    {
        std::size_t n {};
        (void)std::scanf("%zu", &n);
        if (n < 3u) throw std::out_of_range{"the array is too small"};
        
        std::vector<int> a (n);
        for (auto& x : a) (void)std::scanf("%d", &x);
        return a;
    }
    
    std::vector<int> get_running_max_ltr(std::vector<int> b)
    {
        std::partial_sum(b.cbegin(), b.cend(), b.begin(),
                [](const int x, const int y) { return std::max(x, y); });
                
        return b;
    }
    
    std::vector<int> get_running_min_rtl(std::vector<int> c)
    {
        std::partial_sum(c.crbegin(), c.crend(), c.rbegin(),
                [](const int x, const int y) { return std::min(x, y); });
        
        return c;
    }
    
    int get_first_pivot(const std::vector<int>& a)
    {
        static constexpr auto not_found = -1;
        
        const auto b = get_running_max_ltr(a), c = get_running_min_rtl(a);
        
        const auto rr = c.cend();
        for (auto q = b.cbegin(), p = a.cbegin() + 1, r = c.cbegin() + 2;
                                                      r != rr; ++q, ++p, ++r)
            if (*q <= *p && *p <= *r) return *p;
        
        return not_found;
    }
}

int main()
{
    auto t = 0;
    for ((void)std::scanf("%d", &t); t > 0; --t)
        std::printf("%d\n", get_first_pivot(read_record()));
}

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifdef __MINGW32__
#define __USE_MINGW_ANSI_STDIO 1
#endif

#include <cstdio>
#include <unordered_set>
#include <vector>

namespace {
    std::vector<int> read_record(const std::size_t size)
    {
        std::vector<int> a (size);
        for (auto& e : a) (void)std::scanf("%d", &e);
        return a;
    }
    
    std::unordered_set<int> get_complements(const std::vector<int>& a,
                                            const int sum)
    {
        std::unordered_set<int> complements;
        for (const auto e : a) complements.insert(sum - e);
        return complements;
    }
    
    int count_pair_sums(const std::vector<int>& a, const std::vector<int>& b,
                        const int sum)
    {
        const auto complements = get_complements(a, sum);
        const auto not_found = complements.cend();
        
        auto count = 0;
        for (const auto e : b)
            if (complements.find(e) != not_found) ++count;
        
        return count;
    }
}

int main()
{
    auto t = 0;
    for ((void)std::scanf("%d", &t); t > 0; --t) {
        std::size_t m {}, n {};
        (void)std::scanf("%zu%zu", &m, &n);
        
        const auto a = read_record(m), b = read_record(n);
        
        auto sum = 0;
        (void)std::scanf("%d", &sum);
        
        std::printf("%d\n", count_pair_sums(a, b, sum));
    }
}

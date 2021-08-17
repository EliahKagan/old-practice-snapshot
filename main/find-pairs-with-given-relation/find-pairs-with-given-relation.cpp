#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifdef __MINGW32__
#define __USE_MINGW_ANSI_STDIO 1
#endif

#include <cstdio>
#include <unordered_map>
#include <utility>
#include <vector>

namespace {
    using std::size_t;

    std::vector<int> read_record()
    {
        size_t n {};
        (void)std::scanf("%zu", &n);

        std::vector<int> a (n);
        for (auto& x : a) (void)std::scanf("%d", &x);
        return a;
    }

    bool has_disjoint_equal_product_pairs(const std::vector<int>& a)
    {
        if (a.size() < 4u) return false;

        std::unordered_map<int, std::vector<std::pair<size_t, size_t>>> indices;
        const auto jstop = a.size(), istop = jstop - 1u;

        for (size_t i {0u}; i != istop; ++i) {
            for (auto j = i + 1u; j != jstop; ++j) {
                auto& ijs = indices[a[i] * a[j]];

                for (const auto& ij : ijs) {
                    if (i != ij.first && i != ij.second
                            && j != ij.first && j != ij.second)
                        return true;
                }

                ijs.emplace_back(i, j);
            }
        }

        return false;
    }
}

int main()
{
    auto t = 0;
    for ((void)std::scanf("%d", &t); t > 0; --t)
        std::puts(has_disjoint_equal_product_pairs(read_record()) ? "1" : "-1");
}

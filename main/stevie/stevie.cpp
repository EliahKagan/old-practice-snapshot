#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstdio>
#include <unordered_map>
#include <vector>

namespace {
    std::vector<int> read_record(const std::size_t n)
    {
        std::vector<int> a (n);
        for (auto& x : a) (void)std::scanf("%d", &x);
        return a;
    }

    std::unordered_map<int, int> get_aval_to_max_bval_map(
            const std::vector<int>& a, const std::vector<int>& b)
    {
        std::unordered_map<int, int> aval_to_max_bval;

        const auto pend = a.cend();
        for (auto p = a.cbegin(), q = b.cbegin(); p != pend; ++p, ++q) {
            // b is everywhere > 0 (and map values default to 0), so this works
            if (aval_to_max_bval[*p] < *q) aval_to_max_bval[*p] = *q;
        }

        return aval_to_max_bval;
    }
}

int main()
{
    std::size_t n {};
    (void)std::scanf("%zu", &n);

    const auto a = read_record(n), b = read_record(n);
    const auto aval_to_max_bval = get_aval_to_max_bval_map(a, b);

    for (const auto x : a) std::printf("%d ", aval_to_max_bval.at(x));
    std::putchar('\n');
}

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <set> 

namespace {
    using DescendingMultiset = std::multiset<int, std::greater<int>>;
    using AscendingMultiset = std::multiset<int, std::less<int>>;

    inline std::ptrdiff_t get_balance(const DescendingMultiset& low,
                                      const AscendingMultiset& high)
    {
        return static_cast<std::ptrdiff_t>(low.size())
                - static_cast<std::ptrdiff_t>(high.size());
    }

    inline void add(DescendingMultiset& low, AscendingMultiset& high,
                    const int e)
    {
        const auto p = low.cbegin();

        if (p == low.cend() || e < *p)  low.insert(e);
        else                            high.insert(e);
    }

    template<typename Compare>
    inline bool remove_from(std::multiset<int, Compare>& vals, const int e)
    {
        const auto p = vals.find(e);

        if (p != vals.end()) {
            vals.erase(p);
            return true;
        }

        return false;
    }

    inline bool remove(DescendingMultiset& low, AscendingMultiset& high,
                       const int e) // returns true if an element was removed
    {
        return remove_from(low, e) || remove_from(high, e);
    }

    template<typename SrcCompare, typename DestCompare>
    inline void transfer_front(std::multiset<int, SrcCompare>& src,
                               std::multiset<int, DestCompare>& dest)
    {
        const auto p = src.cbegin();
        dest.insert(dest.cbegin(), *p);
        src.erase(p);
    }

    inline void rebalance(DescendingMultiset& low, AscendingMultiset& high)
    {
        switch (get_balance(low, high)) {
        case +2:
            transfer_front(low, high);
            break;

        case -2:
            transfer_front(high, low);
            break;

        default:
            break; // low and high are as balanced as they can be right now
        }
    }

    inline void complain()
    {
        std::puts("Wrong!");
    }

    inline void special_print(const double x)
    {
        std::printf("%.*f\n", (x == std::nearbyint(x) ? 0 : 1), x);
    }

    inline void print_median_or_complain(const DescendingMultiset& low,
                                         const AscendingMultiset& high)
    {
        switch (get_balance(low, high)) {
        case 0: // they are both empty or both nonempty (and equipotent)
            if (low.empty()) complain();
            else {
                special_print((static_cast<double>(*low.cbegin())
                               + static_cast<double>(*high.cbegin())) / 2.0);
            }
            break;

        case +1:
            special_print(static_cast<double>(*low.cbegin()));
            break;

        case -1:
            special_print(static_cast<double>(*high.cbegin()));
            break;

        default:
            abort(); // the balancing invariant was somehow violated!
        }
    }
}

int main()
{
    DescendingMultiset low;
    AscendingMultiset high;

    auto n = 0;
    for ((void)std::scanf("%d", &n); n > 0; --n) {
        auto q = '\0';
        auto e = 0;
        (void)std::scanf(" %c %d", &q, &e);

        switch (q) {
        case 'a':
            add(low, high, e);
            break;

        case 'r':
            if (!remove(low, high, e)) {
                complain();
                continue; // nothing removed, so don't rebalance or recompute
            }
            break;

        default:
            std::abort();
        }

        rebalance(low, high);
        print_median_or_complain(low, high);
    }
}

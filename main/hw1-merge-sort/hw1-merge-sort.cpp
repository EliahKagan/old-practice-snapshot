#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

namespace {
    template<typename It>
    using Delta = typename std::iterator_traits<It>::difference_type;

    template<typename It>
    using Aux = std::vector<typename std::iterator_traits<It>::value_type>;

    template<typename AuxIt, typename It>
    constexpr void merge(const AuxIt aux_first,
                         const It first, const It mid, const It last) noexcept
    {
        auto aux_last = aux_first;
        auto left = first, right = mid;

        for (; left != mid && right != last; ++aux_last) {
            if (*right < *left) {
                *aux_last = std::move(*right);
                ++right;
            } else {
                *aux_last = std::move(*left);
                ++left;
            }
        }

        aux_last = std::move(left, mid, aux_last);

        assert(aux_last - aux_first == right - first);
        std::move(aux_first, aux_last, first);
    }

    template<typename It>
    void mergesort(const It first, const It last) noexcept
    {
        const auto len = last - first;
        Aux<It> aux (static_cast<typename Aux<It>::size_type>(len));
        const auto aux_first = begin(aux);

        for (Delta<It> delta {1}; delta < len; delta *= 2) {
            for (auto offset = delta; offset < len; offset += delta * 2) {
                merge(aux_first, first + (offset - delta),
                                 first + offset,
                                 first + std::min(offset + delta, len));
            }
        }
    }

    std::vector<int> read_record()
    {
        std::vector<int>::size_type n {};
        std::cin >> n;

        std::vector<int> a (n);
        for (auto& x : a) std::cin >> x;
        return a;
    }

    void print(const std::vector<int>& a)
    {
        std::cout << '[';

        auto sep = "";
        for (const auto x : a) {
            std::cout << sep << x;
            sep = ",";
        }

        std::cout << "]\n";
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    auto a = read_record();
    mergesort(begin(a), end(a));
    print(a);
}

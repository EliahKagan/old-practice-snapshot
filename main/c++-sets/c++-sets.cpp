#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <vector>

namespace {
    std::vector<int> read_set_vector(const std::vector<int>::size_type count)
    {
        assert(count != 0);

        // Create and populate the vector with the specified number of items.
        std::vector<int> v (count);
        const auto p = std::begin(v), q = std::end(v);
        std::copy_n(std::istream_iterator<int>{std::cin}, count, p);

        // Sort the vector and remove duplicate items.
        std::sort(p, q);
        v.erase(std::unique(p, q), q);

        return v;
    }

    void print(const std::vector<int>::const_iterator first,
               const std::vector<int>::const_iterator last)
    {
        static std::ostream_iterator<int> out {std::cout, " "};

        if (first == last) {
            std::cout << "0\n";
        } else {
            std::copy(first, last, out);
            std::cout << '\n';
        }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::vector<int>::size_type m {}, n {};
        std::cin >> m >> n;
        const auto a = read_set_vector(m), b = read_set_vector(n);

        std::vector<int> c (m + n);

        const auto ap = std::cbegin(a), aq = std::cend(a);
        const auto bp = std::cbegin(b), bq = std::cend(b);
        const auto cp = std::begin(c);

        print(cp, std::set_union(ap, aq, bp, bq, cp));
        print(cp, std::set_difference(ap, aq, bp, bq, cp));
        print(cp, std::set_intersection(ap, aq, bp, bq, cp));
    }
}

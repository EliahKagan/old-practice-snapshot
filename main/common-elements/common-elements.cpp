#include <algorithm>
#include <iostream>
#include <vector>

namespace {
    std::vector<int> read_record(const std::vector<int>::size_type n)
    {
        std::vector<int> a (n);
        for (auto& x : a) std::cin >> x;
        return a;
    }

    inline int max(const int x, const int y, const int z)
    {
        return std::max(std::max(x, y), z);
    }

    void print_common(const std::vector<int>& a, const std::vector<int>& b,
                      const std::vector<int>& c)
    {
        auto intersect = false;

        const auto pp = a.cend(), qq = b.cend(), rr = c.cend();
        for (auto p = a.cbegin(), q = b.cbegin(), r = c.cbegin();
                    p != pp && q != qq && r != rr; ) {
            const auto key = max(*p, *q, *r);

            while (p != pp && *p < key) ++p;
            if (p == pp) break;

            while (q != qq && *q < key) ++q;
            if (q == qq) break;

            while (r != rr && *r < key) ++r;
            if (r == rr) break;

            if (*p == key && *q == key && *r == key) {
                if (intersect) std::cout << ' ';
                else intersect = true;

                std::cout << key;

                ++p;
                ++q;
                ++r;
            }
        }

        if (intersect) std::cout << '\n';
        else std::cout << "-1\n";
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::vector<int>::size_type na {}, nb {}, nc {};
        std::cin >> na >> nb >> nc;

        const auto a = read_record(na);
        const auto b = read_record(nb);
        const auto c = read_record(nc);

        print_common(a, b, c);
    }
}

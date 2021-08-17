#include <algorithm>
#include <iostream>
#include <vector>

namespace {
    std::vector<int> get_digits()
    {
        std::vector<int>::size_type n {};
        std::cin >> n;
        
        std::vector<int> a;
        a.reserve(n + 1u);
        a.push_back(0); // ensuring a leading zero simplifies the algorithm
        
        while (n-- != 0u) {
            auto d = 0;
            std::cin >> d;
            a.push_back(d);
        }

        return a;
    }

    void put_digits(const std::vector<int>& a)
    {
        auto p = std::find_if(a.cbegin(), a.cend(),
                              [](const int d) { return d != 0; });

        if (p == a.cend()) {
            std::cout << 0 << '\n';
            return;
        }

        for (; ; ) {
            std::cout << *p;
            if (++p == a.cend()) break;
            std::cout << ' ';
        }

        std::cout << '\n';
    }

    void increment_digits(std::vector<int>& a)
    {
        const auto p = std::find_if(a.rbegin(), a.rend(),
                                    [](const int d) { return d != 9; });
        ++(*p);

        std::for_each(a.rbegin(), p, [](int& d) { d = 0; });
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto a = get_digits();
        increment_digits(a);
        put_digits(a);
    }
}

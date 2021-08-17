#include <iostream>
#include <vector>

namespace {
    std::vector<int> get_record()
    {
        std::vector<int> a;
        typename decltype(a)::size_type n {0u};
        std::cin >> n;
        a.reserve(n);

        for (; n != 0u; --n) {
            auto k = 0;
            std::cin >> k;
            a.push_back(k);
        }

        return a;
    }

    void split_pos_neg(std::vector<int>&& a, std::vector<int>& pos,
                                             std::vector<int>& neg)
    {
        for (const auto k : a)
            (k < 0 ? neg : pos).push_back(k);
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::vector<int> pos, neg;
        split_pos_neg(get_record(), pos, neg);

        auto sep = "";
        auto posp = pos.cbegin(), negp = neg.cbegin();

        const auto print = [&sep](decltype(posp)& p) {
            std::cout << sep << *p;
            sep = " ";
            ++p;
        };

        while (posp != pos.cend() || negp != neg.cend()) {
            if (posp != pos.cend()) print(posp);
            if (negp != neg.cend()) print(negp);
        }

        std::cout << '\n';
    }
}

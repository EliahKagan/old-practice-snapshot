#include <iomanip>
#include <iostream>

int main()
{
    auto n = 0, pos = 0, neg = 0, zero = 0;
    std::cin >> n;
    
    for (auto i = 0; i < n; ++i) {
        auto k = 0;
        std::cin >> k;

        if (k > 0) ++pos;
        else if (k < 0) ++neg;
        else ++zero;
    }

    const auto x = static_cast<double>(n);
    std::cout << std::fixed << std::setprecision(6);
    std::cout << pos / x << '\n' << neg / x << '\n' << zero / x << '\n';
}

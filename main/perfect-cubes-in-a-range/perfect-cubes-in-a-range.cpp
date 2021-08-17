#include <cmath>
#include <iostream>

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto a = 0., b = 0.;
        std::cin >> a >> b;
        auto i = std::lround(std::ceil(std::cbrt(a)));
        auto j = std::lround(std::floor(std::cbrt(b)));

        if (j < i) {
            std::cout << "No\n";
            continue;
        }

        auto sep = "";
        
        do {
            std::cout << sep << i * i * i;
            sep = " ";
        }
        while (++i <= j);

        std::cout << '\n';
    }
}

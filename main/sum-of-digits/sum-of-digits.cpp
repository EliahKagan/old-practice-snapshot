#include <iostream>
#include <string>

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::string n;
        std::cin >> n;

        auto sum = 0;
        for (const auto d : n) sum += d - '0';
        std::cout << sum << '\n';
    }
}

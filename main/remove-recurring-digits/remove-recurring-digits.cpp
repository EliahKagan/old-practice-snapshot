#include <iostream>
#include <string>

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::string n;
        std::cin >> n;

        char d = '\0';
        for (const auto c : n) {
            if (d != c) std::cout << c;
            d = c;
        }

        std::cout << '\n';
    }
}

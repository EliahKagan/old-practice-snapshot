#include <cstdlib>
#include <iostream>
#include <string>

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::string s;
        std::cin >> s;
        std::cout << std::strtol(s.c_str(), nullptr, 2) << '\n';
    }
}

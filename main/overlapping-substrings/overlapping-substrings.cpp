#include <iostream>
#include <regex>
#include <string>

int main()
{
    const std::regex re {R"(XY.*YX|YX.*XY)",
            std::regex_constants::ECMAScript | std::regex_constants::optimize};

    auto t = 0;
    for (std::cin >> t >> std::ws; t > 0; --t) {
        std::string s;
        std::getline(std::cin, s);
        std::cout << (std::regex_search(s, re) ? "YES" : "NO") << '\n';
    }
}

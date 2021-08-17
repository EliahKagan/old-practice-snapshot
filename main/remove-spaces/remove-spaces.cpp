#include <cctype>
#include <iostream>
#include <string>

int main()
{
    auto t = 0;
    for (std::cin >> t >> std::ws; t > 0; --t) {
        std::string s;
        std::getline(std::cin, s);
        
        for (const auto c : s)
            if (!std::isspace(c)) std::cout << c;

        std::cout << '\n';
    }
}

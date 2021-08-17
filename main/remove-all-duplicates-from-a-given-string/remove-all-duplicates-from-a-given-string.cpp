#include <cstdlib>
#include <iostream>
#include <set>
#include <string>

int main()
{
    std::string s;
    std::getline(std::cin, s);
    for (auto t = std::strtol(s.c_str(), nullptr, 10); t > 0L; --t) {
        std::string str;
        std::getline(std::cin, str);
        
        std::set<char> chs;
        for (const auto c : str) {
            if (chs.count(c) != 0u) continue;
            chs.insert(c);
            std::cout << c;
        }

        std::cout << '\n';
    }
}

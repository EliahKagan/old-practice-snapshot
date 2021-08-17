#include <iostream>
#include <string>

int isValid(const char *ip);

int main()
{
    auto t = 0;
    for (std::cin >> t >> std::ws; t > 0; --t) { // FIXME: 2nd line whitespace
        std::string s;
        std::getline(std::cin, s);
        std::cout << isValid(s.c_str()) << '\n';
    }
}

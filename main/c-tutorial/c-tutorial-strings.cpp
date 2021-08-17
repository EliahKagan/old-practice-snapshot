#include <iostream>
#include <string>

int main()
{
    std::string a, b;
    if (std::cin >> a >> b) {
        std::cout << a.size() << ' ' << b.size() << '\n';
        std::cout << a + b << '\n'; // could use:  std::cout << a << b << '\n';

        auto ch = a.at(0);
        a.at(0) = b.at(0);
        b.at(0) = ch;

        std::cout << a << ' ' << b << '\n';
    }
}

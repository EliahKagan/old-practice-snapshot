#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        int n;
        std::string s;
        std::cin >> n >> s;
        std::sort(std::begin(s), std::end(s));
        std::cout << s << '\n';
    }
}

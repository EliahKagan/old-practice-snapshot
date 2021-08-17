#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::string s;
        std::cin >> s;
        std::sort(std::begin(s), std::end(s));
        
        std::cout << s;
        while (std::next_permutation(std::begin(s), std::end(s)))
            std::cout << ' ' << s;

        std::cout << '\n';
    }
}

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

        if (std::prev_permutation(std::begin(s), std::end(s)))
            std::cout << s << '\n';
        else
            std::cout << "-1\n";
    }
}

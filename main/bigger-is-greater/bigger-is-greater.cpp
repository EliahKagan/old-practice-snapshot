#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::string w;
        std::cin >> w;
        
        if (std::next_permutation(std::begin(w), std::end(w)))
            std::cout << w << '\n';
        else
            std::cout << "no answer\n";
    }
}

#include <bitset>
#include <climits>
#include <iostream>

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto a = 0uLL, b = 0uLL;
        std::cin >> a >> b;
        std::cout << std::bitset<CHAR_BIT * sizeof a>{a ^ b}.count() << '\n';
    }
}

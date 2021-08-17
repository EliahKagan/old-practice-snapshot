#include <iostream>

int main()
{
    auto sum = 0LL;
    
    auto n = 0;
    for (std::cin >> n; n > 0; --n) {
        auto k = 0LL;
        std::cin >> k;
        sum += k;
    }

    std::cout << sum << '\n';
}

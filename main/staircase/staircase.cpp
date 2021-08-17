#include <iomanip>
#include <iostream>

int main()
{
    auto n = 0;
    std::cin >> n;
    for (auto i = 1; i <= n; ++i) {
        std::cout << std::setfill(' ') << std::setw(n - i) << ""
                  << std::setfill('#') << std::setw(i) << "" << '\n';
    }
}

#include <bitset>
#include <climits>
#include <iostream>

inline bool is_power_of_2(unsigned long long n)
{
    return std::bitset<CHAR_BIT * sizeof n>{n}.count() == 1u;
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        unsigned long long n {};
        std::cin >> n;
        std::cout << (is_power_of_2(n) ? "YES" : "NO") << '\n';
    }
}

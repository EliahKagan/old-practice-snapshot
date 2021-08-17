#include <iostream>

int main()
{
    constexpr auto mod = 1u << 31;
    unsigned n {}, slow {}, p {}, q {};
    std::cin >> n >> slow >> p >> q;

    auto fast = slow;
    do {
        fast = (fast * p + q);
        fast = (fast * p + q) % mod;
        slow = (slow * p + q) % mod;
        //std::cerr << "fast:" << fast << " slow:" << slow << '\n';
    }
    while (fast != slow);

    auto i = 0u;
    for (fast = (fast * p + q) % mod; fast != slow && n-- != 0u;
                                      fast = (fast * p + q) % mod)
        ++i;

    std::cout << i << '\n';
}

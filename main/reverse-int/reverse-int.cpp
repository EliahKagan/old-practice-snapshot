#include <algorithm>
#include <cstring>
#include <iostream>

namespace {
    int reverse(int x)
    {
        char a[sizeof x] {};
        std::memcpy(a, &x, sizeof x);
        std::reverse(std::begin(a), std::end(a));
        std::memcpy(&x, a, sizeof x);
        return x;
    }
}

int main()
{
    std::cout << std::hex;
    
    std::cout << reverse(1000) << ' ' << reverse(reverse(1000)) << '\n';
}

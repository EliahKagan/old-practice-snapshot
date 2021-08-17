#include <iostream>

int main()
{
    constexpr auto len = 1000;
    int a[len] {}, n;

    if (std::cin >> n && 0 < n && n <= len) {
        // read into the array, in forward order
        auto i = 0;
        for (; i != n && std::cin >> a[i]; ++i) { }
        
        // write out from the array, in reverse order
        if (i != 0) {
            while (--i != 0) std::cout << a[i] << ' ';
            std::cout << a[0] << '\n';
        }
    }
}

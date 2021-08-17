#include <iostream>

int main()
{
    static constexpr void (*f)(int) = [](int n) {
        if (n > 0) {
            std::cout << ' ' << n;
            return f(n - 1);
        }
        else std::cout << '\n';
    };

    f(10);
}

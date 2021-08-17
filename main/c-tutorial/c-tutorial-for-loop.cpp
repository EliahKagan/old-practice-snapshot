#include <iostream>

int main()
{
    constexpr const char* names[] {nullptr, "one", "two", "three", "four",
                                   "five", "six", "seven", "eight", "nine"};

    int a, b;
    if (std::cin >> a >> b) {
        for (; a <= b; ++a) {
            if (1 <= a && a <= 9)
                std::cout << names[a];
            else if (a > 9)
                std::cout << (a % 2 == 0 ? "even" : "odd");

            std::cout << '\n';
        }
    }
}

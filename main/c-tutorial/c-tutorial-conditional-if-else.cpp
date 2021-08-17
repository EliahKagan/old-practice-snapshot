#include <iostream>

int main()
{
    // This program is deliberately bug-compatible with the specification,
    // which demands that any value not in the range 1..9 be reported as
    // "Greater than 9" (even if it is something like 0 or -32768).
    constexpr const char* a[] {"Greater than 9", "one", "two", "three", "four",
                               "five", "six", "seven", "eight", "nine"};

    int n;
    if (std::cin >> n) {
        if (n < 1 || n > 9) n = 0;
        std::cout << a[n] << '\n';
    }
}

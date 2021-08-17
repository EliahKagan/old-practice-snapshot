// subtable.cxx - prints simple 11-by-11 subtraction table

#include <iomanip>
#include <iostream>

int main()
{
    const int w {4}, min {0}, max {10}; // -V112
    static_assert(min <= max, "table must be at least 1-by-1 (min <= max)");

    std::cout << std::setw(w * 3) << min;
    for (auto j = min + 1; j <= max; ++j) std::cout << std::setw(w) << j;
    std::cout << '\n';

    for (auto i = min; i <= max; ++i) {
        std::cout << '\n' << std::setw(w) << i << std::setw(w * 2) << i - min;
        for (auto j = min + 1; j <= max; ++j)
            std::cout << std::setw(w) << i - j;
    }

    std::cout << '\n';
} // -V591

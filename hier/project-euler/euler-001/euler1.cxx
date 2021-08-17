// euler1.cxx - Project Euler exercise - Multiples of 3 and 5

#include <iostream>

int main()
{
    int n {0};
    for (int i {1}; i != 1000; ++i)
        if (i % 3 == 0 || i % 5 == 0) n += i;

    std::cout << n << '\n';
}
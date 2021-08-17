// euler2.cxx - Project Euler exercise - Even Fibonacci numbers

#include <iostream>
#include <vector>

int main()
{
    constexpr long four_million {4L * 1000L * 1000L};
    
    // populate the sequence
    std::vector<long> a {1L, 2L};
    for (long back; (back = a.back()) <= four_million; )
        a.emplace_back(back + a.end()[-2]);

    // sum its even-valued elements
    long accum {0L};
    for (long k : a)
        if (k % 2L == 0L) accum += k;

    std::cout << accum << '\n';
}
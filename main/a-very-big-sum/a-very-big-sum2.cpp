#include <iostream>
#include <iterator>
#include <numeric>

int main()
{
    std::cout << std::accumulate(
                    std::next(std::istream_iterator<long long>{std::cin}),
                    std::istream_iterator<long long>{},
                    0LL)
              << '\n';
                                 
}

// Using `std::min` as an algorithm parameter
// Based on https://stackoverflow.com/a/44353798

#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <random>

int main()
{
    std::default_random_engine e {std::random_device{}()};
    std::uniform_int_distribution<int> d {std::numeric_limits<int>::min()};
    
    std::vector<int>::size_type n {100u};
    std::vector<int> a;
    for (a.reserve(n); n != 0u; --n) a.push_back(d(e));
    
    const auto print = [&a]() {
        for (const auto x : a) std::cout << x << ' ';
        std::cout << "\n\n";
    };
    
    print();
    
    //std::partial_sum(std::cbegin(a), std::cend(a), std::begin(a),
    //                 std::min);
    
    std::partial_sum(std::cbegin(a), std::cend(a), std::begin(a),
            [](const auto& x, const auto& y) { return std::min(x, y); });
    
    print();
}

#include <bitset>
#include <cstddef>
#include <iostream>
#include <memory>
#include <vector>

namespace {
    constexpr std::size_t N = 10000000u;
    //template<std::size_t N>
    std::unique_ptr<std::bitset<N + 1>> raw_sieve()
    {
        std::unique_ptr<std::bitset<N + 1>> p {new std::bitset<N + 1>()};
        
    }
}
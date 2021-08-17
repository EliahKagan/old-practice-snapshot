#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <string>

namespace {
    std::size_t max_frequency(const std::string& word)
    {
        std::array<std::size_t, 26u> freqs {};

        for (const auto c : word)
            ++freqs.at(static_cast<std::size_t>(c - 'a'));

        return *std::max_element(freqs.cbegin(), freqs.cend());
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::string word;
        std::cin >> word;

        std::cout << (max_frequency(word) <= (word.size() + 1u) / 2u) << '\n';
    }
}

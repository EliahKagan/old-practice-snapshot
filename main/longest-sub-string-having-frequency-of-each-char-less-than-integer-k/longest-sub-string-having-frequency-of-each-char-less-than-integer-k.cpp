#include <algorithm>
#include <array>
#include <iostream>
#include <string>

namespace {
    using Delta = std::string::difference_type;

    Delta longest(const std::string& text, const Delta max_freq) noexcept
    {
        std::array<int, 'z' - 'a' + 1> freqs {};
        Delta length {};

        const auto last = text.cend();
        auto left = text.cbegin();
        
        for (auto right = left; right != last; ) {
            auto& freq = freqs[*right - 'a'];
            for (; freq == max_freq; ++left) --freqs[*left - 'a'];
            ++freq;

            length = std::max(length, ++right - left);
        }

        return length;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        Delta max_freq {};
        std::string text;
        std::cin >> max_freq >> text;

        std::cout << longest(text, max_freq) << '\n';
    }
}

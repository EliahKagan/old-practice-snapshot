#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <utility>

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::string s;
        std::cin >> s;
        assert(!s.empty()); // should hold for valid input (given constraints)

        std::map<char, int> freqs;
        for (const auto c : s) ++freqs[c];

        auto max_freq = 0;
        for (const auto& kvp : freqs)
            if (max_freq < kvp.second) max_freq = kvp.second;

        const auto is_max_freq = [&](const std::pair<char, int>& kvp) {
            return kvp.second == max_freq;
        };

        const auto p = std::find_if(freqs.cbegin(), freqs.cend(), is_max_freq);
        assert(p != freqs.cend()); // should always hold, even on invalid input
        std::cout << p->first << '\n';
    }
}

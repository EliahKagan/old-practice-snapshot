// This method doesn't work.

#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <unordered_map>

namespace {
    std::unordered_map<int, int> get_freqfreq_map(const std::string& s)
    {
        std::array<int, 26u> freqs{};
        for (const auto c : s) ++freqs[static_cast<std::size_t>(c - 'a')];

        std::unordered_map<int, int> freqfreqs;
        for (const auto f : freqs) {
            if (f != 0) {
                const auto p = freqfreqs.find(f);
                if (p == freqfreqs.cend()) freqfreqs.emplace(f, 1);
                else ++p->second;
            }
        }

        return freqfreqs;
    }

    bool check_frequencies(const std::string& s)
    {
        const auto freqfreqs = get_freqfreq_map(s);

        switch (freqfreqs.size()) {
        case 0u:
        case 1u:
            return true;

        case 2u:
            for (const auto kv : freqfreqs)
                if (kv.first == 1) return true;

            return false;

        default:
            return false;
        }
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::string s;
        std::cin >> s;
        std::cout << check_frequencies(s) << '\n';
    }
}

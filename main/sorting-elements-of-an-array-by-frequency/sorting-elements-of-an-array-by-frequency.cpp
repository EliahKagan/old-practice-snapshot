#include <iostream>
#include <map>
#include <vector>

namespace {
    std::map<int, int> read_val_freq_map()
    {
        std::map<int, int> val_freqs;

        auto n = 0;
        for (std::cin >> n; n > 0; --n) {
            auto k = 0;
            std::cin >> k;
            ++val_freqs[k];
        }

        return val_freqs; // keyed by val, so already sorted by val
    }

    std::map<int, std::vector<int>>
    compute_freq_vals_map(std::map<int, int>&& val_freqs)
    {
        std::map<int, std::vector<int>> freq_vals;

        for (const auto& kvp : val_freqs)
            freq_vals[kvp.second].push_back(kvp.first);

        return freq_vals;
    }

    void print_vals_by_freq(std::map<int, std::vector<int>>&& freq_vals)
    {
        auto sep = "";
        for (auto p = freq_vals.crbegin(); p != freq_vals.crend(); ++p) {
            for (const auto val : p->second) { // each val has freq of p->first
                for (auto reps = p->first; reps > 0; --reps) {
                    std::cout << sep << val;
                    sep = " ";
                }
            }
        }

        std::cout << '\n';
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t)
        print_vals_by_freq(compute_freq_vals_map(read_val_freq_map()));
}

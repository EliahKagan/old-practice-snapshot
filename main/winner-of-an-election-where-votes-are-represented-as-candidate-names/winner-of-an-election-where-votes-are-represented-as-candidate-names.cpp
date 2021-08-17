#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_map>
#include <vector>

namespace {
    std::vector<std::string> read_words()
    {
        std::vector<std::string>::size_type n {};
        std::cin >> n;

        std::vector<std::string> a (n);
        for (auto& e : a) std::cin >> e;
        return a;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto words = read_words();
        if (words.empty()) std::abort();
        std::sort(std::begin(words), std::end(words));

        std::string best_word;
        auto best_freq = 0;
        std::unordered_map<std::string, int> freqs;

        for (const auto& word : words) {
            const auto freq = ++freqs[word];
            if (best_freq < freq) {
                best_freq = freq;
                best_word = word;
            }
        }

        std::cout << best_word << ' ' << best_freq << '\n';
    }
}

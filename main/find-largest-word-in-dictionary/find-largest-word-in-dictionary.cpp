#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

namespace {
    // Reads words from stdin in the format specified in the problem description,
    // stably sorts them nonincreasingly by length, returning them in a vector.
    std::vector<std::string> read_words()
    {
        std::vector<std::string>::size_type n {};
        std::cin >> n;
        
        std::vector<std::string> words (n);
        for (auto& w : words) std::cin >> w;
        
        std::stable_sort(words.begin(), words.end(), [](const std::string& x,
                                                        const std::string& y) {
            return x.size() > y.size(); // sort by length, decreasing
        });
        
        return words;
    }
    
    // Returns true if the word w is present as a (possibly noncontiguous)
    // subsequence of the text s.
    bool has_subsequence(const std::string& s, const std::string& w)
    {
        if (s.size() < w.size()) return false; // a simple optimization
        
        const auto q = s.cend();
        auto p = s.cbegin();
        
        for (const auto c : w) {
            while (p != q && *p != c) ++p;
            if (p == q) return false;
        }
        
        return true;
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        const auto words = read_words();
        
        std::string s;
        std::cin >> s;
        
        const auto p = std::find_if(words.cbegin(), words.cend(),
                [&s](const std::string& w) { return has_subsequence(s, w); } );
        
        if (p != words.cend()) std::cout << *p;
        std::cout << '\n';
    }
}

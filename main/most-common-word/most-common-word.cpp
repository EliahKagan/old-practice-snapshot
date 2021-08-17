class Solution {
public:
    static string mostCommonWord(const string& paragraph,
                                 const vector<string>& banned);
};

namespace {
    const regex word_regex {R"([A-Za-z]+)"};
    
    void downcase(string& word) noexcept
    {
        for (auto& ch : word)
            ch = tolower(static_cast<unsigned char>(ch));
    }
    
    string most_common(const unordered_map<string, int>& freqs)
    {
        const auto value_less = [](const auto& lhs, const auto& rhs) {
            return lhs.second < rhs.second;
        };

        assert(!freqs.empty());
        return max_element(cbegin(freqs), cend(freqs), value_less)->first;
    }
}

string Solution::mostCommonWord(const string& paragraph,
                                const vector<string>& banned)
{
    const unordered_set<string> bans (cbegin(banned), cend(banned));
    unordered_map<string, int> freqs;
    
    auto p = sregex_iterator{cbegin(paragraph), cend(paragraph), word_regex};
    const auto pp = sregex_iterator{};
    
    for (; p != pp; ++p) {
        auto word = p->str();
        downcase(word);
        if (!bans.count(word)) ++freqs[word];
    }
    
    return most_common(freqs);
}

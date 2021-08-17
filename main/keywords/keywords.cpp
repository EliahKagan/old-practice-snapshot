#include "keywords.h"
using namespace std;

namespace {
    using WordCount = vector<string>::size_type;
    using WordId = WordCount; // because the difference is important to humans
    
    constexpr auto word_id_npos = numeric_limits<WordId>::max();
    
    struct Token {
        WordId word_id;                // index to look up the word, or npos
        string::size_type first, last; // string indices at start and after end

        Token(const WordId word_id, const string::size_type first,
                                    const string::size_type last)
            : word_id{word_id}, first{first}, last{last} { }
    };
    
    unordered_map<string, WordId> invert(const vector<string>& keys)
    {
        unordered_map<string, WordId> lookup;
        
        const auto n = keys.size();
        for (WordId i {0u}; i != n; ++i) lookup.emplace(keys[i], i);
        
        assert(lookup.size() == n);
        return lookup;
    }
    
    vector<Token>
    tokenize(const string& text, const unordered_map<string, WordId>& lookup)
    {
        const auto text_length = text.size();
        const auto word_not_found = lookup.end();
        
        vector<Token> tokens;
        
        for (string::size_type first {0u}; ; ) {
            // advance first so it indexes the first character of the next word
            while (first != text_length && text[first] == ' ') ++first;
            if (first == text_length) break;
            
            // advance last so it indexes after the last character of that word
            auto last = first + 1u;
            while (last != text_length && text[last] != ' ') ++last;
            
            // append the appropriate token for this word
            const auto p = lookup.find(text.substr(first, last - first));
            const auto id = (p == word_not_found ? word_id_npos : p->second);
            tokens.emplace_back(id, first, last);
            
            // the search for the next word will begin right after this one
            first = last;
        }
        
        return tokens;
    }
    
    string::size_type findMinimumLength(const vector<Token>& tokens,
                                        const WordCount need_unique_count)
    {
        WordCount unique_count{0u};
        vector<WordCount> counts (need_unique_count);
        auto min_length = string::npos;

        const auto endp = tokens.cend();
        auto left = tokens.cbegin();

        for (auto right = left; right != endp; ++right) {
            // if the window isn't valid, just keep expanding its right side
            if (right->word_id == word_id_npos || ++counts[right->word_id] != 1
                        || ++unique_count != need_unique_count)
                continue;

            // contract the window's left side until it wouldn't be valid
            while (left->word_id == word_id_npos
                        || --counts[left->word_id] != 0)
                ++left;

            // update the minimum valid substring length
            assert(left <= right);
            min_length = min(min_length, right->last - left->first);
            
            // finish contracting the window's left side so it's invalid
            --unique_count;
            ++left;
        }
        
        return min_length;
    }

    int minimumLength(const string& text, const vector<string>& keys)
    {
        static constexpr auto no_solution = -1;

        if (keys.empty()) return 0;
        
        const auto tokens = tokenize(text, invert(keys));
        const auto need_unique_count = keys.size();
        if (tokens.size() < need_unique_count) return no_solution;

        const auto len = findMinimumLength(tokens, need_unique_count);
        return len == string::npos ? no_solution : static_cast<int>(len);
    }
}

int main() {

    string text, buf;
    vector < string > keys;
    getline(cin, text);
    int keyWords;
    cin >> keyWords;
    for(int i = 0; i < keyWords; i++) {
        cin >> buf;
        keys.push_back(buf);
    }
    cout << minimumLength(text, keys) << endl;

    return 0;
}

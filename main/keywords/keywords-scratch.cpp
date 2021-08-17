#define MAXVAL (int)1e9

namespace {
    using WordCount = vector<string>::size_type;
    using WordId = WordCount; // because the difference is important to humans

    constexpr auto word_id_npos = numeric_limits<WordId>::max();

    struct Token {
        WordId word_id;             # index to look up the word, or npos
        string::size_type = first;  # string index to first character
        string::size_type = last;   # string index after last character
    };

    unordered_map<string, WordId> invert(const vector<string>& keys)
    {
        unordered_map<string, vector<string>::size_type> lookup;

        const auto n = keys.size();
        for (vector<string>::size_type i {0u}; i != n; ++i)
            lookup.emplace(keys[i], i);

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
            const auto word_id = (p == word_not_found ? word_id_npos : *p);
            tokens.emplace_back(word_id, first, last);

            // the search for the next word will begin right after this one
            first = last;
        }

        return tokens;
    }

    int minimumLength(const string& text, const vector<string>& keys)
    {
        static constexpr auto no_solution = -1;

        if (keys.empty()) return 0;

        const auto tokens = tokenize(text, invert(keys));
        const auto need_unique_count = keys.size();
        if (tokens.size() < need_unique_count) return no_solution;

        WordCount unique_count;
        vector<WordCount> counts (need_unique_count);
        auto min_length = numeric_limits<string::size_type>::max();

        const auto endp = tokens.cend();
        auto right = tokens.cbegin();
        assert(right != endp);


        ////
        while (unique_count != need_unique_count) {

        }

        ////
        for (auto left = tokens.cbegin(), right = left; ; ) {

        }

        return unique_count == need_unique_count ? static_cast<int>(min_length)
                                                 : no_solution;
    }
}



int minimumLength(string text, vector < string > keys) {

    int answer = MAXVAL;
    text += " $";
    for(int i = 0; i < text.size(); i++) {
        vector < string > dup = keys;
        string word = "";
        if(i > 0 and text[i - 1] != ' ')
            continue;
        for(int j = i; j < text.size(); j++) {
            if(text[j] == ' ') {
                for(int k = 0; k < dup.size(); k++) {
                    if(dup[k] == word) {
                        dup.erase(dup.begin() + k);
                    }
                }
                word = "";
            }
            else word += text[j];
            if((int)dup.size() == 0) {
                answer = min(answer, j - i);
                break;
            }
        }
    }
    if(answer == MAXVAL)
        answer = -1;

    return answer;
}


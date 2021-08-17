namespace {
    // "Compile" a word to its "canonical" pattern.
    vector<int> cpatternize(const string& word)
    {
        vector<int> cword;
        cword.reserve(word.size());
        
        auto next = 0;
        unordered_map<char, int> table;
        
        for (const auto ch : word) {
            const auto p = table.find(ch);
            
            if (p == table.end()) {
                table.emplace(ch, next);
                cword.push_back(next++);
            }
            else cword.push_back(p->second);
        }
        
        return cword;
    }
}

/* The function returns a  vector of strings 
present in the dictionary which matches
the string pattern.
You are required to complete this method */
vector<string> findMatchedWords(vector<string> dict, const string pattern)
{
    const auto cpattern = cpatternize(pattern);
    vector<string> matches;
    
    for (const auto& word : dict)
        if (cpatternize(word) == cpattern) matches.push_back(move(word));
    
    return matches;
}

class Solution {
public:
    static int ladderLength(string start_word, string end_word,
                            const vector<string>& word_list) noexcept;
};

int Solution::ladderLength(string start_word, const string end_word,
                           const vector<string>& word_list) noexcept
{
    assert(start_word != end_word);
    static constexpr auto no_path = 0;
    
    unordered_set<string> s (cbegin(word_list), cend(word_list));
    if (s.find(end_word) == end(s)) return no_path; // a simple optimization
    s.erase(start_word);
    
    queue<string> q;
    q.push(start_word);
    
    for (auto level = 2; !q.empty(); ++level) {
        for (auto breadth = q.size(); breadth != 0u; --breadth) {
            start_word = std::move(q.front());
            q.pop();
            
            for (auto& ch : start_word) {
                const auto old_ch = ch;
                
                for (auto new_ch = 'a'; new_ch <= 'z'; ++new_ch) {
                    if (old_ch == new_ch) continue;
                    
                    ch = new_ch;
                    const auto it = s.find(start_word);
                    if (it == end(s)) continue;
                    
                    s.erase(it);
                    if (start_word == end_word) return level;
                    q.push(start_word);
                }
                
                ch = old_ch;
            }
        }
    }
    
    return no_path;
}

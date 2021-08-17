class Solution {
public:
    static int minMutation(string start, const string& end,
                           const vector<string>& bank) noexcept;
};

namespace {
    unordered_map<string, int> invert(const vector<string>& words)
    {
        unordered_map<string, int> inverse;
        for (auto i = 0; i != words.size(); ++i) inverse.emplace(words[i], i);
        return inverse;
    }
    
    int bfs(const vector<string>& bank,
            const unordered_map<string, int>& indices, int src) noexcept
    {
        
    }
}

int Solution::minMutation(string start, const string end,
                          const vector<string>& bank) noexcept
{
    unordered_set<string> s (cbegin(bank), cend(bank));
    queue<string> q;
    q.push(start);
    s.erase(start);
    
    for (auto level = 1; !q.empty(); ++level) {
        for (auto breadth = q.size(); breadth != 0u; --breadth) {
            start = std::move(q.front());
            q.pop();
            
            for (auto& ch : start) {
                const auto old_ch = ch;
                for (const auto new_ch : {'A', 'C', 'T', 'G'}) {
                    if (old_ch == new_ch) continue;
                    
                    ch = new_ch;
                    if (!s.count(start)) continue;
                    s.erase(start);
                    
                    if (start == end) return level;
                    q.push(std::move(start));
                }
            }
        }
    }
    
    return -1; // no path
}

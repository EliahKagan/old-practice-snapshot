#include <cassert>
#include <iostream>
#include <iterator>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
    static int minMutation(string start, const string finish,
                           const vector<string>& bank) noexcept;
};

int Solution::minMutation(string start, const string finish,
                          const vector<string>& bank) noexcept
{
	assert(start != finish);
    static constexpr auto no_path = -1;
    
    unordered_set<string> s (cbegin(bank), cend(bank));
    if (s.find(finish) == end(s)) return no_path; // a simple optimization
    s.erase(start);
    
    queue<string> q;
    q.push(start);
    
    for (auto level = 1; !q.empty(); ++level) {
        for (auto breadth = q.size(); breadth != 0u; --breadth) {
            start = std::move(q.front());
            q.pop();
            
            for (auto& ch : start) {
                const auto old_ch = ch;
                
                for (const auto new_ch : {'A', 'C', 'T', 'G'}) {
                    if (old_ch == new_ch) continue;
                    
                    ch = new_ch;
                    const auto it = s.find(start);
                    if (it == end(s)) continue;
                    
                    s.erase(it);
                    if (start == finish) return level;
                    q.push(start);
                }
                
                ch = old_ch;
            }
        }
    }
    
    return no_path;
}

int main()
{
    cout << Solution::minMutation("AACCGGTT", "AACCGCTA",
                                  {"AACCGGTA", "AACCGCTA", "AAACGGTA"})
         << '\n';
}

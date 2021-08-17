class Solution {
public:
    static int ladderLength(string beginWord, const string& endWord,
                            vector<string>& wordList);

private:
    static int minHops(const vector<vector<int>>& adj, int cur, int target);

    static vector<vector<int>> makeGraph(const vector<string>& words);

    static inline bool haveEdge(const string& s, const string& t) noexcept;

    static constexpr auto no_path = 0;
};

int Solution::ladderLength(string beginWord, const string& endWord,
                           vector<string>& wordList)
{
    const auto wl_begin = cbegin(wordList), wl_end = cend(wordList);
    const auto p = find(wl_begin, wl_end, endWord);
    if (p == wl_end) return no_path;

    const auto target = static_cast<int>(p - wl_begin);
    const auto cur = static_cast<int>(wordList.size());

    wordList.push_back(move(beginWord));
    const auto adj = makeGraph(wordList);
    wordList.pop_back();

    const auto hops = minHops(adj, cur, target);
    return hops == numeric_limits<int>::max() ? no_path : hops + 1;
}

int Solution::minHops(const vector<vector<int>>& adj, int cur,
                      const int target)
{
    assert(cur != target);
    vector<bool> vis (adj.size());
    vis[cur] = true;

    queue<int> q;
    q.push(cur);

    for (auto hops = 1; !q.empty(); ++hops) {
        for (auto breadth = q.size(); breadth != 0u; --breadth) {
            cur = q.front();
            q.pop();

            for (const auto next : adj[cur]) {
                if (vis[next]) continue;
                if (next == target) return hops;
                vis[next] = true;
                q.push(next);
            }
        }
    }

    return numeric_limits<int>::max();
}

vector<vector<int>> Solution::makeGraph(const vector<string>& words)
{
    const auto count = words.size(), last = count - 1u;
    vector<vector<int>> adj (count);

    for (size_t i {0u}; i != last; ++i) {
        for (auto j = i + 1u; j != count; ++j) {
            if (haveEdge(words[i], words[j])) {
                adj[i].push_back(static_cast<int>(j));
                adj[j].push_back(static_cast<int>(i));
            }
        }
    }

    return adj;
}

inline bool Solution::haveEdge(const string& s, const string& t) noexcept
{
    auto diff = false;

    auto q = cbegin(t);

    for (const auto ch : s) {
        if (ch != *q) {
            if (diff) return false;
            diff = true;
        }

        ++q;
    }

    return diff;
}

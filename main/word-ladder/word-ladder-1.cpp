class Solution {
public:
    static int ladderLength(const string& src, const string& dest,
                            const vector<string>& words);

private:
    static inline bool haveEdge(const string& s, const string& t) noexcept;

    static constexpr auto no_path = 0;
};

int Solution::ladderLength(const string& src, const string& dest,
                           const vector<string>& words)
{
    const auto count = words.size();
    vector<bool> vis (count);

    queue<reference_wrapper<const string>> q;
    q.push(src);

    for (auto length = 2; !q.empty(); ++length) {
        for (auto breadth = q.size(); breadth != 0u; --breadth) {
            const string& s {q.front()};
            q.pop();

            for (size_t j {0u}; j != count; ++j) {
                if (vis[j]) continue;

                const auto& t = words[j];
                if (!haveEdge(s, t)) continue;

                if (t == dest) return length;
                q.push(t);
                vis[j] = true;
            }
        }
    }

    return no_path;
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

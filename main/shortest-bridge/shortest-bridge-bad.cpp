class Solution {
public:
    static int shortestBridge(vector<vector<int>>& a) noexcept;
};

namespace {
    constexpr auto premark = 1, mark = -1;
    static_assert(premark != mark, "must color components differently");
    
    inline int height(const vector<vector<int>>& a) noexcept
    {
        return static_cast<int>(a.size());
    }
    
    inline int width(const vector<vector<int>>& a) noexcept
    {
        return static_cast<int>(a.front().size());
    }
    
    tuple<int, int> find_component(vector<vector<int>>& a) noexcept
    {
        const auto m = height(a), n = width(a);
        
        for (auto i = 0; i != m; ++i) {
            for (auto j = 0; j != n ; ++j)
                if (a[i][j] == premark) return make_tuple(i, j);
        }
        
        assert(false);
    }
    
    void mark_component(vector<vector<int>>& a, int i, int j) noexcept
    {
        const auto m = height(a), n = width(a);
        assert(a[i][j] == premark);
        stack<tuple<int, int>> s;
        s.emplace(i, j);
        
        while (!s.empty()) {
            tie(i, j) = s.top();
            s.pop();
            
            if (i < 0 || i >= m || j < 0 || j >= n || a[i][j] != premark)
                continue;
            
            a[i][j] = mark;
            
            s.emplace(i - 1, j);
            s.emplace(i + 1, j);
            s.emplace(i, j - 1);
            s.emplace(i, j + 1);
        }
    }
    
    queue<tuple<int, int>>
    make_bfs_queue(vector<vector<int>>& a, int i, int j) noexcept
    {
        const auto m = height(a), n = width(a);
        assert(a[i][j] == premark);
        stack<tuple<int, int>> s;
        s.emplace(i, j);
        
        queue<tuple<int, int>> q;
        
        while (!s.empty()) {
            tie(i, j) = s.top();
            s.pop();
            
            if (i < 0 || i >= m || j < 0 || j >= n || a[i][j] != premark)
                continue;
            
            ++a[i][j];
            q.emplace(i, j); // TODO: maybe only enqueue boundary cells
            
            s.emplace(i - 1, j);
            s.emplace(i + 1, j);
            s.emplace(i, j - 1);
            s.emplace(i, j + 1);
        }
        
        return q;
    }
    
    void print(const vector<vector<int>>& a) noexcept
    {
        for (const auto& row : a) {
            for (const auto entry : row) std::cout << ' ' << entry;
            std::cout << '\n';
        }
    }
}

int Solution::shortestBridge(vector<vector<int>>& a) noexcept
{
    const auto m = height(a), n = width(a);
    int i {}, j {};
    
    // Find and mark the destination component.
    tie(i, j) = find_component(a);
    mark_component(a, i, j);
    
    // Find and enqueue cells of the source component.
    tie(i, j) = find_component(a);
    auto q = make_bfs_queue(a, i, j);
    
    // Remember the initial level index.
    const auto source_level = a[i][j];
    assert(source_level == 2);
    auto level = source_level;
    
    // Returns false on destination landfall, true to keep going.
    const auto process = [&](const int h, const int k) noexcept {
        if (h < 0 || h >= m || k < 0 || k >= n) return true;
        
        if (a[h][k] == mark) return false;
        
        if (a[h][k] == 0) {
            a[h][k] = level;
            q.emplace(h, k);
        }
        
        return true;
    };
    
    for (; ; ) {
        ++level;
        for (auto breadth = q.size(); breadth != 0u; --breadth) {
            tie(i, j) = q.front();
            q.pop();
            
            std::cout << "level=" << level << '\n';
            print(a);
            std::cout << '\n';
            
            if (!(process(i - 1, j) && process(i + 1, j)
                    && process(i, j - 1), process(i, j + 1)))
                return level - source_level;
        }
    }
}

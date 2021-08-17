class Solution {
public:
    static bool canVisitAllRooms(vector<vector<int>>& rooms);
};

bool Solution::canVisitAllRooms(vector<vector<int>>& rooms)
{
    auto count = rooms.size();
    vector<bool> vis (count);
    stack<int> s;

    const auto push = [&count, &vis, &s](const int dest) {
        vis[dest] = true;
        s.push(dest);
        --count;
    };

    for (push(0); !s.empty(); ) {
        const auto src = s.top();
        s.pop();

        for (const auto dest : rooms[src])
            if (!vis[dest]) push(dest);
    }

    return !count;
}

class Solution {
public:
    static bool canVisitAllRooms(vector<vector<int>>& rooms);
};

bool Solution::canVisitAllRooms(vector<vector<int>>& rooms)
{
    auto count = rooms.size();
    vector<bool> vis (count);
    stack<int> s;

    vis[0] = true;
    s.push(0);
    --count;

    while (!s.empty()) {
        const auto src = s.top();
        s.pop();

        for (const auto dest : rooms[src]) {
            if (!vis[dest]) {
                vis[dest] = true;
                s.push(dest);
                --count;
            }
        }
    }

    return !count;
}

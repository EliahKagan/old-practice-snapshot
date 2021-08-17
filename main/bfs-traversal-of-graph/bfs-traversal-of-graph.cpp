/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


/* You have to complete this function*/
void bfs(const int s, vector<int>* const adj, bool* const vis)
{
    vis[s] = true;
    queue<int> q;
    q.push(s);

    while (!q.empty()) {
        const auto v = q.front();
        q.pop();
        cout << v << ' ';

        for (const auto w : adj[v]) {
            if (!vis[w]) {
                vis[w] = true;
                q.push(w);
            }
        }
    }
}

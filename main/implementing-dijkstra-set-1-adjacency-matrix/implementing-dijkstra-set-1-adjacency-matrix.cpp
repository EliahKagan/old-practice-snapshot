/*Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above.*/

namespace {
    using Entry = pair<int, int>; // (cost estimate, vertex)

    constexpr auto not_reached = numeric_limits<int>::max();

    void display(const vector<int>& costs)
    {
        auto sep = "";
        for (const auto cost : costs) {
            cout << sep << cost;
            sep = " ";
        }
    }
}

/* The function prints V space separated integers where
    the ith integer denote the shortest distance of ith vertex
    from source vertex */
void dijkstra(int graph[MAX][MAX], int s,int V)
{
    vector<int> costs (V, not_reached);
    priority_queue<Entry, vector<Entry>, greater<Entry>> heap;
    heap.emplace(0, s);

    while (!heap.empty()) {
        int cost, src;
        tie(cost, src) = heap.top();
        heap.pop();

        if (costs[src] != not_reached) continue;

        costs[src] = cost;

        for (auto dest = 0; dest != V; ++dest) {
            const auto weight = graph[src][dest];
            if (weight != 0 && costs[dest] == not_reached)
                heap.emplace(cost + weight, dest);
        }
    }

    display(costs);
}

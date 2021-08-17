/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


/*The structure of the class is as follows
which contains an integer V denoting the no
of vertices and a list of adjacency vertices.
class Graph
{
    int V;
    list<int> *adj;
public :
    Graph(int V);
    void addEdge(int v,int w);
    bool isCyclic();
};*/
/*You are required to complete this method*/
bool Graph :: isCyclic()
{
    vector<bool> visited (V);

    const function<bool(int,int)>
    isCyclicComponent {[&](const int prev, const int cur) {
        visited[cur] = true;
        auto got_prev = false;

        for (const auto next : adj[cur]) {
            if (next == prev) {
                if (got_prev) return true;
                got_prev = true;
            }
            else if (visited[next] || isCyclicComponent(cur, next))
                return true;
        }

        return false;
    }};

    for (auto v = 0; v != V; ++v)
        if (!visited[v] && isCyclicComponent(-1, v)) return true;

    return false;
}

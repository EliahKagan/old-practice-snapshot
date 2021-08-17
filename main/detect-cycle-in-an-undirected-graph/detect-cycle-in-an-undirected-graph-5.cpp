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

    const auto isCyclicComponent = [&](const int root) {
        auto vertices = 0, edges = 0;

        assert(!visited[root]);
        visited[root] = true;
        stack<int> s;
        s.push(root);

        while (!s.empty()) {
            const auto v = s.top();
            s.pop();

            ++vertices;
            edges += adj[v].size();

            for (const auto w : adj[v]) {
                // If v has an edge to itself, return true immediately. The
                // subsequent arithmetic does not account for this. Returning
                // now leaves visited incomplete, but that's OK, because
                // isCyclicComponent won't be called again on this graph.
                if (w == v) return true;

                if (!visited[w]) {
                    visited[w] = true;
                    s.push(w);
                }
            }
        }

        assert(edges % 2 == 0);
        edges /= 2; // they were double-counted

        return vertices - edges != 1; // Since, in a tree, V - E = 1.
    };

    for (auto v = 0; v != V; ++v)
        if (!visited[v] && isCyclicComponent(v)) return true;

    return false;
}

/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


/*
The structure of the class is as follows
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
};
*/
/*You are required to complete this method*/
bool Graph::isCyclic()
{
    enum class Color { white, gray, black };
    vector<Color> vis (V);

    const function<bool(int)>
    isCyclicFrom {[this, &vis, &isCyclicFrom](const int v) {
        switch (vis[v]) {
        case Color::white:
            vis[v] = Color::gray;
            if (any_of(begin(adj[v]), end(adj[v]), isCyclicFrom)) return true;
            vis[v] = Color::black;
            return false;

        case Color::gray:
            return true;

        case Color::black:
            return false;
        }

        abort(); // unreachable
    }};

    for (auto v = 0; v != V; ++v)
        if (isCyclicFrom(v)) return true;

    return false;
}

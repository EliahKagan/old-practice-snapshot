//Initial Template for C++
#include "path-count-in-directed-graph.h" //#include<bits/stdc++.h>
using namespace std;
class Graph
{
	int V;
	list<int> *adj;
public:
	Graph(int V);
	void addEdge(int u, int v);
	int countPaths(int s, int d);
};
Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}
void Graph::addEdge(int u, int v)
{
	adj[u].push_back(v);
}
int main()
{
    int t;
    cin>>t;
    while(t--) {
        int n, e, x, y, s, d;
        cin>>n>>e;
        Graph g(n);
        while(e--){
            cin>>x>>y;
            g.addEdge(x, y);
        }
	    cin>>s>>d;
	    cout << g.countPaths(s, d) << "\n";
    }
	return 0;
}

/*Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above.*/

namespace {
    constexpr auto unknown = -1;
}

//User function Template for C++
// you are required to complete this function
// the function should return the total possible paths
// possible from s to d
int Graph::countPaths(const int s, const int d)
{
    // This implementation assumes the graph contains no cycles.
    vector<int> memo (V, unknown);
    memo[d] = 1; // more than one path to self would entail a cycle

    const function<int(int)> dfs {[this, &memo, &dfs](const int u) {
        if (memo[u] != unknown) return memo[u];

        auto count = 0;
        for (const auto v : adj[u]) count += dfs(v);
        memo[u] = count;
        return count;
    }};

    return dfs(s);
}

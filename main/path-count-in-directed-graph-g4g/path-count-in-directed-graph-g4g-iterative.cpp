//Initial Template for C++
#include "path-count-in-directed-graph-g4g-iterative.h" //#include<bits/stdc++.h>
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
    struct State {
        inline State(int vertex, list<int>::const_iterator next_pos) noexcept;
        
        int vertex;
        list<int>::const_iterator next_pos;
    };
    
    inline State::State(const int vertex,
                        const list<int>::const_iterator next_pos) noexcept
        : vertex{vertex}, next_pos{next_pos} { }
}

//User function Template for C++
// you are required to complete this function
// the function should return the total possible paths 
// possible from s to d
int Graph::countPaths(int s, const int d)
{
    if (s == d) return 1;
    
    //bool vis[V];
    //memset(vis, 0, V * sizeof vis[0]);
    vector<int> vis (V);
    
    int count = 0;
    stack<State> path;
    path.emplace(s, adj[s].cbegin());
    vis[s] = true;
    
    while (!path.empty()) {
        auto& state = path.top();
        
        if (state.next_pos == adj[state.vertex].cend()) {
            vis[state.vertex] = false;
            path.pop();
            continue;
        }
        
        const auto next_vertex = *state.next_pos;
        
        if (next_vertex == d) {
            ++count;
        }
        else if (!vis[next_vertex]) {
            vis[next_vertex] = true;
            path.emplace(next_vertex, adj[next_vertex].cbegin());
        }
        
        ++state.next_pos;
    }
    
    return count;
}

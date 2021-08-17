#include<bits/stdc++.h>
#include <list>
#define CHARS 26
using namespace std;
class Graph
{
    int V;
    list<int> *adj;
    int *in;
public:
    Graph(int V);
    ~Graph()   { delete [] adj; delete [] in; }
    void addEdge(int v, int w) { adj[v].push_back(w);  (in[w])++; }
    bool isEulerianCycle();
    bool isSC();
    void DFSUtil(int v, bool visited[]);
 
    Graph getTranspose();
};
 
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
    in = new int[V];
    for (int i = 0; i < V; i++)
       in[i] = 0;
}
void Graph::DFSUtil(int v, bool visited[])
{
    visited[v] = true;
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited);
}
int main()
{
    int t;
	cin>>t;
	while(t--){
		int V,E;
		cin>>V>>E;
		Graph g(V);
		for(int i=0;i<E;i++){
			int a,b;
			cin>>a>>b;
			g.addEdge(a,b);
		}
		if (g.isEulerianCycle())
		   cout << "1\n";
		else
		   cout << "0\n";
	}
    return 0;
}

// Checks if the nodes of nonzero in-degree are a strongly connected component.
bool Graph::isSC()
{
    static constexpr auto Vmax = 100;
    assert(0 <= V && V <= Vmax);
    
    for (int v = 0; v != V; ++v) {
        if (in[v] == 0) continue;
        
        array<bool, Vmax> vis {};
        DFSUtil(v, vis.data());
        
        const auto p = vis.cbegin(), q = p + V;
        if (!all_of(p, q, [](const bool b) { return b; } )) return false;
    }
    
    return true;
}

// Checks if the graph has a Eulerian cycle.
bool Graph::isEulerianCycle()
{
    for (int v = 0; v != V; ++v) // each node needs equal in and out degrees
        if (in[v] != adj[v].size()) return false;
    
    return isSC(); // nonzero-degree nodes must be reachable from each other
}

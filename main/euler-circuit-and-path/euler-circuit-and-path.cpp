#include<bits/stdc++.h>
#include <list>
using namespace std;
class Graph
{
    int V;
    list<int> *adj;
public:
    Graph(int V)   {this->V = V; adj = new list<int>[V]; }
    ~Graph() { delete [] adj; }
    void addEdge(int v, int w);
    int isEulerian();
    bool isConnected();
    void DFSUtil(int v, bool visited[]);
};

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);
}

void Graph::DFSUtil(int v, bool visited[])
{
    visited[v] = true;
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited);
}
void test(Graph &g)
{
    int res = g.isEulerian();
    if (res == 0)
        cout << "0\n";    //none
    else if (res == 1)
        cout << "1\n";    //Euler path
    else
        cout << "2\n";    //Euler cycle
}
int main()
{
	int t;
	cin>>t;
	while(t--){
		int v,e;
		cin>> v>>e;
		Graph g1(v);
		for(int i=0;i<e;i++){
			int a,b;
			cin>>a>>b;
		g1.addEdge(a, b);
		}
		test(g1);
	}
    return 0;
}

enum Euler { neither, path, cycle };

// Returns a member of Euler, converted to int, to indicate if the graph has
// a Eulerian cycle, a Eulerian path but no Eulerian cycle, or neither.
int Graph::isEulerian()
{
    constexpr auto Vmax = 100;
    assert(0 <= V && V <= Vmax);

    array<bool, Vmax> vis {};
    auto start = V, odd_degree_node_count = 0;

    for (auto v = 0; v != V; ++v) {
        const auto degree = adj[v].size();

        if (degree == 0u) {
            vis[v] = true; // mark isolated nodes "visited"
            continue;
        }

        start = v; // when we perform DFS, we can start at any nonisolated node

        if (degree % 2u != 0u && ++odd_degree_node_count == 3) return neither;
    }

    if (odd_degree_node_count == 1) return neither;

    if (start != V) { // not all nodes are isolated
        DFSUtil(start, vis.data());
        const auto p = vis.cbegin(), q = p + V;
        if (!all_of(p, q, [](const bool b) { return b; } )) return neither;
    }

    return odd_degree_node_count == 0 ? cycle : path;
}

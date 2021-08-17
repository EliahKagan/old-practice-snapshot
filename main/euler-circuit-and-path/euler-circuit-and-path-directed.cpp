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
    //adj[w].push_back(v);
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

namespace {
    constexpr auto Vmax = 100;

    array<int, Vmax> getIndegrees(const int V, const list<int>* const adj)
    {
        assert(0 <= V && V <= Vmax);

        array<int, Vmax> in {};

        for (auto v = 0; v != V; ++v)
            for (const auto w : adj[v]) ++in[w];

        return in;
    }
}

enum Euler { neither, path, cycle };

// Returns a member of Euler, converted to int, to indicate if the graph has
// a Eulerian cycle, a Eulerian path but no Eulerian cycle, or neither.
int Graph::isEulerian()
{
    const auto in = getIndegrees(V, adj);
    array<bool, Vmax> vis {};
    auto start = V;
    auto got_source = false, got_sink = false;

    for (auto v = 0; v != V; ++v) {
        const auto outdegree = static_cast<int>(adj[v].size());

        switch (outdegree - in[v]) { // outdeg - indeg
        case 0:
            if (outdegree == 0) vis[v] = true; // mark isolated nodes "visited"
            else if (start == V) start = v;
            break;

        case 1:
            if (got_source) return neither;
            got_source = true;
            start = v; // if there is a "start node," we MUST start there
            break;

        case -1:
            if (got_sink) return neither;
            got_sink = true;
            break;

        default:
            return neither;
        }
    }

    if (start != V) { // not all nodes are isolated
        DFSUtil(start, vis.data());
        const auto p = vis.cbegin(), q = p + V;
        if (!all_of(p, q, [](const bool b) { return b; } )) return neither;

        if (got_source || got_sink) return path;
    }

    return cycle;
}

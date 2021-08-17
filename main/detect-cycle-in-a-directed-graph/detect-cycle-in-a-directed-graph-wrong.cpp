//#include<bits/stdc++.h>
#include "detect-cycle-in-a-directed-graph-wrong.h"


using namespace std;

class Graph
{
    int V;
    list<int> *adj;
public :
    Graph(int V);
    void addEdge(int v,int w);
    bool isCyclic();
};


Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v,int w)
{
    adj[v].push_back(w);
}




int main()
{

    int T;
    cin>>T;
    while(T--)
    {
        int _size,N;
        cin>>_size>>N;
        Graph *g = new Graph(_size);
        for(int i=0;i<N;i++)
        {
            int u,v;
            cin>>u>>v;
            g->addEdge(u,v);

        }
        cout<<g->isCyclic()<<endl;
    }
}

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

namespace {
    constexpr auto Vmax = 100;

    constexpr auto debug_marked_cycle = true;
    
    bool isCyclicFrom(const int V, const list<int> *const adj,
                      array<int, Vmax>& vis, const int mark, const int v)
    {
        if (vis[v] != 0) return vis[v] == mark;
        vis[v] = mark;
        
        for (const auto w : adj[v])
            if (isCyclicFrom(V, adj, vis, mark, w)) return true;
        
        return false;
    }
}

/*You are required to complete this method*/
bool Graph::isCyclic() // This solution is WRONG.
{
    assert(0 < V && V <= Vmax);
    
    array<int, Vmax> vis {};
    for (auto v = 0; v != V; ++v) {
        const auto mark = v + 1; // prevents conflict with the default 0 value

        if (isCyclicFrom(V, adj, vis, mark, v)) {
            if (debug_marked_cycle) {
                cerr << "DEBUG:";
                for (auto w = 0; w != V; ++w)
                    if (vis[w] == mark) cerr << ' ' << w;
                cerr << '\n';
            }

            return true;
        }
    }
    
    return false;
}

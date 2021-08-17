#include "minimum-spanning-tree-g4g-kruskal.h" // #include<bits/stdc++.h>

using namespace std;
const int MAX = 1e4 + 5;

int spanningTree(vector <pair<int,int> > g[], int n);
int main()
{
	int t ;
	cin>>t;
	while(t--)
	{
	vector <pair<int,int> > adj[MAX];
    int n,e;
    int w, mC;
    cin >> n>> e;
    for(int i = 0;i < e;++i)
    {
    	int x,y;
        cin >> x >> y >> w;
        adj[x].push_back({w, y});
        adj[y].push_back({w, x});
    }
  
    mC= spanningTree(adj, MAX);
    cout << mC << endl;
	}
    return 0;
}

/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/

namespace {
    class DisjointSets {
    public:
        // Creates count non-overlapping sets, each containing one element.
        explicit DisjointSets(int count);

        // Joins the set containing i with the set containing j. Returns false
        // if they were already in the same set. Returns true if they were not.
        bool unite(int i, int j) noexcept;

    private:
        // Finds the representative element for the set that contains i.
        int find(int i) noexcept;

        std::vector<int> elems_;
    };

    DisjointSets::DisjointSets(const int count) : elems_(count, -1) { }

    bool DisjointSets::unite(int i, int j) noexcept
    {
        // Find the ancestors and check if they're already the same.
        i = find(i);
        j = find(j);
        if (i == j) return false;

        // Union by rank.
        if (elems_[i] > elems_[j]) {
            elems_[i] = j; // j has superior (more negative) rank
        } else {
            // if i and j have equal rank, then promote i
            if (elems_[i] == elems_[j]) --elems_[i];

            elems_[j] = i; // i has superior (more negative) rank
        }

        return true;
    }

    int DisjointSets::find(int i) noexcept
    {
        // Find the ancestor.
        auto j = i;
        while (elems_[j] >= 0) j = elems_[j];

        // Compress the path.
        while (i != j) {
            const auto p = elems_[i];
            elems_[i] = j;
            i = p;
        }

        return j;
    }

    struct Edge {
        int u, v, weight;
        
        constexpr Edge(int u, int v, int weight) noexcept
            : u{u}, v{v}, weight{weight} { }
    };
    
    constexpr bool operator<(const Edge& lhs, const Edge& rhs) noexcept
    {
        return lhs.weight < rhs.weight;
    }
    
    constexpr bool operator>(const Edge& lhs, const Edge& rhs) noexcept
    {
        return lhs.weight > rhs.weight;
    }
    
    constexpr int weight(const pair<int,int>& wv) noexcept
    {
        return wv.first;
    }
    
    constexpr int dest(const pair<int,int>& wv) noexcept
    {
        return wv.second;
    }
}

/* Finds the sum of weights of the edges of the Minimum Spanning Tree.
    Graph is represented as adjacency list using array of vectors.  MAX 
    is an upper  limit on number of vertices.
   g[u] represents adjacency list of vertex u,  Every element of this list 
   is a pair<w,v>  where v is another vertex and w is weight of edge (u, v)
  Note : Vertex numbers start with 1 and don't need to be contiguous.   */
int spanningTree(vector<pair<int,int>>* const g, const int MAX)
{
    priority_queue<Edge, vector<Edge>, greater<Edge>> heap;
    for (auto u = 0; u != MAX; ++u) {
        for (const auto& wv : g[u]) {
            // The graph is undirected, so we will encounter u => v and v => u
            // for each edge. Emplacing both would work, but we only need one.
            // [This is false of loops (u => u), but we can exclude those.]
            if (u < dest(wv)) heap.emplace(u, dest(wv), weight(wv));
        }
    }
    
    auto sum = 0;
    for (DisjointSets sets {MAX}; !heap.empty(); heap.pop()) {
        const auto& edge = heap.top();
        if (sets.unite(edge.u, edge.v)) sum += edge.weight;
    }
    
    return sum;
}

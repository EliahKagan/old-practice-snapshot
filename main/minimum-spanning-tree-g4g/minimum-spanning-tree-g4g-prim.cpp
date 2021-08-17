#include "minimum-spanning-tree-g4g-prim.h" //#include<bits/stdc++.h>
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

/*Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above.*/

namespace {
    // A binary minheap augmented with contains() and decrease() methods.
    template<typename Key, typename Value>
    class PrimHeap {
    public:
        struct Entry {
            Entry(const Key key, const Value value) : key{key}, value{value}
            {
            }
            
            Key key;
            Value value;
        };

        PrimHeap() noexcept;

        bool empty() const noexcept { return elems_.empty(); }

        size_t size() const noexcept { return elems_.size(); }

        void push(Key key, Value value = numeric_limits<Value>::max());

        const Entry& top() const { return elems_.at(0u); }

        void pop();

        bool contains(const Key key) const noexcept
        {
            return table_.count(key) != 0;
        }

        void decrease(Key key, Value value);

    private:
        static constexpr auto npos = std::numeric_limits<size_t>::max();

        void sift_up(size_t child);

        void sift_down(size_t parent);

        size_t pick_child(size_t parent) const noexcept;

        void exchange(size_t src, size_t dest);

        void record(const size_t src) { table_[elems_[src].key] = src; }

        bool order_ok(size_t parent, size_t child) const noexcept
        {
            return elems_[parent].value <= elems_[child].value;
        }

        std::unordered_map<Key, size_t> table_;
        std::vector<Entry> elems_;
    };

    template<typename Key, typename Value>
    PrimHeap<Key, Value>::PrimHeap() noexcept : table_{}, elems_{}
    {
    }

    template<typename Key, typename Value>
    void PrimHeap<Key, Value>::push(const Key key, const Value value)
    {
        const auto child = size();
        table_.emplace(key, child);
        elems_.emplace_back(key, value);
        sift_up(child);
    }

    template<typename Key, typename Value>
    void PrimHeap<Key, Value>::pop()
    {
        if (size() == 1u) {
            table_.clear();
            elems_.clear();
        } else {
            table_.erase(top().key);
            elems_.front() = elems_.back();
            elems_.pop_back();
            sift_down(0u);
        }
    }

    template<typename Key, typename Value>
    void PrimHeap<Key, Value>::decrease(const Key key, const Value value)
    {
        const auto child = table_.at(key);
        auto& ent = elems_[child];

        if (value < ent.value) {
            ent.value = value;
            sift_up(child);
        }
    }

    template<typename Key, typename Value>
    void PrimHeap<Key, Value>::sift_up(size_t child)
    {
        while (child != 0u) {
            const auto parent = (child - 1u) / 2u;
            if (order_ok(parent, child)) break;

            exchange(child, parent);
            child = parent;
        }

        record(child);
    }

    template<typename Key, typename Value>
    void PrimHeap<Key, Value>::sift_down(size_t parent)
    {
        for (; ; ) {
            const auto child = pick_child(parent);
            if (child == npos || order_ok(parent, child)) break;

            exchange(parent, child);
            parent = child;
        }

        record(parent);
    }

    template<typename Key, typename Value>
    size_t PrimHeap<Key, Value>::pick_child(const size_t parent) const noexcept
    {
        const auto left = parent * 2u + 1u;
        if (left >= size()) return npos;

        const auto right = left + 1u;
        return right == size() || order_ok(left, right) ? left : right;
    }

    template<typename Key, typename Value>
    inline void PrimHeap<Key, Value>::exchange(const size_t src,
                                               const size_t dest)
    {
        swap(elems_[dest], elems_[src]);
        record(src);
    }

    PrimHeap<int, int> make_heap(vector<pair<int, int>>* const g, const int n)
    {
        PrimHeap<int, int> cost_heap;
        for (auto u = 0; u != n; ++u)
            if (!g[u].empty()) cost_heap.push(u);

        if (!cost_heap.empty()) cost_heap.decrease(cost_heap.top().key, 0);
        return cost_heap;
    }
}

/* Finds the sum of weights of the edges of the Minimum Spanning Tree.
Graph is represented as adjacency list using array of vectors.  MAX (n)
is an upper  limit on number of vertices.
g[u] represents adjacency list of vertex u,  Every element of this list
is a pair<w,v>  where v is another vertex and w is weight of edge (u, v)
Note : Vertex numbers start with 1 and don't need to be contiguous.   */
int spanningTree(vector<pair<int, int>>* const g, const int n)
{
    auto total_cost = 0;

    for (auto cost_heap = make_heap(g, n); !cost_heap.empty(); ) {
        auto ent = cost_heap.top();
        cost_heap.pop();

        total_cost += ent.value;

        for (const auto& edge : g[ent.key]) {
            int wt, v;
            tie(wt, v) = edge;

            if (cost_heap.contains(v)) cost_heap.decrease(v, wt);
        }
    }

    return total_cost;
}

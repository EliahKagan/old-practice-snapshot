//Initial Template for C++  [MODIFIED FROM ORIGINAL TO REMOVE NONPORTABLE VLAs]
/* script for test case http://code.geeksforgeeks.org/PetjYq */
#include "alien-dictionary-fast.h" //#include<bits/stdc++.h>
using namespace std;
string printOrder(string[], int, int);
string order;
bool f(string a, string b)
{
    int p1 = 0; int p2 = 0;
    for (int i = 0; i<min(a.size(), b.size()) and p1 == p2; i++)
    {
        p1 = order.find(a[i]);
        p2 = order.find(b[i]);
        //	cout<<p1<<" "<<p2<<endl;
    }

    if (p1 == p2 and a.size() != b.size())
        return a.size() < b.size();

    return p1 < p2;
}

// Driver program to test above functions
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, k;
        cin >> n >> k;
        vector<string> s (n);
        for (int i = 0; i < n; i++) cin >> s[i];

        string ss = printOrder(s.data(), n, k);
        order = "";
        for (int i = 0; i < ss.size(); i++)
            order += ss[i];

        vector<string> temp (s);
        sort(temp.data(), temp.data() + n, f);

        bool f = true;
        for (int i = 0; i < n; i++)
            if (s[i] != temp[i]) f = false;

        cout << f;
        cout << endl;

    }
    return 0;
}

/*Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above.*/

namespace {
    class GraphMakerTrie {
    public:
        explicit GraphMakerTrie(size_t order);

        GraphMakerTrie(const GraphMakerTrie&) = delete;
        GraphMakerTrie(GraphMakerTrie&&) = delete;
        GraphMakerTrie& operator=(const GraphMakerTrie&) = delete;
        GraphMakerTrie& operator=(GraphMakerTrie&&) = delete;
        ~GraphMakerTrie() = default;

        // Registers [first,last) as a new lexicographically greatest chain.
        void insert(std::string::const_iterator first,
                    std::string::const_iterator last);
        
        // Registers word as a new lexicographically greatest chain.
        void insert(const std::string& word)
        {
            insert(word.cbegin(), word.cend());
        }

        string compute_possible_character_ordering() const;

    private:
        // A trie node.
        class Node {
        public:
            explicit Node(const size_t order) : children_(order) { }

            size_t size() const noexcept { return children_.size(); }

            Node* const& operator[](const size_t index) const noexcept
            {
                return children_[index];
            }

            Node*& operator[](const size_t index) noexcept
            {
                return children_[index];
            }

            Node* const& at(const size_t index) const
            {
                return children_.at(index);
            }

            Node*& at(const size_t index)
            {
                return children_.at(index);
            }

        private:
            vector<Node*> children_;
        };

        // Visitation states for traversing a directed graph.
        enum class Color {
            white,  // unvisited
            gray,   // visited but not fully explored
            black   // visited and fully explored
        };

        // Translates a character into its corresponding vertex number (index).
        static constexpr size_t vertex(const char ch) noexcept
        {
            return static_cast<size_t>(ch) - static_cast<size_t>('a');
        }

        // Translates a vertex number (index) into its corresponding character.
        static constexpr char character(const size_t vertex) noexcept
        {
            return static_cast<char>(static_cast<size_t>('a') + vertex);
        }

        size_t order() const noexcept { return adj_.size(); }

        Node* make_node();

        void place_edges(const Node& source_parent, size_t dest);

        stack<size_t> topological_sort() const;

        deque<Node> nodes_;
        vector<vector<size_t>> adj_;
    };

    GraphMakerTrie::GraphMakerTrie(const size_t order) : nodes_{}, adj_(order)
    {
        make_node();
    }

    void GraphMakerTrie::insert(std::string::const_iterator first,
                                const std::string::const_iterator last)
    {
        auto parent = &nodes_.front();

        for (auto subchain = true; subchain && first != last; ++first) {
            const auto dest = vertex(*first);
            auto& child = parent->at(dest);

            if (!child) {
                subchain = false;
                place_edges(*parent, dest);
                child = make_node();
            }

            parent = child;
        }

        for (; first != last; ++first)
            parent = parent->at(vertex(*first)) = make_node();
    }

    string GraphMakerTrie::compute_possible_character_ordering() const
    {
        auto vertices = topological_sort();
        assert(vertices.size() == order());

        string ret;
        for (ret.reserve(order()); !vertices.empty(); vertices.pop())
            ret.push_back(character(vertices.top()));

        return ret;
    }

    inline GraphMakerTrie::Node* GraphMakerTrie::make_node()
    {
        nodes_.emplace_back(order());
        return &nodes_.back();
    }

    void GraphMakerTrie::place_edges(const GraphMakerTrie::Node& source_parent,
                                     const size_t dest)
    {
        assert(!source_parent[dest]);

        const auto ord = order();
        assert(ord == source_parent.size());

        for (size_t src {0u}; src != ord; ++src)
            if (source_parent[src]) adj_[src].push_back(dest);
    }

    stack<size_t> GraphMakerTrie::topological_sort() const
    {
        const auto ord = order();
        vector<Color> vis (ord, Color::white);
        stack<size_t> out;

        const function<void(size_t)>
        dfs {[this, &vis, &out, &dfs](const size_t src) {
            switch (vis[src]) {
            case Color::white:
                vis[src] = Color::gray;
                for (const auto dest : adj_[src]) dfs(dest);
                vis[src] = Color::black;
                out.push(src);
                break;

            case Color::gray:
                throw domain_error{"cycle found, no topological ordering"};

            case Color::black:
                break;
            }
        }};

        for (size_t src {0u}; src != ord; ++src) dfs(src);
        return out;
    }
}

//User function Template for C++
/*The function should return a string denoting the
order of the words in the Alien Dictionary */
string printOrder(string* const dict, const int N, const int k)
{
    GraphMakerTrie solver {static_cast<size_t>(k)};
    for_each(dict, dict + N, [&solver](const string& w) { solver.insert(w); });
    return solver.compute_possible_character_ordering();
}

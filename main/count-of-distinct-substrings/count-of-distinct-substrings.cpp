/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/

namespace {
    constexpr auto lowercase = "abcdefghijklmnopqrstuvwxyz";

    constexpr bool have_contiguous_lowercase(const ptrdiff_t i = 1)
    {
        return lowercase[i] == '\0' || (lowercase[i] - lowercase[i - 1] == 1
                                        && have_contiguous_lowercase(i + 1));
    }

    static_assert(have_contiguous_lowercase(),
                  "lower-case letters must be contiguous");

    class Trie {
    public:
        Trie() = default;
        Trie(const Trie&) = delete;
        Trie(Trie&&) = delete;
        Trie& operator=(const Trie&) = delete;
        Trie& operator=(Trie&&) = delete;
        ~Trie() = default;

        size_t size() const { return nodes.size(); }
        void insert(string::const_iterator first, string::const_iterator last);

    private:
        class Node {
        public:
            Node() = default;
            Node(const Node&) = delete;
            Node(Node&&) = delete;
            Node& operator=(const Node&) = delete;
            Node& operator=(Node&&) = delete;
            ~Node() = default;

            Node*& at(const char ch)
            {
                return children.at(static_cast<size_t>(ch - 'a'));
            }

        private:
            array<Node*, 'z' - 'a' + 1> children {};
        };

        Node* make_node()
        {
            nodes.emplace_back();
            return &nodes.back();
        }

        Node* get_node(Node*& node)
        {
            if (node == nullptr) node = make_node();
            return node;
        }

        deque<Node> nodes;
        Node* root {make_node()};
    };

    void Trie::insert(string::const_iterator first,
                      const string::const_iterator last)
    {
        for (auto node = root; first != last; ++first)
            node = get_node(node->at(*first));
    }
}

/*You are required to complete this method */
int countDistinctSubstring(string s)
{
    Trie trie;

    const auto last = s.cend();
    for (auto first = s.cbegin(); first != last; ++first)
        trie.insert(first, last);

    return static_cast<int>(trie.size());
}

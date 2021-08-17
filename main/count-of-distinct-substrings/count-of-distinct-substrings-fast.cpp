/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/

namespace {
    constexpr auto k_lowercase = "abcdefghijklmnopqrstuvwxyz";

    constexpr bool have_contiguous_lowercase(const ptrdiff_t i = 1)
    {
        return k_lowercase[i] == '\0'
                || (k_lowercase[i] - k_lowercase[i - 1] == 1
                    && have_contiguous_lowercase(i + 1));
    }

    static_assert(have_contiguous_lowercase(),
                  "lower-case letters must be contiguous");

    constexpr size_t k_maxlen {1000u};

    class Trie {
    public:
        Trie() = default;
        Trie(const Trie&) = delete;
        Trie(Trie&&) = delete;
        Trie& operator=(const Trie&) = delete;
        Trie& operator=(Trie&&) = delete;
        ~Trie() = default;

        size_t size() const noexcept
        {
            return static_cast<size_t>(endp - nodes.data());
        }

        void clear() noexcept
        {
            memset(nodes.data(), 0, size() * sizeof(Node));
            endp = &nodes[1];
        }

        void insert(string::const_iterator first,
                    const string::const_iterator last) noexcept
        {
            for (auto node = nodes.data(); first != last; ++first)
                node = get_node((*node)[*first]);
        }

    private:
        class Node {
        public:
            Node*& operator[](const char ch) noexcept
            {
                return children[static_cast<size_t>(ch - 'a')];
            }

        private:
            array<Node*, 'z' - 'a' + 1> children {};
        };

        Node* get_node(Node*& node) noexcept
        {
            if (node == nullptr) node = endp++;
            return node;
        }

        array<Node, k_maxlen * (k_maxlen + 1u) / 2u> nodes {};
        Node* endp {&nodes[1]};
    };
}

/*You are required to complete this method */
int countDistinctSubstring(string s)
{
    static constexpr size_t maxlen {1000u};
    static Trie trie;

    trie.clear();

    const auto last = s.cend();
    for (auto first = s.cbegin(); first != last; ++first)
        trie.insert(first, last);

    return static_cast<int>(trie.size());
}

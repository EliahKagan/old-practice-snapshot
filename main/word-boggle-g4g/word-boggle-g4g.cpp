#include <algorithm>
#include <array>
#include <climits>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <memory>
#include <numeric>
#include <set>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace {
    using std::size_t;

    using Graph = std::vector<std::vector<size_t>>; // adjacency list

    std::vector<char> read_grid(const size_t m, const size_t n)
    {
        std::vector<char> grid (m * n);
        for (auto& cell : grid) std::cin >> cell;
        return grid;
    }

    Graph build_graph(const size_t m, const size_t n)
    {
        // Vertices 0 through (m * n - 1) represent grid cells in row-major
        // order. Vertex (m * n) is the root, with edges to every other vertex.
        Graph graph (m * n + 1u);

        for (size_t i {0u}; i != m; ++i) {
            for (size_t j {0u}; j != n; ++j) {
                auto& row = graph[i * n + j];

                for (auto h = i - 1u; h != i + 2u; ++h) {
                    if (h < m) {
                        for (auto k = j - 1u; k != j + 2u; ++k) {
                            if (k < n && !(h == i && k == j))
                                row.push_back(h * n + k);
                        }
                    }
                }
            }
        }

        auto& root = graph.back();
        root.resize(m * n);
        std::iota(std::begin(root), std::end(root), 0u);

        return graph;
    }

    class Trie {
    public:
        void insert(std::string word);

        std::set<std::string> extract_matches(const std::vector<char>& grid,
                                              const Graph& graph);

    private:
        using Children = std::array<Trie, static_cast<size_t>(1u) << CHAR_BIT>;

        static constexpr size_t index(char ch) noexcept;

        void dfs(std::set<std::string>& out, const std::vector<char>& grid,
                 const Graph& graph, std::vector<bool>& vis, size_t v);

        std::unique_ptr<Children> children_ {};
        std::unique_ptr<std::string> word_ {};
    };

    constexpr size_t Trie::index(const char ch) noexcept
    {
        return static_cast<size_t>(static_cast<unsigned char>(ch));
    }

    void Trie::insert(std::string word)
    {
        auto node = this;
        for (const auto ch : word) {
            if (!node->children_) node->children_.reset(new Children{});
            node = &(*node->children_)[index(ch)];
        }

        node->word_.reset(new std::string{std::move(word)});
    }

    std::set<std::string> Trie::extract_matches(const std::vector<char>& grid,
                                                const Graph& graph)
    {
        std::vector<bool> vis (graph.size());
        std::set<std::string> matches;
        dfs(matches, grid, graph, vis, graph.size() - 1u);
        return matches;
    }

    void Trie::dfs(std::set<std::string>& out, const std::vector<char>& grid,
                   const Graph& graph, std::vector<bool>& vis, const size_t v)
    {
        if (word_) {
            out.emplace(std::move(*word_));
            word_ = nullptr;
        }

        if (children_) {
            vis[v] = true;

            for (const auto w : graph[v]) {
                if (!vis[w])
                    (*children_)[index(grid[w])].dfs(out, grid, graph, vis, w);
            }

            vis[v] = false;
        }
    }

    std::istream& operator>>(std::istream& in, Trie& trie)
    {
        auto x = 0;
        for (in >> x; x > 0; --x) {
            std::string word;
            in >> word;
            trie.insert(std::move(word));
        }

        return in;
    }

    void report_matches(const std::set<std::string>& matches)
    {
        const auto q = matches.cend();
        auto p = matches.cbegin();

        if (p == q) {
            std::cout << "-1\n";
        } else {
            std::cout << *p;
            while (++p != q) std::cout << ' ' << *p;
            std::cout << '\n';
        }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        // Read the word list into a trie.
        Trie trie;
        std::cin >> trie;

        // Read the grid and build the graph.
        size_t m {}, n {};
        std::cin >> m >> n;
        const auto grid = read_grid(m, n);
        const auto graph = build_graph(m, n);

        // Extract and report the matches.
        report_matches(trie.extract_matches(grid, graph));
    }
}

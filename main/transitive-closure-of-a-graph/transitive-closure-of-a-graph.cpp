#include <array>
#include <cstddef>
#include <iostream>

namespace {
    constexpr std::size_t nmax {100u};
    
    using Table = std::array<std::array<bool, nmax>, nmax>;

    // Builds an adjacency matrix from a stream of 0s and 1s read from stdin.
    Table read_adjacency_table(const std::size_t n)
    {
        Table in {};

        for (std::size_t i {0u}; i != n; ++i)
            for (std::size_t j {0u}; j != n; ++j) std::cin >> in[i][j];

        return in;
    }

    // Adds an edge from orig to each vertex (next) reachable from cur. Helper
    // for get_transitive_closure(). Nonrecursive calls should use orig == cur.
    void connect_to_reachable(const Table& in, Table& out, const std::size_t n,
                              const std::size_t orig, const std::size_t cur)
    {
        for (std::size_t next {0u}; next != n; ++next) {
            if (in[cur][next] && !out[orig][next]) {
                out[orig][next] = true;
                connect_to_reachable(in, out, n, orig, next);
            }
        }
    }

    // Given a graph's adjacency matrix, produces the adjacency matrix for its
    // transitive closure.
    Table get_transitive_closure(const Table& in, const std::size_t n)
    {
        Table out {};

        for (std::size_t orig {0u}; orig != n; ++orig)
            connect_to_reachable(in, out, n, orig, orig);

        return out;
    }

    // Prints the contents of a table on a single line, in row-major order.
    void print_table(const Table& out, const std::size_t n)
    {
        for (std::size_t i {0u}; i != n; ++i) {
            for (std::size_t j {0u}; j != n; ++j)
                std::cout << out[i][j] << ' ';
        }

        std::cout << '\n';
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::size_t n {};
        std::cin >> n;

        print_table(get_transitive_closure(read_adjacency_table(n), n), n);
    }
}

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifdef __MINGW32__
#define __USE_MINGW_ANSI_STDIO 1
#endif

#include <cstdio>
#include <limits>
#include <vector>

namespace {
    using std::size_t;

    using Matrix = std::vector<std::vector<unsigned>>;

    constexpr auto infinity = std::numeric_limits<unsigned>::max();

    Matrix make_distance_matrix(const size_t vertex_count)
    {
        Matrix distances (vertex_count,
                          std::vector<unsigned>(vertex_count, infinity));

        for (size_t i {0u}; i != vertex_count; ++i) distances[i][i] = 0u;

        return distances;
    }

    void populate_distance_matrix(Matrix& distances, size_t edge_count)
    {
        while (edge_count--) {
            size_t src {}, dest {};
            unsigned weight {};
            (void)std::scanf("%zu%zu%u", &src, &dest, &weight);

            if (src == dest) continue;

            // The problem description says that subsequently received parallel
            // edges replace previous ones, even if their weights are larger.
            distances.at(src).at(dest) = weight;
        }
    }

    inline void relax(Matrix& distances, const size_t via,
                      const size_t src, const size_t dest) noexcept
    {
        if (distances[src][via] == infinity || distances[via][dest] == infinity)
            return;

        // I assume this will not overflow, based on the problem constraints.
        const auto d = distances[src][via] + distances[via][dest];
        if (distances[src][dest] > d) distances[src][dest] = d;
    }

    void floyd_warshall(Matrix& distances) noexcept
    {
        const auto vertex_count = distances.size();

        for (size_t via {0u}; via != vertex_count; ++via) {
            for (size_t src {0u}; src != vertex_count; ++src) {
                for (size_t dest {0u}; dest != vertex_count; ++dest)
                    relax(distances, via, src, dest);
            }
        }
    }

    void run_queries(Matrix& distances, int query_count)
    {
        while (query_count-- > 0) {
            size_t src {}, dest {};
            (void)std::scanf("%zu%zu", &src, &dest);

            const auto d = distances.at(src).at(dest);

            if (d == infinity) std::puts("-1");
            else std::printf("%u\n", d);
        }
    }
}

int main()
{
    size_t vertex_count {}, edge_count {};
    (void)std::scanf("%zu%zu", &vertex_count, &edge_count);
    ++vertex_count; // for 1-based indexing

    auto distances = make_distance_matrix(vertex_count);
    populate_distance_matrix(distances, edge_count);
    floyd_warshall(distances);

    int query_count {};
    (void)std::scanf("%d", &query_count);
    run_queries(distances, query_count);
}

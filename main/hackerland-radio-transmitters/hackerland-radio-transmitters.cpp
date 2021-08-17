#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

namespace {
    // Returns a sorted list of nodes (houses) that may be sources or sinks.
    // Writes the transmission range (k) to the reference argument.
    std::vector<int> read_scenario(int& range)
    {
        std::vector<int>::size_type size {};
        std::cin >> size >> range;

        std::vector<int> nodes(size);
        for (auto& node : nodes) std::cin >> node;
        std::sort(nodes.begin(), nodes.end());

        return nodes;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    int range {};
    const auto nodes = read_scenario(range);

    auto count = 0;

    const auto edge = nodes.cend();
    for (auto sink = nodes.cbegin(); sink != edge; ) {
        // find source for sink
        auto source = std::upper_bound(sink, edge, *sink + range);
        --source;
        ++count;

        // find next sink
        sink = std::upper_bound(source, edge, *source + range);
    }

    std::cout << count << '\n';
}

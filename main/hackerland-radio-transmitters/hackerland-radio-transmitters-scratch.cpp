#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

int main()
{
    std::ios_base::sync_with_stdio(false);

    std::vector<int>::size_type size {};
    int range {};
    std::cin >> size >> range;

    std::vector<int> x (size);
    for (auto& xi : x) std::cin >> xi;
    std::sort(x.begin(), x.end());

    const auto edge = x.cend();
    auto sink = x.cbegin();
    assert(sink != edge);

    auto count = 0;

find_source:
    auto source = std::upper_bound(sink, edge, *sink + range);
    --source;
    ++count;

find_sink:
    sink = std::upper_bound(source, edge, *source + range);
    if (sink != edge) goto find_source;
}

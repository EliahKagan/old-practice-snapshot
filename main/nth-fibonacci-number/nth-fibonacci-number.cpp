#ifdef _MSC_VER
#define NOMINMAX
#endif

#include <algorithm>
#include <iostream>
#include <vector>

namespace {
    constexpr auto modulo = 1000000007;
    using Index = std::vector<int>::size_type;

    std::vector<Index> read_indices()
    {
        std::vector<Index>::size_type t {};
        std::cin >> t;
        std::vector<Index> indices;

        for (indices.reserve(t); t != Index{0}; --t) {
            Index n {};
            std::cin >> n;
            indices.push_back(n - Index{1});
        }

        return indices;
    }

    std::vector<int> fibonacci_sequence(Index size)
    {
        if (size < Index{2}) size = Index{2};

        std::vector<int> seq;
        seq.reserve(size);
        seq.push_back(0);
        seq.push_back(1);

        for (Index i {2}; i != size; ++i)
            seq.push_back((seq[i - Index{2}] + seq[i - Index{1}]) % modulo);

        return seq;
    }
}

int main()
{
    const auto indices = read_indices();

    const auto maxp = std::max_element(indices.cbegin(), indices.cend());
    const auto size = (maxp == indices.cend() ? Index{0} : *maxp + Index{1});
    const auto seq = fibonacci_sequence(size);

    for (const auto n : indices) std::cout << seq.at(n) << '\n';
}

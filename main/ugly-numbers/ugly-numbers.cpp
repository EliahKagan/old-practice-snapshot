#include <algorithm>
#include <iostream>
#include <vector>

namespace {
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

    int remove_factor(int product, const int factor)
    {
        while (product % factor == 0) product /= factor;
        return product;
    }

    bool is_ugly(const int val)
    {
        return remove_factor(remove_factor(remove_factor(val, 2), 3), 5) == 1;
    }

    std::vector<int> compute_uglies(const Index count)
    {
        std::vector<int> uglies;
        uglies.reserve(count);

        for (auto val = 1; uglies.size() != count; ++val)
            if (is_ugly(val)) uglies.push_back(val);

        return uglies;
    }
}

int main()
{
    const auto indices = read_indices();

    const auto maxp = std::max_element(indices.cbegin(), indices.cend());
    const auto size = (maxp == indices.cend() ? Index{0} : *maxp + Index{1});
    const auto uglies = compute_uglies(size);

    for (const auto n : indices) std::cout << uglies.at(n) << '\n';
}

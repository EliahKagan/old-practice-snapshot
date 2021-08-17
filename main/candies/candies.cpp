#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <vector>

namespace {
    std::vector<int> read_marks()
    {
        std::size_t pupil_count {};
        std::cin >> pupil_count;
        assert(pupil_count != 0u);

        std::vector<int> marks (pupil_count);
        std::copy_n(std::istream_iterator<int>{std::cin},
                    pupil_count, begin(marks));

        return marks;
    }

    int candy(const std::vector<int>& marks, std::vector<int>& candies,
              const std::size_t pupil) noexcept
    {
        if (candies[pupil] == 0) {
            auto adj = 0;

            if (pupil != 0u && marks[pupil - 1u] < marks[pupil])
                adj = candy(marks, candies, pupil - 1u);

            if (pupil != marks.size() - 1u && marks[pupil + 1u] < marks[pupil])
                adj = std::max(adj, candy(marks, candies, pupil + 1u));

            candies[pupil] = adj + 1;
        }

        assert(candies[pupil] > 0);
        return candies[pupil];
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    const auto marks = read_marks();
    std::vector<int> candies (marks.size());

    auto total_candies = 0LL;
    for (std::size_t pupil {0u}; pupil != marks.size(); ++pupil)
        total_candies += candy(marks, candies, pupil);

    std::cout << total_candies << '\n';
}

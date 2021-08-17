#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

namespace {
    using It = std::vector<int>::const_iterator;

    std::vector<int> read_record()
    {
        std::size_t length {};
        std::cin >> length;

        std::vector<int> ret (length);
        std::copy_n(std::istream_iterator<int>{std::cin}, length, begin(ret));
        return ret;
    }

    long long clipped_height_sum(const std::vector<int>& heights,
                                 const std::vector<int>& lasers) noexcept
    {
        const auto first = cbegin(lasers), last = cend(lasers);
        const auto nheights = static_cast<int>(heights.size());
        auto sum = 0LL;

        for (auto i = 0; i != nheights; ++i) {
            const auto building = i + 1;
            const auto laserp = std::upper_bound(first, last, building);

            auto height = heights[i];
            if (laserp != last) height = std::min(height, *laserp - building);
            //std::cerr << height << '\n';
            sum += height;
        }

        return sum;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    const auto heights = read_record();

    auto lasers = read_record();
    std::sort(begin(lasers), end(lasers));

    std::cout << clipped_height_sum(heights, lasers) << '\n';
}

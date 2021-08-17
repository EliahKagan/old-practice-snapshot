#include <algorithm>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <utility>
#include <vector>

namespace {
    using Coord = long long;
    using Interval = std::pair<Coord, Coord>;

    inline Coord get_area()
    {
        Coord n {}, m {};
        std::cin >> n >> m;
        return n * m;
    }

    std::unordered_map<Coord, std::vector<Interval>> get_rows()
    {
        int k {};
        std::cin >> k;
        std::unordered_map<Coord, std::vector<Interval>> rows;

        for (Coord r {}, c1 {}, c2 {}; k > 0; --k) {
            std::cin >> r >> c1 >> c2;
            ++c2;
            const auto p = rows.find(r);

            if (p == rows.end()) {
                std::vector<Interval> row;
                row.emplace_back(c1, c2);
                rows.emplace(r, std::move(row));
            }
            else p->second.emplace_back(c1, c2);
        }

        return rows;
    }

    inline void sort_and_sentinelize_row(std::vector<Interval>& row)
    {
        std::sort(row.begin(), row.end(), [](const Interval& w,
                                             const Interval& z) {
            return w.first < z.first;
        });

        row.emplace_back(std::numeric_limits<Coord>::max(),
                         std::numeric_limits<Coord>::max());
    }

    Coord measure_row(const std::vector<Interval>& row)
    {
        Coord length {0};

        auto left = std::numeric_limits<Coord>::min();
        auto right = std::numeric_limits<Coord>::min();

        for (const auto& interval : row) {
            if (right < interval.first) {
                length += right - left;
                left = interval.first;
                right = interval.second;
            }
            else if (right < interval.second) right = interval.second;
        }

        return length;
    }
}

int main()
{
    auto area = get_area();

    for (auto& kv : get_rows()) {
        sort_and_sentinelize_row(kv.second);
        area -= measure_row(kv.second);
    }

    std::cout << area << '\n';
}

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <tuple>
#include <utility>
#include <vector>

class Solution {
public:
    static std::vector<int>
    smallestRange(const std::vector<std::vector<int>>& nums);
};

namespace {
    class AndCounter {
    public:
        explicit AndCounter(std::size_t size);
        void add(unsigned item) noexcept;
        void remove(unsigned item) noexcept;
        bool goal_met() const noexcept;

    private:
        std::vector<unsigned> targets_;
        std::size_t need_;
    };

    AndCounter::AndCounter(const std::size_t size) : targets_(size), need_{size}
    {
    }

    inline void AndCounter::add(const unsigned item) noexcept
    {
        if (targets_[item]++ == 0u) --need_;
    }

    inline void AndCounter::remove(const unsigned item) noexcept
    {
        if (--targets_[item] == 0u) ++need_;
    }

    inline bool AndCounter::goal_met() const noexcept
    {
        return need_ == 0u;
    }

    struct Element {
        int value;
        unsigned row_id;
    };

    constexpr bool operator<(const Element& lhs, const Element& rhs) noexcept
    {
        return lhs.value < rhs.value;
    }

#ifdef __GNUC__
    [[gnu::unused]]
#endif
    constexpr bool operator>(const Element& lhs, const Element& rhs) noexcept
    {
        return lhs.value > rhs.value;
    }

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#pragma clang diagnostic ignored "-Wglobal-constructors"
#endif
    const std::vector<int> k_empty_row;
#ifdef __clang__
#pragma clang diagnostic pop
#endif

    std::vector<Element>
    mark_and_merge(const std::vector<int>& row1, const unsigned id1,
                   const std::vector<int>& row2 = k_empty_row,
                   const unsigned id2 = std::numeric_limits<unsigned>::max())
    {
        const auto last1 = std::cend(row1), last2 = std::cend(row2);
        auto first1 = std::cbegin(row1), first2 = std::cbegin(row2);

        std::vector<Element> dest (row1.size() + row2.size());
        auto d_first = std::begin(dest);

        for (; first1 != last1 && first2 != last2; ++d_first) {
            if (*first2 < *first1) {
                *d_first = {*first2, id2};
                ++first2;
            } else {
                *d_first = {*first1, id1};
                ++first1;
            }
        }

        for (; first1 != last1; ++first1, ++d_first) *d_first = {*first1, id1};
        for (; first2 != last2; ++first2, ++d_first) *d_first = {*first2, id2};

        assert(d_first == std::end(dest));
        return dest;
    }

    std::vector<std::vector<Element>>
    do_mark_and_merge_pass(const std::vector<std::vector<int>>& in)
    {
        const auto in_count = static_cast<unsigned>(in.size());
        if (in_count == 0u) throw std::invalid_argument{"there are no rows"};

        std::vector<std::vector<Element>> out;
        out.reserve((in_count + 1u) / 2u);

        for (auto i = 1u; i < in_count; i += 2) {
            auto elems = mark_and_merge(in[i - 1u], i - 1u, in[i], i);
            if (!elems.empty()) out.push_back(std::move(elems));
        }

        if (in_count % 2u != 0u && !in.back().empty())
            out.push_back(mark_and_merge(in.back(), in_count - 1u));

        if (out.empty()) throw std::invalid_argument{"there are no elements"};
        return out;
    }

    void do_merge_pass(std::vector<std::vector<Element>>& in)
    {
        const auto out_count = (in.size() + 1u) / 2;
        std::vector<std::vector<Element>> out;
        out.reserve(out_count);

        auto pp = std::end(in);
        if (in.size() % 2u != 0u) --pp;

        for (auto p = std::begin(in); p != pp; p += 2) {
            const auto q = std::next(p);

            if (q->front() < p->back() && p->front() < q->back()) { // merge
                out.emplace_back(p->size() + q->size());

                std::merge(std::cbegin(*p), std::cend(*p),
                           std::cbegin(*q), std::cend(*q),
                           std::begin(out.back()));
            } else { // concatenate
                if (q->front() < p->back()) std::iter_swap(p, q);

                out.push_back(std::move(*p));
                auto& cat = out.back();

                const auto psize = cat.size();
                cat.resize(psize + q->size());

                std::copy(std::cbegin(*q), std::cend(*q),
                          std::begin(cat) + static_cast<std::ptrdiff_t>(psize));
            }

        }

        if (pp != std::end(in)) out.push_back(std::move(*pp));
        assert(out.size() == out_count);
        in = std::move(out);
    }

    std::vector<Element> merge_rows(const std::vector<std::vector<int>>& in)
    {
        auto out = do_mark_and_merge_pass(in);
        while (out.size() != 1u) do_merge_pass(out);
        return out.front();
    }

    inline void update_min_range(std::pair<int, int>& range,
                                 const int first, const int second) noexcept
    {
        if (second - first < range.second - range.first) {
            range.first = first;
            range.second = second;
        }
    }

    std::pair<int, int> find_smallest_range(const std::vector<Element>& a,
                                            AndCounter& counter) noexcept
    {
        auto range = std::make_pair(a.front().value, a.back().value);

        const auto last = std::cend(a);
        for (auto left = std::begin(a), right = left; ; ) {
            for (; !counter.goal_met() && right != last; ++right)
                counter.add(right->row_id);

            if (!counter.goal_met()) break;

            for (; counter.goal_met(); ++left)
                counter.remove(left->row_id);

            update_min_range(range, std::prev(left)->value,
                             std::prev(right)->value);
        }

        return range;
    }
}

std::vector<int>
Solution::smallestRange(const std::vector<std::vector<int>>& nums)
{
    const auto a = merge_rows(nums);
    if (a.empty()) throw std::invalid_argument{"there are no values"};

    AndCounter counter {nums.size()};

    std::vector<int> ret (2u);
    std::tie(ret.front(), ret.back()) = find_smallest_range(a, counter);
    return ret;
}

namespace {
    void test(const std::vector<std::vector<int>>& nums)
    {
        const auto result = Solution::smallestRange(nums);
        std::cout << '[' << result.front() << ", " << result.back() << "]\n";
    }
}

int main()
{
    test({{4, 10, 15, 24, 26},
          {0, 9, 12, 20},
          {5, 18, 22, 30}});

    test({{-39188, -19118},
          {-92167, -74585, -71372, -68941, -66699, -66541, -65520, -61363, -47182, -42837, -42606, -4518, 12948, 18858, 24820, 36209, 55066, 64917, 65611, 82101, 90910, 91233},
          {-54216, -22937, -17115, -1603, 2167, 36929},
          {-94402, -57858, -48916, -38906, -27238, -615, 43439, 57426, 88482},
          {-90879, -88451, -86193, -84039, -83226, -82043, -76734, -70728, -68704, -64036, -61383, -56726, -56542, -50342, -40026, -29768, -27798, -25701, -22833, -21175, -18805, -17066, -16382, -1192, 1599, 7103, 7759, 12194, 19076, 24753, 30678, 31160, 47688, 53150, 56513, 57693, 58054, 58876, 61753, 66660, 67005, 69236, 70360, 77765, 80622, 85875, 87923, 89693, 91719, 93501, 93756, 93965, 98746, 98751, 99624},
          {-93492, -75274, -75042, -73965, -70584, -67383, -62776, -59901, -47608, -46677, -46256, -22718, -13115, -12702, -11416, -10030, -7529, 1512, 5804, 8803, 12381, 19380, 24865, 24983, 28389, 39141, 42273, 45040, 59032, 73663, 74333, 82422, 87044, 87495, 93470, 97758, 99008},
          {-99615, -96435, -94713, -84516, -84092, -83271, -83196, -82663, -81339, -79318, -72884, -72814, -72266, -72059, -63513, -59654, -54579, -53893, -48416, -48342, -44555, -34252, -21257, -20760, -17101, -17093, -16354, -13770, -5325, -2980, -2047, -2041, -1876, 5721, 5850, 7217, 15316, 18064, 18490, 24318, 30518, 37714, 38240, 43405, 47303, 47405, 56965, 60219, 62012, 64024, 68853, 68948, 68987, 71759, 72264, 74765, 76709, 86777, 86947, 87933, 97352},
          {-91797, -87698, -84590, -81956, -74207, -73699, -72692, -72516, -67008, -62520, -61792, -61466, -53035, -44200, -36235, -30447, -27236, -21593, -20133, -17521, -14713, -13694, -12818, -2842, -424, 6649, 10498, 12692, 17478, 26721, 27276, 28361, 30913, 41900, 50333, 52277, 53232, 57268, 57832, 67006, 78180, 78218, 81042, 86146, 86596, 89450},
          {-99254, -91367, -90384, -89507, -88167, -87488, -86508, -85257, -85130, -84787, -80724, -80327, -79068, -78644, -74888, -72647, -70801, -66180, -65235, -65118, -65013, -63480, -62578, -57156, -54835, -50920, -50626, -48537, -48472, -48267, -39760, -38004, -37883, -36034, -33527, -31950, -31155, -28798, -25985, -25818, -22702, -21719, -15520, -15037, -6593, -4347, -4307, -3746, -3170, 1567, 5657, 8100, 10270, 10644, 12976, 14458, 15675, 17582, 18572, 20304, 25305, 31757, 36520, 37121, 37713, 39530, 40236, 47942, 49216, 51242, 53337, 53540, 54578, 54726, 55794, 57054, 58971, 63471, 65853, 66177, 69514, 71366, 72327, 77827, 80458, 88078, 90180, 99435}});

    test({{1, 2, 3, 5, 8, 9, 10, 12, 13, 14, 16, 17},
          {4, 12, 15, 16, 16},
          {-8, -5, -3, -2, -1, 1, 1},
          {-9, -4, -3, 0, 0},
          {4, 18, 33},
          {3, 5, 17, 20, 24},
          {90, 100, 112, 158, 159},
          {91, 99, 103, 155, 177}});
}

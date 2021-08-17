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

    template<typename T>
    std::size_t get_total_size(const std::vector<std::vector<T>>& rows) noexcept
    {
        std::size_t size {0u};
        for (const auto& row : rows) size += row.size();
        return size;
    }

    std::vector<Element> flatten(const std::vector<std::vector<int>>& rows)
    {
        std::vector<Element> a (get_total_size(rows));
        auto p = std::begin(a);

        const auto row_count = static_cast<unsigned>(rows.size());
        for (auto row_id = 0u; row_id != row_count; ++row_id) {
            const auto& row = rows[row_id];
            const auto first = std::cbegin(row), last = std::cend(row);

            p = std::transform(first, last, p, [row_id](const int value) {
                return Element{value, row_id};
            });
        }

        assert(p == std::end(a));
        return a;
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
        for (auto left = std::cbegin(a), right = left; ; ) {
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
    auto a = flatten(nums);
    if (a.empty()) throw std::invalid_argument{"there are no values"};
    std::sort(std::begin(a), std::end(a));

    AndCounter counter {nums.size()};

    std::vector<int> ret (2u);
    std::tie(ret.front(), ret.back()) = find_smallest_range(a, counter);
    return ret;
}

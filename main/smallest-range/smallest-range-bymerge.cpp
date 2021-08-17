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

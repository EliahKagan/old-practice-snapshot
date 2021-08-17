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
        // Allows Element objects to be emplaced into standard containers.
        constexpr Element(int value, unsigned row_id) noexcept;

        int value;
        unsigned row_id;
    };

    constexpr Element::Element(const int value, const unsigned row_id) noexcept
            : value{value}, row_id{row_id}
    {
    }

#ifdef __GNUC__
    [[gnu::unused]]
#endif
    constexpr bool operator<(const Element& lhs, const Element& rhs) noexcept
    {
        return lhs.value < rhs.value;
    }

    constexpr bool operator>(const Element& lhs, const Element& rhs) noexcept
    {
        return lhs.value > rhs.value;
    }

    template<typename T>
    using MinHeap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

    class MergingQueue {
    public:
        explicit MergingQueue(const std::vector<std::vector<int>>& rows);
        bool can_enqueue() const noexcept;
        Element enqueue();
        Element dequeue();

    private:
        using It = std::vector<int>::const_iterator;

        void acquire(std::size_t row_id);
        Element dispense();

        std::queue<Element> fifo_;
        MinHeap<Element> heap_;
        std::vector<It> firsts_, lasts_;
    };

    MergingQueue::MergingQueue(const std::vector<std::vector<int>>& rows)
    {
        const auto row_count = rows.size();
        firsts_.reserve(row_count);
        lasts_.reserve(row_count);

        for (const auto& row : rows) {
            firsts_.push_back(std::cbegin(row));
            lasts_.push_back(std::cend(row));
        }

        for (std::size_t row_id {0u}; row_id != row_count; ++row_id)
            acquire(row_id);
    }

    bool MergingQueue::can_enqueue() const noexcept
    {
        return !heap_.empty();
    }

    Element MergingQueue::enqueue()
    {
        const auto elem = dispense();
        fifo_.push(elem);
        return elem;
    }

    Element MergingQueue::dequeue()
    {
        const auto elem = fifo_.front();
        fifo_.pop();
        return elem;
    }

    void MergingQueue::acquire(const std::size_t row_id)
    {
        if (firsts_[row_id] != lasts_[row_id]) {
            heap_.emplace(*firsts_[row_id], row_id);
            ++firsts_[row_id];
        }
    }

    Element MergingQueue::dispense()
    {
        const auto elem = heap_.top();
        heap_.pop();
        acquire(elem.row_id);
        return elem;
    }

    inline void update_min_range(std::pair<int, int>& range,
                                 const int low, const int high) noexcept
    {
        if (high - low < range.second - range.first) {
            range.first = low;
            range.second = high;
        }
    }

    std::pair<int, int>
    find_smallest_range(MergingQueue& merger, AndCounter& counter)
    {
        auto range = std::make_pair(0, std::numeric_limits<int>::max());

        for (auto low = range.first, high = range.second; ; ) {
            while (!counter.goal_met() && merger.can_enqueue()) {
                const auto elem = merger.enqueue();
                high = elem.value;
                counter.add(elem.row_id);
            }

            if (!counter.goal_met()) break;

            while (counter.goal_met()) {
                const auto elem = merger.dequeue();
                low = elem.value;
                counter.remove(elem.row_id);
            }

            update_min_range(range, low, high);
        }

        return range;
    }
}

std::vector<int>
Solution::smallestRange(const std::vector<std::vector<int>>& nums)
{
    MergingQueue merger {nums};
    if (!merger.can_enqueue())
        throw std::invalid_argument{"there are no values"};

    AndCounter counter {nums.size()};

    std::vector<int> ret(2u);
    std::tie(ret.front(), ret.back()) = find_smallest_range(merger, counter);
    return ret;
}

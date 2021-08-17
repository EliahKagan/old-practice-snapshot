#include <cstddef>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <queue>
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

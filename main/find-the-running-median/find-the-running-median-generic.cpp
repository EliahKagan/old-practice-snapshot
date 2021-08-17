#include <cassert>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

namespace {
    // Priority queue implemented as a binary heap. Unlike std::priority_queue,
    // this makes a minheap (not a maxheap) with Compare=std::less<>.
    template<typename T, typename Container, typename Compare>
    class Heap {
    public:
        using size_type = typename Container::size_type;

        explicit constexpr Heap(const Compare compare)
            : compare_{compare} { }

        constexpr Heap() : Heap{Compare{}} { }

        bool empty() const noexcept { return elems_.empty(); }

        size_type size() const noexcept { return elems_.size(); }

        void push(T elem);

        void pop() noexcept;

        const T& top() const noexcept { return elems_.front(); }

        T& top() noexcept { return elems_.front(); };

    private:
        static constexpr auto no_child = std::numeric_limits<size_type>::max();

        void sift_up() noexcept;

        void sift_down(T elem) noexcept;

        size_type pick_child(size_type parent) const noexcept;

        Container elems_;
        Compare compare_;
    };

    template<typename T, typename Container, typename Compare>
    void Heap<T, Container, Compare>::push(T elem)
    {
        elems_.push_back(std::move(elem));
        sift_up();
    }

    template<typename T, typename Container, typename Compare>
    void Heap<T, Container, Compare>::pop() noexcept
    {
        auto elem = std::move(elems_.back());
        elems_.pop_back();
        sift_down(std::move(elem));
    }

    template<typename T, typename Container, typename Compare>
    void Heap<T, Container, Compare>::sift_up() noexcept
    {
        auto child = size() - 1u;
        auto elem = std::move(elems_[child]);

        while (child != 0u) {
            const auto parent = (child - 1u) / 2u;
            if (!compare_(elem, elems_[parent])) break;

            elems_[child] = std::move(elems_[parent]);
            child = parent;
        }

        elems_[child] = std::move(elem);
    }

    template<typename T, typename Container, typename Compare>
    void Heap<T, Container, Compare>::sift_down(T elem) noexcept
    {
        size_type parent {};

        for (; ; ) {
            const auto child = pick_child(parent);
            if (child == no_child || !compare_(elems_[child], elem)) break;

            elems_[parent] = std::move(elems_[child]);
            parent = child;
        }

        elems_[parent] = std::move(elem);
    }

    template<typename T, typename Container, typename Compare>
    auto Heap<T, Container, Compare>::pick_child(
            const size_type parent) const noexcept -> size_type
    {
        const auto left = parent * 2 + 1;
        if (left >= size()) return no_child;

        const auto right = left + 1;
        return right != size() && compare_(elems_[right], elems_[left]) ? right
                                                                        : left;
    }

    template<typename T>
    using MinHeap = Heap<T, std::vector<T>, std::less<>>;

    template<typename T>
    using MaxHeap = Heap<T, std::vector<T>, std::greater<>>;

    class ExpandingMedianBag {
    public:
        void insert(int value);

        double median() const noexcept;

    private:
        std::ptrdiff_t delta() const noexcept;

        void rebalance();

        MaxHeap<int> low_;
        MinHeap<int> high_;
    };

    void ExpandingMedianBag::insert(const int value)
    {
        if (high_.empty() || high_.top() < value)
            high_.push(value);
        else
            low_.push(value);

        rebalance();
    }

    double ExpandingMedianBag::median() const noexcept
    {
        switch (delta()) {
        case 0: // Even number of values. Take the mean of the center two.
            return (static_cast<double>(low_.top())
                    + static_cast<double>(high_.top())) / 2.0;

        case +1: // Odd number of values. The median is in low_.
            return static_cast<double>(low_.top());

        case -1: // Odd number of values. The median is in high_.
            return static_cast<double>(high_.top());

        default: // This could only happen in a balancing invariant violation.
            assert(false);
        }
    }

    inline std::ptrdiff_t ExpandingMedianBag::delta() const noexcept
    {
        return static_cast<std::ptrdiff_t>(low_.size())
                - static_cast<std::ptrdiff_t>(high_.size());
    }

    void ExpandingMedianBag::rebalance()
    {
        switch (delta()) {
        case +2: // low_ is too big, so move an element from low_ to high_.
            high_.push(low_.top());
            low_.pop();
            break;

        case -2: // high_ is too big, so move an element from high_ to low_.
            low_.push(high_.top());
            high_.pop();
            break;

        default: // Do nothing. The heaps cannot be made any more balanced.
            break;
        }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(1);

    ExpandingMedianBag bag;

    int n {};
    for (std::cin >> n; n > 0; --n) {
        int x {};
        std::cin >> x;
        bag.insert(x);
        std::cout << bag.median() << '\n';
    }
}

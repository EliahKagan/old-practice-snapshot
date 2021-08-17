#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace {
    // A PrimHeapMultiSet is a modified version of the kind of binary minheap
    // commonly used in Prim's algorithm. A true Prim heap would map keys,
    // used as vertex IDs, to values, used as costs, where lookup is by key and
    // heap ordering is by value. In the same sense that a Prim heap is a
    // (uni)map, a PrimHeapMultiSet is a multiset.
    template<typename T, template<typename> class Compare = std::less>
    class PrimHeapMultiSet {
    public:
        using size_type = typename std::vector<T>::size_type;

        explicit PrimHeapMultiSet(const Compare<T>& compare = Compare<T>{})
                noexcept : compare_{compare} { }

        bool empty() const noexcept { return elems_.empty(); }

        size_type size() const noexcept { return elems_.size(); }

        template<typename... Args>
        void emplace(Args&&... args);

        void push(const T& value) { emplace(value); }

        void push(T&& value) { emplace(std::move(value)); }

        void pop();

        const T& top() const
        {
            throw_if_empty();
            return elems_.front();
        }

        bool contains(const T& value) const noexcept
        {
            return table_.find(value) != std::end(table_);
        }

        void decrease(const T& old_value, const T& new_value);

    private:
        static void erase_index(std::unordered_set<size_type>& row,
                                const size_type index) noexcept
        {
            const auto count = row.erase(index);
            assert(count == 1u);
        }

        static void insert_index(std::unordered_set<size_type>& row,
                                 const size_type index)
        {
            auto inserted = false;
            std::tie(std::ignore, inserted) = row.insert(index);
            assert(inserted);
        }

        static constexpr auto npos = std::numeric_limits<size_type>::max();

        void throw_if_empty() const
        {
            if (empty()) throw std::out_of_range{"heap is empty"};
        }

        void map(const size_type index)
        {
            insert_index(table_[elems_[index]], index);
        }

        void unmap_by_index(size_type index) noexcept;

        size_type unmap_by_value(const T& value) noexcept; // returns index

        void replace_index(const T& value, size_type outgoing,
                                           size_type incoming);

        void sift_up(size_type child);

        void sift_down(size_type parent);

        size_type pick_child(size_type parent) const noexcept;

        void exchange(size_type src, size_type dest);

        bool order_ok(const size_type parent,
                      const size_type child) const noexcept
        {
            return !compare_(elems_[child], elems_[parent]);
        }

        std::unordered_map<T, std::unordered_set<size_type>> table_;
        std::vector<T> elems_ {};
        Compare<T> compare_;
    };

    template<typename T, template<typename> class Compare>
    template<typename... Args>
    void PrimHeapMultiSet<T, Compare>::emplace(Args&&... args)
    {
        const auto child = size();
        elems_.emplace_back(std::forward<Args>(args)...);
        map(child);
        sift_up(child);
    }

    template<typename T, template<typename> class Compare>
    void PrimHeapMultiSet<T, Compare>::pop()
    {
        throw_if_empty();
        unmap_by_index(0u);
        const auto last = size() - 1u;

        if (last == 0u) {
            // this was the only element, so just clear the heap
            assert(table_.empty());
            elems_.clear();
        } else {
            // there are other elements, so the heap property must be restored
            replace_index(elems_.back(), last, 0u);
            elems_.front() = std::move(elems_.back());
            elems_.pop_back();
            sift_down(0u);
        }
    }

    template<typename T, template<typename> class Compare>
    void PrimHeapMultiSet<T, Compare>::decrease(const T& old_value,
                                                const T& new_value)
    {
        if (!contains(old_value))
            throw std::invalid_argument{"value not found"};

        if (compare_(old_value, new_value))
            throw std::domain_error{"can't decrease to a greater value"};

        if (old_value == new_value) return;

        const auto child = unmap_by_value(old_value);
        elems_[child] = new_value;
        map(child);
        sift_up(child);
    }

    template<typename T, template<typename> class Compare>
    void PrimHeapMultiSet<T, Compare>::unmap_by_index(
            const size_type index) noexcept
    {
        const auto row_it = table_.find(elems_[index]);
        assert(row_it != std::end(table_));
        auto& row = row_it->second;

        if (row.size() == 1u) {
            // this element is nowhere else in the heap, so drop the whole row
            table_.erase(row_it);
        } else {
            // this element is duplicated, so find and remove only this index
            erase_index(row, index);
        }
    }

    template<typename T, template<typename> class Compare>
    auto PrimHeapMultiSet<T, Compare>::unmap_by_value(const T& value) noexcept
            -> size_type
    {
        const auto row_it = table_.find(value);
        assert(row_it != std::end(table_));
        auto& row = row_it->second;

        const auto index_it = std::cbegin(row);
        assert(index_it != std::cend(row));
        const auto index = *index_it;

        if (row.size() == 1u) {
            // this element is nowhere else in the heap, so drop the whole row
            table_.erase(row_it);
        } else {
            // this element is duplicated, so remove only this index
            row.erase(index_it);
        }

        return index;
    }

    template<typename T, template<typename> class Compare>
    void PrimHeapMultiSet<T, Compare>::replace_index(
            const T& value, const size_type outgoing, const size_type incoming)
    {
        auto& row = table_.at(value);
        erase_index(row, outgoing);
        insert_index(row, incoming);
    }

    template<typename T, template<typename> class Compare>
    void PrimHeapMultiSet<T, Compare>::sift_up(size_type child)
    {
        while (child != 0u) {
            const auto parent = (child - 1u) / 2u;
            if (order_ok(parent, child)) break;
            
            exchange(child, parent);
            child = parent;
        }
    }

    template<typename T, template<typename> class Compare>
    void PrimHeapMultiSet<T, Compare>::sift_down(size_type parent)
    {
        for (; ; ) {
            const auto child = pick_child(parent);
            if (child == npos || order_ok(parent, child)) break;

            exchange(parent, child);
            parent = child;
        }
    }

    template<typename T, template<typename> class Compare>
    auto PrimHeapMultiSet<T, Compare>::pick_child(const size_type parent)
            const noexcept -> size_type
    {
        const auto len = size();

        const auto left = parent * 2u + 1u;
        if (left >= len) return npos;

        const auto right = left + 1u;
        return right == len || order_ok(left, right) ? left : right;
    }

    template<typename T, template<typename> class Compare>
    void PrimHeapMultiSet<T, Compare>::exchange(const size_type src,
                                                const size_type dest)
    {
        assert(src != dest);

        auto& src_elem = elems_[src];
        auto& dest_elem = elems_[dest];
        assert(src_elem != dest_elem);

        replace_index(src_elem, src, dest);
        replace_index(dest_elem, dest, src);

        using std::swap;
        swap(src_elem, dest_elem);
    }

    // A multiset of ints, supporting logarithmic insertion and removal, and
    // (when non-empty) constant-time computation of the current median.
    class MedianBag {
    private:
        using MaxHeap = PrimHeapMultiSet<int, std::greater>;
        using MinHeap = PrimHeapMultiSet<int, std::less>;

    public:
        using size_type = MaxHeap::size_type;

        bool empty() const noexcept { return size() == 0u; }

        size_type size() const noexcept { return low_.size() + high_.size(); }

        void add(int value);

        bool remove(int value); // true iff found

        double compute_median() const;

    private:
        static_assert(std::is_same<MaxHeap::size_type,
            MinHeap::size_type>::value,
            "minheap and maxheap sizes must be of the same type");

        inline bool remove_low(int value); // true iff found

        inline bool remove_high(int value); // true iff found

        void rebalance();

        inline void pass_low_to_high();

        inline void pass_high_to_low();

        size_type get_size_delta() const noexcept
        {
            return high_.size() - low_.size();
        }

        MaxHeap low_ {};
        MinHeap high_ {};
    };

    void MedianBag::add(const int value)
    {
        if (low_.empty() || value < low_.top()) low_.push(value);
        else high_.push(value);

        rebalance();
    }

    bool MedianBag::remove(const int value)
    {
        if (remove_low(value) || remove_high(value)) {
            rebalance();
            return true;
        }

        return false;
    }

    double MedianBag::compute_median() const
    {
        switch (get_size_delta()) {
        case static_cast<size_type>(0):
            // converting before adding rather than after prevents overflow
            return (static_cast<double>(low_.top())
                    + static_cast<double>(high_.top())) / 2.0;

        case static_cast<size_type>(-1):
            return static_cast<double>(low_.top());

        case static_cast<size_type>(+1):
            return static_cast<double>(high_.top());

        default:
            std::abort(); // would mean the balancing invariant was violated
        }
    }

    inline bool MedianBag::remove_low(const int value)
    {
        if (!low_.contains(value)) return false;

        low_.decrease(value, std::numeric_limits<int>::max());
        low_.pop();
        return true;
    }

    inline bool MedianBag::remove_high(const int value)
    {
        if (!high_.contains(value)) return false;

        high_.decrease(value, std::numeric_limits<int>::min());
        high_.pop();
        return true;
    }

    void MedianBag::rebalance()
    {
        switch (get_size_delta()) {
        case static_cast<size_type>(-2):
            // low_ is too big and high_ is too small
            pass_low_to_high();
            break;

        case static_cast<size_type>(+2):
            // high_ is too big and low_ is too small
            pass_high_to_low();
            break;

        default:
            ; // the heaps can't currently be made any more balanced
        }
    }

    inline void MedianBag::pass_low_to_high()
    {
        const auto low_max = low_.top();
        low_.pop();
        high_.push(low_max);
    }

    inline void MedianBag::pass_high_to_low()
    {
        const auto high_min = high_.top();
        high_.pop();
        low_.push(high_min);
    }

    inline void display(const double x)
    {
        std::printf("%.*f\n", (x == std::nearbyint(x) ? 0 : 1), x);
    }
}

int main()
{
    MedianBag bag;
    
    auto n = 0;
    if (std::scanf("%d", &n) != 1) std::abort(); // read error

    while (n-- > 0) {
        auto act = '\0';
        auto arg = 0;
        if (std::scanf(" %c %d", &act, &arg) != 2) std::abort(); // read error

        switch (act) {
        case 'a':
            bag.add(arg);
            break;

        case 'r':
            if (!bag.remove(arg) || bag.empty()) {
                std::puts("Wrong!");
                continue; // don't attempt to compute and display a median
            }
            break;

        default:
            std::abort(); // unrecognized action
        }

        display(bag.compute_median());
    }
}

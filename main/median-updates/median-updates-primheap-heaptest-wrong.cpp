#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cassert>
#include <cstdio>
#include <functional>
#include <iostream> // TODO: remove after debugging
#include <iterator>
#include <limits>
#include <stdexcept>
#include <tuple>
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
    template<typename T, template<typename> typename Compare = std::less>
    class PrimHeapMultiSet {
    public:
        using size_type = typename std::vector<T>::size_type;

        explicit PrimHeapMultiSet(const Compare<T>& compare = Compare<T>{})
            : compare_{compare} { }

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
        // TODO: make this a function template that takes forwarding references

    private:
        static void erase_index(std::unordered_set<size_type>& row,
                                const size_type index)
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

        void sift_up(size_type child);

        void sift_down(size_type parent);

        size_type pick_child(size_type parent) const noexcept;

        void exchange(size_type src, size_type dest);

        bool order_ok(const size_type parent,
                      const size_type child) const noexcept
        {
            return !compare_(elems_[child], elems_[parent]);
        }

        void dump() const; // emits table_ and elems_ contents for debugging

        std::unordered_map<T, std::unordered_set<size_type>> table_;
        std::vector<T> elems_ {};
        Compare<T> compare_;
    };

    template<typename T, template<typename> typename Compare>
    template<typename... Args>
    void PrimHeapMultiSet<T, Compare>::emplace(Args&&... args)
    {
        // FIXME: remove this stanza after debugging
        dump();
        std::cerr << "emplace(" << '?' << ")\n\n";

        const auto child = size();
        elems_.emplace_back(std::forward<Args>(args)...);
        map(child);
        sift_up(child);
    }

    template<typename T, template<typename> typename Compare>
    void PrimHeapMultiSet<T, Compare>::pop()
    {
        // FIXME: remove this stanza after debugging
        dump();
        std::cerr << "pop()\n\n";

        throw_if_empty();
        static constexpr size_type parent {0u};
        unmap_by_index(parent);

        if (size() == 1u) {
            // this was the only element, so just clear the heap
            assert(table_.empty());
            elems_.clear();
        } else {
            // there are other elements, so the heap property must be restored
            elems_.front() = std::move(elems_.back());
            elems_.pop_back();
            sift_down(parent);
        }
    }

    template<typename T, template<typename> typename Compare>
    void PrimHeapMultiSet<T, Compare>::decrease(const T& old_value,
                                                const T& new_value)
    {
        if (!contains(old_value))
            throw std::invalid_argument{"value not found"};

        if (new_value == old_value) return;

        if (new_value > old_value)
            throw std::domain_error{"can't decrease to a higher value"};

        const auto child = unmap_by_value(old_value);
        elems_[child] = new_value;
        map(child);
        sift_up(child);
    }

    template<typename T, template<typename> typename Compare>
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

    template<typename T, template<typename> typename Compare>
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

    template<typename T, template<typename> typename Compare>
    void PrimHeapMultiSet<T, Compare>::sift_up(size_type child)
    {
        // FIXME: remove this stanza after debugging
        dump();
        std::cerr << "sift_up(" << child << ")\n\n";

        while (child != 0u) {
            const auto parent = (child - 1u) / 2u;
            if (order_ok(parent, child)) break;
            
            exchange(child, parent);
            child = parent;
        }
    }

    template<typename T, template<typename> typename Compare>
    void PrimHeapMultiSet<T, Compare>::sift_down(size_type parent)
    {
        // FIXME: remove this stanza after debugging
        dump();
        std::cerr << "sift_down(" << parent << ")\n\n";

        for (; ; ) {
            const auto child = pick_child(parent);
            if (child == npos || order_ok(parent, child)) break;

            exchange(parent, child);
            parent = child;
        }
    }

    template<typename T, template<typename> typename Compare>
    auto PrimHeapMultiSet<T, Compare>::pick_child(const size_type parent)
        const noexcept -> size_type
    {
        const auto len = size();

        const auto left = parent * 2u + 1u;
        if (left >= len) return npos;

        const auto right = left + 1u;
        return right == len || order_ok(left, right) ? left : right;
    }

    template<typename T, template<typename> typename Compare>
    void PrimHeapMultiSet<T, Compare>::exchange(const size_type src,
                                                const size_type dest)
    {
        // FIXME: remove this stanza after debugging
        dump();
        std::cerr << "exchange(" << src << ", " << dest << ")\n\n";

        assert(src != dest);

        auto& src_elem = elems_[src];
        auto& dest_elem = elems_[dest];
        assert(src_elem != dest_elem);

        auto& src_row = table_.at(src_elem);
        erase_index(src_row, src); //src_row.erase(src);
        insert_index(src_row, dest); //src_row.insert(dest);

        auto& dest_row = table_.at(dest_elem);
        erase_index(dest_row, dest); //dest_row.erase(dest);
        insert_index(dest_row, src); //dest_row.insert(src); // TODO: do just once in sift_{up,down} instead

        using std::swap;
        swap(src_elem, dest_elem);
    }

    template<typename T, template<typename> class Compare>
    void PrimHeapMultiSet<T, Compare>::dump() const
    {
        std::cerr << '<';

        for (const auto& kv : table_) {
            std::cerr << ' ' << kv.first << " {";
            for (const auto& index : kv.second) std::cerr << ' ' << index;
            std::cerr << " }";
        }

        std::cerr << " >\n[";

        for (decltype(elems_.size()) i{0u}; i != elems_.size(); ++i)
            std::cerr << ' ' << i << ':' << elems_[i];

        std::cerr << " ]\n";
    }

    template class PrimHeapMultiSet<int>; // FIXME: remove after testing
}

int main()
{
    PrimHeapMultiSet<int> heap;

    for (auto x : {10, 90, 50, 70, 80, 60, 30, 20, 40}) {
        std::cerr << "Pushing " << x << "...\n\n";
        heap.push(x);
    }

    while (!heap.empty()) {
        heap.pop();
    }
}

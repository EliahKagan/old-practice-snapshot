#ifdef NDEBUG
#error Assertions unexpectedly disabled.
#endif

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <unordered_map>
#include <vector>

namespace {
    // A disjoint-set-union data structure that tracks component sizes.
    class DisjointSets {
    public:
        // Creates a new singleton set. Returns the element index.
        int make_set();

        // Union by size. Returns the size of the resulting set.
        int unite(int index1, int index2) noexcept;
        
    private:
        // Finds the ancestor, performing full path compression.
        int find_set(int index) noexcept;

        // Joins the child to the parent. Returns the size of the new set.
        int join(int parent, int child) noexcept;

        // Reports the total number of elements across all sets.
        int count() const noexcept;

        // Reports of an element exists in any set.
        int exists(int index) const noexcept;

        // When i is a representative element, elems_[i] is the negative size
        // of the set containing i. Otherwise, elems_[i] is is the parent of i.
        std::vector<int> elems_;
    };

    int DisjointSets::make_set()
    {
        elems_.push_back(-1);
        return count() - 1;
    }

    int DisjointSets::unite(int index1, int index2) noexcept
    {
        assert(exists(index1));
        assert(exists(index2));

        // Find the ancestors and stop if they are the same.
        index1 = find_set(index1);
        index2 = find_set(index2);
        if (index1 == index2) return -elems_[index1];

        // Union by size. Sizes are stored negatively, so the index with the
        // more negative associated value will be the parent. If there is a
        // tie, pick index1 as the parent (either could be used in that case).
        return elems_[index2] < elems_[index1] ? join(index2, index1)
                                               : join(index1, index2);
    }

    int DisjointSets::find_set(int index) noexcept
    {
        assert(exists(index));

        // Find the ancestor.
        auto leader = index;
        while (elems_[leader] >= 0) leader = elems_[leader];

        // Compress the path.
        while (index != leader) {
            const auto parent = elems_[index];
            elems_[index] = leader;
            index = parent;
        }

        return leader;
    }

    int DisjointSets::join(const int parent, const int child) noexcept
    {
        elems_[parent] += elems_[child];
        elems_[child] = parent;
        return -elems_[parent];
    }

    inline int DisjointSets::count() const noexcept
    {
        return static_cast<int>(elems_.size());
    }

    inline int DisjointSets::exists(const int index) const noexcept
    {
        return 0 <= index && index < count();
    }

    // Wraps DisjointSets for a Key type that is hashable and equatable.
    template<typename Key>
    class KeyedDisjointSets {
    public:
        // Unite the sets containing key1 and key2. Returns the size of that
        // set. If a key is not yet an element, a makeset operation is first
        // performed to create a singleton set containing that key.
        int unite(Key key1, Key key2);

    private:
        // Obtains or creates the index for the specified key.
        int index(Key key);

        std::unordered_map<Key, int> map_;
        DisjointSets sets_;
    };

    template<typename Key>
    int KeyedDisjointSets<Key>::unite(const Key key1, const Key key2)
    {
        return sets_.unite(index(key1), index(key2));
    }

    template<typename Key>
    int KeyedDisjointSets<Key>::index(const Key key)
    {
        const auto it = map_.find(key);
        if (it != end(map_)) return it->second;

        const auto ret = sets_.make_set();
        map_.emplace(key, ret);
        return ret;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    int query_count {};
    std::cin >> query_count;
    assert(query_count > 0);

    KeyedDisjointSets<int> ksets;
    auto max_size = 0;

    while (query_count-- > 0) {
        int key1 {}, key2 {};
        std::cin >> key1 >> key2;
        assert(key1 > 0 && key2 > 0);
        
        max_size = std::max(max_size, ksets.unite(key1, key2));
        std::cout << max_size << '\n';
    }
}

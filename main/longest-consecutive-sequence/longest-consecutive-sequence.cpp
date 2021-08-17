namespace {
    class DisjointSetElement {
    public:
        DisjointSetElement() = default;
        DisjointSetElement(const DisjointSetElement&) = delete;
        DisjointSetElement(DisjointSetElement&&) = delete;
        DisjointSetElement& operator=(const DisjointSetElement&) = delete;
        DisjointSetElement& operator=(DisjointSetElement&&) = delete;
        ~DisjointSetElement() = default;

        // Size of the set this element represents (leads) if any. Otherwise 0.
        int size() const { return size_; }

        void unite(DisjointSetElement& other); // union by size

    private:
        DisjointSetElement& findSet(); // finds representative element

        DisjointSetElement* parent_ {this};

        int size_ {1};
    };

    inline bool operator==(const DisjointSetElement& a,
                           const DisjointSetElement& b)
    {
        return &a == &b;
    }

    inline bool operator!=(const DisjointSetElement& a,
                           const DisjointSetElement& b)
    {
        return !(a == b);
    }

    void DisjointSetElement::unite(DisjointSetElement& other)
    {
        auto& a = findSet();
        auto& b = other.findSet();
        if (a == b) return;

        if (a.size_ < b.size_) {
            b.size_ += a.size_;
            a.size_ = 0;
            a.parent_ = &b;
        } else {
            a.size_ += b.size_;
            b.size_ = 0;
            b.parent_ = &a;
        }
    }

    DisjointSetElement& DisjointSetElement::findSet()
    {
        auto res = this;
        while (res != res->parent_) res = res->parent_;

        for (auto cur = this; cur != res; ) { // path compression
            const auto next = cur->parent_;
            cur->parent_ = res;
            cur = next;
        }

        return *res;
    }

    class DisjointRanges {
    public:
        int max_size() const;

        void insert(int value);

    private:
        void try_connect(DisjointSetElement& elem, int adjacent);

        unordered_map<int, DisjointSetElement> elems_;
    };

    int DisjointRanges::max_size() const
    {
        auto acc = 0;
        for (const auto& kv : elems_) acc = max(acc, kv.second.size());
        return acc;
    }

    void DisjointRanges::insert(const int value)
    {
        // Only newly introduced elements need to trigger connection attempts.
        if (elems_.find(value) != elems_.end()) return;

        auto& elem = elems_[value]; // creates the element
        if (value != numeric_limits<int>::min()) try_connect(elem, value - 1);
        if (value != numeric_limits<int>::max()) try_connect(elem, value + 1);
    }

    void DisjointRanges::try_connect(DisjointSetElement& elem,
                                     const int adjacent)
    {
        const auto it = elems_.find(adjacent);
        if (it != elems_.end()) elem.unite(it->second);
    }
}

class Solution {
public:
    int longestConsecutive(vector<int>& nums)
    {
        DisjointRanges ranges;
        for (const auto value : nums) ranges.insert(value);
        return ranges.max_size();
    }
};

class Solution {
public:
    static int numSimilarGroups(const vector<string>& a);
};

namespace {
    class DisjointSets {
    public:
        explicit DisjointSets(size_t size);

        int countComponents() const noexcept
        {
            return static_cast<int>(countdown_);
        }

        void unite(size_t u, size_t v) noexcept;

    private:
        size_t findSet(size_t u) noexcept;

        vector<int> elems_;

        size_t countdown_;
    };

    DisjointSets::DisjointSets(const size_t size)
        : elems_(size, -1), countdown_{size}
    {
    }

    void DisjointSets::unite(size_t u, size_t v) noexcept
    {
        // find the current roots and stop if they are already the same
        u = findSet(u);
        v = findSet(v);
        if (u == v) return;

        // union by rank
        if (elems_[u] > elems_[v]) {
            // v has superior (more negative) rank, so it will be kept the root
            elems_[u] = static_cast<int>(v);
        } else {
            // if u and v have have the same rank, promote u
            if (elems_[u] == elems_[v]) --elems_[u];

            // u has superior (more negative) rank, so it will be kept the root
            elems_[v] = static_cast<int>(u);
        }

        // we joined formerly separate sets, so decrement the component count
        --countdown_;
    }

    size_t DisjointSets::findSet(size_t u) noexcept
    {
        // find the root
        auto v = u;
        while (elems_[v] >= 0) v = static_cast<size_t>(elems_[v]);

        // compress the path
        for (const auto vElem = static_cast<int>(v); u != v; ) {
            const auto uParent = static_cast<size_t>(elems_[u]);
            elems_[u] = vElem;
            u = uParent;
        }

        return v;
    }

    bool similar(string::const_iterator p, const string::const_iterator pp,
                 string::const_iterator q) noexcept
    {
        // similar strings, unless identical, have a first mismatch
        tie(p, q) = mismatch(p, pp, q);
        if (p == pp) return true;

        // nonidentical similar strings have a corresponding second mismatch
        const auto x = *p, y = *q;
        tie(p, q) = mismatch(++p, pp, ++q);
        if (p == pp || *p != y || *q != x) return false;

        // similar strings have no further mismatches
        tie(p, q) = mismatch(++p, pp, ++q);
        return p == pp;
    }
}

int Solution::numSimilarGroups(const vector<string>& a)
{
    const auto size = a.size();
    if (size == 0u) return 0;

    DisjointSets sets {size};

    const auto last = size - 1u;
    for (size_t i {0u}; i != last; ++i) {
        const auto p = cbegin(a[i]), pp = cend(a[i]);

        for (auto j = i + 1u; j != size; ++j)
            if (similar(p, pp, cbegin(a[j]))) sets.unite(i, j);
    }

    return sets.countComponents();
}

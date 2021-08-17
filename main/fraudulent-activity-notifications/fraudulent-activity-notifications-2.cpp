#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iterator>
#include <set>
#include <vector>

namespace {
    class DoubledMedianBag {
    public:
        DoubledMedianBag() = default;
        DoubledMedianBag(const DoubledMedianBag&) = delete;
        DoubledMedianBag(DoubledMedianBag&&) = default;
        DoubledMedianBag& operator=(const DoubledMedianBag&) = delete;
        DoubledMedianBag& operator=(DoubledMedianBag&&) = default;
        ~DoubledMedianBag() = default;

        void insert(int e);

        bool erase(int e) noexcept; // true iff it found and erased an element

        bool empty() const noexcept
        {
            return bag_.empty();
        }

        std::multiset<int>::size_type size() const noexcept
        {
            return bag_.size();
        }

        int doubled_median() const noexcept // undefined behavior if empty
        {
            return size() % 2 == 0 ? *pos_ + *std::next(pos_)
                                   : *pos_ * 2;
        }

    private:
        std::multiset<int> bag_ {};
        std::multiset<int>::iterator pos_ {std::end(bag_)};
    };

    void DoubledMedianBag::insert(const int e)
    {
        if (size() % 2 != 0) { // odd number of elements
            bag_.insert(e);
            if (e < *pos_) --pos_;
        }
        else if (!empty()) { // even number of elements, but more than zero
            bag_.insert(e);
            if (e >= *pos_) ++pos_;
        }
        else pos_ = bag_.insert(e); // there were no elements before this one
    }

    bool DoubledMedianBag::erase(const int e) noexcept
    {
        const auto p = bag_.lower_bound(e);
        if (p == std::end(bag_) || *p != e) return false;

        if (size() % 2 == 0) { // even number of elements
            if (e <= *pos_) ++pos_;
            bag_.erase(p);
        }
        else if (size() != 1) { // odd number of elements, but more than one
            if (e > *pos_ || p == pos_) --pos_;
            bag_.erase(p);
        }
        else pos_ = bag_.erase(p); // there were no elements except this one

        return true;
    }
}

int main()
{
    std::size_t n {};
    std::ptrdiff_t d {};
    (void)std::scanf("%zu%td", &n, &d);
    if (!(0 < d && static_cast<std::size_t>(d) <= n)) std::abort();

    std::vector<int> a (n);
    for (auto& e : a) (void)std::scanf("%d", &e);
    auto p = std::cbegin(a), q = p + d;

    DoubledMedianBag bag;
    std::for_each(p, q, [&bag](const int e) { bag.insert(e); });

    auto acc = 0;
    for (const auto qq = std::cend(a); q != qq; ++p, ++q) {
        if (bag.doubled_median() <= *q) ++acc;
        bag.erase(*p);
        bag.insert(*q);
    }

    std::printf("%d\n", acc);
}

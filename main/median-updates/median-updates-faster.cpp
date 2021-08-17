#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cmath>
#include <cstdio>
#include <iterator>
#include <set>

namespace {
    class MedianBag {
    public:
        MedianBag() = default;
        MedianBag(const MedianBag&) = delete;
        MedianBag(MedianBag&&) = default;
        MedianBag& operator=(const MedianBag&) = delete;
        MedianBag& operator=(MedianBag&&) = default;
        ~MedianBag() = default;

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

        double median() const noexcept; // undefined behavior if bag is empty

    private:
        std::multiset<int> bag_ {};
        std::multiset<int>::iterator pos_ {std::end(bag_)};
    };

    void MedianBag::insert(const int e)
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

    bool MedianBag::erase(const int e) noexcept
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

    double MedianBag::median() const noexcept
    {
        // With an odd number of elements, the middle element is the median.
        if (size() % 2 != 0) return *pos_;

        // With an even number of elements, we must average the two middle
        // elements. Converting them to double before adding instead of after
        // prevents arithmetic overflow unless their magnitudes are very large.
        // (If int is 32-bit, this is always sufficient to prevent overflow.)
        return (static_cast<double>(*pos_)
                + static_cast<double>(*std::next(pos_))) / 2.0;
    }

    inline void special_print(const double x) noexcept
    {
        std::printf("%.*f\n", (x == std::nearbyint(x) ? 0 : 1), x);
    }
}

int main()
{
    auto n = 0;
    (void)std::scanf("%d", &n);

    MedianBag bag;

    auto op = '\0';
    auto arg = 0;

    while (n-- > 0) {
        (void)std::scanf(" %c %d", &op, &arg);

        if (op == 'a') {
            bag.insert(arg);
        }
        else if (!bag.erase(arg) || bag.empty()) {
            std::puts("Wrong!");
            continue;
        }

        special_print(bag.median());
    }
}

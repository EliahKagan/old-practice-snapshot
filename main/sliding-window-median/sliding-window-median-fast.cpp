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
        multiset<int> bag_ {};
        multiset<int>::iterator pos_ {end(bag_)};
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
        if (p == end(bag_) || *p != e) return false;

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

        // When an even number of elements, we must average the two middle
        // elements. Converting them to double before adding instead of after
        // prevents arithmetic overflow unless their magnitudes are very large.
        // (If int is 32-bit, this is always sufficient to prevent overflow.)
        return (static_cast<double>(*pos_)
                + static_cast<double>(*next(pos_))) / 2.0;
    }
}

class Solution {
public:
    static vector<double> medianSlidingWindow(const vector<int>& nums, int k);
};

vector<double> Solution::medianSlidingWindow(const vector<int>& nums,
                                             const int k)
{
    vector<double> ret;
    if (nums.empty()) return ret;

    assert(0 < k);
    const auto window_size = static_cast<vector<double>::size_type>(k);
    assert(window_size <= nums.size());

    // Calling reserve and push_back is cleaner, but most compilers don't
    // optimize away the capacity check, even in simpler cases than this.
    // https://lemire.me/blog/2012/06/20/do-not-waste-time-with-stl-vectors/
    ret.resize(nums.size() - window_size + 1);
    auto r = begin(ret);

    MedianBag bag;

    auto p = cbegin(nums), q = p + k;
    for_each(p, q, [&bag](const int e) { bag.insert(e); });
    *r = bag.median();

    for (const auto qq = cend(nums); q != qq; ++p, ++q) {
        bag.erase(*p);
        bag.insert(*q);
        *++r = bag.median();
    }

    assert(next(r) == end(ret));
    return ret;
}

namespace {
    using MinBag = multiset<int, less<int>>;
    using MaxBag = multiset<int, greater<int>>;

    inline ptrdiff_t getSizeDelta(const MaxBag& low, const MinBag& high)
    {
        return static_cast<ptrdiff_t>(low.size())
                - static_cast<ptrdiff_t>(high.size());
    }

    void rebalance(MaxBag& low, MinBag& high)
    {
        switch (getSizeDelta(low, high)) {
        case +2: { // low is too big relative to high
            const auto p = low.cbegin();
            high.insert(high.cbegin(), *p);
            low.erase(p);
            break;
        }

        case -2: { // high is too big relative to low
            const auto p = high.cbegin();
            low.insert(low.cbegin(), *p);
            high.erase(p);
            break;
        }

        default:
            ; // the bags cannot currently be made any more balanced
        }
    }

    void add(MaxBag& low, MinBag& high, const int e)
    {
        const auto p = low.cbegin();

        if (p == low.cend() || e < *p) low.insert(e);
        else high.insert(e);

        rebalance(low, high);
    }

    void remove(MaxBag& low, MinBag& high, const int e) // assumes it was added
    {
        const auto p = low.find(e);

        if (p == low.end()) high.erase(high.find(e));
        else low.erase(p);

        rebalance(low, high);
    }

    double computeMedian(const MaxBag& low, const MinBag& high)
    {
        switch (getSizeDelta(low, high)) {
        case 0:
            // The number of values is even, so average the two medial values.
            // Assuming that int is 32-bit, converting to double before adding,
            // instead of after, would then be sufficient to prevent overflow.
            return (static_cast<double>(*low.cbegin())
                    + static_cast<double>(*high.cbegin())) / 2.0;

        case +1:
            return *low.cbegin(); // low is bigger so it has the medial value

        case -1:
            return *high.cbegin(); // high is bigger so it has the medial value

        default:
            abort(); // unreachable unless the balancing invariant was violated
        }
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

    MaxBag low;
    MinBag high;

    auto p = cbegin(nums), q = p + k;
    for_each(p, q, [&low, &high](const int e) { add(low, high, e); });
    *r = computeMedian(low, high);

    for (const auto qq = cend(nums); q != qq; ++p, ++q) {
        remove(low, high, *p);
        add(low, high, *q);
        *++r = computeMedian(low, high);
    }

    assert(++r == end(ret));
    return ret;
}

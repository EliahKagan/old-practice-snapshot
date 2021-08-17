class KthLargest {
public:
    KthLargest(int k, const vector<int>& nums);
    
    int add(int val) noexcept;
    
private:
    std::vector<int> heap_; // will store current heap plus one unused element
    const int k_;
};

KthLargest::KthLargest(const int k, const vector<int>& nums) : k_{k}
{
    // FIXME: refactor this constructor body
    assert(k > 0);
    const auto first = cbegin(nums);
    const auto last = (nums.size() < k ? cend(nums) : first + k_);
    
    heap_.reserve(k_ + 1);
    heap_.assign(first, last);
    make_heap(begin(heap_), end(heap_), greater<>{});
    assert(heap_.capacity() > heap_.size());
    heap_.emplace_back();
    
    for_each(last, cend(nums), [h_first = begin(heap_),
                                h_last = end(heap_)](const int val) noexcept {
        *(h_last - 1) = val;
        push_heap(h_first, h_last, greater<>{});
        pop_heap(h_first, h_last, greater<>{});
    });
}

int KthLargest::add(const int val) noexcept
{
    heap_.back() = val;
    push_heap(begin(heap_), end(heap_), greater<>{});
    
    if (heap_.size() == k_ + 1) {
        pop_heap(begin(heap_), end(heap_), greater<>{});
    } else {
        assert(heap_.size() <= k_);
        heap_.emplace_back();
    }
    
    return heap_.front();
}


/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */

class KthLargest {
public:
    KthLargest(int k, const vector<int>& nums);
    
    int add(int val);

private:
    std::priority_queue<int, std::vector<int>, std::greater<>> heap_;
    const int k_;
};

KthLargest::KthLargest(const int k, const vector<int>& nums)
    : heap_(cbegin(nums), (nums.size() <= k ? cend(nums) : cbegin(nums) + k)),
      k_{k}
{
    if (nums.size() <= k) return;
    
    for_each(cbegin(nums) + k, cend(nums), [this](const int val) noexcept {
        heap_.push(val);
        heap_.pop();
    });
}

int KthLargest::add(const int val)
{
    heap_.push(val);
    
    if (heap_.size() == k_ + 1) {
        heap_.pop();
    } else {
        assert(heap_.size() <= k_);
    }
    
    return heap_.top();
}

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */

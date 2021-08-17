class Solution {
public:
    Solution(vector<int>&& nums);

    /** Resets the array to its original configuration and return it. */
    const vector<int>& reset();

    /** Returns a random shuffling of the array. */
    const vector<int>& shuffle();

private:
    static mt19937_64::result_type seed();

    mt19937_64 gen_ {seed()};
    vector<int> current_, backup_;
};

Solution::Solution(vector<int>&& nums)
    : current_(move(nums)), backup_(current_)
{
}

const vector<int>& Solution::reset()
{
    current_ = backup_;
    return current_;
}

const vector<int>& Solution::shuffle()
{
    ::shuffle(begin(current_), end(current_), gen_);
    return current_;
}

mt19937_64::result_type Solution::seed()
{
    random_device rd;
    return rd();
}

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(nums);
 * vector<int> param_1 = obj.reset();
 * vector<int> param_2 = obj.shuffle();
 */

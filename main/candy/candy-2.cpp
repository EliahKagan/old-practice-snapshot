class Solution {
public:
    static int candy(const vector<int>& ratings);
};

int Solution::candy(const vector<int>& ratings)
{
    vector<int> dp (ratings.size());
    
    const auto candy_at = [&](const auto me, const int i) noexcept {
        if (dp[i] != 0) return dp[i];
        
        auto adj = 0;
        
        if (i != 0 && ratings[i] > ratings[i - 1])
            adj = max(adj, me(me, i - 1));
        
        if (i != ratings.size() - 1 && ratings[i] > ratings[i + 1])
            adj = max(adj, me(me, i + 1));
        
        dp[i] = adj + 1;
        return dp[i];
    };
    
    auto acc = 0;
    for (auto i = 0; i != ratings.size(); ++i) acc += candy_at(candy_at, i);
    return acc;
}

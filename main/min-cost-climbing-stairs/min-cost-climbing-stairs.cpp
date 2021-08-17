class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        cost.push_back(0);

        for (auto i = 2; i < cost.size(); ++i)
            cost[i] += min(cost[i - 2], cost[i - 1]);

        return cost.back();
    }
};

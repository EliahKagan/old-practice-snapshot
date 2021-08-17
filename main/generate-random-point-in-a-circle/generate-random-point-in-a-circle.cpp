class Solution {
public:
    Solution(double radius, double x_center, double y_center);
    
    vector<double> randPoint();

private:
    mt19937 eng_ {random_device{}()};
    uniform_real_distribution<double> dist_;
    double radius_;
    double x_center_;
    double y_center_;
    
};

Solution::Solution(const double radius, const double x_center,
                                        const double y_center)
    : dist_{-radius, radius},
      radius_{radius}, x_center_{x_center}, y_center_{y_center}
{
}

vector<double> Solution::randPoint()
{
    double dx {}, dy {};
    
    do {
        dx = dist_(eng_);
        dy = dist_(eng_);
    }
    while (sqrt(dx * dx + dy * dy) > radius_);
    
    return {x_center_ + dx, y_center_ + dy};
}

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(radius, x_center, y_center);
 * vector<double> param_1 = obj.randPoint();
 */

#include <iostream>
#include <random>
#include <vector>
using namespace std;

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

int main()
{
    Solution s {1.0, 0.0, 0.0};
    
    cout << "ListPlot[{";
    
    auto sep = "";
    for (auto i = 0; i < 5000; ++i) {
        const auto v = s.randPoint();
        cout << sep << '{' << v.front() << ',' << v.back() << '}';
        sep = ", ";
    }
    
    std::cout << "}, AspectRatio -> 1.0]\n";
}

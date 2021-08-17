
namespace {
    inline bool isValidRectangle(int (*const a)[MAX], const int i, const int j,
                                                      const int n, const int m)
    {
        for (auto h = i; h != n; ++h) {
            for (auto k = j; k != m; ++k)
                if (!a[h][k]) return false;
        }
        
        return true;
    }
    
    int maxAreaToLowerRight(int (*const a)[MAX], const int n, const int m)
    {
        auto acc = 0;
        
        for (auto i = 0; i != n; ++i) {
            for (auto j = 0; j != m; ++j) {
                if (isValidRectangle(a, i, j, n, m))
                    acc = max(acc, (n - i) * (m - j));
            }
        }
        
        return acc;
    }
}

/*You are required to complete this method*/
int maxArea(int (*const a)[MAX], const int n, const int m)
{
    auto acc = 0;
    
    for (auto i = n; i != 0; --i) {
        for (auto j = m; j != 0; --j)
            acc = max(acc, maxAreaToLowerRight(a, i, j));
    }
    
    return acc;
}

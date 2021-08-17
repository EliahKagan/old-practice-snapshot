/*You are required to complete this method */
int findPerimeter(int (*const mat)[MAX], const int n, const int m)
{
    constexpr auto vacant = 0;
    const auto imin = 0, imax = n - 1, jmin = 0, jmax = m - 1;
    auto count = 0;
    
    for (auto i = imin; i <= imax; ++i) {
        for (auto j = jmin; j <= jmax; ++j) {
            if (mat[i][j] == vacant) continue;
            
            if (i == imin || mat[i - 1][j] == vacant) ++count;
            if (i == imax || mat[i + 1][j] == vacant) ++count;
            if (j == jmin || mat[i][j - 1] == vacant) ++count;
            if (j == jmax || mat[i][j + 1] == vacant) ++count;
        }
    }
    
    return count;
}

// The matrix is constrainted to be small and extra space isn't prohibited,
// so I ignore mat's existing ordering and use the naive algorithm.
int kthSmallest(int mat[MAX][MAX], const int n, const int k)
{
    vector<int> a;
    a.reserve(n * n);
    
    for (auto i = 0; i != n; ++i)
        for (auto j = 0; j != n; ++j) a.push_back(mat[i][j]);
    
    sort(begin(a), end(a));
    return a[k - 1];
}

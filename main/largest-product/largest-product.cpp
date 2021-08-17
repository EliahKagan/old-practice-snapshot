/*You are required to complete the function*/
long long findMaxProduct(int *const a, const int n, int k)
{
    auto cur = 1LL;
    for (auto i = 0; i != k; ++i) cur *= a[i];
    
    auto best = cur;
    for (auto i = 0; k != n; ++i, ++k) {
        cur /= a[i];
        cur *= a[k];
        if (best < cur) best = cur;
    }
    
    return best;
}

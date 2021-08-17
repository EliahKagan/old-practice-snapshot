/*You are required to complete the function below*/
bool findTriplets(int *const a, const int n)
{
    sort(a, a + n);
    
    for (auto i = 0; i != n; ++i) {
        const auto target = -a[i];
        
        for (auto j = 0, k = n - 1; j < k; ) {
            const auto cur = a[j] + a[k];
            
            if (cur < target)       ++j;
            else if (cur != target) --k;
            else if (j == i)        ++j;
            else if (k == i)        --k;
            else                    return true;
        }
    }
    
    return false;
}

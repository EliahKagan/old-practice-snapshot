/*You are required to complete below method */
void countDistinct(int *const a, int k, const int n)
{
    unordered_map<int, int> freq;
    auto distinct = 0;
    
    for (auto j = 0; j < k; ++j)
        if (++freq[a[j]] == 1) ++distinct;
    
    cout << distinct;
    for (auto i = 0; k < n; ++i, ++k) {
        if (--freq[a[i]] == 0) --distinct;
        if (++freq[a[k]] == 1) ++distinct;
        
        cout << ' ' << distinct;
    }
}

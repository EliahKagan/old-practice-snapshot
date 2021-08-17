// your task is tocomplete this function
// function should return an pointer to output array int*
// of size k*k
int *mergeKArrays(int arr[][N], const int k) // naive way (small k constraint)
{
    // naive technique (since k is constrained to be small)
    const auto ret = new int[k * k] {};
    auto p = ret;
    
    for (auto j = 0; j != k; ++j)
        for (auto i = 0; i != k; ++i) *p++ = arr[i][j];
    
    sort(ret, p);
    return ret;
}

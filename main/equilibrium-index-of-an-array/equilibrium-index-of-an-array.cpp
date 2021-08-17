/* You are required to complete this method*/
int findEquilibrium(int* const a, const int n)
{
    constexpr auto no_equilibrium = -1;
    
    auto right = 0;
    for (auto i = 0; i != n; ++i) right += a[i];
    
    for (auto left = 0, i = 0; i != n; left += a[i++])
        if (left == (right -= a[i])) return i;
    
    return no_equilibrium;
}

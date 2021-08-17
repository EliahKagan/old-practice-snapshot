/*Complete the function given below*/
int num(int* const a, const int n, const int k)
{
    constexpr auto base = 10;
    
    auto count = 0;
    
    if (k >= base) {
        for (auto i = 0; i < n; ++i)
            if (a[i] == k) ++count;
    } else {
        for (auto i = 0; i < n; ++i) {
            auto x = a[i];
            do
                if (x % base == k) ++count;
            while ((x /= base) > 0);
        }
    }
    
    return count;
}
